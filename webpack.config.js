const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin')

module.exports = {
    mode: 'development',
    entry: {
        index: './src/main/js/index.js',
    },
    output: {
        filename: '[name].bundle.js',
        path: path.join(__dirname, '/docs'), // eslint-disable-line
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
                test: /.wasm$/,
                type: "javascript/auto",
                loader: "file-loader",
                options: {
                    name: '[name].[ext]'
                }
            },
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: [{
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env']
                    }
                }]
            }
        ]
    },
    resolve: {
        extensions: ['.js'],
        modules: [
            "node_modules"
        ]
    },
    performance: {
        hints: false
    }
};
