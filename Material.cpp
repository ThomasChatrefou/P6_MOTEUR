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
    m_Shader = std::make_unique<Shader>(shaderPath);
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