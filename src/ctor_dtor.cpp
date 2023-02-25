#include "List_double_link.h"

void list_ctor(list* list_str)
{
    list_str->num_of_nodes = 1;
    list_str->nodes_arr = (node*)calloc(list_str->num_of_nodes, sizeof(node));

    if(list_str->nodes_arr == nullptr)
    {
        safe_exit(list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE, ERR_CALLOC_NODE_ARR);
    }

    list_str->head_node = 0;
    list_str->nodes_arr[0].next = 0;
    list_str->nodes_arr[0].prev = 0;

    list_str->error_code = LIST_OK;
}

void list_dtor(list* list_str)
{
    list_dump(list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    for(size_t i = 0; i < list_str->num_of_nodes; i++)
    {
        list_str->nodes_arr[i].next = POISON;
        list_str->nodes_arr[i].prev = POISON;
        list_str->nodes_arr[i].value = POISON;
    }

    free(list_str->nodes_arr);
    list_str->nodes_arr = nullptr;

    list_str->head_node = POISON;
    list_str->error_code = POISON;
    list_str->num_of_nodes = POISON;
}