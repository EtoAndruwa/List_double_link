#include "List_double_link.h"

const char* enum_to_string(size_t error_code)
{
    #define CONVERT_TO_STRING(enum_code) \
        case enum_code:                     \
            return #enum_code;                \

    switch(error_code)
    {

    CONVERT_TO_STRING(LIST_OK)
    CONVERT_TO_STRING(ERR_OPEN_DUMP)
    CONVERT_TO_STRING(ERR_CLOSE_DUMP)
    CONVERT_TO_STRING(ERR_CALLOC_NODE_ARR)
    CONVERT_TO_STRING(ERR_REALLOC_NODE_ARR)
    CONVERT_TO_STRING(ERR_LIST_FULL)
    CONVERT_TO_STRING(ERR_LIST_EMPTY)

    #undef CONVERT_TO_STRING

    default:
        return "NEW_ERROR_CODE";
    }
}
