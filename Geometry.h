#pragma once

#include "gc_3d_defs.hpp"

namespace GC_3D
{
    struct Geometry
    {
        //These arrays should all have the same size.
        //They can be empty as well
        Vector<vec3> m_Pos;
        Vector<vec3> m_Normals;
        Vector<vec2> m_TexCoord;

        Vector<uint32_t> m_Indices;

        void Bind() const;
        void Draw() const;
    };

}