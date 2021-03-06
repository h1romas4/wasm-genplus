#include <emscripten/emscripten.h>
#include "shared.h"
#include "fileio.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

#define SOUND_FREQUENCY 44100
#define SOUND_SAMPLES_SIZE 2048

#define VIDEO_WIDTH  640
#define VIDEO_HEIGHT 480

#define GAMEPAD_API_INDEX 32

uint32_t *frame_buffer;
int16_t *sound_frame;
float_t *input_buffer;

float_t *web_audio_l;
float_t *web_audio_r;

struct _zbank_memory_map zbank_memory_map[256];

void EMSCRIPTEN_KEEPALIVE init(void)
{
    // vram & sampling malloc
    rom_buffer = malloc(sizeof(uint8_t) * MAXROMSIZE);
    frame_buffer = malloc(sizeof(uint32_t) * VIDEO_WIDTH * VIDEO_HEIGHT);
    sound_frame = malloc(sizeof(int16_t) * SOUND_SAMPLES_SIZE);
    web_audio_l = malloc(sizeof(float_t) * SOUND_SAMPLES_SIZE);
    web_audio_r = malloc(sizeof(float_t) * SOUND_SAMPLES_SIZE);
    input_buffer = malloc(sizeof(float_t) * GAMEPAD_API_INDEX);
}

void EMSCRIPTEN_KEEPALIVE start(void)
{
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
    load_rom("dummy.bin");

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

void EMSCRIPTEN_KEEPALIVE tick(void) {
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

int EMSCRIPTEN_KEEPALIVE wasm_input_update(void) {
    // reset input
    input.pad[0] = 0;
    // read button
    if(input_buffer[8 + 2]) input.pad[0] |= INPUT_A;
    if(input_buffer[8 + 3]) input.pad[0] |= INPUT_B;
    if(input_buffer[8 + 1]) input.pad[0] |= INPUT_C;
    if(input_buffer[8 + 7]) input.pad[0] |= INPUT_START;
    if(input_buffer[8 + 0]) input.pad[0] |= INPUT_X;
    if(input_buffer[8 + 4]) input.pad[0] |= INPUT_Y;
    if(input_buffer[8 + 5]) input.pad[0] |= INPUT_Z;
    if(input_buffer[8 + 6]) input.pad[0] |= INPUT_MODE;
    // read axes
    if(input_buffer[7] == -1) {
        input.pad[0] |= INPUT_UP;
    } else if(input_buffer[7] == 1) {
        input.pad[0] |= INPUT_DOWN;
    }
    if(input_buffer[6] == -1) {
        input.pad[0] |= INPUT_LEFT;
    } else if(input_buffer[6] == 1) {
        input.pad[0] |= INPUT_RIGHT;
    }
    // EM_ASM_({
    //     console.log('input_buffer[4 + 7]: ' + $0);
    // }, input_buffer[8 + 7]);
    return 1;
}

uint8_t* EMSCRIPTEN_KEEPALIVE get_rom_buffer_ref(uint32_t size) {
    rom_size = size;
    return rom_buffer;
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

float_t* EMSCRIPTEN_KEEPALIVE get_input_buffer_ref(void) {
    return input_buffer;
}
