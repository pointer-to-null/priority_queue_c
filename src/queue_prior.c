#include "queue_prior.h"
#include <stdlib.h>

static qpNode_t* qpCreateNode(const qpQueue_t *queue, void *data, uint32_t priority);

qpQueue_t qpCreateQueue(uint32_t queue_size, uint32_t node_data_size) {
	qpQueue_t queue;
	queue.queue_size = queue_size;
	queue.node_data_size = node_data_size;
	queue.node_count = 0;
	return queue;
}

static qpNode_t* qpCreateNode(const qpQueue_t *queue, void *data, uint32_t priority) {
	uint8_t *data_tmp = (uint8_t *)data;
	if(queue->node_data_size == 0) {
		return NULL;
	}
	qpNode_t *temp_node = (qpNode_t *)malloc(sizeof(qpNode_t));
	if(temp_node == NULL) {
		return NULL;
	}
	temp_node->data = (void *)malloc(queue->node_data_size);
	if(temp_node->data == NULL) {
		return NULL;
	}
	uint8_t *temp_node_data = (uint8_t *)temp_node->data;
	for(uint32_t i = 0; i < queue->node_data_size; i++) {
		temp_node_data[i] = data_tmp[i];
	}
	temp_node->priority = priority;
	temp_node->next_node = NULL;
	return temp_node;
}

qpStatus_t qpPeek(const qpQueue_t *queue, void *peek_data, uint32_t peek_priority) {
	if(peek_data == NULL) {
		return qpError;
	}
	uint8_t *peek_data_tmp = (uint8_t *)peek_data;
	uint8_t *head_node_data_tmp = (uint8_t *)queue->head_node->data;
	for(uint32_t i = 0; i < queue->node_data_size; i++) {
		peek_data_tmp[i] = head_node_data_tmp[i];
	}
	peek_priority = queue->head_node->priority;
	return qpOk;
}

qpStatus_t qpPop(qpQueue_t *queue, void *pop_data, uint32_t *pop_priority) {
	if(queue->node_count <= 0) {
		return qpErrorResource;
	}
	if(pop_data == NULL) {
		return qpError;
	}
	uint8_t *pop_data_tmp = (uint8_t *)pop_data;
	uint8_t *head_node_data_tmp = (uint8_t *)queue->head_node->data;
    for(uint32_t i = 0; i < queue->node_data_size; i++) {
		pop_data_tmp[i] = head_node_data_tmp[i];
	}
	if(pop_priority != NULL) {
		*pop_priority = queue->head_node->priority;
	}
	qpNode_t *temp_next_node = queue->head_node->next_node;
	free(queue->head_node->data);
	free(queue->head_node);
	queue->node_count--;
	queue->head_node = temp_next_node;
	return qpOk;
}

qpStatus_t qpPush(qpQueue_t *queue, void *push_data, uint32_t push_priority) {
    if(queue->node_count >= queue->queue_size) {
		return qpErrorResource;
	}
	if(push_data == NULL) {
		return qpError;
	}

	qpNode_t *temp_node = qpCreateNode(queue, push_data, push_priority);
	if(temp_node == NULL) {
		return qpError;
	}

	if(queue->node_count == 0) { //if queue is empty
		queue->head_node = temp_node;
	} else { //if queue is not empty
		if(queue->head_node->priority > push_priority) {
			temp_node->next_node = queue->head_node;
			queue->head_node = temp_node;
		} else {
			qpNode_t *start_node = queue->head_node;
			while((start_node->next_node != NULL) && (start_node->next_node->priority < push_priority)) {
				start_node = start_node->next_node;
			}
			temp_node->next_node = start_node->next_node;
			start_node->next_node = temp_node;
		}
	}
	queue->node_count++;
	return qpOk;
}

bool qpIsEmpty(qpQueue_t *queue) {
    return queue->node_count <= 0;
}
