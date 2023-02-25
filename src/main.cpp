#include "List_double_link.h"

int main()
{
    list list_str = {};

    list_ctor(&list_str);

    push_before(&list_str, 0, 10);

    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);

    push_before(&list_str, 1, 20);
    push_before(&list_str, 2, 30);
    push_before(&list_str, 1, 40);
    list_dump(&list_str, DEF_FUNC_NAME, DEF_FUNC_LINE, DEF_FUNC_FILE);
    print_node(&list_str, 2);

    list_dtor(&list_str);

    return 0;
}