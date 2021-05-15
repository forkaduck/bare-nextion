#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#define QUEUE_SIZE 100
#define QUEUE_FULL 0x80
#define QUEUE_EMPTY 0x81

struct queue {
	volatile char q[QUEUE_SIZE];
	volatile size_t read_offset;
	volatile size_t write_offset;
};

char queue_get_char(struct queue *curr);
char queue_append_char(struct queue *curr, char ch);
void queue_reset(struct queue *curr);

#endif
