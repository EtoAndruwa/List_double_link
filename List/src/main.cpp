#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor();
    create_graph_jpg("first");
    create_graph_jpg("second");
    create_graph_jpg("third");
    create_html("html_output");


    return 0;
}