#include "Backend.hpp"
#include "Logger.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

std::string getArgValue(const std::vector<std::string>& args, const std::string& argName)
{
    auto it = std::find(args.begin(), args.end(), argName);
    if (it != args.end() && std::next(it) != args.end())
    {
        return *std::next(it);
    }
    return ""; // Argument not found or no value provided
}

int main(int argc, char* argv[])
{
    std::vector<std::string> const args(argv + 1, argv + argc);

    std::string const logFilePath = getArgValue(args, "--logFilePath");
    Logger::getInstance().updLogOutput(logFilePath.empty() ? "log.log" : logFilePath);

    std::string const outputFilePath = getArgValue(args, "--outputFilePath");

    backend::Backend backend;

    if (std::find(args.begin(), args.end(), "--retranslate") != args.end())
    {
        std::string const figuresJsonPath = getArgValue(args, "--figuresJsonPath");

        if (figuresJsonPath.empty())
        {
            LOG_ERROR(BACKEND_LOG, "Error: --figuresJsonPath argument is required for --retranslate.");
            return 1;
        }

        backend.retranslate(figuresJsonPath, outputFilePath.empty() ? "code.graph" : outputFilePath);
    }
    else if (std::find(args.begin(), args.end(), "--translate") != args.end())
    {
        std::string const codeFilePath = getArgValue(args, "--codeFilePath");

        if (codeFilePath.empty())
        {
            LOG_ERROR(BACKEND_LOG, "Error: --codeFilePath argument is required for --translate");
            return 1;
        }

        backend.translate(codeFilePath, outputFilePath.empty() ? "figures.json" : outputFilePath);
    }
    else
    {
        LOG_ERROR(BACKEND_LOG, "Error: Must specify either --retranslate or --translate.");
        return 1;
    }

    return 0;
}
