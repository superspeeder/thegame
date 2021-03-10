#pragma once

#include <string>


#include <string>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <vector>
#include <rapidjson/document.h>

#ifndef APPDATA_DIR
#if defined(WIN32)
#define APPDATA_DIR "%APPDATA%/KatEngine/"
#elif __APPLE__
#define APPDATA_DIR "~/Library/Application Support/KatEngine/"
#elif __linux__
#define APPDATA_DIR "~/.katengine/"
#else
#error Unsupported OS
#endif
#endif

namespace kat {

    inline const std::string readFile(std::string fn) {
        std::ostringstream sstream;
        std::ifstream fs(fn);

        if (!fs.good()) {
            spdlog::error("Failed to load file {}", fn);
        }

        sstream << fs.rdbuf();
        return sstream.str();
    };

    inline std::string resourceFilename(std::string intfn) {
        return APPDATA_DIR + intfn;
    };

    class File {
    private:
        std::string m_Filename;
        std::ifstream m_ifstream;

    public:

        File(std::string fn);

        void close();

        std::string readAsString();
        std::vector<char> readBinary();

        inline std::string getFilename() { return m_Filename; };
    };

    class JsonFile {
    private:
        std::string m_Filename;

        rapidjson::Document m_Document;

    public:

        JsonFile(std::string fn);

        void close();

        inline rapidjson::Document& getDocument() { return m_Document; };

        inline std::string getFilename() { return m_Filename; };

    };
}
