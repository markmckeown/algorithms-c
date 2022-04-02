#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define NO_OF_CHARS 256

// Based on 
// https://www.geeksforgeeks.org/finite-automata-algorithm-for-pattern-searching/
// The link also has a version in Java, implementation is the 
// same as the C version, however Java char is 2 bytes so not clear its correct.
static int getNextState(char *pat, int M, int state, int x)
{
	int ret = 0;
	// ns stores the result which is next state
	int ns, i;

	// If the character c is same as next character
	// in pattern,then simply increment state
	if (state < M && x == pat[state]) {
		ret = state + 1;
		goto out;
	}

	// ns finally contains the longest prefix
	// which is also suffix in "pat[0..state-1]c"
	// Start from the largest possible value
	// and stop when you find a prefix which
	// is also suffix
	for (ns = state; ns > 0; ns--) {
		if (pat[ns - 1] == x) {
			for (i = 0; i < ns - 1; i++) {
				if (pat[i] != pat[state - ns + 1 + i]) {
					break;
				}
			}
			if (i == ns - 1) {
				ret = ns;
				goto out;
			}
		}
	}

out:
	return ret;
}

static void computeTF(char *pat, int M, int TF[][NO_OF_CHARS])
{
	int state, x;
	for (state = 0; state <= M; ++state) {
		for (x = 0; x < NO_OF_CHARS; ++x) {
			TF[state][x] = getNextState(pat, M, state, x);
		}
	}
	return;
}

uint32_t dfa_search(char *txt, char *pat, uint32_t *offsets, uint32_t offset_count)
{
	uint32_t ret = 0;
	int M = strlen(pat);
	int N = strlen(txt);
	int TF[M + 1][NO_OF_CHARS];
	int i, state = 0;

	if (offset_count == 0) {
		goto out;
	}

	computeTF(pat, M, TF);

	for (i = 0; i < N; i++) {
		state = TF[state][(uint8_t) txt[i]];
		if (state == M) {
			printf("Pattern found at index %d\n", i - M + 1);
			*offsets =  i - M + 1;
			ret++;
			offsets++;
			if (ret == offset_count) {
				break;
			}
		}
	}

out:
	return ret;
}
