#include "CmdLineParser.hpp"

void Settings::CmdLineParser::Parse(int argc, char **argv, std::string& filename, std::string& config_filename) {
    int i = 1;
    if (argc > i) {
        std::string new_filename(argv[i]);
        if (new_filename.size() >= 4 && new_filename.substr(new_filename.size() - 4) != ".ppm" && new_filename != "--fast") {
            if (new_filename.substr(new_filename.size() - 4) != ".cfg") {
                throw std::runtime_error("Wrong config filename.");
            }
            config_filename = new_filename;
            ++i;
        }
    }
    if (argc > i) {
        std::string new_filename(argv[i]);
        if (new_filename != "--fast") {
            if (new_filename.size() < 4 || new_filename.substr(new_filename.size() - 4) != ".ppm") {
                throw std::runtime_error("Wrong filename for output.");
            }
            filename = new_filename;
            ++i;
        }
    }
    if (argc > i) {
        if (std::string(argv[i]) != "--fast") {
            throw std::runtime_error("Unknown argument: --fast expected.");
        }
        fast = true;
        ++i;
    }
    if (argv[i] != NULL) {
        throw std::runtime_error("Incorrect command line arguments.");
    }
}

