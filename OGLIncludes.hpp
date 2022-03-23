#pragma once 

#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <filesystem>
#include <string_view>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



template <typename T>
using Vector = std::vector<T>;

struct BoundingSphere
{
    glm::vec3 m_Center;
    float m_Radius;
};