#ifndef NX4832T035
#define NX4832T035

#include <stddef.h>

void display_send(const char instruction[], size_t size);
size_t display_read(char out[], const size_t out_size);

#endif
