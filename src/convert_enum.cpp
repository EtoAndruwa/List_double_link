#include "List_double_link.h"

const char* enum_to_string(size_t error_code)
{
    switch(error_code)
    {
    case LIST_OK:
        return "LIST_OK";
    case ERR_OPEN_DUMP:
        return "ERR_OPEN_DUMP";
    case ERR_CLOSE_DUMP:
        return "ERR_CLOSE_DUMP";
    case ERR_CALLOC_NODE_ARR:
        return "ERR_CALLOC_NODE_ARR";
    case ERR_REALLOC_NODE_ARR:
        return "ERR_REALLOC_NODE_ARR";
    case ERR_LIST_FULL:
        return "ERR_LIST_FULL";
    case ERR_LIST_EMPTY:
        return "ERR_LIST_EMPTY";
    default:
        return "NEW_ERROR_CODE";
    }
}
