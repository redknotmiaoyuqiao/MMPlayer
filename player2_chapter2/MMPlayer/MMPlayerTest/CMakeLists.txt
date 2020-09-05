cmake_minimum_required (VERSION 3.8)

include_directories(../)

link_directories(../3rdpart/ffmpeg/lib)

add_executable (
	MMPlayerTest
	Main.cpp
)

target_link_libraries(MMPlayerTest MMThread)
target_link_libraries(MMPlayerTest MMAV)
target_link_libraries(MMPlayerTest MMPlayer)

target_link_libraries(MMPlayerTest avcodec)
target_link_libraries(MMPlayerTest avdevice)
target_link_libraries(MMPlayerTest avformat)
target_link_libraries(MMPlayerTest avutil)
target_link_libraries(MMPlayerTest swresample)
target_link_libraries(MMPlayerTest swscale)