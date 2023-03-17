#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(20);
    push_after(list_str, 0, 100);
    push_after(list_str, 0, 20);
push_after(list_str, 1, 40);

    create_html("html_output");


    return 0;
}