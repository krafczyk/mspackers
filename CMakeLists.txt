cmake_minimum_required(VERSION 2.8.9)
project(mspackers)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMSPACK REQUIRED libmspack)

include_directories(${LIBMSPACK_INCLUDE_DIRS})
include_directories("include")
add_definitions(-Wall -Wextra -Werror)

add_executable(kwaj_unpack "src/kwaj_unpack")
target_link_libraries(kwaj_unpack ${LIBMSPACK_LIBRARIES})

add_executable(kwaj_pack "src/kwaj_pack")
target_link_libraries(kwaj_pack ${LIBMSPACK_LIBRARIES})
