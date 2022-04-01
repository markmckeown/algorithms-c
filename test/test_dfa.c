#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <string.h>

#include "search/dfa.h"
#include "./main.h"

Ensure(test_match)
{       
	char *txt = "AABAACAADAABAAABAA";
	char *pat = "AABA";
	int ret = search(pat, txt);
	assert_equal(ret, 9);
	txt += 9;
	ret = search(pat, txt);
	assert_equal(ret, 4);
}

TestSuite *dfa_tests()
{
        TestSuite *suite = create_test_suite();

        add_test(suite, test_match);

        return suite;
}

CGREEN_TEST_MAIN(dfa_tests);
