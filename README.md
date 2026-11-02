# Lock-Free Ring Buffer (User-Space Packet Processor)

A single-producer, single-consumer (SPSC) ring buffer in C++, built as a
step toward a lock-free version for low-latency, high-throughput packet
processing in user space.

## Status

In progress (currently implementing a correct, mutex-based version as a
baseline before replacing locks with atomics).

- [x] Project scaffolding (CMake, build pipeline)
- [x] Mutex + condition variable based ring buffer
- [ ] Lock-free version using `std::atomic` with acquire/release ordering
- [ ] Packet ingestion (libpcap / raw sockets)
- [ ] Benchmarks: lock-free vs. mutex-based throughput and latency

## Why this project

Most "concurrent queue" tutorials stop at using a mutex. This project goes
further: replacing the lock with atomic operations and explicit memory
ordering, while staying correct — and measuring whether that effort
actually pays off in throughput and latency compared to the naive
lock-based version.

## Build

Requires CMake 3.16+ and a C++20 compiler.

```bash
cmake -B build
cmake --build build
```

Run the placeholder executables:

```bash
./build/packet_processor
./build/test_ring_buffer
./build/bench_ring_buffer
```

## Design

_(Filled in as the implementation progresses — see also `NOTES.md` for
day-to-day design decisions.)_

### Ring buffer

- Fixed-capacity circular buffer, single producer / single consumer.
- Full/empty disambiguation via the "reserve one slot" technique: the
  buffer is considered full when advancing `head` by one would collide
  with `tail`, so only `Capacity - 1` slots are ever used at once.

### Concurrency strategy

- **Current**: `std::mutex` + two `std::condition_variable`s (one for
  "not full," one for "not empty") to avoid unnecessary wakeups.
- **Planned**: replace the mutex with `std::atomic<size_t>` head/tail
  indices, using `memory_order_release` on the writer side and
  `memory_order_acquire` on the reader side.

## Benchmarks

_(To be added once the lock-free version is implemented — throughput and
latency compared against the mutex-based baseline.)_

## License

MIT
