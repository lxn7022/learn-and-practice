/*
 * spin_mutex.h
 */

#pragma once
#include <atomic>

class spin_mutex
{
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
    spin_mutex() = default;
    ~spin_mutex() = default;
    spin_mutex(const spin_mutex &) = delete;
    spin_mutex &operator=(const spin_mutex &) = delete;
    spin_mutex(spin_mutex &&) = delete;
    spin_mutex &operator=(spin_mutex &&) = delete;

    void lock()
    {
        while (flag_.test_and_set(std::memory_order_acquire))
            ;
    }
    void unlock()
    {
        flag_.clear(std::memory_order_release);
    }
};
