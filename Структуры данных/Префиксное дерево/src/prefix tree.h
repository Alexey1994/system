#ifndef PREFIX_TREE_H_INCLUDED
#define PREFIX_TREE_H_INCLUDED


#include <data structures/string/string.h>
#include <extends/extends.h>


typedef struct
{
    Byte               *data;
    struct Prefix_Tree *prefixes[2];
}
Prefix_Tree;


function  Prefix_Tree* create_prefix_tree  ();
procedure              destroy_prefix_tree (Prefix_Tree *tree, procedure (*destroy_data)(Byte *data));

procedure              add_in_prefix_tree  (Prefix_Tree *tree, Byte *key, Byte *value);
function  Byte*        find_in_prefix_tree (Prefix_Tree *tree, Byte *key);
procedure              crawl_prefix_tree   (Prefix_Tree *tree, procedure (*element)(Byte *element, String *key, Byte *arguments), Byte *arguments);


#include "prefix tree.c"

#endif // PREFIX_TREE_H_INCLUDED
