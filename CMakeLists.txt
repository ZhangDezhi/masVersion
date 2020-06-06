cmake_minimum_required(VERSION 3.7)
project(DynamicLayouts)
# 指定c++标准的版本
set(CMAKE_CXX_STANDARD 14)

# 设置Qt5的cmake模块所在目录，如果不设置将使用系统提供的版本
# QT_DIR和QT_VERSION是指定了qt安装目录和版本的环境变量
# set(CMAKE_PREFIX_PATH $ENV{QT_DIR}/$ENV{QT_VERSION}/mingw53_32/lib/cmake)
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.8.0\\5.8\\mingw53_32\\lib\\cmake")

#设置工程包含当前目录，非必须
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#打开全局moc,设置自动生成moc文件，一定要设置
set(CMAKE_AUTOMOC ON)
#打开全局uic，非必须
set(CMAKE_AUTOUIC ON)
#打开全局rcc，非必须，如需打开，注意修改33行的qrc文件名
set(CMAKE_AUTORCC ON)

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

#设置运行时输出可执行文件目录(CMAKE源目录CMAKE_CURRENT_SOURCE_DIR，执行目录CMAKE_CURRENT_BINARY_DIR)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
#设置运行时输出共享库文件目录
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加
set(Projects_QT5_COMPONENTS
        Core
        Gui
        Widgets
        )

set(Projects_QT5_Includes
        ${Qt5Core_INCLUDE}
        ${Qt5Gui_INCLUDE}
        ${Qt5Widgets_INCLUDE}
        )

set(Projects_QT5_Libraries
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

find_package(Qt5 COMPONENTS ${Projects_QT5_COMPONENTS} REQUIRED)

INCLUDE_DIRECTORIES(
        .
        ${Projects_QT5_Includes}
)#设置项目包含目录

#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB SRC_FILES "masVersion/*.cpp")
#查找设置当前文件夹中所有的头文件
FILE(GLOB HEAD_FILES "masVersion/*.h")
#查找设置当前文件夹中所有的ui文件
FILE(GLOB UI_FILES "masVersion/*.ui")

#通过Ui文件生成对应的头文件，一定要添加
# qt5_wrap_ui(WRAP_FILES ${UI_FILES})

#添加资源文件，非必须，一旦采用，注意修改相应的qrc文件名
# set(RCC_FILES rcc.qrc)

#将ui文件和生成文件整理在一个文件夹中，非必须
# source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )

#创建工程文件
# add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES} ${RCC_FILES} ${WRAP_FILES})
add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ${HEAD_FILES}
        )

#添加Qt5依赖项
target_link_libraries(${PROJECT_NAME}
        ${Projects_QT5_Libraries}
        )