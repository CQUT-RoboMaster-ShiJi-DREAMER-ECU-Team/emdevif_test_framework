# emdevif_test_framework

一个纯 C 语言，适用于嵌入式平台的简易测试框架。也是 [emdevif](https://github.com/CQUT-RoboMaster-ShiJi-DREAMER-ECU-Team/emdevif)
的一个子项目（不依赖 emdevif，可以独立运行）。

## 特点

* 纯C语言实现
* 依赖项少，对嵌入式平台友好
* 支持通过注册钩子函数以获取测试信息，或者与其他测试框架关联

## 构建

首先使用 `git clone` 或 `git submodule add`（推荐）将此仓库添加到你的仓库中。

### 使用 CMake 构建

通过 `add_subdirectory()` 函数将其添加到 CMakeLists.txt 中：
```CMake
add_subdirectory(
    # path to emdevif_test_framework
)

target_link_libraries(
    # your project name
    # PUBLIC / PRIVATE / INTERFACE
    emdevif_test_framework
)
```
即可将库链接到你的工程中。

### 其他构建系统

将仓库内的 `inc` 与 `src` 内的文件分别添加到编译器的头文件路径和源文件中编译即可（头文件仅需添加 `inc` 路径，子路径无需增加）。

## 使用方式

* 一个简单的示例：
```C
#include <stdio.h>
#include "emdevif_test_framework.h"  // required

void myPrintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

TEST_SUIT(MyTestSuit)
{
    TEST_CASE_BEGIN(TestCase1)
    {
        EXPECT_TRUE(1 == 1)->MESSAGE("If failed, it will print.");
        EXPECT_FALSE(114514 == 1919810)->MESSAGE("Support %s", "format in printf style.");
        EXPECT_FALSE(67978 == 0);
        ASSERT_TRUE(1 == 1, "Assert macros must add message here. If failed, it will print and stop test");
        ASSERT_TRUE(2 != 1, "Support %s", "format in printf style too.");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(TestCase2)
    {
        INT_EXPECT_EQ(3, 3);
        INT_EXPECT_GT(235326, -45);
        INT_EXPECT_NE(1, 2);
        INT_EXPECT_GE(2, -9);
        INT_EXPECT_GE(2, 2);
        INT_EXPECT_LT(-9, 0);
        INT_EXPECT_LE(-1, 0);
        INT_EXPECT_LE(-114514, -114514);

        INT_ASSERT_EQ(1, 1, "");
        
        UINT_EXPECT_EQ(1234U, 1234U);
        FP_EXPECT_EQ(123.456, 123.456);
    }
    TEST_CASE_END();
    // you can add more cases...
}

static void testEntry(void)
{
    RUN_SUIT(MyTestSuit);
}

int main(void)
{
    const emdevif_test_Callbacks callback = {.printfCallback = myPrintf,
                                             .testEntryCallback = testEntry,
                                             .testFinishCallback = testFinishHandler};

    emdevif_test_framework_main("\n", &callback, NULL);

    return 0;
}
```

* 支持多文件：
```C
// external.c

#include "emdevif_test_framework.h"

TEST_SUIT(ExternalSuit)
{
    TEST_CASE_BEGIN(TestCase1)
    {
        EXPECT_TRUE(1 == 1);
    }
    TEST_CASE_END();
}
```
```C
// main.c

#include "emdevif_test_framework.h"

TEST_SUIT(ExternalSuit);  // similar to declare a function

static void testEntry(void)
{
    RUN_SUIT(ExternalSuit);
}
```

* 支持测试夹具。使用方式参考[集成测试](./test/integration_test/classic_test/external_test.c)中的 FixtureTest。

## 自定义配置

### 预定义宏

您可以通过预定义宏以配置 emdevif 的一些属性。

| 预定义宏                            | 预定义宏的值的类型 | 预定义宏的含义                                             |
|---------------------------------|-----------|-----------------------------------------------------|
| EMDEVIF_TEST_VALUE_BUFFER_SIZE  | size_t    | 存储 ASSERT 与 EXPECT 宏的数值的字符串长度，默认为 64。               |
| EMDEVIF_TEST_FLOAT_EQUAL_ERROR  | double    | 浮点数等于判定的误差值，即两个浮点类型数据之差的绝对值小于这个值即认为它们相等，默认为 0.0001。 |

使用 CMake 预定义宏的示例：
```CMake
add_subdirectory(
    # path to emdevif_test_framework
)
target_compile_definitions(emdevif_test_framework INTERFACE EMDEVIF_TEST_VALUE_BUFFER_SIZE=128)  # example about how to set macro EMDEVIF_TEST_VALUE_BUFFER_SIZE to 128

target_link_libraries(
    # your project name
    # PUBLIC / PRIVATE / INTERFACE
    emdevif_test_framework
)
```
