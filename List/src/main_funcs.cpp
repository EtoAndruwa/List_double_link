#include "List_double_link.h"

// size_t safe_exit(list* list_ptr, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE, size_t error_code)
// {
//     list_ptr->error_code = error_code;
//     printf("Error code: %ld (%s)\n", list_ptr->error_code, enum_to_string(list_ptr->error_code));
//     list_dump(list_ptr, FUNC_NAME, FUNC_LINE, FUNC_FILE);
//     list_dtor(list_ptr);
//     return error_code);
// }

void push_after(list* list_ptr, size_t node_index, node_val_type value)
{   
    list_realloc(list_ptr);
    int new_node_index = list_ptr->free_node;

    if(node_index > list_ptr->max_num_of_nodes - 1)
    {
        // printf("Index is out of array, try again\n");
        return;
    }
    else
    {
        if(list_ptr->head_node == -1)
        {
            list_ptr->head_node = list_ptr->free_node;
            list_ptr->tail_node = list_ptr->free_node;
            list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
            list_ptr->nodes_arr[list_ptr->head_node].value = value;
            list_ptr->nodes_arr[list_ptr->head_node].next = -1;
            list_ptr->nodes_arr[list_ptr->head_node].prev = -1;
            list_ptr->cur_num_of_nodes++;
        }
        else                
        {
            if(list_ptr->nodes_arr[node_index].prev == -1 && list_ptr->head_node != node_index)
            {   
                printf("Node does not exist");
            }
            else
            {
                if(node_index == list_ptr->tail_node)
                {
                    list_ptr->tail_node = list_ptr->free_node;
                }
                list_ptr->nodes_arr[new_node_index].value = value;
                list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
                list_ptr->nodes_arr[new_node_index].next = list_ptr->nodes_arr[node_index].next;    
                list_ptr->nodes_arr[new_node_index].prev = node_index;

                if(list_ptr->nodes_arr[new_node_index].next != -1)
                {
                    list_ptr->nodes_arr[list_ptr->nodes_arr[new_node_index].next].prev = new_node_index;
                }

                list_ptr->nodes_arr[node_index].next = new_node_index;
                list_ptr->cur_num_of_nodes++;
            }
        }
    }

    char* legend = create_legend(__func__ , new_node_index, node_index, value, list_ptr->nodes_arr[node_index].value);
    create_graph_jpg(list_ptr, legend);
}

// void push_before(list* list_ptr, size_t node_index, node_val_type value)
// {
//     if(node_index > list_ptr->max_num_of_nodes - 1)
//     {
//         printf("Index is out of array, try again\n");
//     }
//     else
//     {
//         if(list_ptr->cur_num_of_nodes != 0)
//         {
//             if(list_realloc(list_ptr) == 1)
//             {
//                 list_ptr->nodes_arr[list_ptr->cur_num_of_nodes].value = value;
//                 list_ptr->nodes_arr[list_ptr->cur_num_of_nodes].next = node_index;
//                 list_ptr->nodes_arr[list_ptr->cur_num_of_nodes].prev = list_ptr->nodes_arr[node_index].prev;
//                 list_ptr->nodes_arr[list_ptr->nodes_arr[node_index].prev].next = list_ptr->cur_num_of_nodes;
//                 list_ptr->nodes_arr[node_index].prev = list_ptr->cur_num_of_nodes;
//                 list_ptr->cur_num_of_nodes++;
//             }
//             else
//             {
//                 search_empty_node(list_ptr);
//                 if(list_ptr->nodes_arr[node_index].next != -1 && list_ptr->cur_num_of_nodes != 1)
//                 {   
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].value = value;
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].next = node_index;
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].prev = list_ptr->nodes_arr[node_index].prev;
//                     list_ptr->nodes_arr[list_ptr->nodes_arr[node_index].prev].next = list_ptr->empty_node_index;
//                     list_ptr->nodes_arr[node_index].prev = list_ptr->empty_node_index;
//                     list_ptr->cur_num_of_nodes++;
//                 }
//                 else if(list_ptr->nodes_arr[node_index].next != -1 && list_ptr->cur_num_of_nodes == 1)
//                 {
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].value = value;
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].next = list_ptr->head_node;
//                     list_ptr->nodes_arr[list_ptr->empty_node_index].prev = list_ptr->head_node;
//                     list_ptr->nodes_arr[list_ptr->head_node].next = list_ptr->empty_node_index;
//                     list_ptr->nodes_arr[list_ptr->head_node].prev = list_ptr->empty_node_index;
//                     list_ptr->cur_num_of_nodes++;
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
//             list_ptr->head_node = node_index;
//             list_ptr->nodes_arr[node_index].value = value;
//             list_ptr->nodes_arr[node_index].next = node_index;
//             list_ptr->nodes_arr[node_index].prev = node_index;
//             list_ptr->cur_num_of_nodes++;
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

    list_ptr->head_node = -1;
    list_ptr->free_node =  0;
    list_ptr->tail_node = -1;

    list_ptr->error_code = LIST_OK;
}

void list_dtor(list* list_ptr)
{

    for(size_t i = 0; i < list_ptr->cur_num_of_nodes; i++)
    {
        list_ptr->nodes_arr[i].next  = POISON;
        list_ptr->nodes_arr[i].prev  = POISON;
        list_ptr->nodes_arr[i].value = POISON;
    }

    free(list_ptr->nodes_arr);
    list_ptr->nodes_arr = nullptr;

    list_ptr->head_node = POISON;
    list_ptr->error_code = POISON;
    list_ptr->cur_num_of_nodes = POISON;
    list_ptr->max_num_of_nodes = POISON;

    free(list_ptr);
    list_ptr = nullptr;
}

size_t list_realloc(list* list_ptr)
{
    if(list_ptr->cur_num_of_nodes == list_ptr->max_num_of_nodes)
    {   
        node* realloc_ptr = (node*)realloc(list_ptr->nodes_arr, list_ptr->max_num_of_nodes * 2 * sizeof(node));

        if(realloc_ptr == nullptr)
        {
            return ERR_LIST_FULL; // Realloc doesn't take place
        }
        else
        {
            list_ptr->max_num_of_nodes *= 2;
            list_ptr->nodes_arr = realloc_ptr;

            for(size_t i = list_ptr->cur_num_of_nodes; i < list_ptr->max_num_of_nodes; i++)
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
            list_ptr->free_node = list_ptr->cur_num_of_nodes;
            return REALLOC_TRUE; // Realloc took place
        }
    }
    else
    {
        return REALLOC_FALSE;
    }
}

size_t delete_node(list* list_ptr, size_t node_index)
{
    int node_value = list_ptr->nodes_arr[node_index].value;
    int next_node_index = list_ptr->nodes_arr[node_index].next;
    int prev_node_index = list_ptr->nodes_arr[node_index].prev;

    if(node_index == list_ptr->tail_node && list_ptr->cur_num_of_nodes != 1)
    {
        list_ptr->tail_node = list_ptr->nodes_arr[node_index].prev;
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[node_index].next  = list_ptr->free_node;
        list_ptr->nodes_arr[prev_node_index].next = -1;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
        list_ptr->cur_num_of_nodes--;
    }
    else if(list_ptr->tail_node == list_ptr->head_node)  
    {
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[node_index].next  = list_ptr->free_node;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
        list_ptr->head_node = -1;
        list_ptr->tail_node = -1;
        list_ptr->cur_num_of_nodes--;
    }
    else
    {
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[next_node_index].prev = list_ptr->nodes_arr[node_index].prev;
        list_ptr->nodes_arr[prev_node_index].next = list_ptr->nodes_arr[node_index].next;
        list_ptr->nodes_arr[node_index].next  = list_ptr->free_node;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
        list_ptr->cur_num_of_nodes--;
    }

    char* legend = create_legend(__func__ , 0, node_index, 0, node_value);
    create_graph_jpg(list_ptr, legend);
}




