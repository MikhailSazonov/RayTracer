#pragma once

#include <string>
#include <stdexcept>

class Settings {
    private:
        inline static bool fast{false};

    public:
        inline static bool isFast() { return fast; }

        class CmdLineParser {
            public:
                static void Parse(int, char **, std::string&, std::string&);
        };

};
