file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/components/qps/query_evaluator/factory/interface/Clause.h src/components/qps/QPS.cpp src/components/qps/QPS.h src/components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.h src/components/qps/abstract_query_object/Query.cpp src/components/qps/abstract_query_object/Query.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


