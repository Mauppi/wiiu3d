#include "graphics.h"

#include "app.h"
#include <iostream>
#include <whb/log.h>
#include <gx2r/buffer.h>
#include <gx2r/draw.h>
#include <gx2r/mem.h>
#include <gx2r/resource.h>
#include <gx2r/surface.h>
#include <gx2/mem.h>
#include <coreinit/memdefaultheap.h>
#include <libpng16/png.h>
#include <cstddef>
#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <gx2/registers.h>
#include <gx2/state.h>
#include <gx2/display.h>

static const float position_vb[] =
{
   -1.0f, -1.0f,
    1.0f, -1.0f,
    1.0f,  1.0f,
   -1.0f,  1.0f,
};

static const float tex_coord_vb[] =
{
   0.0f, 1.0f,
   1.0f, 1.0f,
   1.0f, 0.0f,
   0.0f, 0.0f,
};

GX2RBuffer vPosBuf;
GX2RBuffer vTexCoordBuf;
GX2RBuffer MVPBuf;
GX2UniformVar *mvp_shaderoffset;
GX2BlendConstantColorReg regiblend;


bool graphics_init() {
    if (WHBGfxInit() != TRUE) {
        WHBLogPrint("WHBGfxInit failed");
        return false;
    }

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
    /*GX2SetTargetChannelMasks(
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA,
    GX2_CHANNEL_MASK_RGBA);*/
   // GX2SetAlphaTest(TRUE, GX2_COMPARE_FUNC_GREATER, 0.0f);

    //GX2InitBlendConstantColorReg(&regiblend, 0.0f, 0.0f, 0.0f, 0.0f);
    //GX2SetBlendConstantColorReg(&regiblend);

    

    FILE *file = fopen("fs:/vol/content/mainshader.gsh", "rb");
    if (!file) {
        WHBLogPrint("Shader failed first open check, trying /vol/content/mainshader.gsh");
        file = fopen("/vol/content/mainshader.gsh", "rb");
    }

    if (!file) {
        WHBLogPrint("Shader load failed!!");
        return false;
    }

    size_t size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *shader = new char[size];
    fread(shader, 1, size, file);
    fclose(file);

    if (!WHBGfxLoadGFDShaderGroup(&graphics_default_shader_group, 0, shader)) {
        WHBLogPrint("WHBGfxLoadGFDShaderGroup failed");
        return false;
    }

    WHBGfxInitShaderAttribute(&graphics_default_shader_group, "vertexPosition_modelspace", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    WHBGfxInitShaderAttribute(&graphics_default_shader_group, "vertexUV", 1, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);

    if (WHBGfxInitFetchShader(&graphics_default_shader_group) != TRUE) {
        WHBLogPrint("WHBGfxInitFetchShader failed");
        return false;
    }

    /*GX2SetViewport(0, 0, 1280, 720, 0.001f, 100.0f);
    GX2SetScissor(0, 0, 1280, 720);*/

    vPosBuf.flags = (GX2RResourceFlags) (GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    vPosBuf.elemSize = 2 * 4;
    vPosBuf.elemCount = 4;
    GX2RCreateBuffer(&vPosBuf);
    void *buffer = GX2RLockBufferEx(&vPosBuf, GX2RResourceFlags::GX2R_RESOURCE_BIND_NONE);
    memcpy(buffer, position_vb, vPosBuf.elemSize * vPosBuf.elemCount);
    GX2RUnlockBufferEx(&vPosBuf, GX2RResourceFlags::GX2R_RESOURCE_BIND_NONE);

    vTexCoordBuf.flags = (GX2RResourceFlags) (GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    vTexCoordBuf.elemSize = 2 * 4;
    vTexCoordBuf.elemCount = 4;
    GX2RCreateBuffer(&vTexCoordBuf);
    buffer = GX2RLockBufferEx(&vTexCoordBuf, GX2RResourceFlags::GX2R_RESOURCE_BIND_NONE);
    memcpy(buffer, tex_coord_vb, vTexCoordBuf.elemSize * vTexCoordBuf.elemCount);
    GX2RUnlockBufferEx(&vTexCoordBuf, GX2RResourceFlags::GX2R_RESOURCE_BIND_NONE);

    mvp_shaderoffset = GX2GetVertexUniformVar(graphics_default_shader_group.vertexShader, "MVP");
    if (mvp_shaderoffset == nullptr) {
        WHBLogPrint("MVP shader variable not found");
        return false;
    }

    WHBLogPrint("Graphics initialized");

    return true;
}

void graphics_run() {


    WHBGfxBeginRender();

    

    WHBGfxBeginRenderTV();

    
    
    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    view = glm::translate(view, current_camera.position);
    
    GX2ColorBuffer *colbuf = WHBGfxGetTVColourBuffer();

    projection = glm::ortho(-1920.0f, 1920.0f, -1080.0f, 1080.0f, 0.001f, 100.0f);

    WHBGfxClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //GX2ClearDepthStencilEx(WHBGfxGetTVDepthBuffer(), 5.0f, 0, GX2_CLEAR_FLAGS_BOTH);
    
    GX2SetFetchShader(&graphics_default_shader_group.fetchShader);
    GX2SetVertexShader(graphics_default_shader_group.vertexShader);
    GX2SetPixelShader(graphics_default_shader_group.pixelShader);
    GX2RSetAttributeBuffer(&vPosBuf, 0, vPosBuf.elemSize, 0);
    GX2RSetAttributeBuffer(&vTexCoordBuf, 1, vTexCoordBuf.elemSize, 0);

    
    

    app_draw();



    WHBGfxFinishRenderTV();
    
    /*GX2SetViewport(0, 0, 854, 480, 0.001f, 100.0f);
    GX2SetScissor(0, 0, 854, 480);*/


    WHBGfxBeginRenderDRC();

    
    WHBGfxClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GX2SetFetchShader(&graphics_default_shader_group.fetchShader);
    GX2SetVertexShader(graphics_default_shader_group.vertexShader);
    GX2SetPixelShader(graphics_default_shader_group.pixelShader);
    GX2RSetAttributeBuffer(&vPosBuf, 0, vPosBuf.elemSize, 0);
    GX2RSetAttributeBuffer(&vTexCoordBuf, 1, vTexCoordBuf.elemSize, 0);

    app_draw_drc();

    WHBGfxFinishRenderDRC();

    WHBGfxFinishRender();
}

void graphics_exit() {

}