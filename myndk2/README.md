# 引入.so文件

##配置 CMakeLists.txt

### 1.添加三方库（类型为IMPORTED）
```text
add_library(
    native-my-lib
        SHARED
IMPORTED)
```

### 2.添加库的路径

之前我们将 so 文件放入到src/main/jniLibs中，但是报错了，错误信息为：
> More than one file was found with OS independent path ‘lib/armeabi-v7a/xxx.so’. 
>If you are using jniLibs and CMake IMPORTED targets, 
>see https://developer.android.com/studio/preview/features#automatic_packaging_of_prebuilt_dependencies_used_by_cmake

最终链接在这里：https://developer.android.com/studio/releases/gradle-plugin#cmake-imported-targets ，
发现实际上是从gradle 4.0开始就对jni的预编译依赖引用方式做出了修改：

原来的直接放在“src/main/jniLibs”中的方法已经作废了.

解决方法就是把 jniLibs 里的预编译库换个位置，比如把 jniLibs改为 nativeLibs，
在 CMakeLists.txt 中的 IMPORTED 路径也要做出相应修改，完事再次 build 即可通过

```text
set_target_properties(
        native-my-lib  #这个一般是文件去掉lib和后缀之后的名字，
        PROPERTIES IMPORTED_LOCATION
        # ${CMAKE_SOURCE_DIR} 是指 CMakeLists.txt 的目录
        # ${ANDROID_ABI} 是指不同CPU架构
        ${CMAKE_SOURCE_DIR}/../nativeLibs/${ANDROID_ABI}/libnative-my-lib.so
)
```

### 3.添加头文件
```text
include_directories(include/)
```

### 4.添加链接
在 target_link_libraries 中添加 so 的链接
```text
target_link_libraries( # Specifies the target library.
        native-lib

        # so的名称
        native-my-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
```