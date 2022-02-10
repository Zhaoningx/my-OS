#include "kernel.h"

void k_ringbuffer_init(k_ringbuffer_t *ringbuffer, uint32_t *buffer, uint32_t size)
{
    ringbuffer->buffer = buffer;
    ringbuffer->buffer_size = size;

    ringbuffer->base = ringbuffer->head = ringbuffer->tail = buffer;
    ringbuffer->top = (buffer + size - 1);

    ringbuffer->empty = true;
}

void k_ringbuffer_insert(k_ringbuffer_t *ringbuffer, uint32_t data)
{
    if (ringbuffer->head == ringbuffer->tail && !ringbuffer->empty) {
        printf("ringbuffer is full\n");
        return;
    }

    ringbuffer->empty = false;

    if (ringbuffer->head >= ringbuffer->tail) {
        if (ringbuffer->head == ringbuffer->top) {
            *(ringbuffer->head) = data;
            ringbuffer->head = ringbuffer->base;
            return;
        }

        *(ringbuffer->head) = data;
        ringbuffer->head++;
    } else {
        *(ringbuffer->head) = data;
        ringbuffer->head++;
    }
}

void k_ringbuffer_get(k_ringbuffer_t *ringbuffer, uint32_t **data)
{
    if (ringbuffer->head == ringbuffer->tail && ringbuffer->empty) {
        printf("ringbuffer is empty\n");
        return;
    }

    ringbuffer->empty = true;

    if (ringbuffer->head >= ringbuffer->tail) {
        *data = ringbuffer->tail;
        ringbuffer->tail++;
    } else {
        if (ringbuffer->tail == ringbuffer->top) {
            *data = ringbuffer->tail;
            ringbuffer->tail = ringbuffer->base;
            return;
        }
        *data = ringbuffer->tail;
        ringbuffer->tail++;
    }
}

void k_ringbuffer_temp_show(k_ringbuffer_t *ringbuffer)
{
    for (int i = 0; i < ringbuffer->buffer_size; i++) {
        printf("buffer[%d] = %d\n", i, (ringbuffer->base)[i]);
    }
}
