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

#include <chrono>
#include <vector>

#include <GL/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace GC_3D
{
  using namespace glm;

  template <typename T>
  using Vector = std::vector<T>;

  using Clock = std::chrono::high_resolution_clock;
  using Timestamp = Clock::time_point;
  using Duration = Clock::duration;

  inline float Seconds(Duration const& iDuration)
  {
    return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
  }

  struct BoundingSphere
  {
      vec3 m_Center;
      float m_Radius;
  };
}