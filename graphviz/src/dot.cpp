#include "dot.h"

size_t graph_start(char* file_name)
{
    FILE* graph_txt = fopen(file_name, "a+");
    if(graph_txt == nullptr)
    {
        return ERR_TO_OPEN_GRAPH_TXT;
    }
    fprintf(graph_txt, "<!DOCTYPE HTML><pre>\n");
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
    fprintf(graph_txt, "</pre></html>\n");

    if(fclose(graph_txt) == EOF)
    {
        return ERR_TO_CLOSE_GRAPH_TXT;
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
    graph_start(file_name);
    graph_end(file_name);
}

void cat_file_directory(char* file_name)
{
    printf("sizeof_dir %d \n", strlen(DIR_TO_DUMPS));
}

