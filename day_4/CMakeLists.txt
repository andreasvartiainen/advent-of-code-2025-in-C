cmake_minimum_required(VERSION 3.10)

project(c_project)

enable_testing()

# C++ standard to 23 to support std::print/ln()
set(CMAKE_C_STANDARD 23)
# add warnings as errors -Werror not in this because it causes catch2 to fail
add_compile_options(-Wall -Wextra -Wpedantic -Wreorder -Wunused -Wshadow -Werror=return-type)

# include(FetchContent)
#
# FetchContent_Declare(
# 	raylib
# 	GIT_REPOSITORY https://github.com/raysan5/raylib
# 	GIT_TAG 5.5
# 	FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
# )
#
# set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
#
# FetchContent_MakeAvailable(raylib)

# find_package(SQLite3 REQUIRED)

# globbing the sources in src folder to not require manual adding of .cpp files
file(GLOB_RECURSE SOURCES "src/*.c")
# list(APPEND SOURCES "ClayMan/clayman.cpp")

# remove main.cpp because that causes problems in the unitTests
list(FILTER SOURCES EXCLUDE REGEX "main.c" )

# include dirs for adding them easier to the unitTests
set(INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} src/main.c ${SOURCES})
add_executable(tests tests/test.c ${SOURCES})
# target_link_libraries(${PROJECT_NAME} raylib sqlite3)
add_test(test tests)

set(FILENAME rolls.input)
set(FILENAME2 rolls-example.input)

# copy stuff automatically
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/${FILENAME} ${CMAKE_BINARY_DIR}/
)

# copy stuff automatically
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/${FILENAME2} ${CMAKE_BINARY_DIR}/
)

include_directories(
	PRIVATE
		${INCLUDE_DIRS}
		# ClayMan
		# ClayMan/include
)

