
#include <stddef.h>

#include "limits.h"

#include "queue.h"

inline char queue_get_char(struct queue *curr)
{
	/* check if queue pointer reached the end */
	if (curr->read_offset >= curr->q + QUEUE_SIZE - 1) {
		curr->read_offset = curr->q;
	}

	/* check if one (or more) chars are readable */
	if ((curr->write_offset - curr->read_offset) > 0) {
		return *curr->read_offset++;
	}
	return CHAR_MAX;
}

inline void queue_append_char(struct queue *curr, char ch)
{
	/* check if queue pointer reached the end */
	if (curr->write_offset >= curr->q + QUEUE_SIZE - 1) {
		curr->write_offset = curr->q;
	}

	/* add char to queue */
	*curr->write_offset = ch;
	curr->write_offset++;
}

inline void queue_reset(struct queue *curr)
{
	size_t i;

	for (i = 0; i < QUEUE_SIZE; i++) {
		curr->q[i] = 0x0;
	}

	curr->read_offset = curr->q;
	curr->write_offset = curr->q;
}
