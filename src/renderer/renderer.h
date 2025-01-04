#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "camera.h"
#include "rendererobject.h"

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Renderer(QWidget *parent = nullptr);
    ~Renderer();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void initShaders();
    void initCube();

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *program;
    QMatrix4x4 projection;
    QMatrix4x4 modelView;
    float rotationAngle;
    std::vector<std::unique_ptr<RendererObject>> objects;

    Camera camera;
    QPoint lastMousePos;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    bool rightMousePressed = false;
};

#endif // GLWIDGET_H
