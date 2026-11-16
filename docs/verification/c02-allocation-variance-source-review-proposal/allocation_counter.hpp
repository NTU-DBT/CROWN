#pragma once
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>

namespace allocation_probe {
struct Sample { std::size_t calls=0, frees=0, bytes=0, aligned=0, overflow=0; };
struct Event { std::size_t bytes=0; bool aligned=false; };
inline thread_local bool measuring=false;
inline thread_local Sample sample;
inline thread_local std::array<Event,32768> events;

[[noreturn]] inline void fail(const char* message) noexcept {
  measuring=false; std::fputs(message,stderr); std::fputc('\n',stderr); std::exit(2);
}
inline void check(bool condition,const char* message) { if(!condition)fail(message); }
inline void begin() {
  check(!measuring,"nested allocation interval"); sample={}; measuring=true;
}
inline Sample end() noexcept { measuring=false; return sample; }
inline void allocated(std::size_t bytes,bool aligned) noexcept {
  if(!measuring)return;
  if(sample.calls<events.size())events[sample.calls]={bytes,aligned};else ++sample.overflow;
  ++sample.calls;sample.bytes+=bytes;if(aligned)++sample.aligned;
}
[[gnu::noinline]] inline void* allocate(std::size_t bytes) {
  if(void* pointer=std::malloc(bytes?bytes:1)){allocated(bytes,false);return pointer;}
  throw std::bad_alloc{};
}
[[gnu::noinline]] inline void* allocate_aligned(std::size_t bytes,std::size_t alignment) {
  void* pointer=nullptr;
  if(::posix_memalign(&pointer,alignment,bytes?bytes:1)==0){allocated(bytes,true);return pointer;}
  throw std::bad_alloc{};
}
[[gnu::noinline]] inline void release(void* pointer) noexcept {
  if(pointer && measuring)++sample.frees;
  std::free(pointer);
}
inline void emit(const char* group,const char* form,const Sample& value) {
  check(!measuring,"output inside allocation interval");
  check(value.overflow==0,"fixed allocation-event capacity exceeded");
  struct Bucket {std::size_t bytes=0,count=0,aligned=0;};
  std::array<Bucket,1024> buckets{};std::size_t used=0;
  for(std::size_t i=0;i<value.calls;++i){
    std::size_t b=0;while(b<used && buckets[b].bytes!=events[i].bytes)++b;
    if(b==used){check(used<buckets.size(),"fixed histogram capacity exceeded");buckets[used++].bytes=events[i].bytes;}
    ++buckets[b].count;if(events[i].aligned)++buckets[b].aligned;
  }
  std::printf("allocation-probe group=%s form=%s calls=%zu frees=%zu requested_bytes=%zu aligned_calls=%zu sizes=",group,form,value.calls,value.frees,value.bytes,value.aligned);
  for(std::size_t i=0;i<used;++i)std::printf("%s%zu:%zu:%zu",i?",":"",buckets[i].bytes,buckets[i].count,buckets[i].aligned);
  std::fputc('\n',stdout);
}
} // namespace allocation_probe

[[gnu::noinline]] void* operator new(std::size_t n){return allocation_probe::allocate(n);}
[[gnu::noinline]] void* operator new[](std::size_t n){return allocation_probe::allocate(n);}
[[gnu::noinline]] void* operator new(std::size_t n,const std::nothrow_t&) noexcept{try{return allocation_probe::allocate(n);}catch(...){return nullptr;}}
[[gnu::noinline]] void* operator new[](std::size_t n,const std::nothrow_t&) noexcept{try{return allocation_probe::allocate(n);}catch(...){return nullptr;}}
[[gnu::noinline]] void* operator new(std::size_t n,std::align_val_t a){return allocation_probe::allocate_aligned(n,static_cast<std::size_t>(a));}
[[gnu::noinline]] void* operator new[](std::size_t n,std::align_val_t a){return allocation_probe::allocate_aligned(n,static_cast<std::size_t>(a));}
[[gnu::noinline]] void* operator new(std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept{try{return allocation_probe::allocate_aligned(n,static_cast<std::size_t>(a));}catch(...){return nullptr;}}
[[gnu::noinline]] void* operator new[](std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept{try{return allocation_probe::allocate_aligned(n,static_cast<std::size_t>(a));}catch(...){return nullptr;}}
[[gnu::noinline]] void operator delete(void* p) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete(void* p,std::size_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p,std::size_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete(void* p,const std::nothrow_t&) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p,const std::nothrow_t&) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete(void* p,std::align_val_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p,std::align_val_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete(void* p,std::size_t,std::align_val_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p,std::size_t,std::align_val_t) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete(void* p,std::align_val_t,const std::nothrow_t&) noexcept{allocation_probe::release(p);}
[[gnu::noinline]] void operator delete[](void* p,std::align_val_t,const std::nothrow_t&) noexcept{allocation_probe::release(p);}
