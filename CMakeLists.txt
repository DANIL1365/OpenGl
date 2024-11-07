cmake_minimum_required(VERSION 3.10)
project(MyOpenGLProject1)

set(CMAKE_CXX_STANDARD 11)

# Пути к GLFW и FreeGLUT
set(GLFW_PATH "C:/Users/User/glfw-3.4.bin.WIN64")
set(FREEGLUT_PATH "C:/Users/User/freeglut")

# Подключаем заголовки и библиотеки GLFW и FreeGLUT
include_directories(${GLFW_PATH}/include ${FREEGLUT_PATH}/include)
link_directories(${GLFW_PATH}/lib-mingw-w64 ${FREEGLUT_PATH}/lib)

# Основной исполняемый файл и связывание с библиотеками
add_executable(MyOpenGLProject1 main.cpp)
target_link_libraries(MyOpenGLProject1 glfw3 freeglut opengl32)
