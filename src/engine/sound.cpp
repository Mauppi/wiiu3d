#include "sound.h"

#include <whb/log.h>
#include <iostream>
#include <coreinit/cache.h>
#include <vorbis/vorbisfile.h>
#include <sndcore2/voice.h>
#include <cstring>

void ax_frame_callback(void *userdata) {
    
}

void test_sound() {

    AXInitParams params;
    params.pipeline = AX_INIT_PIPELINE_SINGLE;
    params.renderer = AX_INIT_RENDERER_48KHZ;

    AXInitWithParams(&params);

    FILE *f = fopen("fs:/vol/content/sigmawin.dsp", "rb");

    if (!f) {
        f = fopen("/vol/content/sigmawin.dsp", "rb");
    }

    if (!f) {
        return;
    }

    fseek(f, 0, SEEK_END);
    int32_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    DSPADPCM dspDat = {0};
    fread(&dspDat, 96, 1, f);

    int16_t *buf = new int16_t[size];
    fread(buf, 1, size, f);
    fclose(f);

    AXVoice *v = AXAcquireVoice(31, NULL, NULL);

    if (!v) {
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