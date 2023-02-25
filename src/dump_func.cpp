#include "List_double_link.h"

void list_dump(list* list_str, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE)
{
    FILE* dump_log = fopen(FILE_DUMP_NAME, "wb");

    if(dump_log == nullptr)
    {
        list_str->error_code = ERR_OPEN_DUMP;
        printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code)); 
        list_dtor(list_str);
        exit(ERR_CLOSE_DUMP);
    }
    else
    {
        for(size_t i = 0; i < list_str->num_of_nodes; i++)
        {
            fprintf(dump_log, "Index of node: %ld\n", i);
            fprintf(dump_log, "Next node: %ld\n", list_str->nodes_arr[i].next);
            fprintf(dump_log, "Previous node: %ld\n", list_str->nodes_arr[i].prev);
            fprintf(dump_log, "Node value: %d\n", list_str->nodes_arr[i].value);
        }
    }

    if(fclose(dump_log) == EOF)
    {
        list_str->error_code = ERR_CLOSE_DUMP;
        printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code)); 
        list_dtor(list_str);
        exit(ERR_CLOSE_DUMP);
    }
}