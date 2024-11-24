cmake_minimum_required(VERSION 3.10)
project(MyOpenGLProject2)

# Встановіть стандарт C++14 або вище
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к GLFW и FreeGLUT
set(GLFW_PATH "C:/Users/User/glfw-3.4.bin.WIN64")
set(FREEGLUT_PATH "C:/Users/User/freeglut")

# Подключаем заголовки и библиотеки GLFW и FreeGLUT
include_directories(${GLFW_PATH}/include ${FREEGLUT_PATH}/include)
link_directories(${GLFW_PATH}/lib-mingw-w64 ${FREEGLUT_PATH}/lib)

# Вкажіть шлях до бібліотеки Eigen
include_directories(${CMAKE_SOURCE_DIR}/eigen)

# Основной исполняемый файл и связывание с библиотеками
add_executable(MyOpenGLProject2 main.cpp)
target_link_libraries(MyOpenGLProject2 glfw3 freeglut opengl32 glu32)
