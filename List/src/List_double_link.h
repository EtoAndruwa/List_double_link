#ifndef LIST_DOUBLE_LINK_H
#define LIST_DOUBLE_LINK_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "../../graphviz/src/graphviz.h"
#include "../../graphviz/src/debugger.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define DEF_FUNC_NAME __func__
#define DEF_FUNC_LINE __LINE__
#define DEF_FUNC_FILE __FILE__

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const char* FILE_DUMP_NAME = "dump_log.txt";
typedef int node_val_type;
static const node_val_type POISON = 0xDED;

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

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct node
{
    size_t next = 0;          //
    size_t prev = 0;          //
    node_val_type value  = 0; // 

}mode;

typedef struct list
{
    node*  nodes_arr        = nullptr; //

    size_t head_node        = 0;       //
    size_t tail_node        = 0;
    size_t free_node        = 0;       //

    size_t cur_num_of_nodes = 0;       //
    size_t max_num_of_nodes = 0;       // 

    size_t error_code       = LIST_OK; //
}list;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

list* list_ctor();

#endif
