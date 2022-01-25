#include "kernel.h"

/**
 * @brief Static list
 * @details 
 * define an arr at compile time.
 * the unused space in one link list, and the head is arr[0]
 * the used space with data is in the another link list, and the head is arr[1]
 * @return NA
 */
void initStaticList(static_link *pbuffer, static_link_t size)
{
    static_link_t index = 0;
    for (; index < size; index++) {
        pbuffer[index].next = index + 1;
        pbuffer[index].data = NULL;
    }

    pbuffer[size - 1].next = 0;
    pbuffer[0].next = pbuffer[1].next;
    pbuffer[1].next = 0;
}

void insertStaticList(static_link *pbuffer, void *data)
{
    uint32_t space;
    uint32_t i = 1;

    if (!pbuffer[0].next) {
        printf("pbuffer is full\n");
        return;
    }
    space = pbuffer[0].next;
    pbuffer[space].data = data;
    pbuffer[0].next = pbuffer[space].next;
    pbuffer[space].next = 0;

    while (pbuffer[i].next) {
        i = pbuffer[i].next;
    }
    pbuffer[i].next = space;
}

bool popStaticList(static_link *pbuffer, static_link_t node, void **data)
{
    static_link_t i;
    static_link_t pre;
    bool flag = false;

    if (!pbuffer[1].next || node == 1) {
        printf("the list is empty or node is 1\n");
        return false;
    }

    if (node) {
        /* get data from pbuffer[node].next */
        i = 1;
        while (pbuffer[i].next) {
            if (pbuffer[i].next == node) {
                flag = true;
                break;
            }
            i = pbuffer[i].next;
        }
        pbuffer[i].next = pbuffer[node].next;
        *data = pbuffer[node].data;
        pbuffer[node].data = NULL;
        pbuffer[node].next = pbuffer[0].next;
        pbuffer[0].next = node;
    } else {
        /* get data from the list tail */
        flag = true;
        pre = 1;
        i = 1;
        while (pbuffer[i].next) {
            pre = i;
            i = pbuffer[i].next;
        }
        *data = pbuffer[i].data;
        pbuffer[i].data = NULL;
        pbuffer[i].next = pbuffer[0].next;
        pbuffer[0].next = pbuffer[pre].next;
        pbuffer[pre].next = 0;
    }
    return flag;
}

void showStaticList(static_link *pbuffer, static_link_t size)
{
    printf("index   next   data\n");
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) data addr: %p\n", i, pbuffer[i].next, pbuffer[i].data);
    }
    
}

/**
 * @brief Single link-list
 * 
 * @return NA
 */

void initSingleList(single_list_t *slist)
{
    slist->head = NULL;
    slist->tail = NULL;
}

void insertAtSingleList(single_list_t *slist, single_node_t *at, single_node_t *node)
{
    bool flag = false;
    single_node_t * phead = slist->head;

    /* head node */
    if (slist->head == NULL && slist->tail == NULL) {
        slist->head = node;
        slist->tail = node;
        node->next = NULL;
        return;
    }

    if (at == NULL || at == slist->tail) {
        /* append node in the tail */
        slist->tail->next = node;
        slist->tail = node;
    } else {
        /* insert node after 'at' node */
        while (phead != NULL) {
            if (phead == at) {
                node->next = at->next;
                at->next = node;
                flag = true;
            }
            phead = phead->next;
        }
        if(!flag) {
            printf("Failed to insert new node\n");
            return;
        }
    }
}

void popSingleList(single_list_t *slist, bool tail, void **data)
{
    single_node_t *phead = slist->head;
    bool flag = false;

    if (slist->head == NULL) {
        printf("empty list\n");
    }

    if (tail) {
        /* pop data from list tail */
        *data = slist->tail;
        while (phead->next != slist->tail) {
            flag = true;
            phead = phead->next;
        }
        if (flag) {
            phead->next = NULL;
            slist->tail = phead;
        } else {
            printf("Failed to get data from the tail\n");
        }
    } else {
        /* pop data from list head */
        *data = slist->head;
        slist->head = slist->head->next;
    }
}

void showSingleList(single_list_t *slist)
{
    single_node_t * phead = slist->head;
    while(phead != NULL) {
        printf("list node: %p\n", phead);
        phead = phead->next;
    }
}

void initDoubleList(double_list_t *dlist)
{
    dlist->head = NULL;
    dlist->tail = NULL;
}

/**
 * @brief double link-list
 * 
 * @return NA
 */
void insertDoubleList(double_list_t *dlist, dlist_node_t *at,dlist_node_t *node)
{
    dlist_node_t *phead = dlist->head;
    bool flag = false;

    if (dlist->head == NULL && dlist->tail == NULL) {
        /* the double is empty */
        node->next = NULL;
        node->prev = NULL;
        dlist->head = node;
        dlist->tail = node;
        return;
    }

    if (at == NULL || at == dlist->tail) {
        /* insert data in the dlist tail */
        dlist->tail->next = node;
        node->next = NULL;
        node->prev = dlist->tail;
        /* move tail to new node */
        dlist->tail = node;
    } else {
        while (phead->next != NULL) {
            if (phead == at) {
                flag = true;
            }
            phead = phead->next;
        }

        if (flag) {
            node->next = at->next;
            at->next->prev = node;
            at->next = node;
            node->prev = at;
        } else {
            printf("ERROR: 'at' node is not exsit\n");
            return;
        }
    }
}

void popDoubleList(double_list_t *dlist, bool tail, void **data)
{
    if (dlist->head == NULL) {
        printf("dlist is empty\n");
        return;
    }

    if (tail) {
        /* pop data from the dlist tail */
        *data = dlist->tail;
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    } else {
        /* pop data from the dlist head */
        *data = dlist->head;
        dlist->head = dlist->head->next;
        dlist->head->prev = NULL;
    }
}

void showDoubleList(double_list_t *dlist)
{
    double_list_t *phead = dlist->head;
    int i = 0;

    if (phead == NULL) {
        printf("dlist is empty\n");
        return;
    }

    while (phead) {
        printf("dlist node %d: %p\n", i, phead);
        phead = phead->next;
        i++;
    }
}