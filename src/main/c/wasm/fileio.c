#include <emscripten/emscripten.h>
#include "shared.h"

uint8_t *rom_buffer;

int load_archive(char *filename, unsigned char *buffer, int maxsize, char *extension)
{
    (void) filename;
    (void) maxsize;
    memcpy(buffer, rom_buffer, 1048576);
    strncpy(extension, "BIN", 3);
    extension[3] = 0;

    EM_ASM_({
        console.log('rom_buffer: ' + $0);
    }, rom_buffer[0]);

    EM_ASM_({
        console.log('genplus_buffer0: ' + $0);
    }, buffer[0]);
    EM_ASM_({
        console.log('genplus_buffer1: ' + $0);
    }, buffer[1]);

    return 1048576;
}

uint8_t* EMSCRIPTEN_KEEPALIVE get_rom_buffer_ref(void) {
    rom_buffer = malloc(sizeof(uint8_t) * MAXROMSIZE);
    rom_buffer[0] = 99;
    return rom_buffer;
}
