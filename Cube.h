#pragma once

#include "Includes.hpp"

namespace GC_3D
{
    class Cube
    {
    public:
        Cube();
        ~Cube();

    private:
        GLuint _vertexArrayID;
        GLuint _vertexBuffer;
        GLuint _colorBuffer;
        GLfloat _vertexBufferData[108];
        GLfloat _colorBufferData[108];

        mat4 _model;

    public:
        bool OnInit();
        void OnLoop();
        void OnRender();

    public:
        mat4 GetModelMatrix() { return _model; }

        void SetVertex(GLfloat vertexData[108]);
        void SetColor(GLfloat colorData[108]);
        void SetBuffer();
        void SetModelMatrix(mat4 model);
    };
}