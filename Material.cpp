#include "Material.hpp"

#include "Shader.hpp"
#include "MyTexture.hpp"


#ifndef Uniforms
#define Uniforms
const std::string MVP_UNIFORM = "u_MVP";
const std::string TEXTURE_UNIFORM = "u_Texture";
#endif // !Uniforms


Material::Material(const std::string& shaderPath, const std::string& texturePath)
{
    m_Shader = std::make_shared<Shader>(shaderPath);
    m_Shader->Bind();

    m_Texture = std::make_unique<MyTexture>(texturePath);
    m_Shader->SetUniform1i(TEXTURE_UNIFORM, 0);
}

Material::~Material()
{

}

void Material::UpdateMVP(const glm::mat4& mvp)
{
    m_Shader->Bind();
    m_Shader->SetUniformMat4f(MVP_UNIFORM, mvp);
    m_Shader->Unbind();
}

void Material::SetVec3(const std::string& name, float v0, float v1, float v2) 
{
    m_Shader->SetUniform3f(name, v0, v1, v2);
}

void Material::SetFloat(const std::string& name, float f0)
{
    m_Shader->SetUniform1f(name, f0);
}

void Material::SetInt(const std::string& name, int i0) 
{
    m_Shader->SetUniform1i(name, i0);
}

void Material::Bind() const
{
	m_Shader->Bind();
	m_Texture->Bind();
}

void Material::Unbind() const
{
	m_Shader->Unbind();
	m_Texture->Unbind();
}