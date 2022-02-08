#include "kernel.h"
static k_slist_t slist;

void k_queue_init(k_queue_t *queue)
{
    k_slist_init(&slist);
    queue->slist = &slist;
}

void k_queue_append(k_queue_t *queue, k_snode_t *node)
{
    k_slist_insert_at(queue->slist, NULL, node);
}

void k_queue_preappend(k_queue_t *queue, k_snode_t *node)
{
    k_snode_t *head = queue->slist->head;

    k_slist_insert_at(queue->slist, head, node);
}

void k_queue_get(k_queue_t *queue, void **node)
{
    k_slist_get(queue->slist, true, node);
}

void k_queue_temp_show(k_queue_t *queue)
{
    k_slist_temp_show(queue->slist);
}
