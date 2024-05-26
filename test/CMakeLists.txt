add_executable(Test test.cpp)

target_include_directories(Test PUBLIC ${GUI_Library_SOURCE_DIR}/include)
target_link_libraries(Test PUBLIC GUI_Library)
