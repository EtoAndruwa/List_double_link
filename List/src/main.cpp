#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(3);
    push_after(list_str, 0, 100);
    push_after(list_str, 0, 300);
    push_after(list_str, 1, 200);
    push_after(list_str, 2, 200);
    delete_node(list_str, 1);
    delete_node(list_str, 2);
    push_after(list_str, 3, 300);
    push_after(list_str, 2, 400);
    push_after(list_str, 1, 500);
    delete_node(list_str, 2);
    exchange_nodes(list_str, 3, 1);
    // put_to_correct_phys(list_str, 1);
    // make_linear(list_str);
    // search_logical(list_str, 400);
    // search_physical(list_str, 400);
    // get_phys_by_log(list_str, 0);
    // get_log_by_phys(list_str, 0);

    create_html("html_output");

    list_dtor(list_str);

    return 0;
}
