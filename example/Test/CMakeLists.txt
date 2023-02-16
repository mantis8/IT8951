add_executable(Test src/test.cpp)
target_include_directories(Test PRIVATE thirdparty)
target_link_libraries(Test PRIVATE IT8951 Bcm) 