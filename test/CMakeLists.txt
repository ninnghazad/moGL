find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glbinding REQUIRED)
find_package(GTest REQUIRED)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(MOGL_TEST_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wundef")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLBINDING_INCLUDES}
    ${GLFW_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})

# Setup Precompiled headers
set(PRECOMPILED_HEADER_TARGET pch)
set(PRECOMPILED_HEADER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h")
get_filename_component(PRECOMPILED_HEADER_NAME ${PRECOMPILED_HEADER_SOURCE} NAME)
set(PRECOMPILED_HEADER_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${PRECOMPILED_HEADER_NAME}.gch")

add_custom_command(OUTPUT "${PRECOMPILED_HEADER_OUTPUT}"
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++14 -x c++-header -o ${PRECOMPILED_HEADER_OUTPUT} ${PRECOMPILED_HEADER_SOURCE} -I ${CMAKE_SOURCE_DIR}
    DEPENDS ${PRECOMPILED_HEADER_SOURCE})
add_custom_target(${PRECOMPILED_HEADER_TARGET}
    DEPENDS ${PRECOMPILED_HEADER_OUTPUT})

# Setup context library
add_library(context SHARED
    ${CMAKE_SOURCE_DIR}/common/glcontext.cpp
    ${CMAKE_SOURCE_DIR}/common/gltestfixture.cpp)
target_link_libraries(context ${OPENGL_LIBRARIES} ${GLBINDING_LIBRARIES} ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES} pthread)

set_target_properties(context PROPERTIES
    CXX_STANDARD 14
    COMPILE_FLAGS "${MOGL_TEST_COMPILE_FLAGS}")

function(moglCreateTest NAME)
    if(MOGL_BUILD_TESTS)
        set(TEST_NAME test-${NAME})
        add_executable(${TEST_NAME} ${NAME}.cpp ${PRECOMPILED_HEADER_OUTPUT})
        set_target_properties(${TEST_NAME} PROPERTIES CXX_STANDARD 14 COMPILE_FLAGS "${MOGL_TEST_COMPILE_FLAGS} -include ${PRECOMPILED_HEADER_SOURCE} -Winvalid-pch")
        target_link_libraries(${TEST_NAME} ${OPENGL_LIBRARIES} ${GLBINDING_LIBRARIES} ${GLFW_LIBRARIES} ${GTEST_BOTH_LIBRARIES} pthread context)
        add_test(NAME ${TEST_NAME}
            COMMAND $<TARGET_FILE:${TEST_NAME}>)
        add_dependencies(${TEST_NAME} ${PRECOMPILED_HEADER_TARGET})
    endif()
endfunction()

moglCreateTest(buffer_object)
moglCreateTest(debug)
moglCreateTest(framebuffer)
moglCreateTest(handle)
moglCreateTest(pipeline)
moglCreateTest(query)
moglCreateTest(renderbuffer)
moglCreateTest(shader_program)
moglCreateTest(sync)
moglCreateTest(texture)
moglCreateTest(transform_feedback)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
