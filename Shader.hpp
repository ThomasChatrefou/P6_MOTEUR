#pragma once
#include "OGLIncludes.hpp"

class Shader
{
private:
    unsigned int m_ID;

public:
    bool InitShaders();
	void LoadShader(const char*, const char*, const char*);
    void LoadAndCreateTexture(const char* m_texture1, const char* m_texture2);
    void BindTextures(unsigned int texture1, unsigned int texture2);
	void UseShader();
    void CheckCompileErrors(GLuint shader, std::string type);

public:
    unsigned int getID() { return m_ID; }
    void setID(unsigned int id) { m_ID = id; }
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w); 
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

};