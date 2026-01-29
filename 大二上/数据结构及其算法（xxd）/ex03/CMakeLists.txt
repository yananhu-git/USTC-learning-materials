cmake_minimum_required(VERSION 3.10)
project(EX02 C)

# 设置C标准（可选）
set(CMAKE_C_STANDARD 99)

# 包含头文件目录（如果有子目录可以在这里加）
# include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件，并指定源文件
add_executable(ex02
    huffman.c
    main.c
)