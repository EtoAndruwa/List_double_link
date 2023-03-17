#include "List_double_link.h"

// void safe_exit(list* list_str, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE, size_t error_code)
// {
//     list_str->error_code = error_code;
//     printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code));
//     list_dump(list_str, FUNC_NAME, FUNC_LINE, FUNC_FILE);
//     list_dtor(list_str);
//     exit(error_code);
// }

void push_after(list* list_str, size_t node_index, node_val_type value)
{   
    if(node_index > list_str->max_num_of_nodes - 1)
    {
        printf("Index is out of array, try again\n");
        return;
    }
    else
    {
        if(list_str->cur_num_of_nodes != 0)
        {


        }
        else                
        {
            printf("Node was made as head with index %ld\n", node_index);
            list_str->head_node = list_str->free_node;
            list_str->nodes_arr[list_str->head_node].value = value;
            list_str->nodes_arr[list_str->head_node].next = -1;
            list_str->nodes_arr[list_str->head_node].prev = -1;
            list_str->free_node++;
            list_str->cur_num_of_nodes++;
        }
    }
}

// void push_before(list* list_str, size_t node_index, node_val_type value)
// {
//     if(node_index > list_str->max_num_of_nodes - 1)
//     {
//         printf("Index is out of array, try again\n");
//     }
//     else
//     {
//         if(list_str->cur_num_of_nodes != 0)
//         {
//             if(list_realloc(list_str) == 1)
//             {
//                 list_str->nodes_arr[list_str->cur_num_of_nodes].value = value;
//                 list_str->nodes_arr[list_str->cur_num_of_nodes].next = node_index;
//                 list_str->nodes_arr[list_str->cur_num_of_nodes].prev = list_str->nodes_arr[node_index].prev;
//                 list_str->nodes_arr[list_str->nodes_arr[node_index].prev].next = list_str->cur_num_of_nodes;
//                 list_str->nodes_arr[node_index].prev = list_str->cur_num_of_nodes;
//                 list_str->cur_num_of_nodes++;
//             }
//             else
//             {
//                 search_empty_node(list_str);
//                 if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes != 1)
//                 {   
//                     list_str->nodes_arr[list_str->empty_node_index].value = value;
//                     list_str->nodes_arr[list_str->empty_node_index].next = node_index;
//                     list_str->nodes_arr[list_str->empty_node_index].prev = list_str->nodes_arr[node_index].prev;
//                     list_str->nodes_arr[list_str->nodes_arr[node_index].prev].next = list_str->empty_node_index;
//                     list_str->nodes_arr[node_index].prev = list_str->empty_node_index;
//                     list_str->cur_num_of_nodes++;
//                 }
//                 else if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes == 1)
//                 {
//                     list_str->nodes_arr[list_str->empty_node_index].value = value;
//                     list_str->nodes_arr[list_str->empty_node_index].next = list_str->head_node;
//                     list_str->nodes_arr[list_str->empty_node_index].prev = list_str->head_node;
//                     list_str->nodes_arr[list_str->head_node].next = list_str->empty_node_index;
//                     list_str->nodes_arr[list_str->head_node].prev = list_str->empty_node_index;
//                     list_str->cur_num_of_nodes++;
//                 }
//                 else    
//                 {
//                     printf("Node doesn't exist\n");
//                 }
//             }
//         }
//         else                
//         {
//             printf("Node was made as head with index %ld\n", node_index);
//             list_str->head_node = node_index;
//             list_str->nodes_arr[node_index].value = value;
//             list_str->nodes_arr[node_index].next = node_index;
//             list_str->nodes_arr[node_index].prev = node_index;
//             list_str->cur_num_of_nodes++;
//         }
//     }
// }

list* list_ctor(size_t number_of_nodes)
{
    list* list_ptr = (list*)calloc(1, sizeof(list));

    if(list_ptr == nullptr)
    {
        
    }

    list_ptr->cur_num_of_nodes = 0;
    list_ptr->max_num_of_nodes = number_of_nodes;
    list_ptr->nodes_arr = (node*)calloc(list_ptr->max_num_of_nodes, sizeof(node));

    if(list_ptr->nodes_arr == nullptr)
    {
        
    }

    for(size_t i = 0; i < list_ptr->max_num_of_nodes; i++)
    {
        if(i == (list_ptr->max_num_of_nodes - 1))
        {

            list_ptr->nodes_arr[i].next  = -1;
            list_ptr->nodes_arr[i].prev  = -1;
            list_ptr->nodes_arr[i].value = POISON;
        }
        else
        {
            list_ptr->nodes_arr[i].next  = i + 1;
            list_ptr->nodes_arr[i].prev  = -1;
            list_ptr->nodes_arr[i].value = POISON;
        }
    }

    list_ptr->head_node = 1;
    list_ptr->free_node = 0;
    list_ptr->tail_node = 2;

    list_ptr->error_code = LIST_OK;
}



void list_dtor(list* list_str)
{

    for(size_t i = 0; i < list_str->cur_num_of_nodes; i++)
    {
        list_str->nodes_arr[i].next  = POISON;
        list_str->nodes_arr[i].prev  = POISON;
        list_str->nodes_arr[i].value = POISON;
    }

    free(list_str->nodes_arr);
    list_str->nodes_arr = nullptr;

    list_str->head_node = POISON;
    list_str->error_code = POISON;
    list_str->cur_num_of_nodes = POISON;
    list_str->max_num_of_nodes = POISON;
}



// size_t list_realloc(list* list_str)
// {
//     if(list_str->cur_num_of_nodes == list_str->max_num_of_nodes)
//     {   
//         node* realloc_ptr = (node*)realloc(list_str->nodes_arr, list_str->max_num_of_nodes * 2 * sizeof(node));

//         if(realloc_ptr == nullptr)
//         {
//             printf("ERROR: list cannot be realloced, please, delete old nodes\n");
//             list_str->error_code = ERR_LIST_FULL;
//             return 1; // Realloc doesn't take place
//         }
//         else
//         {
//             list_str->max_num_of_nodes *= 2;
//             list_str->nodes_arr = realloc_ptr;

//             for(size_t i = list_str->cur_num_of_nodes; i < list_str->max_num_of_nodes; i++)
//             {
//                 list_str->nodes_arr[i].next = -1;
//                 list_str->nodes_arr[i].prev = -1;
//                 list_str->nodes_arr[i].value = POISON;
//             }
//             return 2; // Realloc took place
//         }
//     }
// }

