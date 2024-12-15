#include "sprite.h"

#include "graphics.h"
#include "camera.h"
#include "resourcemanager.h"
#include <whb/log.h>
#include <gx2/registers.h>

std::vector<std::string> spriteTextureNames;

bool Sprite::init(const char* filename) {

    FileResource resource = ResourceManager_LoadResource(filename);
    if (!resource.loaded) {
        WHBLogPrintf("Failed to load sprite: %s", filename);
        return false;
    }


    bool texture_found = false;
    for (int i = 0; i < spriteTextureNames.size(); i++) {
        if (strcmp(spriteTextureNames[i].c_str(), filename) == 0) {
            texture_found = true;
            break;
        }
    }
    if (!texture_found) {
        spriteTextureNames.push_back(filename);
    }

    texture = WHBGfxLoadGFDTexture(0, resource.data);
    
    GX2InitSampler(&sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_POINT);

    graphics_spriteRefs.push_back(this);

    return true;
}

void Sprite::draw() {

    if (!visible || !current_camera.isInViewFrustum(position, scale)) {
        return;
    }

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    MVP = glm::mat4(1.0f);
    MVP = projection * view * model;
    
    
    GX2SetBlendConstantColor(1.0f, 1.0f, 1.0f, colorModulate.w);

    GX2SetVertexUniformReg(0, 16, &MVP[0][0]);
    GX2SetPixelUniformReg(0, 4, &colorModulate[0]);

    GX2SetPixelTexture(texture, graphics_default_shader_group.pixelShader->samplerVars[0].location);
    GX2SetPixelSampler(&sampler, graphics_default_shader_group.pixelShader->samplerVars[0].location);

    GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, FALSE, TRUE);
    //GX2SetColorControl(GX2_LOGIC_OP_COPY, 0xFF, FALSE, TRUE);
    GX2SetBlendControl(GX2_RENDER_TARGET_0,
            /* RGB = [srcRGB * srcA] + [dstRGB * (1-srcA)] */
            GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
            GX2_BLEND_COMBINE_MODE_ADD,
            TRUE,
            /* A = [srcA * 1] + [dstA * (1-srcA)] */
            GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_ONE,
            GX2_BLEND_COMBINE_MODE_ADD);

    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);
}

Sprite::~Sprite() {
    for (int i = 0; i < graphics_spriteRefs.size(); i++) {
        if (graphics_spriteRefs[i] == this) {
            graphics_spriteRefs.erase(graphics_spriteRefs.begin() + i);
            break;
        }
    }
}