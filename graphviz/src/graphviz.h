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
size_t create_hmtl(char* file_name);
size_t hmtl_start(char* file_name); 
size_t html_end(char* file_name);

#endif
