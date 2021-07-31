cmake_minimum_required(VERSION 3.16.0)
project(NetChat VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_sources(${PROJECT_NAME} PUBLIC src/Socket.cpp scr/Client.cpp scr/Server.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)