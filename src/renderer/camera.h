#include <QVector3D>
#include <QMatrix4x4>

class Camera {
private:
    QVector3D position;
    QVector3D front;
    QVector3D up;
    QVector3D right;
    QVector3D worldUp;

    // Angles d'Euler
    float yaw;
    float pitch;
    float roll;  // Si vous voulez aussi la rotation sur Z

    // Options de caméra
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
        view.rotate(yaw, QVector3D(0.0f, 1.0f, 0.0f));   // Rotation Y
        view.rotate(pitch, QVector3D(1.0f, 0.0f, 0.0f)); // Rotation X
        return view;
    }

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        // Contraindre le pitch pour éviter le retournement de la caméra
        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        // Calculer le nouveau vecteur front
        QVector3D front;
        front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        front.setY(sin(qDegreesToRadians(pitch)));
        front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        this->front = front.normalized();

        // Recalculer les vecteurs right et up
        right = QVector3D::crossProduct(this->front, worldUp).normalized();
        up = QVector3D::crossProduct(right, this->front).normalized();
    }
};