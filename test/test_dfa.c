#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <string.h>
#include <stdint.h>

#include "algorithms/dfa.h"
#include "./main.h"

Ensure(test_match)
{       
	char *txt = "AABAACAADAABAAABAA";
	char *pat = "AABA";
	u_int32_t offsets[3];
	int ret = search(pat, txt, offsets, 3);
	assert_equal(ret, 3);
	assert_equal(offsets[0], 0);
	assert_equal(offsets[1], 9);
	assert_equal(offsets[2], 13);
}

TestSuite *dfa_tests()
{
        TestSuite *suite = create_test_suite();

        add_test(suite, test_match);

        return suite;
}

CGREEN_TEST_MAIN(dfa_tests);
