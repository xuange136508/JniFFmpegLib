cmake_minimum_required(VERSION 3.4.1) # CMake版本

#增加其他目录的源文件到集合变量中
list(APPEND SRC_LIST
        src/main/cpp/ffmpeg/call_ffmpeg.cpp
        src/main/cpp/jni.cpp
        src/main/cpp/onLoad.cpp


        src/main/cpp/ffmpeg/excute_ffmpeg.cpp
        src/main/cpp/command/ffmpeg_mod.c
        src/main/cpp/command/ffmpeg_opt.c
        src/main/cpp/command/ffmpeg_filter.c
        src/main/cpp/command/cmdutils.c

    )

add_library(
            jni_demo # 动态库的名称
            SHARED # 作为共享库（动态引入）
            # 这里用list变量
             ${SRC_LIST}
           )



# 引入本地so
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libavcodec-56.so)
add_library(avdevice SHARED IMPORTED)
set_target_properties(avdevice  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libavdevice-56.so)
add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libavfilter-5.so)
add_library(avformat SHARED IMPORTED)
set_target_properties(avformat  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libavformat-56.so)
add_library(avutil SHARED IMPORTED)
set_target_properties(avutil  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libavutil-54.so)
add_library(postproc SHARED IMPORTED)
set_target_properties(postproc  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libpostproc-53.so)
add_library(swresample SHARED IMPORTED)
set_target_properties(swresample  PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libswresample-1.so)
add_library(swscale SHARED IMPORTED)
set_target_properties(swscale  PROPERTIES IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/src/main/cpp/ffmpeg_so/libswscale-3.so)



find_library(
               log-lib
               log
           )

# 被链接的目标库的名称
target_link_libraries(
                      jni_demo avcodec avdevice avfilter  avformat  avutil postproc swresample swscale
                      # 日志
                      ${log-lib}
                    )