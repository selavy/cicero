#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <cicero/mafsa.h>
#include <string.h>
#include <assert.h>

#define assert_ok(x) (assert_that(x, is_equal_to(0)))
#define ASIZE(x) (sizeof(x)/sizeof(x[0]))


Describe(BuildMAFSA);
BeforeEach(BuildMAFSA) {}
AfterEach(BuildMAFSA) {}

mafsa create_mafsa(const char* const words[], const size_t n_words)
{
    mafsa         m;
    mafsa_builder builder;
    assert_ok(mafsa_builder_start(&builder));
    for (size_t i = 0; i < n_words; ++i) {
        assert_ok(mafsa_builder_insert(&builder, words[i]));
    }
    assert_ok(mafsa_builder_finish(&builder, &m));
    return m;
}

Ensure(BuildMAFSA, added_word_is_found_and_terminal)
{
    int found;
    mafsa m;

    const char* const words[] = {
        "HELLO",
        "GOODBYE",
        "ATE",
        "ATTENTION",
        "ATT",
        "BATS",
        "BAT",
        "BATT",
        "BATTS",
        "WORLD",
        "WONDERFUL",
        "WOWOW",
    };
    const size_t n_words = ASIZE(words);

    m = create_mafsa(words, n_words);

    for (size_t i = 0; i < n_words; ++i) {
        found = mafsa_isword(&m, words[i]);
        assert_that(found != 0);
    }

    const char* const missing[] = {
        "THIS",
        "HELLOT",
        "HELL",
        "WORLDA",
    };
    const size_t n_missing = sizeof(missing) / sizeof(missing[0]);
    for (size_t i = 0; i < n_missing; ++i) {
        found = mafsa_isword(&m, missing[i]);
        assert_that(found == 0);
    }

    mafsa_free(&m);
}


Ensure(BuildMAFSA, get_prefix_edges)
{
    int rc;
    mafsa_builder builder;
    mafsa m;

    const char* const words[] = {
        "ABACTERIAL",
        "ABACTINAL",
        "ABACTINALLY",
        "ABACTOR",
        "ABACTORS",
        "ABACUS",
        "ABACUSES",
        "ABAFT",
        "ABAKA",
        "ABAKAS",
        "ABALONE",
        "ABALONES",
        "ABAMP",
        "ABAMPERE",
        "ABAMPERES",
        "ABAMPS",
        "ABAND",
        "ABANDED",
        "ABANDING",
        "ABANDON",
        "ABANDONED",
        "ABANDONEDLY",
        "ABANDONEE",
        "ABANDONEES",
        "ABANDONER",
        "ABANDONERS",
        "ABANDONING",
        "ABANDONMENT",
        "ABANDONMENTS",
        "ABANDONS",
        "ABANDONWARE",
        "ABANDONWARES",
        "ABANDS",
        "ABAPICAL",
        "ABAS",
        "ABASE",
        "ABASED",
        "SUFFIX",
        "SUFFICIENT",
        "SUFFICE",
        "SUFFICATE",
        "SUFFICATES",
        "SULFATE",
        "SULFATES",
    };
    const size_t n_words = ASIZE(words);

    rc = mafsa_builder_start(&builder);
    assert_that(rc, is_equal_to(0));

    for (size_t i = 0; i < n_words; ++i) {
        rc = mafsa_builder_insert(&builder, words[i]);
        assert_that(rc, is_equal_to(0));
    }

    rc = mafsa_builder_finish(&builder, &m);
    assert_that(rc, is_equal_to(0));

    for (size_t i = 0; i < n_words; ++i) {
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

    mafsa_free(&m);
}
