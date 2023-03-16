#include "graphviz.h"

size_t graph_start(char* file_name)
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
    fprintf(graph_txt, "\tnode_\n");


    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
    }
}

size_t graph_end(char* file_name)
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

size_t html_end(char* file_name)
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {   
        // ERROR_MESSAGE(stderr, 1)
    }
    fprintf(graph_txt, "</pre></html>\n");

    if(fclose(graph_txt) == EOF)
    {
        
    }
}

size_t hmtl_start(char* file_name)
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        
    }
    fprintf(graph_txt, "<!DOCTYPE HTML><pre> asdasdasdad\n");

    if(fclose(graph_txt) == EOF)
    {
        
    }
}

// size_t print_node_data(node* node_ptr, char* file_name)
// {
//     FILE* graph_txt = fopen(file_name, "a+");
//     if(graph_txt == nullptr)
//     {
//         return ERR_TO_OPEN_GRAPH_TXT;
//     }

//     if(node_ptr != nullptr)
//     {
//         if(node_ptr->parent_node == nullptr)
//         {
//             fprintf(graph_txt, "\tnode_%d[shape = record, label =\" { <f0> left_child = %p } | { <here> value = %d \\n | parent = %p } | { <f1> right_child = %p } \", style=\"filled\", fillcolor=\"lightgrey\"];\n", node_ptr->node_value, node_ptr->left_child, node_ptr->node_value, node_ptr->parent_node, node_ptr->right_child);
//         }
//         else
//         {
//             fprintf(graph_txt, "\tnode_%d[shape = record, label =\" { <f0> left_child = %p } | { <here> value = %d \\n | parent = %p } | { <f1> right_child = %p } \"];\n", node_ptr->node_value, node_ptr->left_child, node_ptr->node_value, node_ptr->parent_node, node_ptr->right_child);
//         }
//         if(node_ptr->left_child != nullptr)
//         {
//             print_node_data(tree_struct, node_ptr->left_child, file_name);
//         }
//         if(node_ptr->right_child != nullptr)
//         {
//             print_node_data(tree_struct, node_ptr->right_child, file_name);
//         }
//     }

//     if(fclose(graph_txt) == EOF)
//     {
//         return ERR_TO_CLOSE_GRAPH_TXT;
//     }
// }

// size_t print_node_links(node* node_ptr, char* file_name)
// {
//     FILE* graph_txt = fopen(file_name, "a+");
//     if(graph_txt == nullptr)
//     {
//         return ERR_TO_OPEN_GRAPH_TXT;
//     }

//     if(node_ptr->left_child != nullptr)
//     {
//         fprintf(graph_txt, "\tnode_%d:f0 -> node_%d:here[color=\"blue\", label = \"left_child\"];\n", node_ptr->node_value, node_ptr->left_child->node_value);
//         print_node_links(tree_struct, node_ptr->left_child, file_name);
//     }
//     if(node_ptr->right_child != nullptr)
//     {
//         fprintf(graph_txt, "\tnode_%d:f1 -> node_%d:here[color=\"red\", label = \"right_child\"];\n", node_ptr->node_value, node_ptr->right_child->node_value);
//         print_node_links(tree_struct, node_ptr->right_child, file_name);
//     }
//     // if(node_ptr->parent_node != nullptr)
//     // {
//     //     fprintf(graph_txt, "\tnode_%d -> node_%d[color=\"green\", label = \"parent\"];\n", node_ptr->node_value, node_ptr->parent_node->node_value);
//     // }

//     if(fclose(graph_txt) == EOF)
//     {
//         return ERR_TO_CLOSE_GRAPH_TXT;
//     }
// }

size_t create_graph_jpg(char* file_name)
{
    char* dir_file_name = cat_file_directory(file_name, TXT_FOLDER, INPUT_FORMAT);

    graph_start(dir_file_name);
    graph_end(dir_file_name);

    system_dot(file_name);

    free(dir_file_name);
    dir_file_name = nullptr;

    return 0;
}

char* cat_file_directory(char* file_name, char* dir, char* format)
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

    printf("%s \n\n", dir_file_name);

    return dir_file_name;
}

size_t create_html(char* file_name)
{
    char* dir_file_name = cat_file_directory(file_name, DIR_TO_DUMPS, HTML);

    hmtl_start(dir_file_name);
    add_image_to_html(dir_file_name);
    html_end(dir_file_name);

    // open_in_chrome(dir_file_name);

    free(dir_file_name);
    dir_file_name = nullptr;    

    return 0;
}

char* system_dot(char* file_name)
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

size_t add_to_image_list(char* file_name)
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

size_t add_image_to_html(char* dir_file_name)
{
    FILE* graph_txt = fopen(dir_file_name, "a+");
    if(graph_txt == nullptr)
    {
        ERROR_MESSAGE(stderr, 1);
    }
    
    get_size_file();
    char* buffer = get_tokens_into_buf();
    get_tokens(buffer, graph_txt);


    if(fclose(graph_txt) == EOF)
    {
        ERROR_MESSAGE(stderr, 1);
    }
}

// void open_in_chrome(char* file_name)
// {
//     char* chrome = "explorer.exe ";

//     size_t size_of_chrome = strlen(chrome) + 1;
//     size_t size_of_file   = strlen(file_name) + 1;

//     char* cmd = (char*)calloc(size_of_chrome + size_of_file, sizeof(char));

//     strcpy(cmd, chrome);
//     strcat(cmd, file_name);

//     printf("\n\n%s\n\n", cmd);

//     system(cmd);

//     free(cmd);
//     cmd = nullptr;
// }

char* get_tokens_into_buf() 
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

size_t get_size_file() 
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

size_t get_tokens(char* buffer, FILE* file_tpr) 
{
    char* token = strtok(buffer," \n\r");

    while (token != NULL)                        
    {   
        fprintf(file_tpr, "<img src=\"%s\" alt=\"%s \">\n", token, token);
        token = strtok(NULL, " \n\r");
    }
}
