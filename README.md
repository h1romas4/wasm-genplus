# wasm-genplus

![](https://github.com/h1romas4/wasm-genplus/workflows/Emscripten%20CI/badge.svg)

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) WebAssembly porting

![](https://github.com/h1romas4/wasm-genplus/blob/master/assets/ipad-wasm.jpg)

## Build with Local

### Require

* [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

```
$ source ./emsdk_env.sh
Adding directories to PATH:
PATH += /home/hiromasa/devel/toolchain/emsdk
PATH += /home/hiromasa/devel/toolchain/emsdk/upstream/emscripten
PATH += /home/hiromasa/devel/toolchain/emsdk/node/12.18.1_64bit/bin

Setting environment variables:
EMSDK = /home/hiromasa/devel/toolchain/emsdk
EM_CONFIG = /home/hiromasa/devel/toolchain/emsdk/.emscripten
EM_CACHE = /home/hiromasa/devel/toolchain/emsdk/upstream/emscripten/cache
EMSDK_NODE = /home/hiromasa/devel/toolchain/emsdk/node/12.18.1_64bit/bin/node

$ emcc -v
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 1.40.1
clang version 12.0.0 (/b/s/w/ir/cache/git/chromium.googlesource.com-external-github.com-llvm-llvm--project 9f21947a331203ee2579db87f1d1ec22a949e20a)
```

### Build

**Emscripten**

```
git clone --recursive https://github.com/h1romas4/wasm-genplus.git
cd wasm-genplus
mkdir build && cd build
emcmake cmake ..
emmake make
```

**webpack**

```
cd ..
npm install
npm run start
```

**ROM file**

Deploy the .bin file

```
docs/roms
```

Set path, src/main/js/index.js

```
const ROM_PATH = './roms/sonic2.bin';
```

**Play**

(recommended) Firefox or Safari

```
http://localhost:9000
```

## Build with Gitpod

**Open in Gitpod**

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/h1romas4/wasm-genplus)

**Gitpod terminal:**

```
mkdir build && cd build
emcmake cmake ..
emmake make
```

**ROM file**

Drag and drop the .bin file

```
docs/roms/
```

Set path, src/main/js/index.js

```
const ROM_PATH = './roms/sonic2.bin';
```

**Play**

```
cd ..
npm run server
```

![](https://github.com/h1romas4/wasm-genplus/blob/master/assets/gitpod-01.jpg)

## License

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX/blob/master/LICENSE.txt) License

## Thanks!

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX)
