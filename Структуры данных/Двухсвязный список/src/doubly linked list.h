#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED


#include <extends/extends.h>


typedef struct
{
    struct DoublyLinkedListNode  *next;
    struct DoublyLinkedListNode  *previouse;
    Byte                         *data;
}
DoublyLinkedListNode;


typedef struct
{
    DoublyLinkedListNode *begin;
    N_32                  length;
    procedure            (*destroy_data)(Byte *data);
}
DoublyLinkedList;


function DoublyLinkedList*     create_doubly_linked_list       (procedure (*destroy_data)(Byte *data));
procedure                      destroy_doubly_linked_list      (DoublyLinkedList *list);

function DoublyLinkedListNode* create_doubly_linked_list_node  (DoublyLinkedListNode *previouse, DoublyLinkedListNode *next, Byte *data);
procedure                      destroy_doubly_linked_list_node (DoublyLinkedListNode *node);

procedure                      add_in_doubly_linked_list       (DoublyLinkedList *list, N_32 position, Byte *data);
procedure                      delete_from_doubly_linked_list  (DoublyLinkedList *list, N_32 position);
function DoublyLinkedListNode* get_doubly_linked_list_node     (DoublyLinkedList *list, N_32 position);

procedure                      print_doubly_linked_list        (DoublyLinkedList *list, procedure (*print_data)(Byte *data));


#include "doubly linked list.c"

#endif // DOUBLY_LINKED_LIST_H_INCLUDED
