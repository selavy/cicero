#include <assert.h>
#include <cicero/mafsa.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "iconv.h"

typedef unsigned int uint;
typedef mafsa_node_ node;

int isterm(const uint *terms, int s) {
    assert(0 <= s);
    size_t entry = (size_t)s / sizeof(uint);
    size_t shift = (size_t)s % sizeof(uint);
    uint mask = 1u << shift;
    return ((terms[entry] & mask) != 0) ? 1 : 0;
}

int mafsa_isterm(const mafsa *m, int s) {
    if (!(0 <= s && s < m->size)) {
        return 0;
    }
    return isterm(m->terms, s);
}

int mafsa_isword(const struct mafsa *m, const char *const word) {
    const node *nodes = m->nodes;
    const int size = m->size;
    int s = 0;
    for (const char *p = word; *p != '\0'; ++p) {
        const int c = iconv(*p);
        const int t = nodes[s].children[c];
        assert(0 <= s && s < size);
        assert(0 <= c && c <= 26);
        if (t == 0) {
            return 0;
        }
        s = t;
    }
    return isterm(m->terms, s);
}

void mafsa_free(mafsa *m) {
    free(m->nodes);
    free(m->terms);
    m->nodes = NULL;
    m->terms = NULL;
    m->size = 0;
}

mafsa_edges mafsa_prefix_edges(const mafsa *m, const char *const word) {
    mafsa_edges result;
    const node *nodes = m->nodes;
    const int size = m->size;
    int s = 0;
    memset(&result, 0, sizeof(result));
    for (const char *p = word; *p != '\0'; ++p) {
        const int c = iconv(*p);
        const int t = nodes[s].children[c];
        if (t == 0) {
            return result;
        }
        s = t;
    }
    result.terminal = isterm(m->terms, s);
    int ntiles = 0;
    for (int i = 0; i < 26; ++i) {
        if (nodes[s].children[i] != 0) {
            result.edges[ntiles++] = (char)(i + 'A');
        }
    }
    return result;
}
