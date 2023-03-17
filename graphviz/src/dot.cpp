#include "graphviz.h"

static size_t number_of_images = 0; // global variable in order to count the number of jpg files

size_t graph_start(char* file_name) // writes the start of the .txt file
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        printf("ERROR_TO_OPEN");
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    fprintf(graph_txt, "\n");
    fprintf(graph_txt, "digraph\n");
    fprintf(graph_txt, "{\n");
    fprintf(graph_txt, "\trankdir=%s;\n", RANKDIR_DOT);

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t graph_end(char* file_name) // writes the end of the .txt file 
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    fprintf(graph_txt, "}\n");

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t html_end(char* file_name) // writes the end of the html file
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {   
        ERROR_MESSAGE(stderr, 1)
    }
    fprintf(graph_txt, "</pre></html>\n");

    if(fclose(graph_txt) == EOF)
    {
        
    }
}

size_t hmtl_start(char* file_name) // writes the start of the html file 
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        
    }
    fprintf(graph_txt, "<!DOCTYPE HTML><pre>\n");

    if(fclose(graph_txt) == EOF)
    {
        
    }
}

size_t print_node_data(list* list_ptr, char* file_name) // prints all datta about the list 
{
    FILE* graph_txt = fopen(file_name, "a+");   
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    for(size_t i = 0; i < list_ptr->max_num_of_nodes; i++)
    {
        fprintf(graph_txt, "\tnode_%d[shape = record, style=\"filled\" fillcolor=\"%s\", label =\" {node_%d} | { <f0> prev = %d } |{<here> value = %d}| { <f1> next = %d } \"];\n", i, BLUE_BG_COLOR_DOT, i, list_ptr->nodes_arr[i].value, 
        list_ptr->nodes_arr[i].prev, list_ptr->nodes_arr[i].next);
    }


    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t print_node_links(list* list_ptr, char* file_name) // prints all the links of the list 
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    int next_node = list_ptr->head_node;

    while(next_node != -1)
    {
        if(list_ptr->nodes_arr[next_node].next != -1)
        {
            fprintf(graph_txt, "\tnode_%d:f1 -> node_%d:f1[color=\"%s\", label = \"next node\"];\n", next_node, list_ptr->nodes_arr[next_node].next, RED_COLOR_DOT);
        }
        if(list_ptr->nodes_arr[next_node].prev != -1)
        {
            fprintf(graph_txt, "\tnode_%d:f0 -> node_%d:f0[color=\"%s\", label = \"previous node\"];\n", list_ptr->nodes_arr[next_node].prev, next_node, BLUE_COLOR_DOT);
        }

        next_node = list_ptr->nodes_arr[next_node].next;
    }

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t create_graph_jpg(list* list_ptr) // prints all data about the list into the .txt file
{
    char int_str_equivalent[11] = {};
    sprintf(int_str_equivalent, "%d", number_of_images);
    char* file_name = cat_file_directory(OUTPUT_NAME, "", int_str_equivalent);

    char* dir_file_name = cat_file_directory(file_name, TXT_FOLDER, INPUT_FORMAT);

    graph_start(dir_file_name);
    print_legend("", dir_file_name);
    print_node_data(list_ptr, dir_file_name);
    print_node_links(list_ptr, dir_file_name);
    print_h_t_f_data(list_ptr, dir_file_name);
    graph_end(dir_file_name);

    system_dot(file_name);

    free(dir_file_name);
    dir_file_name = nullptr;

    free(file_name);
    file_name = nullptr;

    number_of_images++;

    return 0;
}

char* cat_file_directory(char* file_name, char* dir, char* format) // cats the file name, dir path and extension into the one string
{
    size_t size_of_file_name = strlen(file_name) + 1;
    size_t size_of_dir_name = strlen(dir) + 1;
    size_t size_of_input_format = strlen(dir) + 1;

    char* dir_file_name = (char*)calloc(size_of_dir_name + size_of_file_name + size_of_input_format, sizeof(char));

    if(dir_file_name == nullptr)
    {

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

    return 0;
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
}

char* get_tokens_into_buf() // reads all tokens into the buffer
{
    char* dir_file_name = cat_file_directory("image_list.txt", DIR_TO_DUMPS, "");
    FILE* image_list = fopen(dir_file_name, "r");
    if(image_list == nullptr)
    {
        ERROR_MESSAGE(stderr, 1);
    }
    size_t size_of_file = get_size_file();

    char* buffer_ptr = (char*)calloc(1, sizeof(char) * (size_of_file + 1)); 

    fread(buffer_ptr, sizeof(char), size_of_file, image_list);

    buffer_ptr[size_of_file] = '\0'; // Makes form the file_struct_ptr null-terminated string

    if(fclose(image_list) == EOF)
    {
        ERROR_MESSAGE(stderr, 1);
    }

    return buffer_ptr;
}

size_t get_size_file() // gets the size of the file
{
    char* dir_file_name = cat_file_directory("image_list.txt", DIR_TO_DUMPS, "");
    FILE* image_list = fopen(dir_file_name, "r");
    if(image_list == nullptr)
    {
        ERROR_MESSAGE(stderr, 1);
    }

    fseek(image_list, 0, SEEK_END); // Puts the pointer inside the file_struct_ptr to the end of it
    size_t size = ftell(image_list); // Get the size of the file_struct_ptr with '\r'!

    if(fclose(image_list) == EOF)
    {
        ERROR_MESSAGE(stderr, 1);
    }

    return size;
}

size_t get_tokens(char* buffer, FILE* file_tpr) // prints all the tokens into the file (the path to the image)
{
    char* token = strtok(buffer," \n\r");

    while (token != NULL)                        
    {   
        fprintf(file_tpr, "<h2>The image below%s</h2>\n", token);
        fprintf(file_tpr, "<img src=\"%s\" alt=\"%s \">\n", token, token);
        token = strtok(NULL, " \n\r");
    }
}

size_t print_legend(char* legen_text, char* dir_file_name)
{
    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(strlen(legen_text) == 0)
    {   
        fprintf(graph_txt, "\tnode_legend[shape = record, label = \"%s\"];\n", DEFAULT_LEGEND_TEXT);
    }
    else    
    {
        fprintf(graph_txt, "\tnode_legend[shape=record , label = \"%s\"];\n", legen_text);
    }
    
       
    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t print_h_t_f_data(list* list_ptr, char* file_name)
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(list_ptr->free_node != -1)
    {
        fprintf(graph_txt, "\tfree_node -> node_%d:f1[color=\"%s\", label = \"Free node\"];\n", list_ptr->free_node, GREEN_COLOR_DOT);
    }
    if(list_ptr->head_node != -1)
    {
        fprintf(graph_txt, "\thead_node -> node_%d:f1[color=\"%s\", label = \"Head node\"];\n", list_ptr->head_node, GREEN_COLOR_DOT);
    }
    if(list_ptr->tail_node != -1)
    {
        fprintf(graph_txt, "\ttail_node -> node_%d:f1[color=\"%s\", label = \"Tail node\"];\n", list_ptr->tail_node, GREEN_COLOR_DOT);
    }

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

