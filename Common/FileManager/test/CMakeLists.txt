set(SOURCE_FILE_MANAGER_TEST test.cpp)

add_executable(FileManagerTest ${SOURCE_FILE_MANAGER_TEST})

target_link_libraries(FileManagerTest PRIVATE
    Catch2::Catch2WithMain
    FileManager
)

target_include_directories(FileManagerTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/FileManager/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME FileManagerTest COMMAND FileManagerTest)
