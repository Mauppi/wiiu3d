#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Camera
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, -10.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 70.0f;

    glm::vec4 borders = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    void init();
    void update();

    bool isInViewFrustum(glm::vec3 pos, glm::vec3 scale);
};

#endif