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
        return 0;
    }

    int current_node = list_ptr->head_node;
    int logical_id = 0;
    size_t flag_found = 0;

    while(current_node != -1)
    {
        if(logical_id == logical_index)
        {
            return current_node;
            flag_found = 1;
        }
        logical_id++;
        current_node = list_ptr->nodes_arr[current_node].next;
    }

    if(flag_found == 0)
    {
        return NODE_DOES_NOT_EXIST;
    }
}

size_t get_log_by_phys(list* list_ptr, int physical_index)
{
    if(check_is_linear(list_ptr) != NON_LINEAR)
    {
        return physical_index;
    }

    int current_node = list_ptr->head_node;
    int logical_id = 0;

    while(current_node != -1)
    {
        if(current_node == physical_index)
        {
            return logical_id;
        }
        logical_id++;
        current_node = list_ptr->nodes_arr[current_node].next;
    }

    return NODE_DOES_NOT_EXIST;
}

size_t make_linear(list* list_ptr)
{
    if(check_is_linear(list_ptr) != NON_LINEAR)
    {
        return IS_LINEAR;
    }

    if(list_ptr->tail_node == 0 && list_ptr->head_node == list_ptr->cur_num_of_nodes - 1)
    {
        change_head_tail(list_ptr, list_ptr->head_node, list_ptr->tail_node);
    }
    else if((list_ptr->tail_node < list_ptr->head_node || list_ptr->tail_node == 0) && (list_ptr->head_node != list_ptr->cur_num_of_nodes - 1))
    {
        put_tail(list_ptr);
        put_head(list_ptr);
    }
    else    
    {
        put_head(list_ptr);
        put_tail(list_ptr);
    }

    for(size_t logc_index = 1; logc_index < list_ptr->cur_num_of_nodes - 1; logc_index++)
    {
        int phys_index = get_phys_by_log(list_ptr, logc_index);

        if(phys_index == NODE_DOES_NOT_EXIST)
        {
            put_to_free(list_ptr, logc_index, phys_index);
        }
        else if(list_ptr->nodes_arr[logc_index].prev == phys_index)
        {
            exchange_neighbor(list_ptr, phys_index, logc_index);
        }
        else
        {
            exchange_stranger(list_ptr, phys_index, logc_index);
        }
    }
}

size_t check_is_linear(list* list_ptr) // checks the index for being linear
{   
    int node_phys_index = list_ptr->head_node;
    int node_logc_index = 0;

    while(node_logc_index != -1)
    {
        if(node_phys_index != node_logc_index)
        {   
            return NON_LINEAR;
        }   
        node_phys_index = list_ptr->nodes_arr[node_phys_index].next;
        node_logc_index++;
    }
    
    return IS_LINEAR;
}

void exchange_stranger(list* list_ptr, int first_node, int second_node)
{   
    if(first_node == second_node)
    {
        return;
    }
    int second_value = list_ptr->nodes_arr[second_node].value;
    int second_next = list_ptr->nodes_arr[second_node].next;
    int second_prev = list_ptr->nodes_arr[second_node].prev;

    int first_prev = list_ptr->nodes_arr[first_node].prev;
    int first_next = list_ptr->nodes_arr[first_node].next;
    int first_value = list_ptr->nodes_arr[first_node].value;

    list_ptr->nodes_arr[second_node].value = first_value;
    list_ptr->nodes_arr[first_node].value = second_value;

    if(first_prev != -1)
    {
        list_ptr->nodes_arr[first_prev].next = second_node;
    }
    if(first_next != -1)
    {
        list_ptr->nodes_arr[first_next].prev = second_node;
    }
    if(second_next != -1)
    {
        list_ptr->nodes_arr[second_next].prev = first_node;
    } 
    if(second_prev != -1)
    {
        list_ptr->nodes_arr[second_prev].next = first_node;
    } 
    
    list_ptr->nodes_arr[second_node].prev =  first_prev;
    list_ptr->nodes_arr[second_node].next =  first_next;

    list_ptr->nodes_arr[first_node].next = second_next;
    list_ptr->nodes_arr[first_node].prev = second_prev;

    char* legend = create_legend(__func__, first_node, first_value, second_node, second_value);
    create_graph_jpg(list_ptr, legend);
}

void exchange_neighbor(list* list_ptr, int first_node, int second_node)
{
    if(first_node == second_node)
    {
        return;
    }
    int second_value = list_ptr->nodes_arr[second_node].value;
    int second_next  = list_ptr->nodes_arr[second_node].next;
    int second_prev  = list_ptr->nodes_arr[second_node].prev;

    int first_prev  = list_ptr->nodes_arr[first_node].prev;
    int first_next  = list_ptr->nodes_arr[first_node].next;
    int first_value = list_ptr->nodes_arr[first_node].value;

    list_ptr->nodes_arr[second_node].value = list_ptr->nodes_arr[first_node].value;
    list_ptr->nodes_arr[first_node].value = second_value;

    if(first_prev != -1)
    {
        list_ptr->nodes_arr[first_prev].next = second_node;
    }
    if(second_next != -1)
    {
        list_ptr->nodes_arr[second_next].prev = first_node;
    }   
    
    list_ptr->nodes_arr[second_node].prev =  first_prev;
    list_ptr->nodes_arr[second_node].next =  first_node;

    list_ptr->nodes_arr[first_node].next = second_next;
    list_ptr->nodes_arr[first_node].prev = second_node;

    char* legend = create_legend(__func__, first_node, first_value, second_node, second_value);
    create_graph_jpg(list_ptr, legend);
}

void put_to_free(list* list_ptr, int first_logical_index, int first_phys_index)
{
    int second_next = list_ptr->nodes_arr[first_logical_index].next; // next free node
    int second_prev = get_prev_free(list_ptr, first_logical_index);  // prev of the this free node
    int first_prev = list_ptr->nodes_arr[first_phys_index].prev;
    int first_next = list_ptr->nodes_arr[first_phys_index].next;

    list_ptr->nodes_arr[first_logical_index].value = list_ptr->nodes_arr[first_phys_index].value;
    list_ptr->nodes_arr[first_logical_index].next  = first_next;
    list_ptr->nodes_arr[first_logical_index].prev  = first_prev;
    list_ptr->nodes_arr[first_prev].next = first_logical_index;
    list_ptr->nodes_arr[first_next].prev = first_logical_index;

    list_ptr->nodes_arr[first_phys_index].value = POISON;
    list_ptr->nodes_arr[first_phys_index].prev = -1;
    list_ptr->nodes_arr[first_phys_index].next = second_next;
    list_ptr->nodes_arr[second_prev].next = first_phys_index;

    if(first_logical_index == list_ptr->free_node)
    {
        list_ptr->free_node = first_phys_index;
    }
    if(first_phys_index == list_ptr->tail_node)
    {
        list_ptr->tail_node = first_logical_index;
    }
    if(first_phys_index == list_ptr->head_node)
    {
        list_ptr->head_node = first_logical_index;
    }
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

size_t put_head(list* list_ptr)
{
    int first_node_id = 0;
    int second_node = get_log_by_phys(list_ptr, 0); // if the node is free one

    if(first_node_id == list_ptr->head_node)
    {
        return 0;
    }
    else if(second_node == NODE_DOES_NOT_EXIST) // is not free
    {
        put_to_free(list_ptr, 0, list_ptr->head_node);
    }
    else    
    {
        int first_node_val  = list_ptr->nodes_arr[first_node_id].value;
        int first_node_prev = list_ptr->nodes_arr[first_node_id].prev;
        int first_node_next = list_ptr->nodes_arr[first_node_id].next;

        int head_id   = list_ptr->head_node;
        int head_next = list_ptr->nodes_arr[list_ptr->head_node].next;

        list_ptr->nodes_arr[first_node_id].prev  = -1;
        list_ptr->nodes_arr[first_node_id].value = list_ptr->nodes_arr[head_id].value;
        list_ptr->nodes_arr[head_id].value = first_node_val;

        if(first_node_prev == head_id)
        {
            list_ptr->nodes_arr[head_id].next  = first_node_next;
            list_ptr->nodes_arr[head_id].prev  = first_node_id;
            list_ptr->nodes_arr[first_node_id].prev  = -1;
            list_ptr->nodes_arr[first_node_id].next = head_id;
            list_ptr->nodes_arr[first_node_next].prev = head_id;
        }
        else
        {
            list_ptr->nodes_arr[head_id].next  = first_node_next;
            list_ptr->nodes_arr[head_id].prev  = first_node_prev;

            list_ptr->nodes_arr[first_node_id].next = head_next;
            list_ptr->nodes_arr[first_node_id].prev = -1;

            list_ptr->nodes_arr[head_next].prev = first_node_id;
            list_ptr->nodes_arr[first_node_prev].next = head_id;
            list_ptr->nodes_arr[first_node_next].prev = head_id;
        }

        list_ptr->head_node = first_node_id;
    }

    create_graph_jpg(list_ptr, "put head");
}

size_t put_tail(list* list_ptr)
{
    int max_node_id = list_ptr->cur_num_of_nodes - 1;
    int second_node = get_log_by_phys(list_ptr, max_node_id); // if the node is free one

    if(max_node_id == list_ptr->tail_node)
    {
        return 0;
    }
    else if(second_node == NODE_DOES_NOT_EXIST) // is not free
    {
        put_to_free(list_ptr, list_ptr->tail_node, max_node_id);
    }
    else    
    {
        int last_node_val  = list_ptr->nodes_arr[max_node_id].value;
        int last_node_prev = list_ptr->nodes_arr[max_node_id].prev;
        int last_node_next = list_ptr->nodes_arr[max_node_id].next;

        int tail_id   = list_ptr->tail_node;
        int tail_prev = list_ptr->nodes_arr[list_ptr->tail_node].prev;
        list_ptr->tail_node = max_node_id;

        list_ptr->nodes_arr[max_node_id].next  = -1;
        list_ptr->nodes_arr[max_node_id].value = list_ptr->nodes_arr[tail_id].value;
        list_ptr->nodes_arr[tail_id].value = last_node_val;

        if(last_node_next == tail_id)
        {
            list_ptr->nodes_arr[tail_id].next  = max_node_id;
            list_ptr->nodes_arr[tail_id].prev  = last_node_prev;
            list_ptr->nodes_arr[max_node_id].prev    = tail_id;
            list_ptr->nodes_arr[last_node_prev].next = tail_id;
        }
        else
        {
            list_ptr->nodes_arr[tail_id].next  = last_node_next;
            list_ptr->nodes_arr[tail_id].prev  = last_node_prev;

            list_ptr->nodes_arr[last_node_prev].next = tail_id;
            list_ptr->nodes_arr[last_node_next].prev = tail_id;

            list_ptr->nodes_arr[max_node_id].prev = tail_prev;
            list_ptr->nodes_arr[tail_prev].next   = max_node_id;
        }
    }

    create_graph_jpg(list_ptr, "put tail");
}

void change_head_tail(list* list_ptr, int head_id, int tail_id)
{
    int tail_prev = list_ptr->nodes_arr[tail_id].prev;
    int tail_val  = list_ptr->nodes_arr[tail_id].value;
    int head_next = list_ptr->nodes_arr[head_id].next;

    list_ptr->nodes_arr[tail_id].value = list_ptr->nodes_arr[head_id].value;
    list_ptr->nodes_arr[tail_id].next = list_ptr->nodes_arr[head_id].next;
    list_ptr->nodes_arr[tail_id].prev = -1;

    list_ptr->nodes_arr[tail_prev].next = head_id;
    list_ptr->nodes_arr[head_next].prev = tail_id;
    list_ptr->nodes_arr[head_id].value = tail_val;
    list_ptr->nodes_arr[head_id].prev = tail_prev;
    list_ptr->nodes_arr[head_id].next = -1;

    list_ptr->head_node = tail_id;
    list_ptr->tail_node = head_id;

    create_graph_jpg(list_ptr, "change_head_tail");
}

