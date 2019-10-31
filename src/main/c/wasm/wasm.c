#include <emscripten/emscripten.h>
#include "shared.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

#define SOUND_FREQUENCY 44100
#define SOUND_SAMPLES_SIZE 2048

#define VIDEO_WIDTH  320
#define VIDEO_HEIGHT 240

md_ntsc_t *md_ntsc;
sms_ntsc_t *sms_ntsc;

uint32_t *frame_buffer;
int16_t *sound_frame;

float_t *web_audio_l;
float_t *web_audio_r;

struct _zbank_memory_map zbank_memory_map[256];

int sdl_input_update(void) {
    return 1;
}

void EMSCRIPTEN_KEEPALIVE init(void)
{
    // vram & sampling malloc
    frame_buffer = malloc(sizeof(uint32_t) * VIDEO_WIDTH * VIDEO_HEIGHT);
    sound_frame = malloc(sizeof(int16_t) * SOUND_SAMPLES_SIZE);
    web_audio_l = malloc(sizeof(float_t) * SOUND_SAMPLES_SIZE);
    web_audio_r = malloc(sizeof(float_t) * SOUND_SAMPLES_SIZE);

    // system init
    error_init();
    set_config_defaults();

    // video ram init
    memset(&bitmap, 0, sizeof(bitmap));
    bitmap.width      = VIDEO_WIDTH;
    bitmap.height     = VIDEO_HEIGHT;
    bitmap.pitch      = VIDEO_WIDTH * 4;
    bitmap.data       = (uint8_t *)frame_buffer;
    bitmap.viewport.changed = 3;

    // load rom
    load_rom("sonic2.bin");

    // emurator init
    audio_init(SOUND_FREQUENCY, 0);
    system_init();
    system_reset();
}

float_t convert_sample_i2f(int16_t i) {
    float_t f;
    if(i < 0) {
        f = ((float) i) / (float) 32768;
    } else {
        f = ((float) i) / (float) 32767;
    }
    if( f > 1 ) f = 1;
    if( f < -1 ) f = -1;
    return f;
}

void EMSCRIPTEN_KEEPALIVE loop(void) {
    system_frame_gen(0);
}

int EMSCRIPTEN_KEEPALIVE sound(void) {
    int size = audio_update(sound_frame);
    int p = 0;
    for(int i = 0; i < size * 2; i += 2) {
        web_audio_l[p] = convert_sample_i2f(sound_frame[i]);
        web_audio_r[p] = convert_sample_i2f(sound_frame[i + 1]);
        p++;
    }
    return p;
}

uint32_t* EMSCRIPTEN_KEEPALIVE get_frame_buffer_ref(void) {
    return frame_buffer;
}

float_t* EMSCRIPTEN_KEEPALIVE get_web_audio_l_ref(void) {
    return web_audio_l;
}

float_t* EMSCRIPTEN_KEEPALIVE get_web_audio_r_ref(void) {
    return web_audio_r;
}
