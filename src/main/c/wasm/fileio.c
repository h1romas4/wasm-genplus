#include <emscripten/emscripten.h>
#include "shared.h"

uint8_t *rom_buffer;

int load_archive(char *filename, unsigned char *buffer, int maxsize, char *extension)
{
    (void) filename;
    memcpy(buffer, rom_buffer, maxsize);
    strncpy(extension, "BIN", 3);
    extension[3] = 0;

    // 53 45 47 41
    // for(int i = 0; i < 4; i++) {
    //     EM_ASM_({
    //         console.log('genplus_buffer0: ' + $0.toString(16));
    //     }, buffer[0x100 + i]);
    // }

    return maxsize;
}
