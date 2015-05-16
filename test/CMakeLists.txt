add_executable(test_jaro test_jaro.c)
target_link_libraries(test_jaro jaro)

add_test("test_jaro_winkler_distance" test_jaro)
