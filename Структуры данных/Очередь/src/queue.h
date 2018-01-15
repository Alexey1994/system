#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED


#include <extends/extends.h>


typedef struct
{
    int    begin_index;

    Byte **data;
    int    length;
    int    buffer_length;
    int    reserve;
    void (*destroy_node)(Byte *node);
}
Queue;

Queue* create_queue   (int reserve, void (*destroy_node)(Byte *node));
void   destroy_queue  (Queue *queue);

void   add_in_queue   (Queue *queue, Byte *data);
Byte*  pop_from_queue (Queue *queue);


#include "queue.c"

#endif // QUEUE_H_INCLUDED
