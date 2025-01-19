#include "renderer.h"
#include <QTimer>
#include <QTime>
#include <QEvent>
#include <QKeyEvent>
#include "genericcube.h"
#include "plane.h"

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

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cube.vert")) {
        qDebug() << "Failed to load vertex shader:" << program->log();
    }
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cube.frag")) {
        qDebug() << "Failed to load fragment shader:" << program->log();
    }

    if (!program->link()) {
        qDebug() << "Failed to link shader program:" << program->log();
    }

    auto skybox = std::make_unique<genericcube>(
        ":/assets/textures/sky_tex.jpg",
        100.0f,
        QVector3D(0.0f, 0.0f, 0.0f)
    );

    // Pour le sol
    auto ground = std::make_unique<Plane>(
        ":/assets/textures/ground_sand_tex.jpg",
        20.0f,                             // grande échelle pour le sol
        QVector3D(0.0f, -0.5f, 0.0f)      // juste sous le cube
    );

    // Pour un cube normal
    auto cube = std::make_unique<genericcube>(
        ":/assets/textures/cliff_tex.jpg",
        1.0f,
        QVector3D(0.0f, 0.0f, 0.0f),     // Le cube reste au centre
        QVector3D(0.0f, 0.0f, 0.0f)
    );



    skybox->init(program);
    ground->init(program);
    cube->init(program);

    objects.push_back(std::move(skybox));
    objects.push_back(std::move(ground));
    objects.push_back(std::move(cube));


    camera = Camera(QVector3D(0.0f, 0.0f, 3.0f));

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    float aspect = float(width()) / float(height() ? height() : 1);
    projection.setToIdentity();
    projection.perspective(0.0f, aspect, 0.1f, 100.0f);

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

    program->setUniformValue("projection", projection);
    program->setUniformValue("view", camera.getViewMatrix());

    for(const auto& obj : objects) {
        if (obj) {
            obj->render(program);
        } else {
            qDebug() << "Null object in render list";
        }
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
     switch (event->key()) {
    case Qt::Key_Z: camera.moveForward(1.5f); break;
    case Qt::Key_S: camera.moveBackward(1.5f); break;
    case Qt::Key_Q: camera.moveLeft(1.0f); break;
    case Qt::Key_D: camera.moveRight(1.0f); break;
    case Qt::Key_A: camera.moveUp(1.0f); break;
    case Qt::Key_E: camera.moveDown(1.0f); break;
    }
}

void Renderer::mouseMoveEvent(QMouseEvent *event)
{
    if (!rightMousePressed) return;

    // Calcule le centre de la fenêtre
    QPoint center = QPoint(width()/2, height()/2);

    // Calcule l'offset par rapport au centre plutôt que la dernière position
    float xoffset = (event->pos().x() - center.x()) * 0.5;
    float yoffset = (center.y() - event->pos().y()) * 0.5;  // Inversé pour Y

    // Met à jour la caméra
    camera.processMouseMovement(xoffset, yoffset, true);

    // Replace le curseur au centre
    QCursor::setPos(mapToGlobal(center));

    update();
}


void Renderer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rightMousePressed = true;
        // Place immédiatement le curseur au centre quand on commence
        QPoint center = QPoint(width()/2, height()/2);
        QCursor::setPos(mapToGlobal(center));
        setCursor(Qt::BlankCursor);  // Cache le curseur
    }
}

void Renderer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rightMousePressed = false;
        setCursor(Qt::ArrowCursor);  // Réaffiche le curseur
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
