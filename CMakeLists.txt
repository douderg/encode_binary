cmake_minimum_required (VERSION 3.15)
project (encode_binary VERSION 0.0.1)

add_executable (${PROJECT_NAME} main.cpp)
set_target_properties (${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

function (add_binary_resource TARGET_NAME SOURCE)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources
    )

    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources/${TARGET_NAME}.cpp
        DEPENDS ${SOURCE} ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources
        COMMAND encode_binary ${TARGET_NAME} ${SOURCE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources
    )

    add_library(${TARGET_NAME} ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources/${TARGET_NAME}.cpp)
    target_include_directories (${TARGET_NAME} PUBLIC ${CMAKE_BINARY_DIR}/${TARGET_NAME}_sources)
endfunction()