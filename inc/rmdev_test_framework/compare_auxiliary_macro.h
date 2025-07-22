/**
 * @file compare_auxiliary_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 比较检查宏的辅助宏
 */

#pragma once
#ifndef RMDEV_TEST_COMPARE_AUXILIARY_MACRO_H
#define RMDEV_TEST_COMPARE_AUXILIARY_MACRO_H

#define RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs)         \
    (rmdev___msg.test_suit = rmdev___suit,              \
     rmdev___msg.file = __FILE__,                       \
     rmdev___msg.line = __LINE__,                       \
     rmdev___msg.current_case_name = rmdev___case_name, \
     rmdev___msg.lhs_name = #lhs,                       \
     rmdev___msg.rhs_name = #rhs)

#define RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ...)                                \
    if (!rmdev___msg.is_passed) {                                                   \
        rmdev_test___printfCallback___(format, ##__VA_ARGS__);                      \
        rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___); \
        rmdev_test_assertFailEntry();                                               \
    }

#endif  // !RMDEV_TEST_COMPARE_AUXILIARY_MACRO_H
