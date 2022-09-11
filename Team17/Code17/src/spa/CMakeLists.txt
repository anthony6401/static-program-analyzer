file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/components/qps/query_evaluator/factory/clauses/relationship/UsesSClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/UsesSClause.h src/components/qps/query_evaluator/factory/clauses/relationship/UsesPClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/UsesPClause.h src/components/qps/query_evaluator/factory/clauses/relationship/FollowsClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/FollowsClause.h src/components/qps/query_evaluator/factory/clauses/relationship/FollowsTClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/FollowsTClause.h src/components/qps/query_evaluator/factory/clauses/relationship/ParentClause.cpp src/components/qps/query_evaluator/factory/clauses/relationship/ParentClause.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


