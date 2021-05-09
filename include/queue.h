#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define QUEUE_SIZE 10

struct queue {
	volatile char q[QUEUE_SIZE];
	volatile char *read_offset;
	volatile char *write_offset;
	volatile bool write_wrap;
};

char queue_get_char(struct queue *curr);
void queue_append_char(struct queue *curr, char ch);
void queue_reset(struct queue *curr);
bool queue_check_overwrite(struct queue *curr);

#endif
