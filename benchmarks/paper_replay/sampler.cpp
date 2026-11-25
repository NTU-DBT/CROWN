// Minimal in-process SIGPROF sampling profiler (perf/ptrace unavailable here).
// Enabled when CROWN_PROF=<output path>. Walks frame pointers (binary built with
// -fno-omit-frame-pointer, -no-pie). Writes one line of hex return addresses per
// sample at normal process exit or on SIGTERM.
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <ucontext.h>
#include <unistd.h>

namespace {
constexpr int kDepth = 48;
constexpr std::size_t kMax = 400000;
std::uintptr_t* g_buf = nullptr;
volatile std::size_t g_count = 0;
const char* g_path = nullptr;
std::uintptr_t g_stack_lo = 0, g_stack_hi = 0;

void on_prof(int, siginfo_t*, void* raw) {
  if (g_count >= kMax) return;
  auto* uc = static_cast<ucontext_t*>(raw);
  std::uintptr_t* out = g_buf + g_count * kDepth;
  int n = 0;
  out[n++] = static_cast<std::uintptr_t>(uc->uc_mcontext.gregs[REG_RIP]);
  auto fp = static_cast<std::uintptr_t>(uc->uc_mcontext.gregs[REG_RBP]);
  auto sp = static_cast<std::uintptr_t>(uc->uc_mcontext.gregs[REG_RSP]);
  while (n < kDepth && fp >= sp && fp < sp + (64u << 20) && (fp & 7) == 0) {
    auto* frame = reinterpret_cast<std::uintptr_t*>(fp);
    const auto ret = frame[1];
    if (!ret) break;
    out[n++] = ret;
    const auto next = frame[0];
    if (next <= fp) break;
    fp = next;
  }
  for (; n < kDepth; ++n) out[n] = 0;
  g_count = g_count + 1;
}

void dump() {
  if (!g_path || !g_buf) return;
  struct itimerval off{};
  setitimer(ITIMER_PROF, &off, nullptr);
  FILE* f = std::fopen(g_path, "w");
  if (!f) return;
  for (std::size_t i = 0; i < g_count; ++i) {
    for (int d = 0; d < kDepth; ++d) {
      const auto a = g_buf[i * kDepth + d];
      if (!a) break;
      std::fprintf(f, "%lx ", static_cast<unsigned long>(a));
    }
    std::fputc('\n', f);
  }
  std::fclose(f);
  g_path = nullptr;
}

void on_term(int) { dump(); _exit(143); }

struct Init {
  Init() {
    g_path = std::getenv("CROWN_PROF");
    if (!g_path) return;
    g_buf = static_cast<std::uintptr_t*>(std::calloc(kMax * kDepth, sizeof(std::uintptr_t)));
    struct sigaction sa{};
    sa.sa_sigaction = on_prof;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGPROF, &sa, nullptr);
    std::signal(SIGTERM, on_term);
    std::signal(SIGINT, on_term);
    const char* hz = std::getenv("CROWN_PROF_HZ");
    const long rate = hz ? std::atol(hz) : 997;
    struct itimerval it{};
    it.it_interval.tv_usec = 1000000 / rate;
    it.it_value = it.it_interval;
    setitimer(ITIMER_PROF, &it, nullptr);
    std::atexit(dump);
  }
} g_init;
}  // namespace
