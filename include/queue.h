#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 100

struct queue {
	volatile char q[QUEUE_SIZE];
	volatile char *read_offset;
	volatile char *write_offset;
};

char queue_get_char(struct queue *curr);
void queue_append_char(struct queue *curr, char ch);
void queue_reset(struct queue *curr);

#endif
