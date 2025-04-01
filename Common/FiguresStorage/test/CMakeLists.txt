set(SOURCE_FIGURES_STORAGE_TEST test.cpp)

add_executable(FiguresStorageTest ${SOURCE_FIGURES_STORAGE_TEST})

target_link_libraries(FiguresStorageTest PRIVATE
    Catch2::Catch2WithMain
    FiguresStorage
)

target_include_directories(FiguresStorageTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/FiguresStorage/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME FiguresStorageTest COMMAND FiguresStorageTest)
