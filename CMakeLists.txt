cmake_minimum_required(VERSION 3.0)

include(./cmake/macros.cmake)
project(genplus C CXX)

header_directories(./src/main/c)

add_source_files(
    ./src/main/c/core/z80/z80.c
    ./src/main/c/core/m68k/m68kcpu.c
    ./src/main/c/core/m68k/s68kcpu.c
    ./src/main/c/core/genesis.c
    ./src/main/c/core/vdp_ctrl.c
    ./src/main/c/core/vdp_render.c
    ./src/main/c/core/system.c
    ./src/main/c/core/io_ctrl.c
    ./src/main/c/core/mem68k.c
    ./src/main/c/core/memz80.c
    ./src/main/c/core/membnk.c
    ./src/main/c/core/state.c
    ./src/main/c/core/loadrom.c
    ./src/main/c/core/input_hw/input.c
    ./src/main/c/core/input_hw/gamepad.c
    ./src/main/c/core/input_hw/lightgun.c
    ./src/main/c/core/input_hw/mouse.c
    ./src/main/c/core/input_hw/activator.c
    ./src/main/c/core/input_hw/xe_1ap.c
    ./src/main/c/core/input_hw/teamplayer.c
    ./src/main/c/core/input_hw/paddle.c
    ./src/main/c/core/input_hw/sportspad.c
    ./src/main/c/core/input_hw/terebi_oekaki.c
    ./src/main/c/core/input_hw/graphic_board.c
    ./src/main/c/core/sound/sound.c
    ./src/main/c/core/sound/psg.c
    ./src/main/c/core/sound/ym2413.c
    ./src/main/c/core/sound/ym2612.c
    ./src/main/c/core/sound/ym3438.c
    ./src/main/c/core/sound/blip_buf.c
    ./src/main/c/core/sound/eq.c
    ./src/main/c/core/cart_hw/sram.c
    ./src/main/c/core/cart_hw/svp/svp.c
    ./src/main/c/core/cart_hw/svp/ssp16.c
    ./src/main/c/core/cart_hw/ggenie.c
    ./src/main/c/core/cart_hw/areplay.c
    ./src/main/c/core/cart_hw/eeprom_93c.c
    ./src/main/c/core/cart_hw/eeprom_i2c.c
    ./src/main/c/core/cart_hw/eeprom_spi.c
    ./src/main/c/core/cart_hw/md_cart.c
    ./src/main/c/core/cart_hw/sms_cart.c
    ./src/main/c/core/cd_hw/cd_cart.c
    ./src/main/c/core/cd_hw/cdc.c
    ./src/main/c/core/cd_hw/cdd.c
    ./src/main/c/core/cd_hw/gfx.c
    ./src/main/c/core/cd_hw/pcm.c
    ./src/main/c/core/cd_hw/scd.c
    ./src/main/c/core/ntsc/sms_ntsc.c
    ./src/main/c/core/ntsc/md_ntsc.c
    ./src/main/c/wasm/config.c
    ./src/main/c/wasm/error.c
    ./src/main/c/wasm/fileio.c
    ./src/main/c/wasm/scrc32.c
    ./src/main/c/wasm/wasm.c
)

# source map option
#   # -Oz
#   -g
#   -fdebug-compilation-dir='../src/main/c'
#   -gseparate-dwarf='../src/main/js/genplus.dbg'

add_compile_flags(C
    -Oz
    -std=gnu11
    -fomit-frame-pointer
    -Wno-strict-aliasing
    -Wno-unused-parameter
    -Wno-unused-function
    -Wno-sign-compare
    -DLSB_FIRST
    -DUSE_32BPP_RENDERING
    -DHAVE_YM3438_CORE
    -DWASM_GENPLUS
)

add_compile_flags(LD
    "-s ALLOW_MEMORY_GROWTH=1"
    "-s MODULARIZE=1"
    "-s TOTAL_MEMORY=32MB"
    "-s FILESYSTEM=0"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../src/main/js)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../src/main/js)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../src/main/js)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
