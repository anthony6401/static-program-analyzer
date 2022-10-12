file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/components/qps/query_evaluator/factory/utils/ClauseUtils.cpp src/components/qps/query_evaluator/factory/utils/ClauseUtils.h src/components/qps/query_evaluator/factory/clauses/relationship/UsesClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/UsesClause.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


