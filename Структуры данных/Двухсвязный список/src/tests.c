#include <stdio.h>
#include "doubly linked list.h"


int main()
{
    DoublyLinkedList *list = create_doubly_linked_list(0);

    add_in_doubly_linked_list(list, 0, "A"); //A
    add_in_doubly_linked_list(list, 0, "B"); //BA
    add_in_doubly_linked_list(list, 0, "C"); //CBA
    add_in_doubly_linked_list(list, 1, "D"); //CDBA
    add_in_doubly_linked_list(list, 4, "E"); //CDBAE
    add_in_doubly_linked_list(list, 5, "F"); //CDBAEF

    delete_from_doubly_linked_list(list, 0); //DBAEF
    delete_from_doubly_linked_list(list, 1); //DAEF
    delete_from_doubly_linked_list(list, 3); //DAE
    delete_from_doubly_linked_list(list, 1); //DE
    delete_from_doubly_linked_list(list, 0); //E

    print_doubly_linked_list(list, printf);

    printf("\n%d", list->length); //1

    return 0;
}
