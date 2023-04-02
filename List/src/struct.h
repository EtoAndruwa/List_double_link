#ifndef STRUCT_LIST_H
#define STRUCT_LIST_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef int  node_val_type;                // The type of the node's data
static const node_val_type POISON = 0xDED; // The poison value of the node's data

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The stuct which contains the information about the node
 * 
 */
typedef struct node
{
    int next = 0;          
    int prev = 0;          
    node_val_type value  = 0; 
}node;

/**
 * @brief The struct which contains the information about the the list
 * 
 */
typedef struct list
{
    node*  nodes_arr        = nullptr; // The pointer to the allocated memmory block for the array of nodes

    int head_node           = 0;       // The physical id of the head node
    int tail_node           = 0;       // The physical id of the tail node
    int free_node           = 0;       // The physical id of the free node

    size_t cur_num_of_nodes = 0;       // The current number of the uded nodes
    size_t max_num_of_nodes = 0;       // The maximum amout of nodes in the list

    size_t error_code       = 0;       // The error code of the struct
    bool   is_linear        = false;   // The flag which is used for optimization in the search
}list;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
