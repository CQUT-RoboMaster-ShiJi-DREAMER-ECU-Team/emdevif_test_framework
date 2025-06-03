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
#define RMDEV_TEST_TRUE  1U
#define RMDEV_TEST_FALSE 0U

/**
 * rmdev 测试框架 主函数
 * @attention 需要将其放在真正的 main 函数中调用
 */
void rmdev_test_framework_main(void);

/**
 * rmdev 测试框架 检查布尔表达式是否正确（测试失败后会继续运行）
 * @attention 不建议直接调用这个函数，而是使用宏 RMDEV_TEST_CHECK，因为这个宏可以自动填写文件名与行号
 * @param name 测试名称
 * @param file 调用函数所在的文件名
 * @param line 调用函数所在的行号
 * @param result 待检查的布尔表达式
 */
void rmdev_test_check(const char* name, const char* file, int line, rmdev_test_bool_t result);

/**
 * rmdev 测试框架 检查布尔表达式是否正确（测试失败后会继续运行）
 * @param name 测试名称
 * @param result 待检查的布尔表达式
 */
#define RMDEV_TEST_CHECK(name, result) rmdev_test_check(name, __FILE__, __LINE__, result)

/**
 * rmdev 测试框架 断言布尔表达式是否正确（测试失败后会停止测试）
 * @attention 不建议直接调用这个函数，而是使用宏 RMDEV_TEST_CHECK，因为这个宏可以自动填写文件名与行号
 * @param name 测试名称
 * @param file 调用函数所在的文件名
 * @param line 调用函数所在的行号
 * @param result 待检查的布尔表达式
 */
void rmdev_test_assert(const char* name, const char* file, int line, rmdev_test_bool_t result);

/**
 * rmdev 测试框架 断言布尔表达式是否正确（测试失败后会停止测试）
 * @param name 测试名称
 * @param result 待检查的布尔表达式
 */
#define RMDEV_TEST_ASSERT(name, result) rmdev_test_assert(name, __FILE__, __LINE__, result)

#ifdef __cplusplus
}
#endif

#endif  // RMDEV_TEST_FRAMEWORK_H
