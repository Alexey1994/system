function DoublyLinkedList* create_doubly_linked_list(procedure (*destroy_data)(Byte *data))
{
    DoublyLinkedList *list = new(DoublyLinkedList);

    list->begin         =  0;
    list->length        =  0;
    list->destroy_data  =  destroy_data;

    return list;
}


procedure destroy_doubly_linked_list(DoublyLinkedList *list)
{
    DoublyLinkedListNode *node;
    DoublyLinkedListNode *previouse_node;

    node = list->begin;

    while(node)
    {
        if(list->destroy_data)
            list->destroy_data(node->data);

        previouse_node = node;
        node = node->next;
        free_memory(previouse_node);
    }

    free_memory(list);
}


function DoublyLinkedListNode* create_doubly_linked_list_node(DoublyLinkedListNode *previouse, DoublyLinkedListNode *next, Byte *data)
{
    DoublyLinkedListNode *node = new(DoublyLinkedListNode);

    node->previouse = previouse;
    node->next      = next;
    node->data      = data;

    if(previouse)
        previouse->next = node;

    if(next)
        next->previouse = node;

    return node;
}


procedure destroy_doubly_linked_list_node(DoublyLinkedListNode *node)
{
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *previouse;

    next = node->next;
    previouse = node->previouse;

    if(next)
        next->previouse = node->previouse;

    if(previouse)
        previouse->next = node->next;

    free_memory(node);
}


procedure add_in_doubly_linked_list(DoublyLinkedList *list, N_32 position, Byte *data)
{
    DoublyLinkedListNode *next_node;
    DoublyLinkedListNode *node;
    DoublyLinkedListNode *new_node;

    node = list->begin;

    if(!position)
    {
        new_node = new(DoublyLinkedListNode);
        new_node->next       =  list->begin;
        new_node->previouse  =  0;
        new_node->data       =  data;

        list->begin  = new_node;
    }
    else
    {
        --position;

        while(node && position)
        {
            node = node->next;
            --position;
        }

        if(!node)
            return;

        new_node = new(DoublyLinkedListNode);
        new_node->next       =  node->next;
        new_node->previouse  =  node;
        new_node->data       =  data;

        next_node = new_node->next;

        if(next_node)
            next_node->previouse = new_node;

        node->next = new_node;
    }

    ++list->length;
}


procedure delete_from_doubly_linked_list(DoublyLinkedList *list, N_32 position)
{
    DoublyLinkedListNode *node;
    DoublyLinkedListNode *delete_node;

    delete_node = list->begin;

    if(!position)
    {
        if(!delete_node)
            return;

        node = delete_node->next;
        node->previouse = 0;
        list->begin = node;
    }
    else
    {
        while(delete_node && position)
        {
            delete_node = delete_node->next;
            position--;
        }

        if(!delete_node)
            return;

        node = delete_node->previouse;
        node->next = delete_node->next;

        node = delete_node->next;

        if(node)
            node->previouse = delete_node->previouse;
    }

    if(list->destroy_data)
        list->destroy_data(delete_node->data);

    free_memory(delete_node);
    list->length--;
}


function DoublyLinkedListNode* get_doubly_linked_list_node(DoublyLinkedList *list, N_32 position)
{
    DoublyLinkedListNode *node;

    node = list->begin;

    while(node && position)
    {
        node = node->next;
        position--;
    }

    return node;
}


procedure print_doubly_linked_list(DoublyLinkedList *list, procedure (*print_data)(Byte *data))
{
    DoublyLinkedListNode *node;

    for(node = list->begin; node; node = node->next)
        print_data(node->data);
}
