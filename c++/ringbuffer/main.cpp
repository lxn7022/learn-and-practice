#include "ring_buffer_s.h"

struct Element
{
    /* data */
    uint8_t data[16];
};

int main()
{

    ring_buffer_s ringbuf(1024);
    Element elem;
    ringbuf.write(&elem, (size_t)16);
    return 0;
}