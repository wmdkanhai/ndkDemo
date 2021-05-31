# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


#1.添加三方库（类型时IMPORTED）
add_library(
        native-my-lib
        SHARED
        IMPORTED)

#2.添加库的路径
set_target_properties(
        native-my-lib  #这个一般是文件去掉lib和后缀之后的名字，
        PROPERTIES IMPORTED_LOCATION
        # ${CMAKE_SOURCE_DIR} 是指 CMakeLists.txt 的目录
        # ${ANDROID_ABI} 是指不同CPU架构
        ${CMAKE_SOURCE_DIR}/../nativeLibs/${ANDROID_ABI}/libnative-my-lib.so
)

#3.添加头文件
# 指定头文件
include_directories(include/)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#4.添加链接
target_link_libraries( # Specifies the target library.
        native-lib
        native-my-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})