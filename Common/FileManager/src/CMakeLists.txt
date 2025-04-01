set(SOURCE_FILE_MANAGER FileManager.cpp)	

add_library(FileManager SHARED ${SOURCE_FILE_MANAGER})

target_include_directories(FileManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
)

target_link_libraries(FileManager PUBLIC
    Logger
)

# Установка библиотеки (опционально)
install(TARGETS FileManager DESTINATION lib)
install(FILES FileManager.hpp DESTINATION include)
