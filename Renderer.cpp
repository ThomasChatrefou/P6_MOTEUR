#include "Renderer.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Material.hpp"


void Renderer::Clear() const
{
	glClearColor(0.13f, 0.13f, 0.13f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}


void Renderer::Draw(const Mesh& mesh, const Material& material) const
{
	mesh.Bind();
	material.Bind();
	glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int count) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElementsInstanced(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr, count);
}

void Renderer::EnableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}