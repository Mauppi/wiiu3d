#include "sound.h"

#include <whb/log.h>
#include <iostream>
#include <coreinit/cache.h>
#include <vorbis/vorbisfile.h>
#include <sndcore2/voice.h>
#include <cstring>
#include "resourcemanager.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

bool sound_init() {

    AXInitParams params = {0};
    params.pipeline = AX_INIT_PIPELINE_SINGLE;
    params.renderer = AX_INIT_RENDERER_48KHZ;

    AXInitWithParams(&params);

    return true;
}

AXVoice *sound_create_voice(const char* soundFile, float volume, float pan, AX_DEVICE_TYPE deviceType ) {

    FileResource soundFileResource = ResourceManager_LoadResource(soundFile);

    if (!soundFileResource.loaded) {
        WHBLogPrintf("sound_create_voice failed: %s", soundFile);
        return 0;
    }

    DSPADPCM dspDat = {0};
    memcpy(&dspDat, soundFileResource.data, 96);

    AXVoice *voice = AXAcquireVoice(24, NULL, NULL);

    if (!voice) {
        WHBLogPrintf("sound_create_voice failed: %s", soundFile);
        return 0;
    }

    AXVoiceBegin(voice);

    
    AXVoiceAdpcm adpcm;
    adpcm.gain = dspDat.gain;
    adpcm.predScale = dspDat.ps;
    adpcm.prevSample[0] = dspDat.yn1;
    adpcm.prevSample[1] = dspDat.yn2;
    memcpy(adpcm.coefficients, dspDat.coef, sizeof(dspDat.coef));
    AXSetVoiceAdpcm(voice, &adpcm);

    AXVoiceOffsets offsets;
    offsets.dataType = AX_VOICE_FORMAT_ADPCM;
    offsets.data = soundFileResource.data + 96;
    offsets.endOffset = dspDat.ea;
    offsets.currentOffset = 0;
    offsets.loopOffset = 0;
    offsets.loopingEnabled = dspDat.loop_flag;
    AXSetVoiceOffsets(voice, &offsets);

    if (!AXCheckVoiceOffsets(&offsets)) {
        WHBLogWrite("test sound failed invalid offsets");
        return 0;
    }

    AXSetVoiceSrcType(voice, AX_VOICE_SRC_TYPE_NONE);

    
    AXVoiceVeData veData;
    veData.delta = 0;
    veData.volume = volume * 0x8000;
    AXSetVoiceVe(voice, &veData);

    pan = fmaxf(-1.0f, fminf(1.0f, pan));

    float left = std::cos((pan + 1) * M_PI_4) * 0x8000;
    float right = std::sin((pan + 1) * M_PI_4) * 0x8000;

    AXVoiceDeviceBusMixData busMixData;
    busMixData.volume = left;
    busMixData.delta = 0;

    AXVoiceDeviceBusMixData busMixData2;
    busMixData2.volume = right;
    busMixData2.delta = 0;

    AXVoiceDeviceMixData mixData[2];
    mixData[0].bus[0] = busMixData;
    mixData[1].bus[0] = busMixData;

    AXResult res = AXSetVoiceDeviceMix(voice, deviceType, 0, mixData);

    if (res != AX_RESULT_SUCCESS) {
        WHBLogWritef("test sound failed setting device mix result: %d", res);
        return 0;
    }

    AXVoiceEnd(voice);

    return voice;
}

bool sound_play_voice(AXVoice *voice) {

    AXSetVoiceCurrentOffset(voice, 0);
    AXSetVoiceState(voice, AX_VOICE_STATE_PLAYING);
    return true;
}

bool sound_stop_voice(AXVoice *voice) {

    AXSetVoiceState(voice, AX_VOICE_STATE_STOPPED);
    return true;
}

bool sound_set_voice_volume(AXVoice *voice, float volume) {

    AXVoiceVeData veData;

    veData.volume = volume * 0x8000;
    veData.delta = 0;

    AXSetVoiceVe(voice, &veData);

    return true;
}

bool sound_set_voice_pan(AXVoice *voice, float pan, AX_DEVICE_TYPE deviceType) {

    pan = fmaxf(-1.0f, fminf(1.0f, pan));

    float left = std::cos((pan + 1) * M_PI_4) * 0x8000;
    float right = std::sin((pan + 1) * M_PI_4) * 0x8000;

    AXVoiceDeviceBusMixData busMixData;
    busMixData.volume = left;
    busMixData.delta = 0;

    AXVoiceDeviceBusMixData busMixData2;
    busMixData2.volume = right;
    busMixData2.delta = 0;

    AXVoiceDeviceMixData mixData[2];
    mixData[0].bus[0] = busMixData;
    mixData[1].bus[0] = busMixData2;

    AXResult res = AXSetVoiceDeviceMix(voice, deviceType, 0, mixData);

    if (res != AX_RESULT_SUCCESS) {
        WHBLogWritef("test sound failed setting device mix result: %d", res);
        return false;
    }

    return true;
}



void test_sound() {


    FILE *f = fopen("fs:/vol/content/sigmawin.dsp", "rb");

    if (!f) {
        f = fopen("/vol/content/sigmawin.dsp", "rb");
    }

    if (!f) {
        WHBLogPrint("test sound failed");
        return;
    }

    fseek(f, 0, SEEK_END);
    int32_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    WHBLogPrintf("test sound size: %d", size);

    DSPADPCM dspDat = {0};
    fread(&dspDat, 96, 1, f);

    WHBLogPrintf("test sound header loaded: %d, gain: %a", size, dspDat.gain);

    int16_t *buf = new int16_t[size];
    fread(buf, 1, size, f);
    fclose(f);

    WHBLogPrint("Buffer loaded! Acquiring voice...");

    AXVoice *v = AXAcquireVoice(31, NULL, NULL);

    if (!v) {
        WHBLogWrite("test sound failed acquire voice");
        return;
    }

    AXVoiceBegin(v);

    WHBLogWritef("test sound loaded: %d, gain: %a", size, dspDat.gain);

    AXVoiceAdpcm adpcm;
    adpcm.gain = dspDat.gain;
    adpcm.predScale = dspDat.ps;
    adpcm.prevSample[0] = dspDat.yn1;
    adpcm.prevSample[1] = dspDat.yn2;
    memcpy(adpcm.coefficients, dspDat.coef, sizeof(dspDat.coef));
    AXSetVoiceAdpcm(v, &adpcm);

    AXVoiceOffsets offsets;
    offsets.dataType = AX_VOICE_FORMAT_ADPCM;
    offsets.data = buf;
    offsets.endOffset = dspDat.ea;
    offsets.currentOffset = 0;
    offsets.loopOffset = 0;
    offsets.loopingEnabled = AX_VOICE_LOOP_ENABLED;
    AXSetVoiceOffsets(v, &offsets);

    if (!AXCheckVoiceOffsets(&offsets)) {
        WHBLogWrite("test sound failed invalid offsets");
        return;
    }

    AXSetVoiceSrcType(v, AX_VOICE_SRC_TYPE_NONE);

    AXVoiceVeData veData;
    veData.delta = 0;
    veData.volume = 0x8000;
    AXSetVoiceVe(v, &veData);

    AXVoiceDeviceBusMixData busMixData;
    busMixData.volume = 0x8000;
    busMixData.delta = 0;

    AXVoiceDeviceMixData mixData[2];
    mixData[0].bus[0] = busMixData;
    mixData[1].bus[0] = busMixData;

    AXResult res = AXSetVoiceDeviceMix(v, AX_DEVICE_TYPE_TV, 0, mixData);

    if (res != AX_RESULT_SUCCESS) {
        WHBLogWritef("test sound failed setting device mix result: %d", res);
        return;
    }

    AXSetVoiceState(v, AX_VOICE_STATE_PLAYING);

    AXVoiceEnd(v);

}