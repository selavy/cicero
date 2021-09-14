#pragma once

#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <cicero/mafsa.h>

#define ASIZE(x) (sizeof(x) / sizeof(x[0]))
#define assert_ok(x) (assert_that(x, is_equal_to(0)))

mafsa create_mafsa_(const char* const words[], const size_t n_words) {
    mafsa m;
    mafsa_builder builder;
    assert_ok(mafsa_builder_start(&builder));
    for (size_t i = 0; i < n_words; ++i) {
        assert_ok(mafsa_builder_insert(&builder, words[i]));
    }
    assert_ok(mafsa_builder_finish(&builder, &m));
    return m;
}

#define create_mafsa(words) create_mafsa_(words, ASIZE(words))

// clang-format off

enum {
    SQ_A1, SQ_A2, SQ_A3, SQ_A4, SQ_A5, SQ_A6, SQ_A7, SQ_A8, SQ_A9, SQ_A10, SQ_A11, SQ_A12, SQ_A13, SQ_A14, SQ_A15,
    SQ_B1, SQ_B2, SQ_B3, SQ_B4, SQ_B5, SQ_B6, SQ_B7, SQ_B8, SQ_B9, SQ_B10, SQ_B11, SQ_B12, SQ_B13, SQ_B14, SQ_B15,
    SQ_C1, SQ_C2, SQ_C3, SQ_C4, SQ_C5, SQ_C6, SQ_C7, SQ_C8, SQ_C9, SQ_C10, SQ_C11, SQ_C12, SQ_C13, SQ_C14, SQ_C15,
    SQ_D1, SQ_D2, SQ_D3, SQ_D4, SQ_D5, SQ_D6, SQ_D7, SQ_D8, SQ_D9, SQ_D10, SQ_D11, SQ_D12, SQ_D13, SQ_D14, SQ_D15,
    SQ_E1, SQ_E2, SQ_E3, SQ_E4, SQ_E5, SQ_E6, SQ_E7, SQ_E8, SQ_E9, SQ_E10, SQ_E11, SQ_E12, SQ_E13, SQ_E14, SQ_E15,
    SQ_F1, SQ_F2, SQ_F3, SQ_F4, SQ_F5, SQ_F6, SQ_F7, SQ_F8, SQ_F9, SQ_F10, SQ_F11, SQ_F12, SQ_F13, SQ_F14, SQ_F15,
    SQ_G1, SQ_G2, SQ_G3, SQ_G4, SQ_G5, SQ_G6, SQ_G7, SQ_G8, SQ_G9, SQ_G10, SQ_G11, SQ_G12, SQ_G13, SQ_G14, SQ_G15,
    SQ_H1, SQ_H2, SQ_H3, SQ_H4, SQ_H5, SQ_H6, SQ_H7, SQ_H8, SQ_H9, SQ_H10, SQ_H11, SQ_H12, SQ_H13, SQ_H14, SQ_H15,
    SQ_I1, SQ_I2, SQ_I3, SQ_I4, SQ_I5, SQ_I6, SQ_I7, SQ_I8, SQ_I9, SQ_I10, SQ_I11, SQ_I12, SQ_I13, SQ_I14, SQ_I15,
    SQ_J1, SQ_J2, SQ_J3, SQ_J4, SQ_J5, SQ_J6, SQ_J7, SQ_J8, SQ_J9, SQ_J10, SQ_J11, SQ_J12, SQ_J13, SQ_J14, SQ_J15,
    SQ_K1, SQ_K2, SQ_K3, SQ_K4, SQ_K5, SQ_K6, SQ_K7, SQ_K8, SQ_K9, SQ_K10, SQ_K11, SQ_K12, SQ_K13, SQ_K14, SQ_K15,
    SQ_L1, SQ_L2, SQ_L3, SQ_L4, SQ_L5, SQ_L6, SQ_L7, SQ_L8, SQ_L9, SQ_L10, SQ_L11, SQ_L12, SQ_L13, SQ_L14, SQ_L15,
    SQ_M1, SQ_M2, SQ_M3, SQ_M4, SQ_M5, SQ_M6, SQ_M7, SQ_M8, SQ_M9, SQ_M10, SQ_M11, SQ_M12, SQ_M13, SQ_M14, SQ_M15,
    SQ_N1, SQ_N2, SQ_N3, SQ_N4, SQ_N5, SQ_N6, SQ_N7, SQ_N8, SQ_N9, SQ_N10, SQ_N11, SQ_N12, SQ_N13, SQ_N14, SQ_N15,
    SQ_O1, SQ_O2, SQ_O3, SQ_O4, SQ_O5, SQ_O6, SQ_O7, SQ_O8, SQ_O9, SQ_O10, SQ_O11, SQ_O12, SQ_O13, SQ_O14, SQ_O15,
};

// clang-format on
