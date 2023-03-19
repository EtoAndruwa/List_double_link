#include "List_double_link.h"

// size_t safe_exit(list* list_ptr, const char* FUNC_NAME, size_t FUNC_LINE, const char* FUNC_FILE, size_t error_code)
// {
//     list_ptr->error_code = error_code;
//     printf("Error code: %ld (%s)\n", list_ptr->error_code, enum_to_string(list_ptr->error_code));
//     list_dump(list_ptr, FUNC_NAME, FUNC_LINE, FUNC_FILE);
//     list_dtor(list_ptr);
//     return error_code);
// }

void push_after(list* list_ptr, size_t node_index, node_val_type value)
{
    list_realloc(list_ptr);
    int new_node_index = list_ptr->free_node;

    if(node_index > list_ptr->max_num_of_nodes - 1)
    {
        // printf("Index is out of array, try again\n");
        return;
    }
    else
    {
        if(list_ptr->head_node == -1)
        {
            list_ptr->head_node = list_ptr->free_node;
            list_ptr->tail_node = list_ptr->free_node;
            list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
            list_ptr->nodes_arr[list_ptr->head_node].value = value;
            list_ptr->nodes_arr[list_ptr->head_node].next = -1;
            list_ptr->nodes_arr[list_ptr->head_node].prev = -1;
            list_ptr->cur_num_of_nodes++;
        }
        else
        {
            if(list_ptr->nodes_arr[node_index].prev == -1 && list_ptr->head_node != node_index)
            {
                printf("Node does not exist");
            }
            else
            {
                if(node_index == list_ptr->tail_node)
                {
                    list_ptr->tail_node = list_ptr->free_node;
                }
                list_ptr->nodes_arr[new_node_index].value = value;
                list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
                list_ptr->nodes_arr[new_node_index].next = list_ptr->nodes_arr[node_index].next;
                list_ptr->nodes_arr[new_node_index].prev = node_index;

                if(list_ptr->nodes_arr[new_node_index].next != -1)
                {
                    list_ptr->nodes_arr[list_ptr->nodes_arr[new_node_index].next].prev = new_node_index;
                }

                list_ptr->nodes_arr[node_index].next = new_node_index;
                list_ptr->cur_num_of_nodes++;
            }
        }
    }

    char* legend = create_legend(__func__ , new_node_index, node_index, value, list_ptr->nodes_arr[node_index].value);
    create_graph_jpg(list_ptr, legend);
}

void push_before(list* list_ptr, size_t node_index, node_val_type value)
{
  list_realloc(list_ptr);
  int new_node_index = list_ptr->free_node;

  if(node_index > list_ptr->max_num_of_nodes - 1)
  {
      // printf("Index is out of array, try again\n");
      return;
  }
  else
  {
      if(list_ptr->head_node == -1)
      {
          list_ptr->head_node = list_ptr->free_node;
          list_ptr->tail_node = list_ptr->free_node;
          list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
          list_ptr->nodes_arr[list_ptr->head_node].value = value;
          list_ptr->nodes_arr[list_ptr->head_node].next = -1;
          list_ptr->nodes_arr[list_ptr->head_node].prev = -1;
          list_ptr->cur_num_of_nodes++;
      }
      else
      {
          if(list_ptr->nodes_arr[node_index].prev == -1 && list_ptr->head_node != node_index)
          {
              printf("Node does not exist");
          }
          else
          {
              if(node_index == list_ptr->head_node)
              {
                  list_ptr->head_node = list_ptr->free_node;
              }
              list_ptr->nodes_arr[new_node_index].value = value;
              list_ptr->free_node = list_ptr->nodes_arr[list_ptr->free_node].next;
              list_ptr->nodes_arr[new_node_index].next = node_index;
              list_ptr->nodes_arr[new_node_index].prev = list_ptr->nodes_arr[node_index].prev;
              if(list_ptr->nodes_arr[node_index].prev != -1)
              {
                  list_ptr->nodes_arr[list_ptr->nodes_arr[node_index].prev].next = new_node_index;
              }
              list_ptr->nodes_arr[node_index].prev = new_node_index;
              list_ptr->cur_num_of_nodes++;
          }
      }
  }

  char* legend = create_legend(__func__ , new_node_index, node_index, value, list_ptr->nodes_arr[node_index].value);
  create_graph_jpg(list_ptr, legend);
}

list* list_ctor(size_t number_of_nodes)
{
    list* list_ptr = (list*)calloc(1, sizeof(list));

    if(list_ptr == nullptr)
    {

    }

    list_ptr->cur_num_of_nodes = 0;
    list_ptr->max_num_of_nodes = number_of_nodes;
    list_ptr->nodes_arr = (node*)calloc(list_ptr->max_num_of_nodes, sizeof(node));

    if(list_ptr->nodes_arr == nullptr)
    {

    }

    for(size_t i = 0; i < list_ptr->max_num_of_nodes; i++)
    {
        if(i == (list_ptr->max_num_of_nodes - 1))
        {

            list_ptr->nodes_arr[i].next  = -1;
            list_ptr->nodes_arr[i].prev  = -1;
            list_ptr->nodes_arr[i].value = POISON;
        }
        else
        {
            list_ptr->nodes_arr[i].next  = i + 1;
            list_ptr->nodes_arr[i].prev  = -1;
            list_ptr->nodes_arr[i].value = POISON;
        }
    }

    list_ptr->head_node = -1;
    list_ptr->free_node =  0;
    list_ptr->tail_node = -1;

    list_ptr->error_code = LIST_OK;
}

void list_dtor(list* list_ptr)
{

    for(size_t i = 0; i < list_ptr->cur_num_of_nodes; i++)
    {
        list_ptr->nodes_arr[i].next  = POISON;
        list_ptr->nodes_arr[i].prev  = POISON;
        list_ptr->nodes_arr[i].value = POISON;
    }

    free(list_ptr->nodes_arr);
    list_ptr->nodes_arr = nullptr;

    list_ptr->head_node = POISON;
    list_ptr->error_code = POISON;
    list_ptr->cur_num_of_nodes = POISON;
    list_ptr->max_num_of_nodes = POISON;

    free(list_ptr);
    list_ptr = nullptr;
}

size_t list_realloc(list* list_ptr)
{
    if(list_ptr->cur_num_of_nodes == list_ptr->max_num_of_nodes)
    {
        node* realloc_ptr = (node*)realloc(list_ptr->nodes_arr, list_ptr->max_num_of_nodes * 2 * sizeof(node));

        if(realloc_ptr == nullptr)
        {
            return ERR_LIST_FULL; // Realloc doesn't take place
        }
        else
        {
            list_ptr->max_num_of_nodes *= 2;
            list_ptr->nodes_arr = realloc_ptr;

            for(size_t i = list_ptr->cur_num_of_nodes; i < list_ptr->max_num_of_nodes; i++)
            {
                if(i == (list_ptr->max_num_of_nodes - 1))
                {

                    list_ptr->nodes_arr[i].next  = -1;
                    list_ptr->nodes_arr[i].prev  = -1;
                    list_ptr->nodes_arr[i].value = POISON;
                }
                else
                {
                    list_ptr->nodes_arr[i].next  = i + 1;
                    list_ptr->nodes_arr[i].prev  = -1;
                    list_ptr->nodes_arr[i].value = POISON;
                }
            }
            list_ptr->free_node = list_ptr->cur_num_of_nodes;
            return REALLOC_TRUE; // Realloc took place
        }
    }
    else
    {
        return REALLOC_FALSE;
    }
}

size_t delete_node(list* list_ptr, size_t node_index)
{
    int node_value = list_ptr->nodes_arr[node_index].value;
    int next_node_index = list_ptr->nodes_arr[node_index].next;
    int prev_node_index = list_ptr->nodes_arr[node_index].prev;

    if(node_index == list_ptr->tail_node && list_ptr->cur_num_of_nodes != 1)
    {
        list_ptr->tail_node = list_ptr->nodes_arr[node_index].prev;
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[node_index].next = list_ptr->free_node;
        list_ptr->nodes_arr[list_ptr->tail_node].next = -1;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
    }
    else if(node_index == list_ptr->head_node && list_ptr->cur_num_of_nodes != 1)
    {
        list_ptr->head_node = list_ptr->nodes_arr[node_index].next;
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[next_node_index].prev  = -1;
        list_ptr->nodes_arr[node_index].next = list_ptr->free_node;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
    }
    else if(list_ptr->tail_node == list_ptr->head_node)
    {
        list_ptr->nodes_arr[node_index].value = POISON;
        list_ptr->nodes_arr[node_index].next  = list_ptr->free_node;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
        list_ptr->head_node = -1;
        list_ptr->tail_node = -1;
    }
    else
    {
        list_ptr->nodes_arr[node_index].value = POISON;
        if(list_ptr->nodes_arr[node_index].prev != -1)
        {
            list_ptr->nodes_arr[next_node_index].prev = list_ptr->nodes_arr[node_index].prev;
        }
        if(list_ptr->nodes_arr[node_index].next != -1)
        {
            list_ptr->nodes_arr[prev_node_index].next = list_ptr->nodes_arr[node_index].next;
        }
        list_ptr->nodes_arr[node_index].next  = list_ptr->free_node;
        list_ptr->nodes_arr[node_index].prev = -1;
        list_ptr->free_node = node_index;
    }
    list_ptr->cur_num_of_nodes--;

    char* legend = create_legend(__func__ , 0, node_index, 0, node_value);
    create_graph_jpg(list_ptr, legend);
}

size_t search_physical(list* list_ptr, int value)
{
    int current_node = list_ptr->head_node;
    size_t flag_found = 0;

    while(current_node != -1)
    {
        if(list_ptr->nodes_arr[current_node].value == value)
        {
            printf("Node with value %d was found on logical id %d\n", value, current_node);
            flag_found = 1;
        }
         current_node = list_ptr->nodes_arr[current_node].next;
    }

    if(flag_found == 0)
    {
        printf("Node with value %d was not found\n", value);
    }
}

size_t search_logical(list* list_ptr, int value)
{
    int current_node = list_ptr->head_node;
    int logical_id = 0;
    size_t flag_found = 0;

    while(current_node != -1)
    {
        if(list_ptr->nodes_arr[current_node].value == value)
        {
            printf("Node with value %d was found on logical id %d\n", value, logical_id);
            flag_found = 1;
        }
        logical_id++;
         current_node = list_ptr->nodes_arr[current_node].next;
    }

    if(flag_found == 0)
    {
        printf("Node with value %d was not found\n", value);
    }
}

size_t get_phys_by_log(list* list_ptr, int logical_index)
{
    if(check_is_linear(list_ptr) != NON_LINEAR)
    {
        printf("\n\nIS LINEAR!\n\n");
        printf("get_phys_by_log: Node with logical id %d was found with physical id %d\n", logical_index, logical_index);
        return 0;
    }

    int current_node = list_ptr->head_node;
    int logical_id = 0;
    size_t flag_found = 0;

    while(current_node != -1)
    {
        if(logical_id == logical_index)
        {
            printf("get_phys_by_log: Node with logical id %d was found with physical id %d\n", logical_index, current_node);
            return current_node;
            flag_found = 1;
        }
        logical_id++;
        current_node = list_ptr->nodes_arr[current_node].next;
    }

    if(flag_found == 0)
    {
        printf("Node with logical id %d was not found\n", logical_index);
        return NODE_DOES_NOT_EXIST;
    }
}

size_t get_log_by_phys(list* list_ptr, int physical_index)
{
    if(check_is_linear(list_ptr) != NON_LINEAR)
    {
        printf("get_log_by_phys: Node with physical id %d was found with logical id %d\n", physical_index, physical_index);
        return physical_index;
    }

    int current_node = list_ptr->head_node;
    int logical_id = 0;

    while(current_node != -1)
    {
        if(current_node == physical_index)
        {
            printf("get_log_by_phys: Node with physical id %d was found with logical id %d\n", current_node, logical_id);
            return logical_id;
        }
        logical_id++;
        current_node = list_ptr->nodes_arr[current_node].next;
    }

    printf("Node with physical id %d was not found\n", physical_index);
    return NODE_DOES_NOT_EXIST;
}

size_t make_linear(list* list_ptr)
{
    if(check_is_linear(list_ptr) != NON_LINEAR)
    {
        return IS_LINEAR;
    }

    for(size_t node_index = 0; node_index < list_ptr->cur_num_of_nodes; node_index++)
    {
        put_to_correct_phys(list_ptr, node_index);
    }
}

void put_to_correct_phys(list* list_ptr, int first_logical_index)
{
    int first_node = get_phys_by_log(list_ptr, first_logical_index); // physical index of first node

    if(first_node == first_logical_index)
    {
        return;
    } 
    else
    {
        int second_node = get_log_by_phys(list_ptr, first_logical_index); // if the node is free one
        if(second_node == NODE_DOES_NOT_EXIST) // is not free
        {
            int second_next = list_ptr->nodes_arr[first_logical_index].next; // next free node
            int second_prev = get_prev_free(list_ptr, first_logical_index);  // prev of the this free node
            int first_prev = list_ptr->nodes_arr[first_node].prev;
            int first_next = list_ptr->nodes_arr[first_node].next;

            list_ptr->nodes_arr[first_logical_index].value = list_ptr->nodes_arr[first_node].value;
            list_ptr->nodes_arr[first_logical_index].next  = first_next;
            list_ptr->nodes_arr[first_logical_index].prev  = first_prev;
            list_ptr->nodes_arr[first_prev].next = first_logical_index;
            list_ptr->nodes_arr[first_next].prev = first_logical_index;

            list_ptr->nodes_arr[first_node].value = POISON;
            list_ptr->nodes_arr[first_node].prev = -1;
            list_ptr->nodes_arr[first_node].next = second_next;
            list_ptr->nodes_arr[second_prev].next = first_node;

            if(first_logical_index == list_ptr->free_node)
            {
                list_ptr->free_node = first_node;
            }
            if(first_node == list_ptr->tail_node)
            {
                list_ptr->tail_node = first_logical_index;
            }
            if(first_node == list_ptr->head_node)
            {
                list_ptr->head_node = first_logical_index;
            }
        }
        else    
        {


        }
    }

    create_graph_jpg(list_ptr, "put");
}

size_t check_is_linear(list* list_ptr)
{   
    int current_node = list_ptr->head_node;
    int logical_number = 0;
    while(current_node != -1)
    {
        if(current_node != logical_number)
        {   
            return NON_LINEAR;
        }   
        current_node = list_ptr->nodes_arr[current_node].next;
        logical_number++;
    }
}

void exchange_nodes(list* list_ptr, int first_node, int second_node)
{
    int second_value = list_ptr->nodes_arr[second_node].value;
    int second_next = list_ptr->nodes_arr[second_node].next;
    int second_prev = list_ptr->nodes_arr[second_node].prev;

    int first_prev = list_ptr->nodes_arr[first_node].prev;
    int first_next = list_ptr->nodes_arr[first_node].next;

    list_ptr->nodes_arr[second_node].value = list_ptr->nodes_arr[first_node].value;
    list_ptr->nodes_arr[first_node].value = second_value;

    list_ptr->nodes_arr[first_prev].next = second_node;
    list_ptr->nodes_arr[second_next].prev = first_node;
    
    list_ptr->nodes_arr[second_node].prev =  first_prev;
    list_ptr->nodes_arr[second_node].next =  first_node;

    list_ptr->nodes_arr[first_node].next = second_next;
    list_ptr->nodes_arr[first_node].prev = second_node;

    create_graph_jpg(list_ptr, "exchange");
}

size_t get_prev_free(list* list_ptr, int this_free_index)
{
    int current_node = list_ptr->free_node;
    while(current_node != -1)
    {
        if(list_ptr->nodes_arr[current_node].next == this_free_index )
        {
            return current_node;
        }
        current_node = list_ptr->nodes_arr[current_node].next;
    }
}

