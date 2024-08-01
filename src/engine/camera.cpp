#include "camera.h"

float calculateVerticalBorders(float fov, float near) {
    // Calculate the height of the near plane
    float nearHeight = 2.0f * near * tan(fov / 2.0f);
    
    // The top border is half of the near height
    float topBorder = nearHeight / 2.0f;

    return topBorder;
}

float calculateRightBorder(float fov, float aspectRatio, float near) {
    // Calculate the height of the near plane
    float nearHeight = 2.0f * near * tan(fov / 2.0f);
    
    // Calculate the width of the near plane
    float nearWidth = nearHeight * aspectRatio;
    
    // The right border is half of the near width
    float rightBorder = nearWidth / 2.0f;

    return rightBorder;
}

void Camera::init() {

    borders.y = calculateRightBorder(fov, 16.0f / 9.0f, 0.01f);
    borders.x = -borders.y;
    borders.w = calculateVerticalBorders(fov, 0.01f);
    borders.z = -borders.w;

}

void Camera::update() {
}

bool Camera::isInViewFrustum(glm::vec3 pos, glm::vec3 scale) {
    return !(pos.x + scale.x < position.x || pos.x - scale.x > position.y || pos.y + scale.y < position.x + 1920.0f || pos.y - scale.y > position.y + 1080.0f);
}