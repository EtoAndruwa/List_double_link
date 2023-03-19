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

    create_html("html_output");

    list_dtor(list_str);

    return 0;
}
