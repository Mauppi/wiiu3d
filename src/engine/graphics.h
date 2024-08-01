#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <whb/gfx.h>
#include <gx2/clear.h>
#include <gx2/draw.h>
#include <gx2/swap.h>
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "sprite.h"

inline WHBGfxShaderGroup graphics_default_shader_group;
inline Camera current_camera;
inline glm::mat4 projection = glm::mat4(1.0f);
inline glm::mat4 view = glm::mat4(1.0f);
inline glm::mat4 model = glm::mat4(1.0f);
inline glm::mat4 MVP = glm::mat4(1.0f);
inline std::vector<Sprite*> graphics_spriteRefs;

bool graphics_init();
void graphics_run();
void graphics_exit();

#endif