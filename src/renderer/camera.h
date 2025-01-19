#include <QVector3D>
#include <QMatrix4x4>

class Camera {
public:
    QVector3D position;
    QVector3D front;
    QVector3D up;
    QVector3D right;
    QVector3D worldUp;

    // Euler angles
    float yaw; // psi autout de l'axe Y
    float pitch; // theta autour de laxe
    float roll;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

public:
    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 3.0f))
        : position(position)
        , front(QVector3D(0.0f, 0.0f, -1.0f))
        , worldUp(QVector3D(0.0f, 1.0f, 0.0f))
        , yaw(-90.0f)
        , pitch(0.0f)
        , movementSpeed(2.5f)
        , mouseSensitivity(0.1f)
        , zoom(45.0f)
    {
        updateCameraVectors();
    }

    QMatrix4x4 getViewMatrix() {
        QMatrix4x4 view;
        view.lookAt(position, position + front, up);

        return view;
    }


    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        // Avoid pitch for upside down camera
        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void moveBackward(float deltaTime) {
        position -= front * deltaTime * 0.1;
    }

    void moveForward(float deltaTime) {
        position -= -front * deltaTime * 0.1;
    }

    void moveRight(float deltaTime) {
        position -= -right * deltaTime * 0.1;
    }

    void moveUp(float deltaTime) {
        position -= up * deltaTime * 0.1;
    }


    void moveDown(float deltaTime) {
        position -= -up * deltaTime * 0.1;
    }


    void moveLeft(float deltaTime) {
        position -= right * deltaTime * 0.1;
    }


private:
    void updateCameraVectors() {
        // COmpute new front vector
        QVector3D front;
        front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        front.setY(sin(qDegreesToRadians(pitch)));
        front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        this->front = front.normalized();

        // Comput eup and down vector
        right = QVector3D::crossProduct(this->front, worldUp).normalized();
        up = QVector3D::crossProduct(right, this->front).normalized();
    }
};
