# CMakeList.txt: MMPlayer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories(../)

link_directories(../3rdpart/ffmpeg/lib)

# 将源代码添加到此项目的可执行文件。
add_executable (MMPlayer "MMPlayer.cpp" "MMPlayer.h")

target_link_libraries(MMPlayer MMThread)
target_link_libraries(MMPlayer MMAV)

target_link_libraries(MMPlayer avcodec)
target_link_libraries(MMPlayer avdevice)
target_link_libraries(MMPlayer avformat)
target_link_libraries(MMPlayer avutil)
target_link_libraries(MMPlayer swresample)
target_link_libraries(MMPlayer swscale)

# TODO: 如有需要，请添加测试并安装目标。
