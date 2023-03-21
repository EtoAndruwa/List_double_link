#ifndef STRUCT_LIST_H
#define STRUCT_LIST_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef int node_val_type;                 //
static const node_val_type POISON = 0xDED; //

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
typedef struct node
{
    int next = 0;          
    int prev = 0;          
    node_val_type value  = 0; 

}mode;

/**
 * @brief 
 * 
 */
typedef struct list
{
    node*  nodes_arr        = nullptr; 

    int head_node           = 0;       
    int tail_node           = 0;
    int free_node           = 0;       

    size_t cur_num_of_nodes = 0;       
    size_t max_num_of_nodes = 0;        

    size_t error_code       = 0; 
    bool   is_linear        = false;
    
}list;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
