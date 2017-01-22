cmake_minimum_required(VERSION 3.0.2)
project(gproj)


# build options
set(TARGET_OS "Linux" CACHE STRING "Specifies your target OS for build config")
set(TARGET_CPU "native" CACHE STRING "Specifies the target CPU architecture for -march option")

option(TESTS OFF)
option(ASAN OFF)
option(USAN OFF)
option(ENABLE_LTO OFF)
option(ASM_OUTPUT OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors \
	-Wall -Wextra -Wshadow -Wstrict-aliasing \
	-fno-exceptions -fno-rtti -Wno-missing-braces")

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -Werror -fstrict-aliasing \
	-march=${TARGET_CPU} -fomit-frame-pointer -ffunction-sections \
	-fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables \
	-ffast-math")

set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -DDEBUG -O0 -g3")


if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, defaulted to Debug")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if (${USAN} OR ${ASAN} AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(FATAL_ERROR "ASAN and USAN cannot be used on ${CMAKE_BUILD_TYPE} build type")
endif()

# "Release" full optimization , no debug info.
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(LINK_FLAGS "-nodefaultlibs -s -Wl,--gc-sections")
	if(ENABLE_LTO)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
		set(LINK_FLAGS "${LINK_FLAGS} -flto") 
	endif()

	set(CMAKE_EXE_LINKER_FLAGS "${LINK_FLAGS}")
	set(CMAKE_SHARED_LINKER_FLAGS "${LINK_FLAGS}")
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${LINK_FLAGS}")
	set(CMAKE_STATIC_LIBRARY_LINK_CXX_FLAGS "${LINK_FLAGS}")


# "Debug" full debug information, no optimization, asserts enabled
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	if (${ASAN})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	endif()

	if (${USAN})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
	endif()
endif()


# gbx src directory
set(GPROJ_SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GPROJ_TEST_DIR "./tests")


# specific platform configurations
if (${TARGET_OS} STREQUAL "Linux")
	set(GPROJ_LINK_LIBRARIES "-lc -lm")
else()
	message(FATAL_ERROR "Add your platform build configuration")
endif()

# dependencies
add_subdirectory(./externals/glew/build/cmake)
add_subdirectory(./externals/glfw)
add_subdirectory(./externals/soil)

# include src directory
include_directories("${GPROJ_SRC_DIR}")
include_directories("./externals/glew/include")
include_directories("./externals/glfw/include")
include_directories("./externals/soil/include")

# build
file(GLOB_RECURSE GPROJ_SRC_FILES "${GPROJ_SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${GPROJ_SRC_FILES} ${GPROJ_PLATFORM_SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${GPROJ_LINK_LIBRARIES} glew_s glfw soil)

if (ASM_OUTPUT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -S")
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAG "-save-temps")
endif()



