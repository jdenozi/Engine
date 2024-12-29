// // camera.cpp
// #include "camera.h"
// #include <QtMath>

// Camera::Camera(const QVector3D& position)
//     : position(position)
//     , front(QVector3D(0.0f, 0.0f, -1.0f))
//     , worldUp(QVector3D(0.0f, 1.0f, 0.0f))
// {
//     updateCameraVectors();
// }

// void Camera::processKeyboard(float deltaTime)
// {
//     float velocity = movementSpeed * deltaTime;
//     if (moveForward)
//         position += front * velocity;
//     if (moveBackward)
//         position -= front * velocity;
//     if (moveRight)
//         position += right * velocity;
//     if (moveLeft)
//         position -= right * velocity;
//     if (moveUp)
//         position += worldUp * velocity;
//     if (moveDown)
//         position -= worldUp * velocity;
// }

// void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
// {
//     xoffset *= mouseSensitivity;
//     yoffset *= mouseSensitivity;

//     yaw += xoffset;
//     pitch += yoffset;

//     if (constrainPitch) {
//         if (pitch > 89.0f)
//             pitch = 89.0f;
//         if (pitch < -89.0f)
//             pitch = -89.0f;
//     }

//     updateCameraVectors();
// }

// void Camera::processMouseScroll(float yoffset)
// {
//     zoom -= yoffset;
//     if (zoom < 1.0f)
//         zoom = 1.0f;
//     if (zoom > 120.0f)
//         zoom = 120.0f;
// }

// QMatrix4x4 Camera::getViewMatrix() const
// {
//     QMatrix4x4 view;
//     view.lookAt(position, position + front, up);
//     return view;
// }

// void Camera::updateCameraVectors()
// {
//     QVector3D newFront;
//     newFront.setX(qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
//     newFront.setY(qSin(qDegreesToRadians(pitch)));
//     newFront.setZ(qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
//     front = newFront.normalized();
//     right = QVector3D::crossProduct(front, worldUp).normalized();
//     up = QVector3D::crossProduct(right, front).normalized();
// }
