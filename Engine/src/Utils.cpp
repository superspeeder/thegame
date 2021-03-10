#include "kat/Utils.hpp"

kat::File::File(std::string fn) {
    m_Filename = fn;
    m_ifstream = std::ifstream(fn);
}

void kat::File::close() {
    m_ifstream.close();
}

std::string kat::File::readAsString() {
    std::ostringstream sstream;
    m_ifstream.seekg(0);
    if (!m_ifstream.good()) {
        spdlog::error("Error opening file {}", m_Filename);
    }

    sstream << m_ifstream.rdbuf();
    return sstream.str();
}

std::vector<char> kat::File::readBinary() {
    std::ifstream fs(m_Filename, std::ios_base::binary | std::ios_base::in);
    std::istream_iterator<char> start(fs), end;
    m_ifstream.seekg(0);
    std::vector<char> vec(start, end);
    fs.close();
    return vec;
}

kat::JsonFile::JsonFile(std::string fn) {
    kat::File f(fn);
    m_Filename = fn;

    std::string cont = f.readAsString();
    m_Document.Parse(cont.c_str());
    f.close();
}

void kat::JsonFile::close() {
}

