#pragma once

#include <glad/glad.h>
#include <ostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "kat/Utils.hpp"

#define SHADER_DIR "Resources/Shaders/"

namespace kat {

    enum class UniformType {
        e1f, e2f, e3f, e4f,
        e1i, e2i, e3i, e4i,
        e1ui, e2ui, e3ui, e4ui,
        e1d, e2d, e3d, e4d,

        eMat2f, eMat3f, eMat4f,

        eMat2x3f, eMat3x2f,
        eMat2x4f, eMat4x2f,
        eMat3x4f, eMat4x3f,

        eMat2d, eMat3d, eMat4d,

        eMat2x3d, eMat3x2d,
        eMat2x4d, eMat4x2d,
        eMat3x4d, eMat4x3d
    };

    enum class ShaderType {
        eVertex = GL_VERTEX_SHADER,
        eFragment = GL_FRAGMENT_SHADER,
        eGeometry = GL_GEOMETRY_SHADER,
        eTessellationControl = GL_TESS_CONTROL_SHADER,
        eTessellationEvaluation = GL_TESS_EVALUATION_SHADER,
        eCompute = GL_COMPUTE_SHADER
    };

    std::string to_string(UniformType);
    std::string to_string(ShaderType);

    class Shader {
    private:
        uint32_t m_Handle;

    public:
        Shader(std::string fn, ShaderType type);

        inline uint32_t getHandle() { return m_Handle; };
        inline void destroy() { glDeleteShader(m_Handle); };
    };

    class ShaderProgram {
    private:
        uint32_t m_Handle;

    public:
        ShaderProgram(std::vector<Shader*> m_Shaders);

        inline void destroy() { glDeleteProgram(m_Handle); };
        inline void use() { glUseProgram(m_Handle); };

        void uniform1f(std::string name, float x);
        void uniform2f(std::string name, float x, float y);
        void uniform3f(std::string name, float x, float y, float z);
        void uniform4f(std::string name, float x, float y, float z, float w);

        void uniform1i(std::string name, int x);
        void uniform2i(std::string name, int x, int y);
        void uniform3i(std::string name, int x, int y, int z);
        void uniform4i(std::string name, int x, int y, int z, int w);

        void uniform1ui(std::string name, unsigned int x);
        void uniform2ui(std::string name, unsigned int x, unsigned int y);
        void uniform3ui(std::string name, unsigned int x, unsigned int y, unsigned int z);
        void uniform4ui(std::string name, unsigned int x, unsigned int y, unsigned int z, unsigned int w);

        void uniform1d(std::string name, double x);
        void uniform2d(std::string name, double x, double y);
        void uniform3d(std::string name, double x, double y, double z);
        void uniform4d(std::string name, double x, double y, double z, double w);

        void uniform1f(std::string name, glm::vec1 v);
        void uniform2f(std::string name, glm::vec2 v);
        void uniform3f(std::string name, glm::vec3 v);
        void uniform4f(std::string name, glm::vec4 v);

        void uniform1i(std::string name, glm::ivec1 v);
        void uniform2i(std::string name, glm::ivec2 v);
        void uniform3i(std::string name, glm::ivec3 v);
        void uniform4i(std::string name, glm::ivec4 v);

        void uniform1ui(std::string name, glm::uvec1 v);
        void uniform2ui(std::string name, glm::uvec2 v);
        void uniform3ui(std::string name, glm::uvec3 v);
        void uniform4ui(std::string name, glm::uvec4 v);

        void uniform1d(std::string name, glm::dvec1 v);
        void uniform2d(std::string name, glm::dvec2 v);
        void uniform3d(std::string name, glm::dvec3 v);
        void uniform4d(std::string name, glm::dvec4 v);

        void uniformMat2(std::string name, glm::mat2 m);
        void uniformMat3(std::string name, glm::mat3 m);
        void uniformMat4(std::string name, glm::mat4 m);

        void uniformMat2d(std::string name, glm::dmat2 m);
        void uniformMat3d(std::string name, glm::dmat3 m);
        void uniformMat4d(std::string name, glm::dmat4 m);

        void uniformMat2x3(std::string name, glm::mat2x3 m);
        void uniformMat3x2(std::string name, glm::mat3x2 m);
        void uniformMat2x4(std::string name, glm::mat2x4 m);
        void uniformMat4x2(std::string name, glm::mat4x2 m);
        void uniformMat4x3(std::string name, glm::mat4x3 m);
        void uniformMat3x4(std::string name, glm::mat3x4 m);

        void uniformMat2x3d(std::string name, glm::dmat2x3 m);
        void uniformMat3x2d(std::string name, glm::dmat3x2 m);
        void uniformMat2x4d(std::string name, glm::dmat2x4 m);
        void uniformMat4x2d(std::string name, glm::dmat4x2 m);
        void uniformMat4x3d(std::string name, glm::dmat4x3 m);
        void uniformMat3x4d(std::string name, glm::dmat3x4 m);

    };
};


std::ostream& operator<<(std::ostream& strm, const kat::UniformType& v);
std::ostream& operator<<(std::ostream& strm, const kat::ShaderType& v);