#ifndef DFA_H
#define DFA_H

#include <stdint.h>

uint32_t dfa_search(char *txt, char *pat, uint32_t *offsets, uint32_t offset_count);

#endif
