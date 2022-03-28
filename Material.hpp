#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>


class Shader;
class MyTexture;


class Material
{
public:
	Material(const std::string& shaderPath, const std::string& texturePath);
	~Material();

	void UpdateMVP(const glm::mat4& mvp);

	void Bind() const;
	void Unbind() const;

private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<MyTexture> m_Texture;
};