#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor();
    create_graph_jpg(list_str, "first");
    create_graph_jpg(list_str, "second");
    create_graph_jpg(list_str, "third");
    create_html("html_output");


    return 0;
}