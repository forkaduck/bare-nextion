/** @file
 *  @brief Contains the input queue implementation.
*/

#include <stddef.h>
#include <limits.h>

#include "queue.h"

inline char queue_get_char(struct queue *curr)
{
	/* return if the queue is empty */
	if (curr->read_offset == curr->write_offset) {
		return QUEUE_EMPTY;
	}
	/* calculate new read offset */
	curr->read_offset = (curr->read_offset + 1) % QUEUE_SIZE;

	return curr->q[curr->read_offset];
}

inline char queue_append_char(struct queue *curr, char ch)
{
	/* return if the queue is full */
	if ((curr->write_offset + 1) == curr->read_offset) {
		return QUEUE_FULL;
	}
	/* calculate new offset and write char to position in the array */
	curr->write_offset = (curr->write_offset + 1) % QUEUE_SIZE;
	curr->q[curr->write_offset] = ch;

	return curr->q[curr->write_offset];
}

inline void queue_reset(struct queue *curr)
{
	size_t i;

	for (i = 0; i < QUEUE_SIZE; i++) {
		curr->q[i] = 0;
	}

	curr->read_offset = 0;
	curr->write_offset = 0;
}
