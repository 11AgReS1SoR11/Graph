set(SOURCE_BACKEND_TEST test.cpp)

add_executable(BackendTest ${SOURCE_BACKEND_TEST})

target_link_libraries(BackendTest PRIVATE
    Catch2::Catch2WithMain
    Backend
)

target_include_directories(BackendTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Backend/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME BackendTests COMMAND BackendTest)
