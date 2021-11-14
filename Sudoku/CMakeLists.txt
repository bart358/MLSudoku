cmake_minimum_required (VERSION 3.21)

find_package(OpenMP)

add_executable (Sudoku "Sudoku.cpp" "main.cpp" "Sudoku.h" "Csv.cpp" "Csv.h" "Timer.h" "Timer.cpp")

target_include_directories(Sudoku PRIVATE "${CMAKE_SOURCE_DIR}/z3/src/api")
target_include_directories(Sudoku PRIVATE "${CMAKE_SOURCE_DIR}/z3/src/api/c++")

target_link_libraries(Sudoku PRIVATE libz3)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Sudoku PRIVATE OpenMP::OpenMP_CXX)
endif()

add_custom_command(TARGET Sudoku POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy
    "$<TARGET_FILE:libz3>" "$<TARGET_FILE_NAME:libz3>"
    COMMENT "Copying libz3 to executable directory")
