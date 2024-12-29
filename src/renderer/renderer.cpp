#include "renderer.h"
#include <QTimer>
#include <QTime>
#include <QEvent>
#include <QKeyEvent>
#include "cube.h"

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent)
    , vbo(QOpenGLBuffer::VertexBuffer)
    , program(nullptr)
    , rotationAngle(0.0f)
{
}

Renderer::~Renderer()
{
    makeCurrent();
    vbo.destroy();
    delete program;
    doneCurrent();
}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    program = new QOpenGLShaderProgram(this);

    // Charger et compiler les shaders
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cube.vert")) {
        qDebug() << "Failed to load vertex shader:" << program->log();
    }
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cube.frag")) {
        qDebug() << "Failed to load fragment shader:" << program->log();
    }

    // Lier le programme de shader
    if (!program->link()) {
        qDebug() << "Failed to link shader program:" << program->log();
    }

    auto basicCube = std::make_unique<Cube>();
    basicCube->init(program);
    objects.push_back(std::move(basicCube));

    camera = Camera(QVector3D(0.0f, 0.0f, 3.0f));

    // Activer la capture de la souris
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    float aspect = float(width()) / float(height() ? height() : 1);
    projection.setToIdentity();
    projection.perspective(45.0f, aspect, 0.1f, 100.0f);

    // S'assurer que la caméra est à une position où elle peut voir le cube
    camera = Camera(QVector3D(0.0f, 0.0f, 3.0f));
}


void Renderer::paintGL()
{
    float currentFrame = QTime::currentTime().msecsSinceStartOfDay() / 1000.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //camera.processKeyboard(deltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();

    // Définir les matrices uniformes AVANT le rendu
    program->setUniformValue("projection", projection);
    program->setUniformValue("view", camera.getViewMatrix());

    // Une seule boucle de rendu
    for(const auto& obj : objects) {
        obj->render(program);
    }

    program->release();

    update();
}
void Renderer::resizeGL(int width, int height)
{
    float aspect = float(width) / float(height ? height : 1);
    projection.setToIdentity();
    projection.perspective(45.0f, aspect, 0.1f, 100.0f);
}


void Renderer::keyPressEvent(QKeyEvent *event)
{
    // switch (event->key()) {
    // case Qt::Key_Z: camera.moveForward = true; break;
    // case Qt::Key_S: camera.moveBackward = true; break;
    // case Qt::Key_Q: camera.moveLeft = true; break;
    // case Qt::Key_D: camera.moveRight = true; break;
    // case Qt::Key_A: camera.moveUp = true; break;
    // case Qt::Key_E: camera.moveDown = true; break;
    //}
}

void Renderer::keyReleaseEvent(QKeyEvent *event)
{
    // switch (event->key()) {
    // case Qt::Key_Z: camera.moveForward = false; break;
    // case Qt::Key_S: camera.moveBackward = false; break;
    // case Qt::Key_Q: camera.moveLeft = false; break;
    // case Qt::Key_D: camera.moveRight = false; break;
    // case Qt::Key_A: camera.moveUp = false; break;
    // case Qt::Key_E: camera.moveDown = false; break;
    //}
}
void Renderer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rightMousePressed = true;
        lastMousePos = event->pos();
    }
}

void Renderer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rightMousePressed = false;
    }
}

void Renderer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton) {
        QPoint currentPos = event->pos();
        float xoffset = currentPos.x() - lastMousePos.x();
        float yoffset = lastMousePos.y() - currentPos.y();
        lastMousePos = currentPos;

        camera.processMouseMovement(xoffset, yoffset);
        update();
    }
}

void Renderer::wheelEvent(QWheelEvent *event)
{
    // camera.processMouseScroll(event->angleDelta().y() / 120.0f);
    // projection.setToIdentity();
    // projection.perspective(camera.getZoom(),
    //                        float(width()) / float(height() ? height() : 1),
    //                        0.01f, 100.0f);
}
