const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin')

module.exports = {
    mode: 'production',
    entry: {
        index: './src/main/js/index.js',
    },
    output: {
        filename: '[name].bundle.js',
        path: path.join(__dirname, '/dest'), // eslint-disable-line
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: './src/main/html/index.html'
        })
    ],
    externals: {
        fs: "empty"
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: [{
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env']
                    }
                }]
            },
            {
                test: /\.clist$/,
                use: [
                    {
                        loader: 'emcc-loader',
                        options: {
                            buildDir: path.join(__dirname, '/temp'), // eslint-disable-line
                            commonFlags: [
                                '-g',
                                '-Wall',
                                '-Wextra',
                                '-Isrc/main/c/core',
                                '-Isrc/main/c/core/sound',
                                '-Isrc/main/c/core/cart_hw',
                                '-Isrc/main/c/core/cart_hw/svp',
                                '-Isrc/main/c/core/cd_hw',
                                '-Isrc/main/c/core/ntsc',
                                '-Isrc/main/c/core/tremor',
                                '-Isrc/main/c/core/debug',
                                '-Isrc/main/c/core/z80',
                                '-Isrc/main/c/core/input_hw',
                                '-Isrc/main/c/core/m68k',
                                '-Isrc/main/c/wasm'
                            ],
                            cFlags: [
                                '-DENVIRONMENT=web',
                                '-std=gnu11',
                                '-fomit-frame-pointer',
                                '-Wno-strict-aliasing',
                                '-Wno-unused-parameter',
                                '-Wno-unused-function',
                                '-Wno-sign-compare',
                                '-DLSB_FIRST',
                                '-DUSE_16BPP_RENDERING',
                                '-DMAXROMSIZE=1048576',
                                '-DHAVE_ALLOCA_H',
                                '-DUSE_DYNAMIC_ALLOC',
                                '-DALT_RENDERER',
                                '-DALIGN_LONG',
                                '-DMAIXDUINO',
                            ],
                            ldFlags: [
                                '-s', 'DEMANGLE_SUPPORT=1',
                                '-s', "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"
                            ]
                        }
                    }
                ]
            }
        ]
    },
    resolve: {
        extensions: ['.js', '.clist'],
        modules: [
            "node_modules"
        ]
    },
    performance: {
        hints: false
    }
};
