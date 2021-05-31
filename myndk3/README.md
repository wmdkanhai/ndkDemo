## 项目中使用 .a 库

1、第一步：将.a文件需要的头文件放到指定目录，这里放在了include/下面

2、在main下创建jniLibs把需要的.a文件粘贴进去

3、修改CMakeLists.txt

- 添加include_directories(include/) , 括号里是.a文件的头文件
- 添加库
```
# 指定头文件
include_directories(include/)

add_library(
        native-my-lib
        STATIC
        IMPORTED)

set_target_properties(
        native-my-lib  #这个一般是.a文件去掉lib和后缀之后的名字，
        PROPERTIES IMPORTED_LOCATION
        # ${CMAKE_SOURCE_DIR} 是指 CMakeLists.txt 的目录
        # ${ANDROID_ABI} 是指不同CPU架构
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libnative-my-lib.a
)
```
- 在 target_link_libraries 中添加
```
target_link_libraries(
        # Specifies the target library.
        native-lib

        # 引入.a文杰
        native-my-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
)
```