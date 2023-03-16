#ifndef STRUCT_LIST_H
#define STRUCT_LIST_H

typedef int node_val_type;
static const node_val_type POISON = 0xDED;

typedef struct node
{
    size_t next = 0;          //
    size_t prev = 0;          //
    node_val_type value  = 0; // 

}mode;

typedef struct list
{
    node*  nodes_arr        = nullptr; //

    size_t head_node        = 0;       //
    size_t tail_node        = 0;
    size_t free_node        = 0;       //

    size_t cur_num_of_nodes = 0;       //
    size_t max_num_of_nodes = 0;       // 

    size_t error_code       = 0; //
}list;

#endif
