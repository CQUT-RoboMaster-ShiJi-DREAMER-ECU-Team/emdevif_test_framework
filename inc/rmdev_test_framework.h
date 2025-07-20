/**
 * @file rmdev_test_framework.h
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#pragma once
#ifndef RMDEV_TEST_FRAMEWORK_H
#define RMDEV_TEST_FRAMEWORK_H

#include <stddef.h>

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#include <stdbool.h>

#define RMDEV_TEST_USE_STD_BOOL 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RMDEV_TEST_NULL NULL

#if (defined(RMDEV_TEST_USE_STD_BOOL) && RMDEV_TEST_USE_STD_BOOL)

typedef bool rmdev_test_bool_t;
#define RMDEV_TEST_TRUE  true
#define RMDEV_TEST_FALSE false

#else  // (defined(RMDEV_TEST_USE_STD_BOOL) && RMDEV_TEST_USE_STD_BOOL)

typedef unsigned char rmdev_test_bool_t;
#define RMDEV_TEST_TRUE  (1U)
#define RMDEV_TEST_FALSE (0U)

#endif  // (defined(RMDEV_TEST_USE_STD_BOOL) && RMDEV_TEST_USE_STD_BOOL)

/**
 * 错误码
 */
typedef enum rmdev_test_ErrorCode {
    RMDEV_TEST_NO_ERROR = 0,            ///< 无错误
    RMDEV_TEST_NO_BREAK_CHARACTER,      ///< 没有设置换行符
    RMDEV_TEST_NO_PRINTF_CALLBACK,      ///< 没有设置 printf 回调函数
    RMDEV_TEST_NO_DELAY_CALLBACK,       ///< 没有设置 delay 回调函数
    RMDEV_TEST_NO_TEST_ENTRY_CALLBACK,  ///< 没有设置 testEntry 回调函数
    RMDEV_TEST_TEST_SUIT_COUNT_ERROR,   ///< 测试项计数与成功、错误的项目计数不匹配
    RMDEV_TEST_OTHER_ERROR              ///< 其他错误
} rmdev_test_ErrorCode;

/**
 * rmdev 测试框架 格式化输出回调函数类型
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
typedef void (*rmdev_test_printfCallback)(const char* format, ...);

/**
 * rmdev 测试框架 延时回调函数类型
 * @param ms 毫秒数
 */
typedef void (*rmdev_test_delayCallback)(unsigned int ms);

/**
 * rmdev 测试框架 测试入口回调函数类型
 */
typedef void (*rmdev_test_testEntryCallback)(void);

/**
 * 测试结束回调函数类型
 */
typedef void (*rmdev_test_testFinishCallback)(void);

/**
 * 测试错误处理
 * @param error_code 错误码
 */
typedef void (*rmdev_test_errorCallback)(rmdev_test_ErrorCode error_code);

/**
 * 需要由用户自定义的回调函数
 */
typedef struct rmdev_test_Callbacks {
    rmdev_test_printfCallback printfCallback;          ///< 格式化输出回调函数
    rmdev_test_delayCallback delayCallback;            ///< 延时回调函数
    rmdev_test_testEntryCallback testEntryCallback;    ///< 测试入口回调函数

    rmdev_test_testFinishCallback testFinishCallback;  ///< 测试结束（正常退出）回调函数
                                                       ///< @note 这个函数指针可以传入 @c NULL
                                                       ///< 以表示使用默认的结束方式：进入一个无限空循环
    rmdev_test_errorCallback errorCallback;            ///< 错误处理回调函数
                                                       ///< @note 这个函数指针可以传入 @c NULL
                                                       ///< 以表示使用默认的错误处理方式：进入一个无限空循环
} rmdev_test_Callbacks;

/**
 * 测试夹具
 */
typedef struct rmdev_test_TestFixture {
    void (*setUp)(struct rmdev_test_TestFixture* this_);
    void (*tearDown)(struct rmdev_test_TestFixture* this_);
} rmdev_test_TestFixture;

/**
 * 测试套件
 */
typedef struct rmdev_test_TestSuit {
    const char* name;                           ///< 名称

    rmdev_test_TestFixture* fixture;            ///< 测试夹具

    int total_count;                            ///< 当前这个测试套件中，测试计数
    int success_count;                          ///< 当前这个测试套件中，成功计数
    int fail_count;                             ///< 当前这个测试套件中，失败计数

    void (*body)(struct rmdev_test_TestSuit*);  ///< 测试内容
} rmdev_test_TestSuit;

/**
 * 作比较的方式
 */
enum rmdev_test_CompareType {
    RMDEV_TEST_COMPARE_EQUAL = 0,      ///< @c EQ 等于
    RMDEV_TEST_COMPARE_NOT_EQUAL,      ///< @c NE 不等于
    RMDEV_TEST_COMPARE_GREATER_THAN,   ///< @c GT 大于
    RMDEV_TEST_COMPARE_LESS_THAN,      ///< @c LT 小于
    RMDEV_TEST_COMPARE_GREATER_EQUAL,  ///< @c GE 大于等于
    RMDEV_TEST_COMPARE_LESS_EQUAL      ///< @c LE 小于等于
};

/**
 * 进行检查的类型
 */
enum rmdev_test_CheckType_ {
    RMDEV_TEST_CHECK_TYPE_EXPECT = 0,        ///< @c EXPECT 期望
    RMDEV_TEST_CHECK_TYPE_ASSERT             ///< @c ASSERT 断言
};
typedef unsigned char rmdev_test_CheckType;  ///< 检查类型

/**
 * 比较信息
 */
typedef struct rmdev_test_CompareMsg {
    rmdev_test_TestSuit* test_suit;     ///< 测试套件指针

    const char* file;                   ///< 调用函数所在的文件名
    int line;                           ///< 调用函数所在的行号

    const char* compare_type_msg;       ///< 比较方式的信息

    const char* current_case_name;      ///< 当前测试的名称

    const char* lhs_name;               ///< 左侧参数的名称
    const char* lhs_value;              ///< 左侧参数的值（字符串形式）
    const char* rhs_name;               ///< 右侧参数的名称
    const char* rhs_value;              ///< 右侧参数的值（字符串形式）

    rmdev_test_bool_t is_passed;        ///< 测试通过

    rmdev_test_printfCallback message;  ///< 输出信息的格式化输出回调函数
} rmdev_test_CompareMsg;

extern rmdev_test_printfCallback rmdev_test___printfCallback___;
extern const char* rmdev_test___line_break_character___;

/**
 * 测试夹具 - 构造函数
 * @param this_ 用户自定义的测试夹具
 * @param setUp 测试样例执行前的行为
 * @param tearDown 测试样例执行后的行为
 */
void rmdev_test_TestFixture_Constructor(void* this_,
                                        void (*setUp)(rmdev_test_TestFixture* this_),
                                        void (*tearDown)(rmdev_test_TestFixture* this_));
void rmdev_test_run_test(rmdev_test_TestSuit* test_suit);

#define RMDEV_TEST_TEST_SUIT(test_suit) void rmdev_test__##test_suit##__(rmdev_test_TestSuit* rmdev___suit)

#define RMDEV_TEST_TEST_CASE_BEGIN(case_name)                        \
    do {                                                             \
        const char* rmdev___case_name = #case_name;                  \
        rmdev_test_CompareMsg rmdev___msg;                           \
                                                                     \
        if (rmdev___suit->fixture != RMDEV_TEST_NULL) {              \
            if (rmdev___suit->fixture->setUp != RMDEV_TEST_NULL) {   \
                rmdev___suit->fixture->setUp(rmdev___suit->fixture); \
            }                                                        \
        }

#define RMDEV_TEST_TEST_CASE_END(void)                              \
    if (rmdev___suit->fixture != RMDEV_TEST_NULL) {                 \
        if (rmdev___suit->fixture->tearDown != RMDEV_TEST_NULL) {   \
            rmdev___suit->fixture->tearDown(rmdev___suit->fixture); \
        }                                                           \
    }                                                               \
    }                                                               \
    while (0)

#define RMDEV_TEST_RUN_SUIT(test_suit)                                                \
    do {                                                                              \
        rmdev_test_TestSuit rmdev___test_suit = {.name = #test_suit,                  \
                                                 .body = rmdev_test__##test_suit##__, \
                                                 .fixture = RMDEV_TEST_NULL,          \
                                                 .total_count = 0,                    \
                                                 .success_count = 0,                  \
                                                 .fail_count = 0};                    \
        rmdev_test_run_test(&rmdev___test_suit);                                      \
    } while (0)

#define RMDEV_TEST_RUN_SUIT_F(test_suit, test_fixture_instance)                                        \
    do {                                                                                               \
        rmdev_test_TestFixture* rmdev_test___fixture = (rmdev_test_TestFixture*)test_fixture_instance; \
        rmdev_test_TestSuit rmdev___test_suit = {.name = #test_suit,                                   \
                                                 .body = rmdev_test__##test_suit##__,                  \
                                                 .fixture = rmdev_test___fixture,                      \
                                                 .total_count = 0,                                     \
                                                 .success_count = 0,                                   \
                                                 .fail_count = 0};                                     \
        rmdev_test_run_test(&rmdev___test_suit);                                                       \
    } while (0)

const rmdev_test_CompareMsg* rmdev_test_checkTure(rmdev_test_CompareMsg* msg,
                                                  rmdev_test_CheckType check_type,
                                                  rmdev_test_bool_t result);
const rmdev_test_CompareMsg* rmdev_test_checkFalse(rmdev_test_CompareMsg* msg,
                                                   rmdev_test_CheckType check_type,
                                                   rmdev_test_bool_t result);
void rmdev_test_assertFailEntry(void);

#define RMDEV_TEST_EXPECT_TRUE(result)                  \
    (rmdev___msg.test_suit = rmdev___suit,              \
     rmdev___msg.file = __FILE__,                       \
     rmdev___msg.line = __LINE__,                       \
     rmdev___msg.current_case_name = rmdev___case_name, \
     rmdev___msg.rhs_name = #result,                    \
     rmdev_test_checkTure(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, result))

#define RMDEV_TEST_EXPECT_FALSE(result)                 \
    (rmdev___msg.test_suit = rmdev___suit,              \
     rmdev___msg.file = __FILE__,                       \
     rmdev___msg.line = __LINE__,                       \
     rmdev___msg.current_case_name = rmdev___case_name, \
     rmdev___msg.rhs_name = #result,                    \
     rmdev_test_checkFalse(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, result))

#define RMDEV_TEST_ASSERT_TRUE(result, format, ...)                                     \
    do {                                                                                \
        rmdev___msg.test_suit = rmdev___suit;                                           \
        rmdev___msg.file = __FILE__;                                                    \
        rmdev___msg.line = __LINE__;                                                    \
        rmdev___msg.current_case_name = rmdev___case_name;                              \
        rmdev___msg.rhs_name = #result;                                                 \
        rmdev_test_checkTure(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_ASSERT, result);       \
        if (!rmdev___msg.is_passed) {                                                   \
            rmdev_test___printfCallback___(format, ##__VA_ARGS__);                      \
            rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___); \
            rmdev_test_assertFailEntry();                                               \
        }                                                                               \
    } while (0)

#define RMDEV_TEST_ASSERT_FALSE(result, format, ...)                                    \
    do {                                                                                \
        rmdev___msg.test_suit = rmdev___suit;                                           \
        rmdev___msg.file = __FILE__;                                                    \
        rmdev___msg.line = __LINE__;                                                    \
        rmdev___msg.current_case_name = rmdev___case_name;                              \
        rmdev___msg.rhs_name = #result;                                                 \
        rmdev_test_checkFalse(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_ASSERT, result);      \
        if (!rmdev___msg.is_passed) {                                                   \
            rmdev_test___printfCallback___(format, ##__VA_ARGS__);                      \
            rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___); \
            rmdev_test_assertFailEntry();                                               \
        }                                                                               \
    } while (0)

#define RMDEV_TEST_MESSAGE(format, ...)                                 \
    is_passed ? ((void)0)                                               \
              : (rmdev_test___printfCallback___(format, ##__VA_ARGS__), \
                 rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___))

/**
 * rmdev 测试框架 主函数
 * @attention 需要将其放在真正的 main 函数中调用
 * @param line_break 换行符
 * @param callback 回调函数
 */
void rmdev_test_framework_main(const char* line_break, const rmdev_test_Callbacks* callback);

#ifdef __cplusplus
}
#endif

#endif  // RMDEV_TEST_FRAMEWORK_H
