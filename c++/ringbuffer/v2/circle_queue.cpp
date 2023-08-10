#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class CircleQueue
{
private:
    //队头指针，队尾指针
    size_t d_rear;
    size_t d_front;

    size_t d_size;
    size_t d_capacity;
    T * d_arr;

public:
    //默认构造函数
    CircleQueue();

    //自定义构造函数
    CircleQueue(size_t);

    //析构函数
    ~CircleQueue();

    //拷贝构造函数
    CircleQueue(const CircleQueue &)=delete;

    //移动构造函数
    CircleQueue(CircleQueue &&)=delete;

    //踢队操作
    T deque();

    //入队操作
    void enque(const T &);

    //查看队列首端元素
    T front() const;

    //查看队列末端元素
    T rear() const;

    //队列是否非空
    bool is_empty() const;

    //队列是否已满
    bool is_full() const;

    //返回队列已有数量
    const size_t size() { return d_size; }
    //返回队列容量
    const size_t capacity() { return d_capacity; }

    //缓存
    const T *buffer();

    //打印队列
    template <class R>
    friend std::ostream &operator<<(std::ostream &, CircleQueue<R> &);
};

const size_t DEFAULT_SIZE = 20;
template <class T>
CircleQueue<T>::CircleQueue()
{
    d_front = d_rear = -1;
    d_capacity = DEFAULT_SIZE;
    d_size = 0;
    d_arr = new T[d_capacity];
}

//构造函数
template <class T>
CircleQueue<T>::CircleQueue(size_t size)
{
    d_size = 0;
    d_capacity = size;
    d_front = d_rear = -1;
    d_arr = new T[d_capacity];
}

//析构函数
template <class T>
CircleQueue<T>::~CircleQueue()
{
    delete[] d_arr;
}

//检查环形队列是否为满载
template <class T>
bool CircleQueue<T>::is_full() const
{
    return (d_rear == d_capacity - 1 && d_front == 0) || (d_rear == d_front - 1);
}

//判断环形队列是否为空
template <class T>
bool CircleQueue<T>::is_empty() const
{
    return d_front == -1 || d_rear == -1;
}

//入队操作
template <class T>
void CircleQueue<T>::enque(const T &value)
{
    if (is_full())
    {
        std::cout << "环形队列已满" << std::endl;
        return;
    }
    // 初始为空
    if (d_front == -1)
    {
        d_rear = d_front = 0;
    }
    // rear回卷
    else if (d_rear == d_capacity - 1 && d_front != 0)
    {
        d_rear = 0;
    }
    else
    {
        d_rear++;
    }
    d_arr[d_rear] = value;
    d_size++;
}

//踢队操作
template <class T>
T CircleQueue<T>::deque()
{
    if (is_empty())
    {
        std::cout << "环形队列为空!!" << std::endl;
        return T();
    }

    T data = d_arr[d_front];
    // 最后一个元素出队列
    if (d_front == d_rear)
    {
        d_front = -1;
        d_rear = -1;
    }
    // 回卷
    else if (d_front == d_size - 1)
    {
        d_front = 0;
    }
    else
    {
        d_front++;
    }
    d_size--;
    return data;
}

//获取队头部元素
template <class T>
T CircleQueue<T>::front() const
{
    return d_arr[d_front];
}

//获取队尾元素
template <class T>
T CircleQueue<T>::rear() const
{
    return d_arr[d_rear];
}

//获取队列内部的缓存指针
template <class T>
const T *CircleQueue<T>::buffer()
{
    return d_arr;
}

//遍历
template <class R>
std::ostream &operator<<(std::ostream &os, CircleQueue<R> &q)
{

    const R *buf = q.d_arr;

    if (q.is_empty())
    {
        os << "CircleQueue为空" << std::endl;
        return os;
    }
    cout << "CircleQueue(";
    // 无回卷，一次循环
    if (q.d_rear >= q.d_front)
    {
        for (auto i = q.d_front; i <= q.d_rear; i++)
        {
            os << buf[i] << ",";
        }
    }
    else
    { // 有回卷，两次循环
        for (auto i = q.d_front; i < q.d_size; i++)
        {
            os << buf[i] << ",";
        }

        for (auto i = 0; i <= q.d_rear; i++)
        {
            os << buf[i] << ",";
        }
    }
    os << ")" ;
    return os;
}

class TestCircleQueue{
public:
    template <class T>
    void queue_info(CircleQueue<T> &que){

        cout << "size:" << que.size() <<endl;
        cout << "capacity:" << que.capacity() << endl;
    }

    void enque_and_deque()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        CircleQueue<int> que;
        for (auto i = 100; i < 150; i++){
            que.enque(i);
        }
        cout << que << endl;

        cout << "deque:" << que.deque() << endl;
        queue_info(que);
    }
};


int main()
{
    TestCircleQueue test;
    test.enque_and_deque();

}