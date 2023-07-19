/*
 * ring_buffer_s.cpp
 */

#include <algorithm>
#include <string.h>
#include <algorithm>
#include "ring_buffer_s.h"

inline ring_buffer_s::ring_buffer_s(const size_t capacity)
    : front_(0), rear_(0), size_(0), capacity_(capacity)
{
    data_ = new uint8_t[capacity];
}

inline ring_buffer_s::~ring_buffer_s()
{
    delete[] data_;
}

inline size_t ring_buffer_s::size() const
{
    return size_;
}

inline size_t ring_buffer_s::capacity() const
{
    return capacity_;
}

inline size_t ring_buffer_s::write(const void *data, const size_t bytes)
{
    if (bytes == 0)
        return 0;

    // 通过互斥量保证任意时刻，至多只有一个线程在写数据。
    std::lock_guard<std::mutex> lk_write(mut_write_);
    const auto capacity = capacity_;
    const auto bytes_to_write = std::min(bytes, capacity - size_);

    if (bytes_to_write == 0)
        return 0;

    // 一次性写入
    if (bytes_to_write <= capacity - rear_)
    {
        memcpy(data_ + rear_, data, bytes_to_write);
        rear_ += bytes_to_write;
        if (rear_ == capacity)
            rear_ = 0;
    }
    // 分两步进行
    else
    {
        const auto size_1 = capacity - rear_;
        memcpy(data_ + rear_, data, size_1);

        const auto size_2 = bytes_to_write - size_1;
        memcpy(data_, static_cast<const uint8_t *>(data) + size_1, size_2);
        rear_ = size_2;
    }

    // 通过自旋锁保证任意时刻，至多只有一个线程在改变 size_ .
    std::lock_guard<spin_mutex> lk(mut_);
    size_ += bytes_to_write;
    return bytes_to_write;
}

inline size_t ring_buffer_s::read(void *data, const size_t bytes)
{
    if (bytes == 0)
        return 0;

    // 通过互斥量保证任意时刻，至多只有一个线程在读数据。
    std::lock_guard<std::mutex> lk_read(mut_read_);

    const auto capacity = capacity_;
    const auto bytes_to_read = std::min(bytes, size_);

    if (bytes_to_read == 0)
        return 0;

    // 一次性读取
    if (bytes_to_read <= capacity - front_)
    {
        memcpy(data, data_ + front_, bytes_to_read);
        front_ += bytes_to_read;
        if (front_ == capacity)
            front_ = 0;
    }
    // 分两步进行
    else
    {
        const auto size_1 = capacity - front_;
        memcpy(data, data_ + front_, size_1);
        const auto size_2 = bytes_to_read - size_1;
        memcpy(static_cast<uint8_t *>(data) + size_1, data_, size_2);
        front_ = size_2;
    }

    // 通过自旋锁保证任意时刻，至多只有一个线程在改变 size_ .
    std::lock_guard<spin_mutex> lk(mut_);
    size_ -= bytes_to_read;
    return bytes_to_read;
}
