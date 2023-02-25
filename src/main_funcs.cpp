#include "List_double_link.h"

void safe_exit(list* list_str, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE, size_t error_code)
{
    list_str->error_code = error_code;
    printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code));
    list_dump(list_str, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    list_dtor(list_str);
    exit(error_code);
}

void push_after(list* list_str, size_t node_index, node_val_type value)
{
    if(list_realloc(list_str) == 1)
    {
        search_empty_node(list_str);
        list_str->nodes_arr[list_str->empty_node_index].value = value;
        list_str->nodes_arr[list_str->empty_node_index].next = list_str->nodes_arr[node_index].next;
        list_str->nodes_arr[list_str->empty_node_index].prev = node_index;
        list_str->nodes_arr[list_str->nodes_arr[node_index].next].prev = list_str->empty_node_index;
        list_str->cur_num_of_nodes++;
    }
    else
    {
        search_empty_node(list_str);
        if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes != 1)
        {   
            list_str->nodes_arr[list_str->empty_node_index].value = value;
            list_str->nodes_arr[list_str->empty_node_index].next = list_str->nodes_arr[node_index].next;
            list_str->nodes_arr[list_str->empty_node_index].prev = node_index;
            list_str->nodes_arr[list_str->nodes_arr[node_index].next].prev = list_str->empty_node_index;
            list_str->nodes_arr[node_index].next = list_str->empty_node_index;
            list_str->cur_num_of_nodes++;
        }
        else if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes == 1)
        {
            list_str->nodes_arr[list_str->empty_node_index].value = value;
            list_str->nodes_arr[list_str->empty_node_index].next = list_str->head_node;
            list_str->nodes_arr[list_str->empty_node_index].prev = list_str->head_node;
            list_str->nodes_arr[list_str->head_node].next = list_str->empty_node_index;
            list_str->nodes_arr[list_str->head_node].prev = list_str->empty_node_index;
            list_str->cur_num_of_nodes++;
        }
        else    
        {
            printf("Node doesn't exist\n");
        }
    }
}

void push_before(list* list_str, size_t node_index, node_val_type value)
{
    if(list_realloc(list_str) == 1)
    {
        list_str->nodes_arr[list_str->cur_num_of_nodes].value = value;
        list_str->nodes_arr[list_str->cur_num_of_nodes].next = node_index;
        list_str->nodes_arr[list_str->cur_num_of_nodes].prev = list_str->nodes_arr[node_index].prev;
        list_str->nodes_arr[list_str->nodes_arr[node_index].prev].next = list_str->cur_num_of_nodes;
        list_str->nodes_arr[node_index].prev = list_str->cur_num_of_nodes;
        list_str->cur_num_of_nodes++;
    }
    else
    {
        search_empty_node(list_str);
        if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes != 1)
        {   
            list_str->nodes_arr[list_str->empty_node_index].value = value;
            list_str->nodes_arr[list_str->empty_node_index].next = node_index;
            list_str->nodes_arr[list_str->empty_node_index].prev = list_str->nodes_arr[node_index].prev;
            list_str->nodes_arr[list_str->nodes_arr[node_index].prev].next = list_str->empty_node_index;
            list_str->nodes_arr[node_index].prev = list_str->empty_node_index;
            list_str->cur_num_of_nodes++;
        }
        else if(list_str->nodes_arr[node_index].next != -1 && list_str->cur_num_of_nodes == 1)
        {
            list_str->nodes_arr[list_str->empty_node_index].value = value;
            list_str->nodes_arr[list_str->empty_node_index].next = list_str->head_node;
            list_str->nodes_arr[list_str->empty_node_index].prev = list_str->head_node;
            list_str->nodes_arr[list_str->head_node].next = list_str->empty_node_index;
            list_str->nodes_arr[list_str->head_node].prev = list_str->empty_node_index;
            list_str->cur_num_of_nodes++;
        }
        else    
        {
            printf("Node doesn't exist\n");
        }
    }
}


void delete_node(list* list_str)
{


}

void print_node(list* list_str, size_t node_index)
{
    if(list_str->nodes_arr[node_index].next != -1 && node_index > 0 && node_index < list_str->max_num_of_nodes)
    {
        printf("\n==========NEXT_NODE==========\n");
        printf("Value: %d\n", list_str->nodes_arr[list_str->nodes_arr[node_index].next].value);
        printf("==========NEXT_NODE==========\n");

        printf("\n==========THIS_NODE==========\n");
        printf("Next node index: %ld\n", list_str->nodes_arr[node_index].next);
        printf("Value: %d\n", list_str->nodes_arr[node_index].value);
        printf("Previous node index: %ld\n", list_str->nodes_arr[node_index].prev);
        printf("==========THIS_NODE==========\n");

        printf("\n==========PREV_NODE==========\n");
        printf("Value: %d\n", list_str->nodes_arr[list_str->nodes_arr[node_index].prev].value);
        printf("==========PREV_NODE==========\n");
    }
    else
    {
        printf("Node with index = %ld doesn't exist. Please, try again\n", node_index);
    }
}

void search_empty_node(list* list_str)
{
    for(size_t i = 0; i < list_str->max_num_of_nodes; i++)
    {
        if(list_str->nodes_arr[i].next == -1)
        {
            list_str->empty_node_index = i;
            break;
        }
    }
}
