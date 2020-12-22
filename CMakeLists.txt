cmake_minimum_required(VERSION 3.17)
project(december_2020)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS system REQUIRED)
if (Boost_VERSION VERSION_LESS 1.74)
    message(FATAL_ERROR "Boost 1.74 or higher required")
endif ()
find_package(OpenSSL COMPONENTS)
find_package(Threads)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(december_2020 ${src_files})
target_link_libraries(december_2020 PUBLIC
        Boost::system
        OpenSSL::SSL OpenSSL::Crypto
        Threads::Threads)
target_include_directories(december_2020 PRIVATE src)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(december_2020 PUBLIC -fcoroutines-ts -stdlib=libc++)
    target_link_options(december_2020 PUBLIC -stdlib=libc++)
else (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(december_2020 PUBLIC -fcoroutines)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(december_2020 PUBLIC -Wall -Werror -Wextra -pedantic)
    endif ()
endif ()