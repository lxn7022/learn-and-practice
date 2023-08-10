#include <iostream>
#include "ring_buffer_s.h"

struct Element
{
    /* data */
    uint8_t data[16];
};

int main()
{
    unsigned long capacity = 1024;
    ring_buffer_s ringbuf(capacity);
    Element elem;
    ringbuf.write(&elem, sizeof(elem));
    for (int i = 0; i < 100;i++){
        auto write_len = ringbuf.write(&elem, sizeof(elem));
        if (write_len == 0){
            std::cout<<"ringbuf.elems:"<<i<<std::endl;
            break;
        }
    }
    std::cout << "ringbuf.size:"<<ringbuf.size() << std::endl;
    for (int i = 0; i < 10;i++){
        ringbuf.read(&elem, sizeof(elem));
    }
    std::cout << "ringbuf.size:"<<ringbuf.size() << std::endl;

    return 0;
}