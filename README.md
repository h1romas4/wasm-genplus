# maixduino-genplus

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) WebAssembly porting

## Setup require

* [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

```
$ source ./emsdk_env.sh
Adding directories to PATH:
PATH += /home/hiromasa/toolchain/emsdk
PATH += /home/hiromasa/toolchain/emsdk/upstream/emscripten
PATH += /home/hiromasa/toolchain/emsdk/node/12.9.1_64bit/bin

Setting environment variables:
EMSDK = /home/hiromasa/toolchain/emsdk
EM_CONFIG = /home/hiromasa/.emscripten
EMSDK_NODE = /home/hiromasa/toolchain/emsdk/node/12.9.1_64bit/bin/node
$ emcc -v
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 1.39.0
```

## Build

**Emscripten**

```
git clone --recursive https://github.com/h1romas4/wasm-genplus.git
cd wasm-genplus.git
mkdir build && cd build
emcmake cmake ..
emmake make
```

**Webpack**

```
cd ..
npm install
npm run server
```

**ROM file**

Put in
```
docs/roms
```

src/main/js/index.js
```
const ROM_PATH = './roms/sonic2.bin';
```

**Play**

```
http://localhost:9000
```

# Thanks!

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX)
