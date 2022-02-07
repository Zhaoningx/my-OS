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
typedef uint32_t static_link_t;
typedef struct {
    static_link_t next;
    void *data;
}static_link;

/* single link-list */
struct single_node {
    struct single_node *next;
};

typedef struct single_node single_node_t;

struct single_list{
    single_node_t *tail, *head;
};

typedef struct single_list single_list_t;

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

/* dynamic stack */
struct link_stack {
    uint32_t *base, *next, *top;
    uint32_t linksize;
};

/**
 * @brief function define
 * 
 */
/* static list */
void initStaticList(static_link *pbuffer, static_link_t size);
void insertStaticList(static_link *pbuffer, void *data);
bool popStaticList(static_link *pbuffer, static_link_t node, void **data);
void showStaticList(static_link *pbuffer, static_link_t size);

/* single list */
void initStaticList(static_link *pbuffer, static_link_t size);
void insertStaticList(static_link *pbuffer, void *data);
bool popStaticList(static_link *pbuffer, static_link_t node, void **data);
void showStaticList(static_link *pbuffer, static_link_t size);

/* double list */
void initDoubleList(double_list_t *dlist);
void insertDoubleList(double_list_t *dlist, dlist_node_t *at,dlist_node_t *node);
void popDoubleList(double_list_t *dlist, bool tail, void **data);
void showDoubleList(double_list_t *dlist);

/* static stack */
void initStack(k_stack_t *stack, stack_data_t *buffer, uint32_t size);
void pushStack(k_stack_t *stack, stack_data_t data);
void popStack(k_stack_t *stack, stack_data_t *data);
void readStack(k_stack_t *stack);
#endif /* _KERNEL_H_ */
