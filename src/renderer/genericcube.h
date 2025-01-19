class genericcube : public RendererObject {
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
    genericcube(const QString& texturePath = "",
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

    void setScale(float newScale) { scale = newScale; }
    void setPosition(const QVector3D& newPos) { position = newPos; }
    void setRotation(const QVector3D& newRot) { rotation = newRot; }

    void init(QOpenGLShaderProgram* shaderProgram) override {
        // Vertex data for the cube
        static const GLfloat vertices[] = {
            // Position         // Couleur           // UV
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Front
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            // Back
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f
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

        // Position (stride = 8 car chaque vertex a 8 flottants : 3 pour position + 3 pour couleur + 2 pour UV)
        shaderProgram->enableAttributeArray("position");
        shaderProgram->setAttributeBuffer("position", GL_FLOAT, 0, 3, 8 * sizeof(GLfloat));

        // Couleur (offset de 3 flottants pour commencer après la position)
        shaderProgram->enableAttributeArray("color");
        shaderProgram->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 8 * sizeof(GLfloat));

        // UV (offset de 6 flottants pour commencer après la position et la couleur)
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
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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