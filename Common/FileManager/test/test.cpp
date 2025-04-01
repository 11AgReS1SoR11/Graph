#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "FileManager.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

static std::string const FILE_PATH = "build/test_file.txt";

TEST_CASE("Write to file", "[FileManager]")
{
    REQUIRE(FileManager::writeToFile(FILE_PATH, "Hello"));
}

TEST_CASE("Read from file", "[FileManager]")
{
    std::string const dataWrite = "Test Read";
    REQUIRE(FileManager::writeToFile(FILE_PATH, dataWrite));

    auto const res = FileManager::readFromFile(FILE_PATH);
    REQUIRE(res);

    REQUIRE(*res == dataWrite);
}

TEST_CASE("Check file exists after write", "[FileManager]")
{
    REQUIRE(FileManager::writeToFile("build/Such_file_non_exist", "Checking existence"));

    REQUIRE(fs::exists(FILE_PATH));
}

TEST_CASE("Read non existent file", "[FileManager]")
{
    auto const res = FileManager::readFromFile("Lalala");
    REQUIRE(!res);
}

TEST_CASE("Overwrite file", "[FileManager]")
{
    std::string const lastData = "Second write";
    REQUIRE(FileManager::writeToFile(FILE_PATH, "First write"));
    REQUIRE(FileManager::writeToFile(FILE_PATH, lastData));

    auto const res = FileManager::readFromFile(FILE_PATH);
    REQUIRE(res);
    REQUIRE(*res == lastData);
}
