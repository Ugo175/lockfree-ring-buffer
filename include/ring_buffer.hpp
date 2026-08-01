#pragma once
#include <atomic>
#include <cstddef>

template <typename T, size_t Capacity>
class RingBuffer {
public:
    RingBuffer() = default;

    bool push(const T& item) {
        // TODO: atomic single-producer push
        return false;
    }

    bool pop(T& item) {
        // TODO: atomic single-consumer pop
        return false;
    }

private:
    T buffer_[Capacity];
    std::atomic<size_t> head_{0};
    std::atomic<size_t> tail_{0};
};
