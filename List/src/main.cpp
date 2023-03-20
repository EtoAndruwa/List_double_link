#include "List_double_link.h"

int main()
{
    list* list_str = nullptr;

    list_str = list_ctor(10);
    // list_str->nodes_arr[0].value = 0;
    // list_str->nodes_arr[1].value = 1;
    // list_str->nodes_arr[2].value = 2;
    // list_str->nodes_arr[3].value = 3;
    // list_str->nodes_arr[4].value = 4;
    // list_str->nodes_arr[5].value = 5;
    // list_str->nodes_arr[6].value = 6;

    // list_str->head_node = 0;
    // list_str->tail_node = 3;
    // list_str->free_node = 7;

    // list_str->nodes_arr[0].next = 3;
    // list_str->nodes_arr[1].next = 6;
    // list_str->nodes_arr[2].next = 4;
    // list_str->nodes_arr[3].next = 2;
    // list_str->nodes_arr[4].next = 5;
    // list_str->nodes_arr[5].next = 1;
    // list_str->nodes_arr[6].next = -1;

    // list_str->nodes_arr[0].prev = -1;
    // list_str->nodes_arr[1].prev = 5;
    // list_str->nodes_arr[2].prev = 3;
    // list_str->nodes_arr[3].prev = 1;
    // list_str->nodes_arr[4].prev = 2;
    // list_str->nodes_arr[5].prev = 4;
    // list_str->nodes_arr[6].prev = 1;

    // create_graph_jpg(list_str, "");
    push_after(list_str, 0, 100);
    push_after(list_str, 0, 200); // 1
    push_after(list_str, 1, 300); // 2
    delete_node(list_str, 0);
    push_after(list_str, 2, 100); // 2
    push_after(list_str, 0, 300); // 3
    // push_after(list_str, 3, 500); // 4
    // delete_node(list_str, 3);
    // push_after(list_str, 4, 400);
    // delete_node(list_str, 0);
    // push_after(list_str, 3, 100);

    put_head(list_str);
    // push_after(list_str, 2, 400);
    // exchange_neighbor(list_str, 1, 2);
    // exchange_neighbor(list_str, 2, 1);
    // put_tail(list_str);
    // create_graph_jpg(list_str, "");
    // push_after(list_str, 2, 400);
    // push_after(list_str, 3, 500);
    // delete_node(list_str, 0);
    // delete_node(list_str, 1);
    // push_after(list_str, 4, 100);
    // push_after(list_str, 1, 200);
    // exchange_nodes(list_str, 4, 1);
    // make_linear(list_str);
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
