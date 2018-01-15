#include "queue.h"


Queue* create_queue(int reserve, void (*destroy_node)(Byte *node))
{
    Queue *queue = new(Queue);

    queue->begin_index   = 0;
    queue->length        = 0;
    queue->reserve       = reserve;
    queue->buffer_length = reserve;
    queue->destroy_node  = destroy_node;
    queue->data          = new_array(Byte*, reserve);

    return queue;
}


void destroy_queue(Queue *queue)
{
    int i;

    for(i=queue->begin_index; i<queue->buffer_length; ++i)
        if(queue->destroy_node)
            queue->destroy_node(queue->data[i]);

    for(i=0; i<queue->begin_index; ++i)
        if(queue->destroy_node)
            queue->destroy_node(queue->data[i]);

    free_memory(queue->data);
    free_memory(queue);
}


static void reallocate_queue(Queue *queue)
{
    Byte **new_data;
    int    new_length;
    int    i;
    int    j;

    //new_length = queue->buffer_length + queue->reserve;
    new_length = queue->buffer_length * queue->reserve;
    new_data = new_array(Byte*, new_length);

    for(i=queue->begin_index, j=0; i<queue->buffer_length; ++i, ++j)
        new_data[j] = queue->data[i];

    for(i=0; i<queue->begin_index; ++i, ++j)
        new_data[j] = queue->data[i];

    queue->begin_index = 0;

    free(queue->data);
    queue->data          = new_data;
    queue->buffer_length = new_length;
}


void add_in_queue(Queue *queue, Byte *data)
{
    if(queue->length == queue->buffer_length)
        reallocate_queue(queue);

    if(queue->begin_index + queue->length < queue->buffer_length)
        queue->data[ queue->begin_index + queue->length ] = data;
    else
        queue->data[ queue->begin_index - (queue->buffer_length - queue->length) ] = data;

    ++queue->length;
}


Byte* pop_from_queue(Queue *queue)
{
    ++queue->begin_index;

    if(queue->begin_index >= queue->buffer_length)
        queue->begin_index = 0;

    --queue->length;

    return queue->data[queue->begin_index-1];
}
