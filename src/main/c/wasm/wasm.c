#include <emscripten/emscripten.h>
#include "shared.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

#define SOUND_FREQUENCY 48000
#define SOUND_SAMPLES_SIZE  2048

#define VIDEO_WIDTH  320
#define VIDEO_HEIGHT 240

md_ntsc_t *md_ntsc;
sms_ntsc_t *sms_ntsc;

uint16_t *frame_buffer;
signed short *soundframe;

struct _zbank_memory_map zbank_memory_map[256];

int sdl_input_update(void) {
    return 1;
}

void EMSCRIPTEN_KEEPALIVE init(void)
{
    // vram & sampling malloc
    frame_buffer = malloc(sizeof(uint16_t) * 320 * 240);
    soundframe = malloc(sizeof(signed short) * SOUND_SAMPLES_SIZE);

    // system init
    error_init();
    set_config_defaults();

    // video ram init
    memset(&bitmap, 0, sizeof(bitmap));
    bitmap.width      = 320;
    bitmap.height     = 240;
    bitmap.pitch      = 320 * 2;
    bitmap.data       = (uint8_t *)frame_buffer;
    bitmap.viewport.changed = 3;

    // load rom
    load_rom("sonic2.bin");

    // emurator init
    audio_init(SOUND_FREQUENCY, 0);
    system_init();
    // system_reset();
}

void EMSCRIPTEN_KEEPALIVE loop(void) {
    system_frame_gen(0);
    audio_update(soundframe);
}

uint16_t* EMSCRIPTEN_KEEPALIVE get_frame_buffer_ref(void) {
    return frame_buffer;
}
