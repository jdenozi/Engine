#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class RendererObject {
public:
    virtual ~RendererObject() = default;

    // Déclarez explicitement les fonctions virtuelles
    virtual void init(QOpenGLShaderProgram* shaderProgram) = 0;
    virtual void render(QOpenGLShaderProgram* shaderProgram) = 0;
    virtual void cleanup() = 0;

protected:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLShaderProgram shader;
};
