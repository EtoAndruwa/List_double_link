#include "List_double_link.h"

int main()
{
    list list_str = {};

    list_ctor(&list_str);

    push_after(&list_str, 2, 10);

    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    push_after(&list_str, 2, 20);
    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    push_after(&list_str, 2, 30);
    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    list_dtor(&list_str);

    return 0;
}