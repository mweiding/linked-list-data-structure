file(GLOB SRCS *.cpp)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testList ${SRCS} ../list/list.h)

target_link_libraries(testList
        gtest
        gmock
)

include_directories("..")

install(TARGETS testList DESTINATION bin)

