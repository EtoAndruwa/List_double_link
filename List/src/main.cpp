#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor();
    char* file_name = "first.html";
    create_graph_jpg("first");
    create_hmtl(file_name);


    return 0;
}