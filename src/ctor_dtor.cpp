#include "List_double_link.h"

void list_ctor(list* list_str)
{
    list_str->cur_num_of_nodes = 1;
    list_str->max_num_of_nodes = 4;
    list_str->nodes_arr = (node*)calloc(list_str->max_num_of_nodes, sizeof(node));

    if(list_str->nodes_arr == nullptr)
    {
        safe_exit(list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE, ERR_CALLOC_NODE_ARR);
    }

    for(size_t i = 1; i < list_str->max_num_of_nodes; i++)
    {
        list_str->nodes_arr[i].next = -1;
        list_str->nodes_arr[i].prev = -1;
        list_str->nodes_arr[i].value = POISON;
    }

    list_str->head_node = 0;
    list_str->nodes_arr[0].next = 0;
    list_str->nodes_arr[0].prev = 0;

    list_str->error_code = LIST_OK;
}

void list_dtor(list* list_str)
{
    list_dump(list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    for(size_t i = 0; i < list_str->cur_num_of_nodes; i++)
    {
        list_str->nodes_arr[i].next = POISON;
        list_str->nodes_arr[i].prev = POISON;
        list_str->nodes_arr[i].value = POISON;
    }

    free(list_str->nodes_arr);
    list_str->nodes_arr = nullptr;

    list_str->head_node = POISON;
    list_str->error_code = POISON;
    list_str->cur_num_of_nodes = POISON;
    list_str->empty_node_index = POISON;
    list_str->max_num_of_nodes = POISON;
}

size_t list_realloc(list* list_str)
{
    if(list_str->cur_num_of_nodes == list_str->max_num_of_nodes)
    {   
        node* realloc_ptr = (node*)realloc(list_str->nodes_arr, list_str->max_num_of_nodes * 2 * sizeof(node));

        if(realloc_ptr == nullptr)
        {
            printf("ERROR: list cannot be realloced, please, delete old nodes\n");
            list_str->error_code = ERR_LIST_FULL;
            return 1;
        }
        else
        {
            list_str->max_num_of_nodes *= 2;
            list_str->nodes_arr = realloc_ptr;

            for(size_t i = list_str->cur_num_of_nodes; i < list_str->max_num_of_nodes; i++)
            {
                list_str->nodes_arr[i].next = -1;
                list_str->nodes_arr[i].prev = -1;
                list_str->nodes_arr[i].value = POISON;
            }

            return 2;
        }
    }
}