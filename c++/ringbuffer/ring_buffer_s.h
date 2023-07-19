/*
 * ring_buffer_s.h
 */

#pragma once
#include <mutex>
#include "spin_mutex.h"

/**
 * \brief 线程安全的环形缓冲区
 */
class ring_buffer_s
{
public:
    explicit ring_buffer_s(const size_t capacity);
    ring_buffer_s(ring_buffer_s &&) = delete;
    ring_buffer_s &operator=(ring_buffer_s &&other) = delete;

    ring_buffer_s(const ring_buffer_s &) = delete;
    ring_buffer_s &operator=(const ring_buffer_s &other) = delete;

    ~ring_buffer_s();

    /**
     * \brief 获取缓冲区已用大小
     */
    size_t size() const;

    /**
     * \brief 获取缓冲区容量
     */
    size_t capacity() const;

    /**
     * \brief 写入数据
     * \param data 要写入的数据
     * \param bytes 要写入的数据的大小
     * \return 最终写入的数据的大小
     */
    size_t write(const void *data, const size_t bytes);

    /**
     * \brief 读取数据
     * \param data 用来存放读取数据的buffer
     * \param bytes 要读取的数据大小
     * \return 最终获取到的数据的大小
     */
    size_t read(void *data, const size_t bytes);

private:
    size_t front_, rear_, size_, capacity_;
    uint8_t *data_;
    mutable spin_mutex mut_;
    mutable std::mutex mut_read_;
    mutable std::mutex mut_write_;
};
