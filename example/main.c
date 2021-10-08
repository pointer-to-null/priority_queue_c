#include <stdio.h>
#include "../src/queue_prior.h"

typedef struct {
	uint8_t data1;
	uint32_t data2;
} custom_type_t;

int main(int argc, char **argv) {
	custom_type_t custom_data1 = {
		.data1 = 5,
		.data2 = 10,
	};

	custom_type_t custom_data2 = {
		.data1 = 15,
		.data2 = 25,
	};

	custom_type_t custom_data3 = {
		.data1 = 30,
		.data2 = 45,
	};

	custom_type_t custom_data4 = {
		.data1 = 50,
		.data2 = 60,
	};

	qpQueue_t queue = qpCreateQueue(10, sizeof(custom_type_t));
	qpPush(&queue, &custom_data1, 5);
	qpPush(&queue, &custom_data2, 2);
	qpPush(&queue, &custom_data3, 7);
	qpPush(&queue, &custom_data4, 2);
	qpPush(&queue, &custom_data1, 3);
	qpPush(&queue, &custom_data2, 5);
	qpPush(&queue, &custom_data3, 1);
	custom_type_t out_data;
	uint32_t priority;
	while(!qpIsEmpty(&queue)) {
		qpPop(&queue, &out_data, &priority);
		printf("popped data1 = %d data2 = %d, priority = %d\n", out_data.data1, out_data.data2, priority);
	}

	printf("\n");

	qpQueue_t queue2 = qpCreateQueue(5, sizeof(uint32_t));
	uint32_t int_data = 5;
	uint32_t int_data2 = 1234;
	qpPush(&queue2, &int_data, 3);
	qpPush(&queue2, &int_data2, 2);
	uint32_t out_int_data;
	uint32_t out_priority;
	while(!qpIsEmpty(&queue2)) {
		qpPop(&queue2, &out_int_data, &out_priority);
		printf("popped intdata = %d priority = %d\n", out_int_data, out_priority);
	}

	printf("\n");

	qpPush(&queue, &custom_data3, 10);
	qpPush(&queue, &custom_data1, 3);
	qpPush(&queue, &custom_data4, 5);
	qpPush(&queue, &custom_data2, 10);
	qpPush(&queue, &custom_data1, 11);
	while(!qpIsEmpty(&queue)) {
		qpPop(&queue, &out_data, &priority);
		printf("popped data1 = %d data2 = %d, priority = %d\n", out_data.data1, out_data.data2, priority);
	}

    return 0;
}
