#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>
#include <stdlib.h>
#include "../config/dot_config.h"
#include "../../List/src/List_double_link.h"
#include "../../List/src/struct.h"
#include "debugger.h"

enum error_codes_dot
{
    ERR_TO_OPEN_GRAPH_TXT  = 1,
    ERR_TO_CLOSE_GRAPH_TXT = 2, 
};

size_t add_to_image_list(char* file_name);
size_t create_graph_jpg(list* list_ptr, char* legend); // prints all data about the list into the .txt file
size_t graph_start(char* file_name);
size_t graph_end(char* file_name);
char*  cat_file_directory(char* file_name, char* dir, char* format);
size_t create_html(char* file_name);
size_t hmtl_start(char* file_name); 
size_t html_end(char* file_name);
char*  system_dot(char* dir_file_name);
size_t print_node_data(list* list_ptr, char* file_name);
size_t get_size_file();
char*  get_tokens_into_buf();
size_t get_tokens(char* buffer, FILE* file_tpr);
size_t add_image_to_html(char* dir_file_name);
size_t print_node_links(list* list_ptr, char* file_name);
size_t print_legend(char* legend_text, char* dir_file_name);
char*  create_legend(const char* func_name, int new_node_index, int node_index, int value, int node_index_value);
size_t delete_node(list* list_ptr, size_t node_index);
size_t print_node_data_phys(list* list_ptr, char* dir_file_name);
size_t print_node_links_phys(list* list_ptr, char* dir_file_name);


#endif
