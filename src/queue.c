
#include <stddef.h>
#include <limits.h>

#include "queue.h"

inline char queue_get_char(struct queue *curr)
{
	/* check if queue read pointer reached the end */
	if (curr->read_offset >= curr->q + QUEUE_SIZE) {
		curr->read_offset = curr->q;
		curr->wrap = true;
	}

	/* check if one (or more) chars are readable */
	if (curr->write_offset > curr->read_offset && !curr->wrap) {
		return *curr->read_offset++;
	}
	return 0x0;
}

inline void queue_append_char(struct queue *curr, char ch)
{
	/* check if queue write pointer reached the end */
	if (curr->write_offset >= curr->q + QUEUE_SIZE) {
		curr->write_offset = curr->q;

		curr->wrap = false;
	}

	/* add char to queue */
	*curr->write_offset++ = ch;
}

inline void queue_reset(struct queue *curr)
{
	curr->read_offset = curr->q;
	curr->write_offset = curr->q;

	curr->wrap = false;
}
