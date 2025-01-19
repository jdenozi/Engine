class Plane : public RendererObject {
private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QMatrix4x4 model;
    QOpenGLTexture* texture;
    float scale;
    QVector3D position;
    QVector3D rotation;

public:
    Plane(const QString& texturePath = "", 
         float scale = 1.0f,
         const QVector3D& position = QVector3D(0.0f, 0.0f, 0.0f),
         const QVector3D& rotation = QVector3D(0.0f, 0.0f, 0.0f))
        : vbo(QOpenGLBuffer::VertexBuffer)
        , ibo(QOpenGLBuffer::IndexBuffer)
        , model()
        , texture(nullptr)
        , scale(scale)
        , position(position)
        , rotation(rotation)
    {
        if (!texturePath.isEmpty()) {
            texture = new QOpenGLTexture(QImage(texturePath));
            texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            texture->setMagnificationFilter(QOpenGLTexture::Linear);
            texture->setWrapMode(QOpenGLTexture::Repeat);
        }
    }

    void init(QOpenGLShaderProgram* shaderProgram) override {
        // Vertex data pour un plan (4 vertices)
        static const GLfloat vertices[] = {
            // Position          // Couleur           // UV
            -0.5f, 0.0f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Avant-gauche
             0.5f, 0.0f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Avant-droit
             0.5f, 0.0f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Arrière-droit
            -0.5f, 0.0f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f   // Arrière-gauche
        };

        static const GLuint indices[] = {
            0, 1, 2,  // Premier triangle
            2, 3, 0   // Second triangle
        };

        vao.create();
        vao.bind();

        vbo.create();
        vbo.bind();
        vbo.allocate(vertices, sizeof(vertices));

        shaderProgram->enableAttributeArray("position");
        shaderProgram->setAttributeBuffer("position", GL_FLOAT, 0, 3, 8 * sizeof(GLfloat));

        shaderProgram->enableAttributeArray("color");
        shaderProgram->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 8 * sizeof(GLfloat));

        shaderProgram->enableAttributeArray("texCoord");
        shaderProgram->setAttributeBuffer("texCoord", GL_FLOAT, 6 * sizeof(GLfloat), 2, 8 * sizeof(GLfloat));

        ibo.create();
        ibo.bind();
        ibo.allocate(indices, sizeof(indices));

        vao.release();
    }

    void render(QOpenGLShaderProgram* shaderProgram) override {
        if (texture) {
            texture->bind(0);
            shaderProgram->setUniformValue("textureSampler", 0);
        }

        model.setToIdentity();
        model.translate(position);
        model.rotate(rotation.x(), 1.0f, 0.0f, 0.0f);
        model.rotate(rotation.y(), 0.0f, 1.0f, 0.0f);
        model.rotate(rotation.z(), 0.0f, 0.0f, 1.0f);
        model.scale(scale);

        shaderProgram->setUniformValue("model", model);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.release();

        if (texture) {
            texture->release();
        }
    }

    void cleanup() override {
        vbo.destroy();
        ibo.destroy();
        vao.destroy();
        if (texture) {
            delete texture;
            texture = nullptr;
        }
    }
};