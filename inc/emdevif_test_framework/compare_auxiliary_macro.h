/**
 * @file compare_auxiliary_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 比较检查宏的辅助宏
 */

#pragma once
#ifndef EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H
#define EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H

#define EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs)         \
    (emdevif___msg.test_suit = emdevif___suit,              \
     emdevif___msg.file = __FILE__,                       \
     emdevif___msg.line = __LINE__,                       \
     emdevif___msg.current_case_name = emdevif___case_name, \
     emdevif___msg.lhs_name = #lhs,                       \
     emdevif___msg.rhs_name = #rhs)

#define EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ...)                                \
    if (!emdevif___msg.is_passed) {                                                   \
        emdevif_test___printfCallback___(format, ##__VA_ARGS__);                      \
        emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___); \
        emdevif_test_assertFailEntry();                                               \
    }

#endif  // !EMDEVIF_TEST_COMPARE_AUXILIARY_MACRO_H
