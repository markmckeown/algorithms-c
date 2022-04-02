#include <string.h>
#include <stdint.h>
#include <stdio.h>


#define RABIN_CARP_Q 0x797a9691
// There are Java implementations of this algorithm that
// use a RADIX of 256, even though the size of a Java
// char is 2 bytes. 
#define RABIN_CARP_RADIX 256

static uint64_t hash (const char *s, size_t m, uint64_t q)
{
        // Horner’s method, applied to modular hashing
        uint64_t h = 0;
	uint64_t j = 0;
        for (j = 0; j < m; j++) {
                h = (RABIN_CARP_RADIX * h + s[j]) % q;
	}
        return h;
}


uint32_t rabin_karp_search(const char *txt, const char *pat, uint32_t *offsets, uint32_t offset_count)
{
	uint32_t ret = 0;
        size_t m=strlen(pat);
        size_t n=strlen(txt);
        uint64_t q= RABIN_CARP_Q; // a large prime, small enough to avoid long overflow
        uint64_t RM;           // 256^(m-1) % q
        uint64_t patHash;
	uint64_t txtHash;
	uint64_t i;
	int offset;

	if (offset_count == 0) {
		goto out;
	}

        if (n < m) {
                goto out;
	}


        // precompute 256^(m-1) % q for use in removing leading digit
        RM = 1;
        for (i = 1; i <= m-1; i++) {
                RM = (256 * RM) % q;
	}

	// Calculate the pattern hash.
        patHash = hash(pat, m, q);
	// Calculare the hash at the start of the text
        txtHash = hash(txt, m, q);

        // check for match at offset 0
        // additional memcmp() required to prevent hash collision
        if (patHash == txtHash && memcmp(txt, pat, m)==0) {
		*offsets = 0;
		offsets++;
                ret++;
		if (ret == offset_count) {
			goto out;
		}
	}

        // check for hash match; if hash match, check for exact match
        for (i = m; i < n; i++)
        {
                // Remove leading digit, add trailing digit, check for match. 
                txtHash = (txtHash + q - RM*txt[i-m] % q) % q; 
                txtHash = (txtHash * RABIN_CARP_RADIX + txt[i]) % q; 

                // match
                offset = i - m + 1;
                // additional memcmp() required to prevent hash collision
                if ((patHash == txtHash) && memcmp(txt+offset, pat, m)==0) {
                        *offsets = offset;
			offsets++;
			ret++;
			if (ret == offset_count) {
				goto out;
			}
		}
        }

out:
        return ret;
}



