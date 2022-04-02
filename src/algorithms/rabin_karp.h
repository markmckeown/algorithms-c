#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <stdint.h>

uint32_t rabin_karp_search(char *txt, char *pat, uint32_t *offsets, uint32_t offset_count);

#endif
