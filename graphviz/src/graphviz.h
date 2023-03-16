#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>
#include <stdlib.h>
#include "../config/dot_config.h"
#include "debugger.h"

enum error_codes_dot
{
    ERR_TO_OPEN_GRAPH_TXT  = 1,
    ERR_TO_CLOSE_GRAPH_TXT = 2, 
};

size_t create_graph_jpg(char* file_name);
size_t graph_start(char* file_name);
size_t graph_end(char* file_name);
char* cat_file_directory(char* file_name, char* dir, char* format);
size_t create_html(char* file_name);
size_t hmtl_start(char* file_name); 
size_t html_end(char* file_name);
char* system_dot(char* dir_file_name);
size_t add_to_image_list(char* file_name);
void open_in_chrome(char* file_name);
size_t get_size_file();
char* get_tokens_into_buf();
size_t get_tokens(char* buffer, FILE* file_tpr);
size_t add_image_to_html(char* dir_file_name);

#endif
