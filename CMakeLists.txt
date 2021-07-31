cmake_minimum_required(VERSION 3.16.0)
project(NetChat VERSION 0.1.0)

add_executable(${PROJECT_NAME}_Server server.cpp)
target_include_directories(${PROJECT_NAME}_Server PUBLIC inc)
target_link_libraries(${PROJECT_NAME}_Server PUBLIC ws2_32)
target_compile_definitions(${PROJECT_NAME}_Server PUBLIC _WIN32_WINNT=0x0602 WINVER=0x0602)
file(GLOB SourceFiles src/*.cpp src/*.cpp)
target_sources(${PROJECT_NAME}_Server PUBLIC ${SourceFiles})
set_target_properties(${PROJECT_NAME}_Server PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

add_executable(${PROJECT_NAME}_Client client.cpp)
target_include_directories(${PROJECT_NAME}_Client PUBLIC inc)
target_link_libraries(${PROJECT_NAME}_Client PUBLIC ws2_32)
target_compile_definitions(${PROJECT_NAME}_Client PUBLIC _WIN32_WINNT=0x0602 WINVER=0x0602)
file(GLOB SourceFiles src/*.cpp src/*.cpp)
target_sources(${PROJECT_NAME}_Client PUBLIC ${SourceFiles})
set_target_properties(${PROJECT_NAME}_Client PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)