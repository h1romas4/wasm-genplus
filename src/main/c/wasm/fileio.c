#include <emscripten/emscripten.h>
#include "shared.h"

uint8_t *rom_buffer;
uint32_t rom_size;

int load_archive(char *filename, unsigned char *buffer, int maxsize, char *extension)
{
    (void) filename;
    memcpy(buffer, rom_buffer, rom_size);
    strncpy(extension, "BIN", 3);
    extension[3] = 0;

    // 53 45 47 41
    for(int i = 0; i < 4; i++) {
        EM_ASM_({
            console.log('rom_buffer: ' + $0.toString(16));
        }, buffer[0x100 + i]);
    }
    EM_ASM_({
        console.log('rom_size: ' + $0);
    }, rom_size);

    return rom_size;
}
