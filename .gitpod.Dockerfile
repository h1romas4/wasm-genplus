FROM gitpod/workspace-full

RUN bash -cl "cargo install wasm-pack cargo-wasm cargo-generate \
    && curl \"https://wasmtime.dev/install.sh\" -sSf | bash; \
       rustup target add wasm32-wasi"

RUN wget "https://github.com/CraneStation/wasi-sdk/releases/download/wasi-sdk-8/wasi-sdk_8.0_amd64.deb" \
    && sudo dpkg -i wasi-sdk_8.0_amd64.deb

RUN git clone "https://github.com/emscripten-core/emsdk.git" $HOME/.emsdk \
    && cd $HOME/.emsdk \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && bash -c "source ./emsdk_env.sh"

RUN printf "\nsource $HOME/.emsdk/emsdk_env.sh\nclear\n" >> ~/.bashrc

RUN sudo git clone "https://github.com/WebAssembly/binaryen.git" $HOME/.binaryen \
    && cd $HOME/.binaryen \
    && sudo env "PATH=$PATH" cmake . && sudo make

ENV PATH="/opt/wasi-sdk/bin:/opt/binaryen/bin:$PATH"
