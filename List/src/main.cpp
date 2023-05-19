#include "List_double_link.h"

// using namespace std::chrono;

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(10);
    create_graph_jpg(list_str, "");
    list_str->nodes_arr[0].value = 0;
    list_str->nodes_arr[1].value = 1;
    list_str->nodes_arr[2].value = 2;
    list_str->nodes_arr[3].value = 3;
    list_str->nodes_arr[4].value = 4;
    list_str->nodes_arr[5].value = 5;
    list_str->nodes_arr[6].value = 6;

    list_str->head_node = 0;
    list_str->tail_node = 6;
    list_str->free_node = 7;

    list_str->nodes_arr[0].next = 3;
    list_str->nodes_arr[1].next = 6;
    list_str->nodes_arr[2].next = 4;
    list_str->nodes_arr[3].next = 2;
    list_str->nodes_arr[4].next = 5;
    list_str->nodes_arr[5].next = 1;
    list_str->nodes_arr[6].next = -1;

    list_str->nodes_arr[0].prev = -1;
    list_str->nodes_arr[1].prev = 5;
    list_str->nodes_arr[2].prev = 3;
    list_str->nodes_arr[3].prev = 0;
    list_str->nodes_arr[4].prev = 2;
    list_str->nodes_arr[5].prev = 4;
    list_str->nodes_arr[6].prev = 1;

    list_str->cur_num_of_nodes = 7;
    create_graph_jpg(list_str, "");
    // auto old = steady_clock::now();
    // make_linear(list_str);
    create_linear(list_str);
    // create_graph_jpg(list_str, "create_linear");
    // auto cpu_time_used = steady_clock::now() - old;
    // std::cout << duration_cast<milliseconds>(cpu_time_used).count() << "\n";

    create_html("html_output");
    list_dtor(list_str);

    return 0;
}
