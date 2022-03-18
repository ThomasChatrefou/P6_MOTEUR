#pragma once

#include "Includes.hpp"

namespace GC_3D
{
    class Triangle
    {
    public:
        Triangle();
        ~Triangle();

    private:
        GLuint _vertexArrayID; 
        GLuint _vertexBuffer;
        GLuint _colorBuffer;
        GLfloat _vertexBufferData[9];
        GLfloat _colorBufferData[9];

        mat4 _model;

    public:
        bool OnInit();
        void OnLoop();
        void OnRender();

    public:
        mat4 GetModelMatrix() { return _model; }

        void SetVertex(GLfloat vertexData[9]);
        void SetVertex(vec3 A, vec3 B, vec3 C);
        void SetColor(GLfloat colorData[9]);
        void SetBuffer();
        void SetModelMatrix(mat4 model);
    };
}