#include "prefix tree.h"


procedure print_prefeix_tree_node(Byte *element, String *key)
{
    printf("%s\n", key->buffer.data);
}


function N_32 main()
{
    Prefix_Tree *tree;

    tree = create_prefix_tree();

    add_in_prefix_tree(tree, "Alexey", 1);
    add_in_prefix_tree(tree, "Borisenko", 123);
    add_in_prefix_tree(tree, "Boriseko", 123);
    //add_data_in_prefix_tree(tree, "Borisenko", 2);

    //printf("%d\n", find_in_prefix_tree(tree, "Alexey"));
    //printf("%d\n", find_data_in_prefix_tree(tree, "Borisenko"));

    crawl_prefix_tree(tree, &print_prefeix_tree_node, 0);

    //destroy_prefix_tree(tree, 0);

    return 0;
}
