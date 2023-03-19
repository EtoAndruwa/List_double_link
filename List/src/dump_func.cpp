#include "List_double_link.h"

void list_dump(list* list_str, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE)
{
    FILE* dump_log = fopen(FILE_DUMP_NAME, "a+");

    if(dump_log == nullptr)
    {
        list_str->error_code = ERR_OPEN_DUMP;
        printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code)); 
        list_dtor(list_str);
        exit(ERR_CLOSE_DUMP);
    }
    else
    {
    	fprintf(dump_log, "" );
        fprintf(dump_log, "\n\n====================STRUCT_DATA====================\n");
        fprintf(dump_log, "Struct error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code));
        fprintf(dump_log, "Head node index: %ld\n",list_str->head_node);
        fprintf(dump_log, "Current number of nodes in list: %ld\n", list_str->cur_num_of_nodes);
        fprintf(dump_log, "Maximum number of nodes in list: %ld\n", list_str->max_num_of_nodes);
        fprintf(dump_log, "====================STRUCT_DATA====================\n");

        fprintf(dump_log, "\n====================DUMP_DATA====================\n");
        fprintf(dump_log, "Function name: %s\n", FUNC_NAME);
        fprintf(dump_log, "From line: %ld\n", FUNC_LINE);
        fprintf(dump_log, "From file: %s\n", FUNC_FILE);
        fprintf(dump_log, "Time: %s\n", __TIME__);
        fprintf(dump_log, "Date: %s\n", __DATE__);
        fprintf(dump_log, "====================DUMP_DATA====================\n");

        for(size_t i = 0; i < list_str->max_num_of_nodes; i++)
        {
            fprintf(dump_log, "\nIndex of node: %ld\n", i);
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
