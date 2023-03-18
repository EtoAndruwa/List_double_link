#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(3);
    push_after(list_str, 0, 100);
    push_after(list_str, 0, 40);
    push_after(list_str, 0, 20);
    push_after(list_str, 1, 50);
    delete_node(list_str, 1);
    delete_node(list_str, 2);
    push_after(list_str, 3, 70);
    push_after(list_str, 3, 90);
    delete_node(list_str, 0);
    delete_node(list_str, 2);  


    create_html("html_output");

    list_dtor(list_str);

    return 0;
}
