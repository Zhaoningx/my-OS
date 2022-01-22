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

struct common_list {
    union {
        struct common_list *head;
        struct common_list *next;
    };
    union {
        struct common_list *tail;
        struct common_list *prev;
    };
    
    
};

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









struct dlist {
    uint32_t * per;
    uint32_t * next;
};

struct stack {
    uint32_t * buffer;
    uint32_t *top, *next, *base;
    uint32_t buffersize;
};

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


#endif /* _KERNEL_H_ */