#include "rendererobject.h"

class Cube : public RendererObject {
private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QMatrix4x4 model;

public:
    Cube() : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer), model() {}

    void init(QOpenGLShaderProgram* shaderProgram) override {
        // Vertex data for the cube
        static const GLfloat vertices[] = {
            // Position         // Couleur
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // Rouge
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Vert
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // Bleu
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // Jaune
            // Face arrière
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // Magenta
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, // Cyan
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Blanc
            -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f  // Gris
        };

        static const GLuint indices[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Right face
            1, 5, 6,
            6, 2, 1,
            // Back face
            5, 4, 7,
            7, 6, 5,
            // Left face
            4, 0, 3,
            3, 7, 4,
            // Top face
            3, 2, 6,
            6, 7, 3,
            // Bottom face
            4, 5, 1,
            1, 0, 4
        };


        vao.create();
        vao.bind();

        vbo.create();
        vbo.bind();
        vbo.allocate(vertices, sizeof(vertices));

        // Position (stride = 6 car chaque vertex a 6 flottants : 3 pour position + 3 pour couleur)
        shaderProgram->enableAttributeArray("position");
        shaderProgram->setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

        // Couleur (offset de 3 flottants pour commencer après la position)
        shaderProgram->enableAttributeArray("color");
        shaderProgram->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

        ibo.create();
        ibo.bind();
        ibo.allocate(indices, sizeof(indices));

        vao.release();
    }
    void render(QOpenGLShaderProgram* shaderProgram) override {
        model.setToIdentity();
        model.rotate(45.0f, QVector3D(1.0f, 1.0f, 0.0f));

        shaderProgram->setUniformValue("model", model);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        vao.release();
    }

    void cleanup() override {
        vbo.destroy();
        ibo.destroy();
        vao.destroy();
    }
};
