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
    if(graph_txt != nullptr)
    {   
        ERROR_MESSAGE(stderr, 1)
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
    fprintf(graph_txt, "<!DOCTYPE HTML><pre>\n");

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

    // system_dot(dir_file_name);

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

size_t create_hmtl(char* file_name)
{
    char* dir_file_name = cat_file_directory(file_name, DIR_TO_DUMPS, HTML);

    hmtl_start(dir_file_name);
    html_end(dir_file_name);

    return 0;
}

// char* system_dot(char* dir_file_name)
// {
//     char dot[] = "dot ";

//     system("dot ./graph.txt -Tjpg -o graph.jpg");
// }

