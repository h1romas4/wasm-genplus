FROM gitpod/workspace-full

RUN git clone "https://github.com/emscripten-core/emsdk.git" $HOME/.emsdk \
    && cd $HOME/.emsdk \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && bash -c "source ./emsdk_env.sh"

RUN printf "\nsource $HOME/.emsdk/emsdk_env.sh\nclear\n" >> ~/.bashrc

RUN sudo git clone "https://github.com/WebAssembly/binaryen.git" $HOME/.binaryen \
    && cd $HOME/.binaryen \
    && sudo env "PATH=$PATH" cmake . && sudo make

ENV PATH="/opt/binaryen/bin:$PATH"
