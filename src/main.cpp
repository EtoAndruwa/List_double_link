#include "List_double_link.h"

int main()
{
    list list_str = {};

    list_ctor(&list_str);

    push_after(&list_str, 0, 10);
    push_after(&list_str, 0, 20);
    push_after(&list_str, 2, 30);
    push_after(&list_str, 1, 40);
    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    list_dtor(&list_str);

    return 0;
}