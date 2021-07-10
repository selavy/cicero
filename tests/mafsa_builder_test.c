#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <cicero/mafsa.h>
#include <string.h>
#include <assert.h>


Describe(BuildMAFSA);
BeforeEach(BuildMAFSA) {}
AfterEach(BuildMAFSA) {}

Ensure(BuildMAFSA, added_word_is_found_and_terminal)
{
    int rc;
    mafsa_builder builder;
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
    const size_t n_words = sizeof(words) / sizeof(words[0]);

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
}
