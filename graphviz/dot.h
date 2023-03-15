#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>
#include "../src/List_double_link.h"
#include "config/dot_config.h"

enum error_codes
{
    ERR_TO_OPEN_GRAPH_TXT  = 1,
    ERR_TO_CLOSE_GRAPH_TXT = 2,
};

size_t print_node_data(node* node_ptr, char* file_name);
size_t graph_start(char* file_name);
size_t graph_end(char* file_name);
size_t print_node_data(node* node_ptr, char* file_name);
size_t print_node_links(node* node_ptr, char* file_name);
size_t create_graph_jpg(char* file_name);
void cat_file_directory(char* file_name);


#endif
