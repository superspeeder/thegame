#include "kat/renderer/Shader.hpp"

#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

std::string kat::to_string(kat::UniformType ut) {
    switch (ut) {
    case      kat::UniformType::e1f: return "Vector<float, 1>";
    case      kat::UniformType::e2f: return "Vector<float, 2>";
    case      kat::UniformType::e3f: return "Vector<float, 3>";
    case      kat::UniformType::e4f: return "Vector<float, 4>";
    case      kat::UniformType::e1i: return "Vector<int, 1>";
    case      kat::UniformType::e2i: return "Vector<int, 2>";
    case      kat::UniformType::e3i: return "Vector<int, 3>";
    case      kat::UniformType::e4i: return "Vector<int, 4>";
    case     kat::UniformType::e1ui: return "Vector<unsigned int, 1>";
    case     kat::UniformType::e2ui: return "Vector<unsigned int, 2>";
    case     kat::UniformType::e3ui: return "Vector<unsigned int, 3>";
    case     kat::UniformType::e4ui: return "Vector<unsigned int, 4>";
    case      kat::UniformType::e1d: return "Vector<double, 1>";
    case      kat::UniformType::e2d: return "Vector<double, 2>";
    case      kat::UniformType::e3d: return "Vector<double, 3>";
    case      kat::UniformType::e4d: return "Vector<double, 4>";
    case   kat::UniformType::eMat2f: return "Matrix<float, 2x2>";
    case   kat::UniformType::eMat3f: return "Matrix<float, 3x3>";
    case   kat::UniformType::eMat4f: return "Matrix<float, 4x4>";
    case kat::UniformType::eMat2x3f: return "Matrix<float, 2x3>";
    case kat::UniformType::eMat3x2f: return "Matrix<float, 3x2>";
    case kat::UniformType::eMat2x4f: return "Matrix<float, 2x4>";
    case kat::UniformType::eMat4x2f: return "Matrix<float, 4x2>";
    case kat::UniformType::eMat3x4f: return "Matrix<float, 3x4>";
    case kat::UniformType::eMat4x3f: return "Matrix<float, 4x3>";
    case   kat::UniformType::eMat2d: return "Matrix<double, 2x2>";
    case   kat::UniformType::eMat3d: return "Matrix<double, 3x3>";
    case   kat::UniformType::eMat4d: return "Matrix<double, 4x4>";
    case kat::UniformType::eMat2x3d: return "Matrix<double, 2x3>";
    case kat::UniformType::eMat3x2d: return "Matrix<double, 3x2>";
    case kat::UniformType::eMat2x4d: return "Matrix<double, 2x4>";
    case kat::UniformType::eMat4x2d: return "Matrix<double, 4x2>";
    case kat::UniformType::eMat3x4d: return "Matrix<double, 3x4>";
    case kat::UniformType::eMat4x3d: return "Matrix<double, 4x3>";
    }
    return "Unknown Type";
}

std::string kat::to_string(kat::ShaderType st) {
    switch (st) {
    case                  kat::ShaderType::eVertex: return "Shader<Vertex>";
    case                kat::ShaderType::eFragment: return "Shader<Fragment>";
    case                kat::ShaderType::eGeometry: return "Shader<Geometry>";
    case     kat::ShaderType::eTessellationControl: return "Shader<Tessellation::Control>";
    case  kat::ShaderType::eTessellationEvaluation: return "Shader<Tessellation::Evaluation>";
    case                 kat::ShaderType::eCompute: return "Shader<Compute>";
    }
    return "What.?";
}


std::ostream& operator<<(std::ostream& strm, const kat::UniformType& v) {
    strm << kat::to_string(v);
    return strm;
}

std::ostream& operator<<(std::ostream& strm, const kat::ShaderType& v) {
    strm << kat::to_string(v);
    return strm;
}

kat::Shader::Shader(std::string fn, ShaderType type) {
    std::string src = kat::readFile(kat::resourceFilename(SHADER_DIR + fn));
    const char* sources_c[1] = { src.c_str() };
    m_Handle = glCreateShader(static_cast<GLenum>(type));
    glShaderSource(m_Handle, 1, sources_c, nullptr);
    glCompileShader(m_Handle);

    int compiled;
    glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        int ils;
        glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &ils);
        char* infoLog = new char[ils];
        int l;
        glGetShaderInfoLog(m_Handle, ils, &l, infoLog);
        spdlog::error("Shader Compilation Failed: {}", infoLog);
    }
}

kat::ShaderProgram::ShaderProgram(std::vector<kat::Shader*> m_Shaders) {
    m_Handle = glCreateProgram();
    for (kat::Shader* shdr : m_Shaders) {
        glAttachShader(m_Handle, shdr->getHandle());
    }
    glLinkProgram(m_Handle);

    int linked;
    glGetProgramiv(m_Handle, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        int ils;
        glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &ils);
        char* infoLog = new char[ils];
        int l;

        glGetProgramInfoLog(m_Handle, ils, &l, infoLog);

        spdlog::error("ShaderProgram Link Failed: {}", infoLog);
    }
}

void kat::ShaderProgram::uniform1f(std::string name, float x) {
    glProgramUniform1f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x);
}

void kat::ShaderProgram::uniform2f(std::string name, float x, float y) {
    glProgramUniform2f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y);
}

void kat::ShaderProgram::uniform3f(std::string name, float x, float y, float z) {
    glProgramUniform3f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z);
}

void kat::ShaderProgram::uniform4f(std::string name, float x, float y, float z, float w) {
    glProgramUniform4f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z, w);
}

void kat::ShaderProgram::uniform1i(std::string name, int x) {
    glProgramUniform1i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x);
}

void kat::ShaderProgram::uniform2i(std::string name, int x, int y) {
    glProgramUniform2i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y);
}

void kat::ShaderProgram::uniform3i(std::string name, int x, int y, int z) {
    glProgramUniform3i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z);
}

void kat::ShaderProgram::uniform4i(std::string name, int x, int y, int z, int w) {
    glProgramUniform4i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z, w);
}

void kat::ShaderProgram::uniform1ui(std::string name, unsigned int x) {
    glProgramUniform1ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x);
}

void kat::ShaderProgram::uniform2ui(std::string name, unsigned int x, unsigned int y) {
    glProgramUniform2ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y);
}

void kat::ShaderProgram::uniform3ui(std::string name, unsigned int x, unsigned int y, unsigned int z) {
    glProgramUniform3ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z);
}

void kat::ShaderProgram::uniform4ui(std::string name, unsigned int x, unsigned int y, unsigned int z, unsigned int w) {
    glProgramUniform4ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z, w);
}

void kat::ShaderProgram::uniform1d(std::string name, double x) {
    glProgramUniform1d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x);
}

void kat::ShaderProgram::uniform2d(std::string name, double x, double y) {
    glProgramUniform2d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y);
}

void kat::ShaderProgram::uniform3d(std::string name, double x, double y, double z) {
    glProgramUniform3d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z);
}

void kat::ShaderProgram::uniform4d(std::string name, double x, double y, double z, double w) {
    glProgramUniform4d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), x, y, z, w);
}

void kat::ShaderProgram::uniform1f(std::string name, glm::vec1 v) {
    glProgramUniform1f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x);
}

void kat::ShaderProgram::uniform2f(std::string name, glm::vec2 v) {
    glProgramUniform2f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y);
}

void kat::ShaderProgram::uniform3f(std::string name, glm::vec3 v) {
    glProgramUniform3f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z);
}

void kat::ShaderProgram::uniform4f(std::string name, glm::vec4 v) {
    glProgramUniform4f(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z, v.w);
}

void kat::ShaderProgram::uniform1i(std::string name, glm::ivec1 v) {
    glProgramUniform1i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x);
}

void kat::ShaderProgram::uniform2i(std::string name, glm::ivec2 v) {
    glProgramUniform2i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y);
}

void kat::ShaderProgram::uniform3i(std::string name, glm::ivec3 v) {
    glProgramUniform3i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z);
}

void kat::ShaderProgram::uniform4i(std::string name, glm::ivec4 v) {
    glProgramUniform4i(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z, v.w);
}

void kat::ShaderProgram::uniform1ui(std::string name, glm::uvec1 v) {
    glProgramUniform1ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x);
}

void kat::ShaderProgram::uniform2ui(std::string name, glm::uvec2 v) {
    glProgramUniform2ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y);
}

void kat::ShaderProgram::uniform3ui(std::string name, glm::uvec3 v) {
    glProgramUniform3ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z);
}

void kat::ShaderProgram::uniform4ui(std::string name, glm::uvec4 v) {
    glProgramUniform4ui(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z, v.w);
}

void kat::ShaderProgram::uniform1d(std::string name, glm::dvec1 v) {
    glProgramUniform1d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x);
}

void kat::ShaderProgram::uniform2d(std::string name, glm::dvec2 v) {
    glProgramUniform2d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y);
}

void kat::ShaderProgram::uniform3d(std::string name, glm::dvec3 v) {
    glProgramUniform3d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z);
}

void kat::ShaderProgram::uniform4d(std::string name, glm::dvec4 v) {
    glProgramUniform4d(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), v.x, v.y, v.z, v.w);
}

void kat::ShaderProgram::uniformMat2(std::string name, glm::mat2 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3(std::string name, glm::mat3 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4(std::string name, glm::mat4 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat2x3(std::string name, glm::mat2x3 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2x3fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3x2(std::string name, glm::mat3x2 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3x2fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat2x4(std::string name, glm::mat2x4 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2x4fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4x2(std::string name, glm::mat4x2 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4x2fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4x3(std::string name, glm::mat4x3 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4x3fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3x4(std::string name, glm::mat3x4 m) {
    float* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3x4fv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat2d(std::string name, glm::dmat2 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3d(std::string name, glm::dmat3 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4d(std::string name, glm::dmat4 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat2x3d(std::string name, glm::dmat2x3 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2x3dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3x2d(std::string name, glm::dmat3x2 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3x2dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat2x4d(std::string name, glm::dmat2x4 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix2x4dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4x2d(std::string name, glm::dmat4x2 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4x2dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat4x3d(std::string name, glm::dmat4x3 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix4x3dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

void kat::ShaderProgram::uniformMat3x4d(std::string name, glm::dmat3x4 m) {
    double* ptr = glm::value_ptr(m);
    glProgramUniformMatrix3x4dv(m_Handle, glGetUniformLocation(m_Handle, name.c_str()), 1, GL_FALSE, ptr);
}

