/**
 * @file rmdev_test_framework.h
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#pragma once
#ifndef RMDEV_TEST_FRAMEWORK_H
#define RMDEV_TEST_FRAMEWORK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char rmdev_test_bool_t;
#define RMDEV_TEST_TRUE  (1U)
#define RMDEV_TEST_FALSE (0U)

#define RMDEV_TEST_NULL  ((void*)0)

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
 * rmdev 测试框架 测试项回调函数类型
 */
typedef void (*rmdev_test_testItemCallback)(void);

/**
 * rmdev 测试框架 主函数
 * @attention 需要将其放在真正的 main 函数中调用
 * @param break_char 换行符
 * @param printfCallback 用于格式化输出的回调函数
 * @param delayCallback 用于延时的回调函数
 * @param testItemCallback 运行测试项的回调函数（你执行的测试在这个函数里执行）
 */
void rmdev_test_framework_main(const char* break_char,
                               rmdev_test_printfCallback printfCallback,
                               rmdev_test_delayCallback delayCallback,
                               rmdev_test_testItemCallback testItemCallback);

/**
 * rmdev 测试框架 定义一个测试项
 * @attention 不建议直接调用这个函数，而是使用宏 RMDEV_TEST_ITEM，因为这个宏可以自动填写文件名与行号
 * @param name 测试项名称
 * @param file 调用函数所在的文件名
 * @param line 调用函数所在的行号
 */
void rmdev_test_item(const char* name, const char* file, int line);

/**
 * rmdev 测试框架 定义一个测试项
 * @param name 测试项名称
 */
#define RMDEV_TEST_ITEM(name) rmdev_test_item((name), __FILE__, __LINE__)

/**
 * rmdev 测试框架 检查布尔表达式是否正确（测试失败后会继续运行）
 * @attention 不建议直接调用这个函数，而是使用宏 RMDEV_TEST_CHECK，因为这个宏可以自动填写文件名与行号
 * @param file 调用函数所在的文件名
 * @param line 调用函数所在的行号
 * @param result 待检查的布尔表达式
 */
void rmdev_test_check(const char* file, int line, rmdev_test_bool_t result);

/**
 * rmdev 测试框架 检查布尔表达式是否正确（测试失败后会继续运行）
 * @param result 待检查的布尔表达式
 */
#define RMDEV_TEST_CHECK(result) rmdev_test_check(__FILE__, __LINE__, (result))

/**
 * rmdev 测试框架 断言布尔表达式是否正确（测试失败后会停止测试）
 * @attention 不建议直接调用这个函数，而是使用宏 RMDEV_TEST_ASSERT，因为这个宏可以自动填写文件名与行号
 * @param file 调用函数所在的文件名
 * @param line 调用函数所在的行号
 * @param result 待检查的布尔表达式
 */
void rmdev_test_assert(const char* file, int line, rmdev_test_bool_t result);

/**
 * rmdev 测试框架 断言布尔表达式是否正确（测试失败后会停止测试）
 * @param result 待检查的布尔表达式
 */
#define RMDEV_TEST_ASSERT(result) rmdev_test_assert(__FILE__, __LINE__, (result))

#ifdef __cplusplus
}
#endif

#endif  // RMDEV_TEST_FRAMEWORK_H
