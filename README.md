# datalink

datalink is a C++20 library implementing a time-division multiple access
(TDMA) protocol for mesh networks. Nodes share a single radio channel by
agreeing on a repeating frame divided into fixed slots, and each node transmits
only during the slots assigned to it. This removes contention and collisions
from the medium-access layer, which makes latency and throughput predictable
enough to be reasoned about in advance rather than measured after the fact.
The library covers slot scheduling, frame synchronisation, neighbour discovery
and multi-hop forwarding, and leaves the radio itself to the integrator.

## Features

- Deterministic TDMA scheduling with a fixed frame layout and per-node slot
  assignment.
- Multi-hop mesh forwarding, so nodes outside direct radio range remain
  reachable.
- A portable protocol core with no operating-system dependencies, suitable for
  bare-metal targets as well as hosted builds.
- An optional POSIX transport layer for running the protocol over host sockets
  during development and testing.
- Static libraries with modern target-based CMake, usable through
  `add_subdirectory` or `FetchContent`.

## Building

Requirements: CMake 3.20 or newer and a C++20 compiler (GCC 11+, Clang 14+ or
Apple Clang 14+).

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Debug builds are instrumented with AddressSanitizer and
UndefinedBehaviorSanitizer. The instrumentation is skipped automatically when
cross-compiling, where the sanitizer runtimes are unavailable. For an
uninstrumented build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Tests are built by default when the project is the top-level build and can be
disabled with `-DDATALINK_BUILD_TESTS=OFF`.

## Running

The `node` application links both libraries and reports their versions:

```sh
./build/apps/node/node
```

```
datalink 0.1.0
net 0.1.0
```

## Testing

The suite uses GoogleTest, fetched at configure time and pinned to a release
tag.

```sh
ctest --test-dir build --output-on-failure
```

## Project Structure

```
CMakeLists.txt              Top-level build, sanitizer configuration
cmake/CompilerWarnings.cmake  Shared warning set as an INTERFACE target
lib/datalink/               Portable protocol core; no OS dependencies
lib/net/                    Host-only POSIX transport
apps/node/                  Example application linking both libraries
tests/                      GoogleTest suite
.github/workflows/ci.yml    Ubuntu build and test workflow
```

`datalink` and `net` are independent: the protocol core does not link the
transport, and the transport does not link the core. Only an application joins
them. This keeps the core buildable for targets that have no sockets, no
threads and no operating system.

## License

Released under the MIT License. See [LICENSE](LICENSE).
