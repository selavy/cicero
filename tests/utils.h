#pragma once

#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <cicero/mafsa.h>

#define ASIZE(x) (sizeof(x)/sizeof(x[0]))
#define assert_ok(x) (assert_that(x, is_equal_to(0)))

mafsa create_mafsa_(const char* const words[], const size_t n_words)
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

#define create_mafsa(words) create_mafsa_(words, ASIZE(words))
