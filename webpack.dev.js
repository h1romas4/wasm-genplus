const merge = require('webpack-merge');
const path = require('path');
const common = require('./webpack.config.js');

module.exports = merge(common, {
    devtool: 'inline-source-map',
    devServer: {
        inline: true,
        contentBase: [
            path.join(__dirname, '/dest'), // eslint-disable-line
        ],
        watchContentBase: true,
        port: 9000,
        open: true,
        openPage: "index.html"
    }
});
