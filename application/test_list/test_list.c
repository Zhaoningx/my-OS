#include "kernel.h"

#if 1
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

#if 0
#define DOUBLESIZE 20
void main()
{
    double_list_t test_list;
    double_list_t *test_dlist = &test_list;
    struct dlist_container {
        dlist_node_t node;
        void *data;
    };
    initDoubleList(test_dlist);
    struct dlist_container arr[DOUBLESIZE];
    uint32_t data[] = {11,22,33,44,55,66,77,88,99,111,222,333,444,555,666,777,888,999,1111,2222, 3333};

    for (int i = 0; i < DOUBLESIZE; i++)  {
        arr[i].node.next = NULL;
        arr[i].node.prev = NULL;
        arr[i].data = &data[i];
        insertDoubleList(test_dlist, NULL, &arr[i].node);
    }
    showDoubleList(test_dlist);

    struct dlist_container brr;
    brr.node.next = brr.node.prev = NULL;
    brr.data = &data[20];
    printf("======================================\n");

    insertDoubleList(test_dlist, &arr[10].node, &brr.node);
    showDoubleList(test_dlist);
    printf("======================================\n");

    struct dlist_container *pdata = NULL;
    popDoubleList(test_dlist, true, (void **)&pdata);
    uint32_t *data1 = pdata->data;

    printf("get data = %p, %d\n", pdata, *data1);
    showDoubleList(test_dlist);
    printf("======================================\n");

    pdata = NULL;
    popDoubleList(test_dlist, false, (void **)&pdata);
    data1 = pdata->data;

    printf("get data = %p, %d\n", pdata, *data1);
    showDoubleList(test_dlist);
    printf("======================================\n");
}
#endif
