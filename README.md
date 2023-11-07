# wasm-genplus

![](https://github.com/h1romas4/wasm-genplus/workflows/Emscripten%20CI/badge.svg)

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) WebAssembly porting

![](https://github.com/h1romas4/wasm-genplus/blob/master/assets/ipad-wasm.jpg)

## Build with Local

### Require

* [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

```
$ source ./emsdk_env.sh
Setting up EMSDK environment (suppress these messages with EMSDK_QUIET=1)
Adding directories to PATH:
PATH += /home/hiromasa/devel/toolchain/emsdk
PATH += /home/hiromasa/devel/toolchain/emsdk/upstream/emscripten

Setting environment variables:
PATH = /home/hiromasa/devel/toolchain/emsdk:/home/hiromasa/devel/toolchain/emsdk/upstream/emscripten:/home/hiromasa/devel/toolchain/appimage:/home/hiromasa/.wasmtime/bin:/home/hiromasa/devel/msx/z88dk/bin:/home/hiromasa/.wasmer/bin:/home/hiromasa/.local/bin:/home/hiromasa/.cargo/bin:/home/hiromasa/.sdkman/candidates/java/current/bin:/home/hiromasa/.sdkman/candidates/groovy/current/bin:/home/hiromasa/.sdkman/candidates/gradle/current/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/hiromasa/.dotnet/tools
EMSDK = /home/hiromasa/devel/toolchain/emsdk
EMSDK_NODE = /home/hiromasa/devel/toolchain/emsdk/node/16.20.0_64bit/bin/node

$ emcc -v
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 3.1.48 (e967e20b4727956a30592165a3c1cde5c67fa0a8)
clang version 18.0.0 (https://github.com/llvm/llvm-project a54545ba6514802178cf7cf1c1dd9f7efbf3cde7)
Target: wasm32-unknown-emscripten
Thread model: posix
InstalledDir: /home/hiromasa/devel/toolchain/emsdk/upstream/bin
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

**Setting**

`.env`

```
ROM_PATH="rom/sonic2.bin"
PORT=9000
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

**Setting**

`.env`

```
ROM_PATH="rom/sonic2.bin"
PORT=9000
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
