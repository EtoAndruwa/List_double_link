#include "List_double_link.h"

int main()
{
    list list_str = {};

    list_ctor(&list_str);

    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    list_dtor(&list_str);

    return 0;
}