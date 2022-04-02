#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "algorithms/rabin_karp.h"
#include "./main.h"

Ensure(test_match)
{       
	char *txt = "AABAACAADAABAAABAA";
	char *pat = "AABA";
	uint32_t offsets[12];
	printf("Text to search %s, pattern %s\n", txt, pat);
	uint32_t ret = rabin_karp_search(txt, pat, offsets, 12);
	assert_equal(ret, 3);
	assert_equal(offsets[0], 0);
	assert_equal(offsets[1], 9);
	assert_equal(offsets[2], 13);
}

TestSuite *rabin_karp_tests()
{
        TestSuite *suite = create_test_suite();

        add_test(suite, test_match);

        return suite;
}

CGREEN_TEST_MAIN(rabin_karp_tests);
