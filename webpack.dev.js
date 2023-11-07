const { merge } = require('webpack-merge');
const path = require('path');
const common = require('./webpack.config.js');
const process = require('process');

module.exports = merge(common, {
    devtool: 'source-map',
    devServer: {
        static: [
            path.join(__dirname, '/docs'), // eslint-disable-line
            // for sourcemap - src/main/c
            path.join(__dirname, '/'), // eslint-disable-line
        ],
        port: process.env['PORT'],
        open: true,
        // host: '0.0.0.0',
        // disableHostCheck: true
    }
});
