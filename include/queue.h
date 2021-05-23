/** @file
 *  @brief Contains the input queue implementation.
*/

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

/**
 * @brief Returns one char from the queue.
 * @param curr A pointer to a queue struct which should be used.
 * @return The char requested or QUEUE_EMPTY.
 */
char queue_get_char(struct queue *curr);

/**
 * @brief Appends one char to the queue.
 * @param curr A pointer to a queue struct which should be used.
 * @param ch A character to be appended.
 * @return The char that was appended or QUEUE_FULL.
 */
char queue_append_char(struct queue *curr, char ch);

/**
 * @brief Resets the queue.
 * @param curr A pointer to a queue struct which should be used.
 */
void queue_reset(struct queue *curr);

#endif
