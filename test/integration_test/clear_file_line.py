#!/bin/python

# 用于将测试函数的输出文件（.out）中的文件名与行号进行替换（替换成 __FILE__:__LINE__）

import sys

if len(sys.argv) != 2:
    print("Usage: python clear_file_line.py <file_name_no_extension>")
    exit(1)

try:
    output_file = open(sys.argv[1] + ".out", "r")
except FileNotFoundError:
    print(f"File {sys.argv[1]}.out not found!")
    exit(1)
except Exception as e:
    print(f"An error occurred while opening the file: {e}")
    exit(1)

try:
    file_lines = output_file.readlines()
except Exception as e:
    print(f"An error occurred while reading the file: {e}")
    output_file.close()
    exit(1)

output_file.close()


def replace_sub_string(src: str, begin: int, end: int, replace: str) -> str:
    """
    将字符串的给定区间替换成指定字符串
    :param src: 待进行替换的字符串
    :param begin: 区间开头
    :param end: 区间结尾
    :param replace: 用于替换的字符串
    :return: 替换后的字符串
    """
    if begin >= end:
        return src

    return src[:begin] + replace + src[end:]


def width_of_num(src: str) -> int:
    """
    计算给定字符串中的数字字符的宽度
    :param src: 字符串
    :return: 数字字符的宽度
    """
    _i: int = 0
    while src[_i].isdigit():
        _i += 1

    return _i


FILE_NAME_EXTENSIONS: list[str] = [".c:", ".cpp:"]

# 逐行检测并替换文件名与行号
for i in range(0, len(file_lines)):
    extension_index: int = file_lines[i].find(FILE_NAME_EXTENSIONS[0])
    is_cpp: bool = False

    if extension_index == -1:
        extension_index = file_lines[i].find(FILE_NAME_EXTENSIONS[1])
        is_cpp = True

    if extension_index == -1:
        continue

    begin_index: int = extension_index

    while begin_index >= 0 and file_lines[i][begin_index] != " ":
        begin_index -= 1
    begin_index += 1

    if is_cpp:
        extension_index += len(FILE_NAME_EXTENSIONS[1]) - 1
    else:
        extension_index += len(FILE_NAME_EXTENSIONS[0]) - 1

    assert file_lines[i][extension_index] == ":"
    assert file_lines[i][begin_index - 1] == " "

    line_tmp: str = file_lines[i][extension_index + 1:]
    line_num_width = width_of_num(line_tmp)
    if line_num_width == 0:
        continue
    else:
        if file_lines[i][extension_index + line_num_width + 1] != ":":
            continue

    FILE_BEGIN_INDEX: int = begin_index

    extension_index += 1
    assert file_lines[i][extension_index].isdigit()

    num_head: int = extension_index
    num_tail: int = num_head
    while file_lines[i][num_tail] != ":":
        num_tail += 1

    assert file_lines[i][num_tail] == ":"

    file_lines[i] = replace_sub_string(file_lines[i], FILE_BEGIN_INDEX, num_tail, "__FILE__:__LINE__")

result: str = ""
for line in file_lines:
    result += line

try:
    write_file = open(sys.argv[1] + ".out", "w")
except FileNotFoundError:
    print(f"File {sys.argv[1]}.out not found!")
    exit(1)
except Exception as e:
    print(f"An error occurred while opening the file: {e}")
    exit(1)

try:
    write_file.write(result)
except Exception as e:
    print(f"An error occurred while writing to the file: {e}")
    exit(1)

exit(0)
