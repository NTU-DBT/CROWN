#include "crown/annotations/policy.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace crown;
using namespace crown::annotations;
namespace {
template<class T, class P> T calculate(const std::string& operation, const P& policy, T a, T b, T c) {
  if (operation == "add") return policy.add(a, b);
  if (operation == "multiply") return policy.multiply(a, b);
  if (operation == "remove") return policy.remove(a, b);
  if (operation == "replace") return policy.replace(a, b, c);
  throw std::runtime_error("invalid oracle operation");
}
void execute(std::istringstream& input) {
  char domain = 0;
  std::string operation;
  input >> domain >> operation;
  if (domain == 'u') {
    std::uint64_t limit = 0, a = 0, b = 0, c = 0;
    input >> limit >> a >> b >> c;
    const auto result = calculate(operation, MultiplicityPolicy(limit), Multiplicity{a}, Multiplicity{b}, Multiplicity{c});
    std::cout << "ok " << result.value << '\n';
  } else if (domain == 'i') {
    std::int64_t a = 0, b = 0, c = 0;
    input >> a;
    if (operation == "scale") {
      std::uint64_t weight = 0;
      input >> weight;
      const auto result = IntegerPolicy::multiply(IntegerPayload{a}, Multiplicity{weight});
      std::cout << "ok " << result.value << '\n';
    } else {
      input >> b >> c;
      const auto result = calculate(operation, IntegerPolicy{}, IntegerPayload{a}, IntegerPayload{b}, IntegerPayload{c});
      std::cout << "ok " << result.value << '\n';
    }
  } else if (domain == 'd') {
    DecimalSpec spec{};
    std::string a, b, c;
    input >> spec.precision >> spec.scale >> a >> b >> c;
    const DecimalPolicy policy(spec);
    const auto left = DecimalPayload{Decimal::parse(a)};
    if (operation == "scale") {
      const auto result = policy.multiply(left, Multiplicity{std::stoull(b)});
      std::cout << "ok " << result.value.to_string() << '\n';
    } else {
      const auto result = calculate(operation, policy, left, DecimalPayload{Decimal::parse(b)}, DecimalPayload{Decimal::parse(c)});
      std::cout << "ok " << result.value.to_string() << '\n';
    }
  } else throw std::runtime_error("invalid oracle domain");
  if (input.fail()) throw std::runtime_error("malformed oracle input");
}
}  // namespace
int main() {
  for (std::string line; std::getline(std::cin, line);) {
    try { std::istringstream input(line); execute(input); }
    catch (const Error& error) { std::cout << "error " << error.code() << '\n'; }
  }
}
