#include "graphviz.h"

static size_t number_of_images = 0; // The global variable which is used in order to count the total number of image files

size_t graph_start(char* file_name) // OK
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    /*
        The text below is the syntax of the DOT language 
        which is used in order to create the graph using
                        the graphviz lib
    */
    fprintf(graph_txt, "\n");
    fprintf(graph_txt, "digraph\n"); // The start of the digraph
    fprintf(graph_txt, "{\n");
    fprintf(graph_txt, "\trankdir=%s;\n", RANKDIR_DOT);
    fprintf(graph_txt, "\tsplines=%s;\n", SPLINES_DOT);

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

size_t graph_end(char* file_name) // OK
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    /*
        The text below is the syntax of the DOT language 
        which is used in order to create the graph using
                        the graphviz lib
    */
    fprintf(graph_txt, "}\n"); // The end of the digraph

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

size_t html_end(char* file_name) // OK
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_HTML)
        return ERR_TO_OPEN_HTML;
    }

    fprintf(graph_txt, "</pre>\n");

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_HTML)
        return ERR_TO_CLOSE_HTML;
    }

    return RETURN_OK;
}

size_t hmtl_start(char* file_name) // OK
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_HTML)
        return ERR_TO_OPEN_HTML;
    }

    fprintf(graph_txt, "<pre>\n");

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_HTML)
        return ERR_TO_CLOSE_HTML;
    }

    return RETURN_OK;
}

size_t print_node_data(list* list_ptr, char* file_name) 
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(list_ptr->head_node != -1)
    {
        int next_node_head = list_ptr->head_node;

        while(next_node_head != -1)
        {
            fprintf(graph_txt, "\tnode_%d[shape = record, style=\"filled\" fillcolor=\"%s\", label =\" {<name> node_%d} | { <f0> prev = %d } |{<here> value = %d}| { <f1> next = %d } \"];\n", next_node_head, BLUE_BG_COLOR_DOT, next_node_head, list_ptr->nodes_arr[next_node_head].prev,
            list_ptr->nodes_arr[next_node_head].value, list_ptr->nodes_arr[next_node_head].next);

            next_node_head = list_ptr->nodes_arr[next_node_head].next;
        }
    }

    if(list_ptr->free_node != -1)
    {
        int next_node_free = list_ptr->free_node;
        next_node_free = list_ptr->nodes_arr[next_node_free].next;

        while(next_node_free != -1)
        {
            fprintf(graph_txt, "\tnode_free_%d[shape = record, style=\"filled\" fillcolor=\"%s\", label =\" {<name> node_%d} | { <f0> prev = %d } |{<here> value = %d}| { <f1> next = %d } \"];\n", next_node_free, RED_BG_COLOR_DOT, next_node_free, list_ptr->nodes_arr[next_node_free].prev,
            list_ptr->nodes_arr[next_node_free].value, list_ptr->nodes_arr[next_node_free].next);
            next_node_free = list_ptr->nodes_arr[next_node_free].next;
        }
    }
    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

size_t print_node_links(list* list_ptr, char* file_name) // prints all the links of the list
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(list_ptr->head_node != -1)
    {
        int next_node_head = list_ptr->head_node;

        while(next_node_head != -1)
        {
            if(list_ptr->nodes_arr[next_node_head].next != -1)
            {
                fprintf(graph_txt, "\tnode_%d:f1 -> node_%d:f1[color=\"%s\", label = \"next node\"];\n", next_node_head, list_ptr->nodes_arr[next_node_head].next, RED_COLOR_DOT);
            }
            if(list_ptr->nodes_arr[next_node_head].prev != -1)
            {
                fprintf(graph_txt, "\tnode_%d:f0 -> node_%d:f0[color=\"%s\", label = \"previous node\"];\n", next_node_head, list_ptr->nodes_arr[next_node_head].prev, BLUE_COLOR_DOT);
            }

            next_node_head = list_ptr->nodes_arr[next_node_head].next;
        }
    }
    if(list_ptr->free_node != -1)
    {
        int next_node_free = list_ptr->free_node;

        while(next_node_free != -1)
        {
            if(list_ptr->nodes_arr[next_node_free].next != -1)
            {
                fprintf(graph_txt, "\tnode_free_%d:f1 -> node_free_%d:f1[color=\"%s\", label = \"next node\"];\n", next_node_free, list_ptr->nodes_arr[next_node_free].next, RED_COLOR_DOT);
            }

            next_node_free = list_ptr->nodes_arr[next_node_free].next;
        }
    }

    if(list_ptr->free_node != -1)
    {
        fprintf(graph_txt, "\tfree_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Free node\"];\n", FREE_NODE_COLOR);
        fprintf(graph_txt, "\tfree_node -> node_free_%d:<name>[color=\"%s\", label = \"Free node\"];\n\n", list_ptr->free_node, FREE_NODE_COLOR);
    }
    if(list_ptr->head_node != -1)
    {
        fprintf(graph_txt, "\thead_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Head node\"];\n", HEAD_NODE_COLOR);
        fprintf(graph_txt, "\thead_node -> node_%d:<name>[color=\"%s\", label = \"Head node\"];\n\n", list_ptr->head_node, HEAD_NODE_COLOR);
    }
    if(list_ptr->tail_node != -1)
    {
        fprintf(graph_txt, "\ttail_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Tail node\"];\n", TAIL_NODE_COLOR);
        fprintf(graph_txt, "\ttail_node -> node_%d:<name>[color=\"%s\", label = \"Tail node\"];\n\n", list_ptr->tail_node, TAIL_NODE_COLOR);
    }

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

size_t create_graph_jpg(list* list_ptr, char* legend) // prints all data about the list into the .txt file
{
    char int_str_equivalent[11] = {};
    sprintf(int_str_equivalent, "%d_%s", number_of_images, "logical");
    char* file_name = cat_file_directory(OUTPUT_NAME, "", int_str_equivalent);
    char* dir_file_name = cat_file_directory(file_name, TXT_FOLDER, INPUT_FORMAT);

    graph_start(dir_file_name);
    print_legend(legend, dir_file_name);
    print_node_data(list_ptr, dir_file_name);
    print_node_links(list_ptr, dir_file_name);
    graph_end(dir_file_name);

    system_dot(file_name);
    free(dir_file_name);
    dir_file_name = nullptr;
    free(file_name);
    file_name = nullptr;

    memset(int_str_equivalent, 0, 11);
    sprintf(int_str_equivalent, "%d_%s", number_of_images, "physical");
    file_name = cat_file_directory(OUTPUT_NAME, "", int_str_equivalent);
    dir_file_name = cat_file_directory(file_name, TXT_FOLDER, INPUT_FORMAT);

    graph_start(dir_file_name);
    print_legend(legend, dir_file_name);
    print_node_data_phys(list_ptr, dir_file_name);
    print_node_links_phys(list_ptr, dir_file_name);
    graph_end(dir_file_name);

    system_dot(file_name);
    free(dir_file_name);
    dir_file_name = nullptr;
    free(file_name);
    file_name = nullptr;
    free(legend);
    legend = nullptr;

    number_of_images++;

    return RETURN_OK;
}

char* cat_file_directory(char* file_name, char* dir, char* format) // cats the file name, dir path and extension into the one string
{
    size_t size_of_file_name    = strlen(file_name) + 1; // additional \0 in the end
    size_t size_of_dir_name     = strlen(dir) + 1;       // additional \0 in the end
    size_t size_of_input_format = strlen(dir) + 1;       // additional \0 in the end

    char* dir_file_name = (char*)calloc(size_of_dir_name + size_of_file_name + size_of_input_format, sizeof(char));

    if(dir_file_name == nullptr)
    {
        ERROR_MESSAGE(stderr, 1)
        return nullptr;
    }

    strcpy(dir_file_name, dir);
    strcat(dir_file_name, file_name);
    strcat(dir_file_name, format);

    return dir_file_name;
}

size_t create_html(char* file_name) // creates the whole html file at once
{
    char* dir_file_name = cat_file_directory(file_name, DIR_TO_DUMPS, HTML);

    hmtl_start(dir_file_name);
    add_image_to_html(dir_file_name);
    html_end(dir_file_name);

    free(dir_file_name);
    dir_file_name = nullptr;

    return RETURN_OK;
}

char* system_dot(char* file_name) // creates a dot function in order to call it automatically
{
    char* dot  = " dot ";
    char* flag = " -o ";

    char* txt_file = cat_file_directory(file_name, TXT_FOLDER, INPUT_FORMAT);
    char* jpg_file = cat_file_directory(file_name, IMAGE_FOLDER, OUTPUT_FORMAT);

    size_t size_of_dot = strlen(dot) + 1;
    size_t size_of_txt_file = strlen(txt_file) + 1;
    size_t size_of_jpg_file = strlen(jpg_file) + 1;
    size_t size_of_flag = strlen(flag) + 1;
    size_t size_of_output_flag = strlen(OUTPUT_FORMAT_FLAG) + 1;

    size_t total_lenght = size_of_dot + size_of_txt_file + size_of_jpg_file + size_of_flag + size_of_output_flag;

    char* system_cmd = (char*)calloc(total_lenght , sizeof(char));

    strcpy(system_cmd, dot);




    strcat(system_cmd, txt_file);
    strcat(system_cmd, OUTPUT_FORMAT_FLAG);
    strcat(system_cmd, flag);
    strcat(system_cmd, jpg_file);

    system(system_cmd);

    free(txt_file);
    free(jpg_file);
    free(system_cmd);


    char* file_with_ext = cat_file_directory(file_name, "", OUTPUT_FORMAT);

    add_to_image_list(file_with_ext);

    free(file_with_ext);
    file_with_ext = nullptr;
    txt_file = nullptr;
    jpg_file = nullptr;
    system_cmd = nullptr;
}

size_t add_to_image_list(char* file_name) // adds the path to the image into the image_list.file
{
    char* dir_file_name = cat_file_directory("image_list.txt", DIR_TO_DUMPS, "");
    char* path_to_write = cat_file_directory(file_name, "../graph_dumps/images/", "");

    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, 1);
    }

    fprintf(graph_txt, "%s\n", path_to_write);

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, 1);
    }

    free(dir_file_name);
    dir_file_name = nullptr;
    free(path_to_write);
    path_to_write = nullptr;

    return RETURN_OK;
}

size_t add_image_to_html(char* dir_file_name) // adds all images to the html at once
{
    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, 1);
        return 1;
    }

    get_size_file();
    char* buffer = get_tokens_into_buf();
    get_tokens(buffer, graph_txt);


    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, 1);
        return 1;
    }

    return RETURN_OK;
}

char* get_tokens_into_buf() // reads all tokens into the buffer
{
    char* dir_file_name = cat_file_directory("image_list.txt", DIR_TO_DUMPS, "");
    FILE* image_list = fopen(dir_file_name, "r");
    if(image_list == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_IMAGE_LST)
        return nullptr;
    }

    size_t size_of_file = get_size_file(); // Gets the size of the file 
    if(get_size_file() == )
    {

    }

    char* buffer_ptr = (char*)calloc(1, sizeof(char) * (size_of_file + 1));
    if(buffer_ptr == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CALLOC_BUFFER)
        return nullptr;
    }

    fread(buffer_ptr, sizeof(char), size_of_file, image_list); // Reads the whole text of the file to the allocated buffer
    buffer_ptr[size_of_file] = '\0'; // Makes from the buffer null-terminated string

    if(fclose(image_list) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_IMAGE_LST)
        return nullptr;
    }

    free(dir_file_name);
    dir_file_name = nullptr;

    return buffer_ptr;
}

size_t get_size_file() // OK
{
    char* dir_file_name = cat_file_directory("image_list.txt", DIR_TO_DUMPS, "");
    FILE* image_list    = fopen(dir_file_name, "r");
    if(image_list == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_IMAGE_LST);
        return ERR_TO_OPEN_IMAGE_LST;
    }

    fseek(image_list, 0, SEEK_END);  // Puts the pointer inside the file_struct_ptr to the end of the file
    size_t size = ftell(image_list); // Get the size of the file_struct_ptr with '\r'!

    if(fclose(image_list) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_IMAGE_LST);
        return ERR_TO_CLOSE_IMAGE_LST;
    }

    free(dir_file_name);
    dir_file_name = nullptr;

    return size;
}

size_t get_tokens(char* buffer, FILE* file_tpr) // OK
{
    char* token = strtok(buffer," \n\r");

    if(token == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_STRTOK_NULL_PTR)
        return ERR_STRTOK_NULL_PTR;
    }

    while (token != NULL)
    {
        if(strstr(token, "logical") == nullptr) // Searches for the substring logic in the token
        {
            fprintf(file_tpr, "<div style =\"text-align: center;\"><h1>The image below %s</h1>\n", strstr(token, OUTPUT_NAME));
            fprintf(file_tpr, "<img src=\"%s\" alt=\"%s \"></div>\n", token, token);
        }
        token = strtok(NULL, " \n\r");
    }

    free(buffer);
    buffer = nullptr;

    return RETURN_OK;
}

size_t print_legend(char* legend_text, char* dir_file_name) // OK
{
    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(strcmp(legend_text, DEFAULT_LEGEND_TEXT) == 0)
    {
        fprintf(graph_txt, "\tnode_legend[shape = record, label = \"%s\"];\n", DEFAULT_LEGEND_TEXT);
    }
    else
    {
        fprintf(graph_txt, "\tnode_legend[shape=record , label = \"%s\"];\n", legend_text);
    }


    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

char* create_legend(const char* func_name, int first_node_id, int first_node_val, int second_node_id, int second_node_val) // OK
{
    char* legend = (char*)calloc(100, sizeof(char));

    if(legend == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CALLOC_LEGEND)
        return nullptr;
    }

    if(strcmp(func_name, "push_after") == 0)
    {
        sprintf(legend, "Node_%d with value = %d was pushed after the Node_%d with value %d", first_node_id, first_node_val, second_node_id, second_node_val);
    }
    else if(strcmp(func_name, "delete_node") == 0)
    {
        sprintf(legend, "Node_%d with value = %d was deleted from the list", first_node_id, first_node_val);
    }
    else if(strcmp(func_name, "push_before") == 0)
    {
        sprintf(legend, "Node_%d with value = %d was pushed before the Node_%d with value %d", first_node_id, first_node_val, second_node_id, second_node_val);
    }
    else if(strcmp(func_name, "exchange_neighbor") == 0)
    {
        sprintf(legend, "Node_%d with value = %d was exchanged with the NEIGHBOR Node_%d with value %d", first_node_id, first_node_val, second_node_id, second_node_val);
    }
    else if(strcmp(func_name, "exchange_stranger") == 0)
    {
        sprintf(legend, "Node_%d with value = %d was exchanged with the STRANGER Node_%d with value %d", first_node_id, first_node_val, second_node_id, second_node_val);
    }
    else
    {
        sprintf(legend, "NEW COMMAND WAS PERFORMED");
    }

    return legend;
}

size_t print_node_data_phys(list* list_ptr, char* dir_file_name) // OK
{
    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    char* node_bg_color = nullptr;
    for(size_t node_index = 0; node_index < list_ptr->max_num_of_nodes - 1; node_index++) // Prints all data about the nodes
    {
        if(node_index == list_ptr->tail_node || node_index == list_ptr->head_node || (list_ptr->nodes_arr[node_index].prev != -1 && list_ptr->nodes_arr[node_index].next != -1))
        {
            node_bg_color = BLUE_BG_COLOR_DOT; // The background color of the node if the node is filled
        }
        else
        {
            node_bg_color = RED_BG_COLOR_DOT; // The background color of the node if the node is free
        }

        fprintf(graph_txt, "\tnode_%d[shape = record, style=\"filled\" fillcolor=\"%s\", label =\" {<name> node_%d} | { <f0> prev = %d } |{<here> value = %d}| { <f1> next = %d } \"];\n",
            node_index, node_bg_color, node_index, list_ptr->nodes_arr[node_index].prev, list_ptr->nodes_arr[node_index].value, list_ptr->nodes_arr[node_index].next);
        fprintf(graph_txt, "\tnode_%d -> node_%d [style=invis]\n", node_index, node_index + 1);
    }

    int last_node_index = list_ptr->max_num_of_nodes - 1; // The code below prints the last node (is uniqe one)
    if(last_node_index == list_ptr->tail_node || last_node_index == list_ptr->head_node || (list_ptr->nodes_arr[last_node_index].prev != -1 &&
        list_ptr->nodes_arr[last_node_index].next != -1))
    {
        node_bg_color = BLUE_BG_COLOR_DOT;
    }
    else
    {
        node_bg_color = RED_BG_COLOR_DOT;
    }
    fprintf(graph_txt, "\tnode_%d[shape = record, style=\"filled\" fillcolor=\"%s\", label =\" {<name> node_%d} | { <f0> prev = %d } |{<here> value = %d}| { <f1> next = %d } \"];\n",
        last_node_index, node_bg_color, last_node_index, list_ptr->nodes_arr[last_node_index].prev, list_ptr->nodes_arr[last_node_index].value, list_ptr->nodes_arr[last_node_index].next);

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}

size_t print_node_links_phys(list* list_ptr, char* dir_file_name) // OK
{
    FILE* graph_txt = fopen(dir_file_name, "a+"); 
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_TO_OPEN_GRAPH_TXT)
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    for(size_t node_index = 0; node_index < list_ptr->max_num_of_nodes; node_index++) // Prints all nodes of the list (filled & free)
    {
        if(list_ptr->nodes_arr[node_index].next != -1) // Prints the link between this FILLED node and it's next
        {
            fprintf(graph_txt, "\tnode_%d:f1 -> node_%d:f1[color=\"%s\", label = \"next node\"];\n", node_index, list_ptr->nodes_arr[node_index].next, RED_COLOR_DOT);
        }
        if(list_ptr->nodes_arr[node_index].prev != -1) // Prints the link between this FREE node and it's next
        {
            fprintf(graph_txt, "\tnode_%d:f0 -> node_%d:f0[color=\"%s\", label = \"prev node\"];\n", node_index, list_ptr->nodes_arr[node_index].prev, BLUE_COLOR_DOT);
        }
    }

    if(list_ptr->free_node != -1) // Links the box "Free node" with the free_node of the list_str if it exists
    {
        fprintf(graph_txt, "\tfree_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Free node\"];\n", FREE_NODE_COLOR);
        fprintf(graph_txt, "\tfree_node -> node_%d:<name>[color=\"%s\", label = \"Free node\"];\n\n", list_ptr->free_node, FREE_NODE_COLOR);
    }
    if(list_ptr->head_node != -1) // Links the box "Head node" with the head_node of the list_str if it exists
    {
        fprintf(graph_txt, "\thead_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Head node\"];\n", HEAD_NODE_COLOR);
        fprintf(graph_txt, "\thead_node -> node_%d:<name>[color=\"%s\", label = \"Head node\"];\n\n", list_ptr->head_node, HEAD_NODE_COLOR);
    }
    if(list_ptr->tail_node != -1) // Links the box "Tail node" with the tail_node of the list_str if it exists
    {
        fprintf(graph_txt, "\ttail_node[shape = record, style=\"filled\" fillcolor=\"%s\", label = \"Tail node\"];\n", TAIL_NODE_COLOR);
        fprintf(graph_txt, "\ttail_node -> node_%d:<name>[color=\"%s\", label = \"Tail node\"];\n\n", list_ptr->tail_node, TAIL_NODE_COLOR);
    }

    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_TO_CLOSE_GRAPH_TXT)
        return ERR_TO_CLOSE_GRAPH_TXT;
    }

    return RETURN_OK;
}
