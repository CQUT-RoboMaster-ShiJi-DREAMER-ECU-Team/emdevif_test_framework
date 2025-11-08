/**
 * @file compare_auxiliary_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 比较检查宏的辅助宏
 */

#pragma once
#ifndef EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H
#define EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H

#define EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs)                                   \
    (emdevif_current_test_compare_message_.test_suit = &emdevif_current_test_suit_, \
     emdevif_current_test_compare_message_.file = __FILE__,                         \
     emdevif_current_test_compare_message_.line = __LINE__,                         \
     emdevif_current_test_compare_message_.current_case_name = emdevif___case_name, \
     emdevif_current_test_compare_message_.lhs_name = #lhs,                         \
     emdevif_current_test_compare_message_.rhs_name = #rhs)

#define EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ...)                                  \
    if (!emdevif_current_test_compare_message_.is_passed) {                             \
        emdevif_test___printfCallback___(format, ##__VA_ARGS__);                        \
        emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___); \
        emdevif_test_assertFailEntry();                                                 \
    }

#endif  // !EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H
