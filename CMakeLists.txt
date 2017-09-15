cmake_minimum_required(VERSION 3.8)
project(Physics_Engine)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include/GLFW)

link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW)

set(SOURCE_FILES src/main.cpp src/core/Vector3D.cpp include/core/Vector3D.h include/core/PNode.h src/core/Particle.cpp include/core/Particle.h src/core/Spring.cpp include/core/Spring.h include/glad/glad.h src/glad/glad.c)
add_executable(Physics_Engine ${SOURCE_FILES} src/core/Vector3D.cpp include/core/Vector3D.h include/core/PNode.h src/core/Particle.cpp include/core/Particle.h src/core/Spring.cpp include/core/Spring.h)
target_link_libraries(Physics_Engine glfw3 gdi32 opengl32)