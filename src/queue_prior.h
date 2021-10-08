#ifndef QUEUE_PRIOR_H
#define QUEUE_PRIOR_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	qpOk = 0, //All good.
	qpError = -1, //Something bad happened.
	qpErrorResource = -2, //Queue do not have enough space for new element when pushing or queue is empty when popping.
} qpStatus_t;

typedef struct qpNode {
    void *data;
	uint32_t priority; // Lower values indicate higher priority.
    struct qpNode *next_node;
} qpNode_t;

typedef struct {
	uint32_t queue_size;
	uint32_t node_data_size; //Node size in bytes.
	uint32_t node_count;
	qpNode_t *head_node;
} qpQueue_t;

qpQueue_t qpCreateQueue(uint32_t queue_size, uint32_t node_data_size);
//Peek do not remove element from the queue.
qpStatus_t qpPeek(const qpQueue_t *queue, void *peek_data, uint32_t peek_priority);
qpStatus_t qpPop(qpQueue_t *queue, void *pop_data, uint32_t *pop_priority);
qpStatus_t qpPush(qpQueue_t *queue, void *push_data, uint32_t push_priority);
bool qpIsEmpty(qpQueue_t *queue);

#endif //QUEUE_PRIOR_H
