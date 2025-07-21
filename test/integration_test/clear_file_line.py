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

FILE_NAME_EXTENSION: str = ".c:"


def replace_sub_string(dst: str, begin: int, end: int, src: str):
    return dst[:begin] + src + dst[end:]


for i in range(0, len(file_lines)):
    extension_index: int = file_lines[i].find(FILE_NAME_EXTENSION)

    if extension_index == -1:
        continue

    begin_index: int = extension_index

    while begin_index >= 0 and file_lines[i][begin_index] != " ":
        begin_index -= 1
    begin_index += 1

    extension_index += len(FILE_NAME_EXTENSION) - 1

    assert file_lines[i][extension_index] == ":"
    assert file_lines[i][begin_index - 1] == " "

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
