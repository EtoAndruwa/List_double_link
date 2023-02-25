#include "List_double_link.h"

void safe_exit(list* list_str, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE, size_t error_code)
{
    list_str->error_code = error_code;
    printf("Error code: %ld (%s)\n", list_str->error_code, enum_to_string(list_str->error_code));
    list_dump(list_str, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    list_dtor(list_str);
    exit(error_code);
}