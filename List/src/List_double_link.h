#ifndef LIST_DOUBLE_LINK_H
#define LIST_DOUBLE_LINK_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "../../graphviz/src/graphviz.h"
#include "../../graphviz/src/debugger.h"
#include "struct.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define DEF_FUNC_NAME __func__
#define DEF_FUNC_LINE __LINE__
#define DEF_FUNC_FILE __FILE__

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const char* FILE_DUMP_NAME = "dump_log.txt";


/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum error_codes
{
    LIST_OK              = 0,
    ERR_OPEN_DUMP        = 1,
    ERR_CLOSE_DUMP       = 2,
    ERR_CALLOC_NODE_ARR  = 3,
    ERR_REALLOC_NODE_ARR = 4,
    ERR_LIST_FULL        = 5,
    ERR_LIST_EMPTY       = 6,
};

enum return_code
{
    REALLOC_TRUE    = 1,
    REALLOC_FALSE   = 2,
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

list*  list_ctor(size_t number_of_nodes);
void   push_after(list* list_str, size_t node_index, node_val_type value);
void   list_dtor(list* list_str);
size_t list_realloc(list* list_ptr);
void   push_before(list* list_ptr, size_t node_index, node_val_type value);
size_t search_physical(list* list_ptr, int value);
size_t search_logical(list* list_ptr, int value);
size_t get_phys_by_log(list* list_ptr, int logical_index);
size_t get_log_by_phys(list* list_ptr, int physical_index);

#endif
