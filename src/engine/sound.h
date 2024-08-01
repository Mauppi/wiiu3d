#ifndef SOUND_H
#define SOUND_H

#include <sndcore2/core.h>
#include <sndcore2/voice.h>


typedef struct
{
     // for header generation during decode
         uint32_t num_samples;       // total number of RAW samples
         uint32_t num_adpcm_nibbles; // number of ADPCM nibbles (including frame headers)
         uint32_t sample_rate;       // Sample rate, in Hz

     // DSP addressing and decode context
         uint16_t loop_flag;    // 1=LOOPED, 0=NOT LOOPED
         uint16_t format;       // Always 0x0000, for ADPCM
         uint32_t sa;           // Start offset address for looped samples (2 for non-looped)
         uint32_t ea;           // End offset address for looped samples
         uint32_t ca;           // always 2
         uint16_t coef[16];     // decode coefficients (eight pairs of 16-bit words)

     // DSP decoder initial state
         uint16_t gain;         // always zero for ADPCM
         uint16_t ps;           // predictor/scale
         uint16_t yn1;          // sample history
         uint16_t yn2;          // sample history

     // DSP decoder loop context
         uint16_t lps;          // predictor/scale for loop context
         uint16_t lyn1;         // sample history (n-1) for loop context
         uint16_t lyn2;         // sample history (n-2) for loop context

     // Multi-DSP 
         uint16_t multi_ch_count;    // number of interleaved adpcm channels (1 through 6) or 0 for single channel
         uint16_t block_frame_count; // Number of ADPCM frames (8 bytes per frame) in each interleaved channel block.  Default is currently 1024 resulting in 8192 bytes per interleaved channel block.

     // Reserved
         uint16_t pad[9];

} DSPADPCM;

//void test_sound();

bool sound_init();

AXVoice *sound_create_voice(const char* soundFile, float volume = 1.0f, float pan = 0.0f, AX_DEVICE_TYPE deviceType = AX_DEVICE_TYPE_TV);
bool sound_play_voice(AXVoice *voice);
bool sound_stop_voice(AXVoice *voice);
bool sound_set_voice_volume(AXVoice *voice, float volume);
bool sound_set_voice_pan(AXVoice *voice, float pan, AX_DEVICE_TYPE deviceType = AX_DEVICE_TYPE_TV);


#endif