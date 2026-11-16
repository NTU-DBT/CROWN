#!/usr/bin/env bash
set -euo pipefail
cd /home/userroot/Codex/CROWN
c++ -std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party -MMD -MF /tmp/crown-c01-scalar-production-strict-attempt-1/scalar_statistics_test.d -c docs/verification/c01-statistics-scalar-proposal/scalar_statistics_test.cpp -o /tmp/crown-c01-scalar-production-strict-attempt-1/scalar_statistics_test.o 
