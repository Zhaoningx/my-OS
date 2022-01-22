#include <kernel.h>

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

#if 0
#define BUFFERSIZE 20
int main(void)
{
    static_link buffer[BUFFERSIZE];
    static_link *pbuffer = buffer;

    initStaticList(pbuffer, (static_link_t)BUFFERSIZE);
    showStaticList(pbuffer, (static_link_t)BUFFERSIZE);
    printf("============================\n");
    uint32_t data[] = {22,33,44,55,66,77,88,99,11,00, 22,33,44,55,66,77,88,99,11,00};
    printf("data[6]%p\n", &data[6]);
    for (int i = 0; i < 20; i++) {
        insertStaticList(pbuffer, (void *)&data[i]);
    }
    showStaticList(pbuffer, (static_link_t)BUFFERSIZE);
    printf("============================\n");;
    uint32_t a = 100;
    uint32_t *data1 = &a; 
    popStaticList(pbuffer, 2,(void **) &data1);
    printf("data = %d\n", *data1);
    showStaticList(pbuffer, (static_link_t)BUFFERSIZE);
}
#endif

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


#if 0
#define SINGLESIZE 20
int main(void)
{
    single_list_t test_list;
    struct slist_container {
        single_node_t node;
        void *data;
    };

    struct slist_container node[SINGLESIZE];
    struct slist_container *pnode = node;
    uint32_t data[] = {11,22,33,44,55,66,77,88,99,111,222,333,444,555,666,777,888,999,1111,2222, 3333};

    for (int i = 0; i < SINGLESIZE; i++) {
        pnode[i].data = (void *)&data[i];
        pnode[i].node.next = NULL;
    }

    initSingleList(&test_list);
    for (int i = 0; i < SINGLESIZE; i++) {
        printf("data addr: %p\n", &node[i]);
        insertAtSingleList(&test_list, NULL, &pnode[i].node);
    }
    showSingleList(&test_list);
    printf("=======\n");

    struct slist_container node_at;
    node_at.data = &data[20];
    node_at.node.next = NULL;

    insertAtSingleList(&test_list, &pnode[0].node, &node_at.node);
    showSingleList(&test_list);
    printf("=======\n");

    single_node_t *pdata = NULL;
    popSingleList(&test_list, false, (void **)&pdata);
    printf("pdata = %p\n", pdata);
    showSingleList(&test_list);
    printf("=======\n");

    popSingleList(&test_list, true, (void **)&pdata);
    printf("pdata = %p\n", pdata);
    showSingleList(&test_list);
    printf("=======\n");
}
#endif