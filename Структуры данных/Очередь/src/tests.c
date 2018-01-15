#include <stdio.h>
#include "queue.h"


void print_queue(Queue *queue)
{
    int i;
    int j;

    printf("begin: %d, length: %d    ", queue->begin_index, queue->length);

    for(i=queue->begin_index, j=0; i<queue->begin_index + queue->length && i<queue->buffer_length; ++i, ++j)
        printf("%s, ", queue->data[i]);

    for(i=0; j<queue->length; ++j, ++i)
        printf("%s, ", queue->data[i]);
}


int main()
{
    Queue *queue = create_queue(2, 0);

    add_in_queue(queue, "1");  printf("push 1    ");     print_queue(queue);
    add_in_queue(queue, "2");  printf("\npush 2    ");   print_queue(queue);
    pop_from_queue(queue);     printf("\npop       ");   print_queue(queue);
    add_in_queue(queue, "3");  printf("\npush 3    ");   print_queue(queue);
    add_in_queue(queue, "4");  printf("\npush 4    ");   print_queue(queue);
    pop_from_queue(queue);     printf("\npop       ");   print_queue(queue);
    pop_from_queue(queue);     printf("\npop       ");   print_queue(queue);
    //pop_from_queue(queue);     printf("\npop       ");   print_queue(queue);

    int i;

    for(i=0; i<1000000; ++i)
        add_in_queue(queue, "4");

    destroy_queue(queue);

    return 0;
}
