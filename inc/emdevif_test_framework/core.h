/**
 * @file core.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 核心声明
 */

#pragma once
#ifndef EMDEVIF_TEST_CORE_H
#define EMDEVIF_TEST_CORE_H

#include <stddef.h>

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#include <stdbool.h>

#define EMDEVIF_TEST_USE_STD_BOOL 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define EMDEVIF_TEST_NULL NULL

#if (defined(EMDEVIF_TEST_USE_STD_BOOL) && EMDEVIF_TEST_USE_STD_BOOL)

typedef bool emdevif_test_bool_t;
#define EMDEVIF_TEST_TRUE  true
#define EMDEVIF_TEST_FALSE false

#else  // (defined(EMDEVIF_TEST_USE_STD_BOOL) && EMDEVIF_TEST_USE_STD_BOOL)

typedef unsigned char emdevif_test_bool_t;
#define EMDEVIF_TEST_TRUE  (1U)
#define EMDEVIF_TEST_FALSE (0U)

#endif  // (defined(EMDEVIF_TEST_USE_STD_BOOL) && EMDEVIF_TEST_USE_STD_BOOL)

/**
 * 错误码
 */
typedef enum emdevif_test_ErrorCode {
    EMDEVIF_TEST_EXIST_FAIL = 1,               ///< 存在未通过的测试
    EMDEVIF_TEST_ALL_PASSED = 0,               ///< 全部测试通过

    EMDEVIF_TEST_NO_ERROR = 0,                 ///< 无错误
    EMDEVIF_TEST_NO_BREAK_CHARACTER = -1,      ///< 没有设置换行符
    EMDEVIF_TEST_NO_PRINTF_CALLBACK = -2,      ///< 没有设置 printf 回调函数
    EMDEVIF_TEST_NO_TEST_ENTRY_CALLBACK = -3,  ///< 没有设置 testEntry 回调函数
    EMDEVIF_TEST_TEST_SUIT_COUNT_ERROR = -4,   ///< 测试项计数与成功、错误的项目计数不匹配
    EMDEVIF_TEST_OTHER_ERROR = -5              ///< 其他错误
} emdevif_test_ErrorCode;

/**
 * emdevif 测试框架 格式化输出回调函数类型
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
typedef void (*emdevif_test_printfCallback)(const char* format, ...);

/**
 * emdevif 测试框架 测试入口回调函数类型
 */
typedef void (*emdevif_test_testEntryCallback)(void);

/**
 * 测试结束回调函数类型
 * @param error_code 错误码。测试全部通过传入 EMDEVIF_TEST_ALL_PASSED，否则传入 EMDEVIF_TEST_EXIST_FAIL
 */
typedef void (*emdevif_test_testFinishCallback)(emdevif_test_ErrorCode error_code);

/**
 * 测试错误处理
 * @param error_code 错误码
 */
typedef void (*emdevif_test_errorCallback)(emdevif_test_ErrorCode error_code);

/**
 * 需要由用户自定义的回调函数
 */
typedef struct emdevif_test_Callbacks {
    emdevif_test_printfCallback printfCallback;          ///< 格式化输出回调函数
    emdevif_test_testEntryCallback testEntryCallback;    ///< 测试入口回调函数

    emdevif_test_testFinishCallback testFinishCallback;  ///< 测试结束（正常退出）回调函数
                                                         ///< @note 这个函数指针可以传入 @c NULL
                                                         ///< 以表示使用默认的结束方式：进入一个无限空循环
    emdevif_test_errorCallback errorCallback;            ///< 错误处理回调函数
                                                         ///< @note 这个函数指针可以传入 @c NULL
                                                         ///< 以表示使用默认的错误处理方式：进入一个无限空循环
} emdevif_test_Callbacks;

/**
 * 测试夹具
 */
typedef struct emdevif_test_TestFixture {
    void (*setUp)(struct emdevif_test_TestFixture* this_);
    void (*tearDown)(struct emdevif_test_TestFixture* this_);
} emdevif_test_TestFixture;

/**
 * 测试套件
 */
typedef struct emdevif_test_TestSuit {
    const char* name;                             ///< 名称

    emdevif_test_TestFixture* fixture;            ///< 测试夹具

    int total_count;                              ///< 当前这个测试套件中，测试计数
    int success_count;                            ///< 当前这个测试套件中，成功计数
    int fail_count;                               ///< 当前这个测试套件中，失败计数

    void (*body)(struct emdevif_test_TestSuit*);  ///< 测试内容
} emdevif_test_TestSuit;

/**
 * 作比较的方式
 */
typedef enum emdevif_test_CompareType {
    EMDEVIF_TEST_COMPARE_EQUAL = 0,      ///< @c EQ 等于
    EMDEVIF_TEST_COMPARE_NOT_EQUAL,      ///< @c NE 不等于
    EMDEVIF_TEST_COMPARE_GREATER_THAN,   ///< @c GT 大于
    EMDEVIF_TEST_COMPARE_LESS_THAN,      ///< @c LT 小于
    EMDEVIF_TEST_COMPARE_GREATER_EQUAL,  ///< @c GE 大于等于
    EMDEVIF_TEST_COMPARE_LESS_EQUAL      ///< @c LE 小于等于
} emdevif_test_CompareType;

/**
 * 进行检查的类型
 */
enum emdevif_test_CheckType_ {
    EMDEVIF_TEST_CHECK_TYPE_EXPECT = 0,        ///< @c EXPECT 期望
    EMDEVIF_TEST_CHECK_TYPE_ASSERT             ///< @c ASSERT 断言
};
typedef unsigned char emdevif_test_CheckType;  ///< 检查类型

/**
 * 比较信息
 */
typedef struct emdevif_test_CompareMsg {
    emdevif_test_TestSuit* test_suit;  ///< 测试套件指针

    const char* file;                  ///< 调用函数所在的文件名
    int line;                          ///< 调用函数所在的行号

    const char* compare_type_name;     ///< 比较方式的信息

    const char* current_case_name;     ///< 当前测试的名称

    const char* lhs_name;              ///< 左侧参数的名称
    const char* lhs_value;             ///< 左侧参数的值（字符串形式）
    const char* rhs_name;              ///< 右侧参数的名称
    const char* rhs_value;             ///< 右侧参数的值（字符串形式）

    emdevif_test_bool_t is_passed;     ///< 测试通过
} emdevif_test_CompareMsg;

/**
 * 测试运行的钩子函数
 */
typedef struct emdevif_test_Hooks {
    /**
     * 测试开始钩子
     */
    void (*testBeginHook)(void);

    /**
     * 测试结束钩子
     * @param suit_total 测试套件总数
     * @param suit_passed 测试套件通过数
     * @param suit_failed 测试套件失败数
     */
    void (*testEndHook)(int suit_total, int suit_passed, int suit_failed);

    /**
     * 测试套件开始钩子
     * @param test_suit 当前的测试套件
     */
    void (*testSuitBeginHook)(emdevif_test_TestSuit* test_suit);

    /**
     * 测试套件结束钩子
     * @param test_suit 当前的测试套件
     */
    void (*testSuitEndHook)(emdevif_test_TestSuit* test_suit);

    /**
     * 测试用例开始钩子
     * @param compare_msg 比较信息
     */
    void (*testCaseBeginHook)(emdevif_test_CompareMsg* compare_msg);

    /**
     * 测试用例结束钩子
     * @param compare_msg 比较信息
     */
    void (*testCaseEndHook)(emdevif_test_CompareMsg* compare_msg);
} emdevif_test_Hooks;

extern emdevif_test_printfCallback emdevif_test___printfCallback___;
extern const char* emdevif_test___line_break_character___;
extern emdevif_test_Hooks emdevif_test___hooks___;

extern emdevif_test_TestSuit emdevif_current_test_suit_;
extern emdevif_test_CompareMsg emdevif_current_test_compare_message_;

/**
 * 执行钩子函数
 * @attention 由框架内部调用
 * @param func 待运行的钩子函数
 * @param ... 钩子函数的参数
 */
#define EMDEVIF_TEST__RUN_HOOK(func, ...) (func == EMDEVIF_TEST_NULL ? ((void)0) : func(__VA_ARGS__))

/**
 * 测试夹具 - 构造函数
 * @param this_ 用户自定义的测试夹具
 * @param setUp 测试样例执行前的行为
 * @param tearDown 测试样例执行后的行为
 */
void emdevif_test_TestFixture_Constructor(void* this_,
                                          void (*setUp)(emdevif_test_TestFixture* this_),
                                          void (*tearDown)(emdevif_test_TestFixture* this_));
void emdevif_test_run_test_suit(emdevif_test_TestSuit* test_suit);

// 由于 C 语言有复合字面量（compound_literal），但 ISO C++ 不支持这个特性。
// 因此使用宏，根据环境自动选择结构体赋值的方式
#ifndef __cplusplus
#define EMDEVIF_TEST_ASSIGNMENT_COMPOUND_LITERAL(var, type, ...) \
    var = (type)                                                 \
    {                                                            \
        __VA_ARGS__                                              \
    }
#else
#define EMDEVIF_TEST_ASSIGNMENT_COMPOUND_LITERAL(var, type, ...) var = {__VA_ARGS__}
#endif

#define EMDEVIF_TEST_TEST_SUIT(test_suit) void emdevif_test__##test_suit##__(emdevif_test_TestSuit* emdevif___suit)

#define EMDEVIF_TEST_TEST_CASE_BEGIN(case_name)                                                                    \
    do {                                                                                                           \
        const char* emdevif___case_name = #case_name;                                                              \
                                                                                                                   \
        EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testCaseBeginHook, &emdevif_current_test_compare_message_); \
                                                                                                                   \
        if (emdevif___suit->fixture != EMDEVIF_TEST_NULL) {                                                        \
            if (emdevif___suit->fixture->setUp != EMDEVIF_TEST_NULL) {                                             \
                emdevif___suit->fixture->setUp(emdevif___suit->fixture);                                           \
            }                                                                                                      \
        }

#define EMDEVIF_TEST_TEST_CASE_END(void)                                                                     \
    if (emdevif___suit->fixture != EMDEVIF_TEST_NULL) {                                                      \
        if (emdevif___suit->fixture->tearDown != EMDEVIF_TEST_NULL) {                                        \
            emdevif___suit->fixture->tearDown(emdevif___suit->fixture);                                      \
        }                                                                                                    \
    }                                                                                                        \
                                                                                                             \
    EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testCaseEndHook, &emdevif_current_test_compare_message_); \
    }                                                                                                        \
    while (0)

#define EMDEVIF_TEST_RUN_SUIT(test_suit)                                         \
    do {                                                                         \
        EMDEVIF_TEST_ASSIGNMENT_COMPOUND_LITERAL(emdevif_current_test_suit_,     \
                                                 emdevif_test_TestSuit,          \
                                                 #test_suit,                     \
                                                 EMDEVIF_TEST_NULL,              \
                                                 0,                              \
                                                 0,                              \
                                                 0,                              \
                                                 emdevif_test__##test_suit##__); \
        emdevif_test_run_test_suit(&emdevif_current_test_suit_);                 \
    } while (0)

#define EMDEVIF_TEST_RUN_SUIT_F(test_suit, test_fixture_instance)                                            \
    do {                                                                                                     \
        emdevif_test_TestFixture* emdevif_test___fixture = (emdevif_test_TestFixture*)test_fixture_instance; \
        EMDEVIF_TEST_ASSIGNMENT_COMPOUND_LITERAL(emdevif_current_test_suit_,                                 \
                                                 emdevif_test_TestSuit,                                      \
                                                 #test_suit,                                                 \
                                                 emdevif_test___fixture,                                     \
                                                 0,                                                          \
                                                 0,                                                          \
                                                 0,                                                          \
                                                 emdevif_test__##test_suit##__);                             \
        emdevif_test_run_test_suit(&emdevif_current_test_suit_);                                             \
    } while (0)

#ifdef __cplusplus

/**
 * 如果要在 C++ lambda 表达式中运行测试，需要在捕获列表中传入这个宏
 */
#define EMDEVIF_TEST_LAMBDA_CAPTURE &emdevif___case_name, &emdevif___suit

#endif

const emdevif_test_CompareMsg* emdevif_test_strEqual(emdevif_test_CompareMsg* msg,
                                                     emdevif_test_CheckType check_type,
                                                     const char* lhs,
                                                     const char* rhs);
const emdevif_test_CompareMsg* emdevif_test_intCompare(emdevif_test_CompareMsg* msg,
                                                       emdevif_test_CheckType check_type,
                                                       emdevif_test_CompareType compare_type,
                                                       int lhs,
                                                       int rhs);
const emdevif_test_CompareMsg* emdevif_test_uintCompare(emdevif_test_CompareMsg* msg,
                                                        emdevif_test_CheckType check_type,
                                                        emdevif_test_CompareType compare_type,
                                                        unsigned int lhs,
                                                        unsigned int rhs);
const emdevif_test_CompareMsg* emdevif_test_floatPointCompare(emdevif_test_CompareMsg* msg,
                                                              emdevif_test_CheckType check_type,
                                                              emdevif_test_CompareType compare_type,
                                                              double lhs,
                                                              double rhs);
const emdevif_test_CompareMsg* emdevif_test_checkTure(emdevif_test_CompareMsg* msg,
                                                      emdevif_test_CheckType check_type,
                                                      emdevif_test_bool_t result);
const emdevif_test_CompareMsg* emdevif_test_checkFalse(emdevif_test_CompareMsg* msg,
                                                       emdevif_test_CheckType check_type,
                                                       emdevif_test_bool_t result);
void emdevif_test_assertFailEntry(void);

#define EMDEVIF_TEST_MESSAGE(format, ...)                                 \
    is_passed ? ((void)0)                                                 \
              : (emdevif_test___printfCallback___(format, ##__VA_ARGS__), \
                 emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___))

#define EMDEVIF_TEST_TEST_LOG(format, ...)                                                   \
    do {                                                                                     \
        emdevif_test___printfCallback___("%s[LOG]", emdevif_test___line_break_character___); \
        emdevif_test___printfCallback___(format, ##__VA_ARGS__);                             \
        emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___);      \
    } while (0)

/**
 * emdevif 测试框架 主函数
 * @attention 需要将其放在真正的 main 函数中调用
 * @param line_break 换行符
 * @param callback 回调函数
 * @param user_hooks 钩子函数。如果不需要，传入 @c NULL 即可
 */
void emdevif_test_framework_main(const char* line_break,
                                 const emdevif_test_Callbacks* callback,
                                 const emdevif_test_Hooks* user_hooks);

#ifdef __cplusplus
}
#endif

#endif  // !EMDEVIF_TEST_CORE_H
