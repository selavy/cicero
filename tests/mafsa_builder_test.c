#include <assert.h>
#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <cicero/mafsa.h>
#include <string.h>

#include "utils.h"

Describe(BuildMAFSA);
BeforeEach(BuildMAFSA) {}
AfterEach(BuildMAFSA) {}

Ensure(BuildMAFSA, added_word_is_found_and_terminal) {
    int found;
    mafsa m;

    const char* const words[] = {
        "HELLO", "GOODBYE", "ATE",   "ATTENTION", "ATT",       "BATS",
        "BAT",   "BATT",    "BATTS", "WORLD",     "WONDERFUL", "WOWOW",
    };
    m = create_mafsa(words);
    for (size_t i = 0; i < ASIZE(words); ++i) {
        found = mafsa_isword(&m, words[i]);
        assert_that(found != 0);
    }

    const char* const missing[] = {
        "THIS",
        "HELLOT",
        "HELL",
        "WORLDA",
    };
    for (size_t i = 0; i < ASIZE(missing); ++i) {
        found = mafsa_isword(&m, missing[i]);
        assert_that(found == 0);
    }

    mafsa_free(&m);
}

Ensure(BuildMAFSA, get_prefix_edges) {
    int rc;
    mafsa m;

    const char* const words[] = {
        "ABACTERIAL",   "ABACTINAL",   "ABACTINALLY", "ABACTOR",
        "ABACTORS",     "ABACUS",      "ABACUSES",    "ABAFT",
        "ABAKA",        "ABAKAS",      "ABALONE",     "ABALONES",
        "ABAMP",        "ABAMPERE",    "ABAMPERES",   "ABAMPS",
        "ABAND",        "ABANDED",     "ABANDING",    "ABANDON",
        "ABANDONED",    "ABANDONEDLY", "ABANDONEE",   "ABANDONEES",
        "ABANDONER",    "ABANDONERS",  "ABANDONING",  "ABANDONMENT",
        "ABANDONMENTS", "ABANDONS",    "ABANDONWARE", "ABANDONWARES",
        "ABANDS",       "ABAPICAL",    "ABAS",        "ABASE",
        "ABASED",       "SUFFIX",      "SUFFICIENT",  "SUFFICE",
        "SUFFICATE",    "SUFFICATES",  "SULFATE",     "SULFATES",
    };
    m = create_mafsa(words);
    for (size_t i = 0; i < ASIZE(words); ++i) {
        rc = mafsa_isword(&m, words[i]);
        assert_that(rc != 0);
    }

    const char* const missing[] = {
        "THIS",
        "HELLOT",
        "HELL",
        "WORLDA",
    };
    const size_t n_missing = sizeof(missing) / sizeof(missing[0]);
    for (size_t i = 0; i < n_missing; ++i) {
        rc = mafsa_isword(&m, missing[i]);
        assert_that(rc == 0);
    }

    {
        mafsa_edges edges = mafsa_prefix_edges(&m, "SU");
        assert_that(edges.terminal, is_false);
        assert_that(edges.edges[0], is_equal_to('F'));
        assert_that(edges.edges[1], is_equal_to('L'));
        assert_that(edges.edges[2], is_equal_to('\0'));
    }

    {
        mafsa_edges edges = mafsa_prefix_edges(&m, "SULFATE");
        assert_that(edges.terminal, is_true);
        assert_that(edges.edges[0], is_equal_to('S'));
        assert_that(edges.edges[1], is_equal_to('\0'));
    }

    {
        mafsa_edges edges = mafsa_prefix_edges(&m, "ABA");
        assert_that(edges.terminal, is_false);
        assert_that(edges.edges[0], is_equal_to('C'));
        assert_that(edges.edges[1], is_equal_to('F'));
        assert_that(edges.edges[2], is_equal_to('K'));
        assert_that(edges.edges[3], is_equal_to('L'));
        assert_that(edges.edges[4], is_equal_to('M'));
        assert_that(edges.edges[5], is_equal_to('N'));
        assert_that(edges.edges[6], is_equal_to('P'));
        assert_that(edges.edges[7], is_equal_to('S'));
        assert_that(edges.edges[8], is_equal_to('\0'));
    }

    {
        mafsa_edges edges = mafsa_prefix_edges(&m, "NOTAWORD");
        assert_that(edges.terminal, is_false);
        assert_that(edges.edges[0], is_equal_to('\0'));
    }

    mafsa_free(&m);
}
