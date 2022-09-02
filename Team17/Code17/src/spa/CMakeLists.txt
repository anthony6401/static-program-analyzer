file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/components/qps/query_evaluator/factory/interface/Clause.h src/components/qps/QPS.cpp src/components/qps/QPS.h src/components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.h src/components/qps/abstract_query_object/QueryObject.cpp src/components/qps/abstract_query_object/QueryObject.h src/components/qps/abstract_query_object/Relationship.cpp src/components/qps/abstract_query_object/Relationship.h src/components/qps/abstract_query_object/Declaration.cpp src/components/qps/abstract_query_object/Declaration.h src/components/qps/abstract_query_object/Pattern.cpp src/components/qps/abstract_query_object/Pattern.h src/components/qps/abstract_query_object/Select.cpp src/components/qps/abstract_query_object/Select.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


