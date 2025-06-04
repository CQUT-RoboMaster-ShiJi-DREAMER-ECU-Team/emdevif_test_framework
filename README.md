# rmdev_test_framework

一个纯 C
语言，适用于单片机开发的简易测试框架。也是 [rmdev](https://github.com/CQUT-RoboMaster-ShiJi-DREAMER-ECU-Team/rmdev)
的一个子项目。

## 使用方法

### 依赖

CMake 3.5 或更高版本。

### 安装框架

#### 方法1

直接将仓库文件下载到本地，然后通过 `add_subdirectory()` 函数将其添加到 CMakeLists.txt 中。

#### 方法2

使用 FetchContent（暂时不要，因为目前是私有库，不方便指定链接）

#### 方法3（不使用 CMake 也可以）

将仓库内的 `inc` 与 `src` 内的文件分别添加到编译器的头文件和源文件选项中编译即可。

### 使用步骤

1. 将 `rmdev_test_framework.h` 头文件包含到主函数所在的文件中。
2. 在测试代码的主函数中调用 `rmdev_test_framework_main()` 函数。相关参数可参考阅读函数的注释。
