#ifndef DFA_H
#define DFA_H

#include <stdint.h>

u_int32_t search(char *pat, char *txt, u_int32_t *offsets, u_int32_t offset_count);

#endif
