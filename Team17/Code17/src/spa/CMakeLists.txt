file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/components/SP/simple_tokenizer/SimpleTokenizer.cpp" "src/components/SP/simple_tokenizer/SimpleTokenizer.h" "src/components/SP/simple_tokenizer/SimpleToken.h" "src/components/SP/simple_tokenizer/SimpleToken.cpp" )
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


