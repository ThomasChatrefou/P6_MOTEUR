#pragma once

#include "OGLIncludes.hpp"


class Scene
{
	Scene();

private:
	std::vector<std::shared_ptr<class Mesh>> meshes;
	std::vector<std::shared_ptr<class Material>> materials;
};