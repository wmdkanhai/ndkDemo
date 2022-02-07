# 项目说明
该项目是将.c/.cpp文件生成不同CPU架构的静态库.a文件或.so

在 CMakeLists.txt 文件中指定，要生成静态库 .a 还是要生成动态库 .so，部分代码如下：
```shell script
# 配置库信息
add_library( # Sets the name of the library.
        native-my-lib

        # Sets the library as a shared library.
        # 指定生成的库
        # STATIC：静态库，是目标文件的归档文件，在链接其它目标的时候使用，生成.a
        # SHARED：动态库，会被动态链接，在运行时被加载，生成.so
        # MODULE：模块库，是不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数动态链接
        STATIC
        #SHARED


        # Provides a relative path to your source file(s).
        # 资源路径是相对路径，相对于本CMakeLists.txt所在目录
        #native-lib.cpp
        my.cpp
        )
```