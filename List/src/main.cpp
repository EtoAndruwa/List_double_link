#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(3);
    push_before(list_str, 0, 100);
    push_before(list_str, 1, 200);
    push_before(list_str, 0, 300);
    push_before(list_str, 1, 400);
    search_logical(list_str, 400);
    search_physical(list_str, 400);
    get_phys_by_log(list_str, 0);
    get_log_by_phys(list_str, 0);

    create_html("html_output");

    list_dtor(list_str);

    return 0;
}
