#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

/* Error type */


/* Typedef data type */
typedef char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;


/**
 * @brief define data structure
 * 
 */

/* static link-list */
typedef uint32_t k_static_node_t;

struct static_link {
    k_static_node_t next;
    void *data;
};

typedef struct static_link k_static_link_t;

/* single link-list */
struct single_node {
    struct single_node *next;
};

typedef struct single_node k_snode_t;

struct single_list{
    k_snode_t *tail, *head;
};

typedef struct single_list k_slist_t;

/* double link-list */
struct double_list {
    union {
        struct double_list *head;
        struct double_list *next;
    };
    union {
        struct double_list *tail;
        struct double_list *prev;
    };
};

typedef struct double_list double_list_t;
typedef struct double_list dlist_node_t;


/* static stack */
typedef long unsigned int stack_data_t;

struct stack {
    stack_data_t *top, *next, *base;
    uint32_t stack_size;
};

typedef struct stack k_stack_t;

/* static queue */

struct queue {
    k_slist_t *slist;
};

typedef struct queue k_queue_t;

/**
 * @brief function define
 * 
 */
/* static list */
void k_static_list_init(k_static_link_t *pbuffer, k_static_node_t size);
void k_static_list_insert(k_static_link_t *pbuffer, void *data);
bool k_static_list_get(k_static_link_t *pbuffer, k_static_node_t node, void **data);
void k_static_list_temp_show(k_static_link_t *pbuffer, k_static_node_t size);

/* single list */
void k_slist_init(k_slist_t *slist);
void k_slist_insert_at(k_slist_t *slist, k_snode_t *at, k_snode_t *node);
void k_slist_get(k_slist_t *slist, bool tail, void **data);
void k_slist_temp_show(k_slist_t *slist);

/* double list */
void k_dlist_init(double_list_t *dlist);
void k_dlist_insert_at(double_list_t *dlist, dlist_node_t *at,dlist_node_t *node);
void k_dlist_get(double_list_t *dlist, bool tail, void **data);
void k_dlist_temp_show(double_list_t *dlist);

/* stack */
void k_stack_init(k_stack_t *stack, stack_data_t *buffer, uint32_t size);
void k_stack_push(k_stack_t *stack, stack_data_t data);
void k_stack_pop(k_stack_t *stack, stack_data_t *data);
void k_stack_temp_show(k_stack_t *stack);

/* queue */
void k_queue_init(k_queue_t *queue);
void k_queue_append(k_queue_t *queue, k_snode_t *node);
void k_queue_preappend(k_queue_t *queue, k_snode_t *node);
void k_queue_get(k_queue_t *queue, void **node);
void k_queue_temp_show(k_queue_t *queue);
#endif /* _KERNEL_H_ */
