import genplus from '../c/genplus';

const CANVAS_WIDTH = 320;
const CANVAS_HEIGHT = 240;

// emulator
let gens;
let romdata;

// canvas member
let canvas;
let canvas_context;
let canvasImageData;

// canvas setting
(function() {
    canvas = document.getElementById('screen');
    canvas.setAttribute('width', CANVAS_WIDTH);
    canvas.setAttribute('height', CANVAS_HEIGHT);
    let pixelRatio = window.devicePixelRatio ? window.devicePixelRatio : 1;
    if(pixelRatio > 1 && window.screen.width < CANVAS_WIDTH) {
        canvas.style.width = 320 + "px";
        canvas.style.heigth = 240 + "px";
    }
    canvas_context = canvas.getContext('2d');
    canvasImageData = canvas_context.createImageData(CANVAS_WIDTH, CANVAS_HEIGHT);
})();

genplus.initialize().then(wasm => {
    gens = wasm;
    console.log(gens);
    // load rom
    fetch('./roms/sonic2.bin').then(response => response.arrayBuffer())
    .then(bytes => {
        // create buffer from wasm
        console.log("ptr: " + gens._get_rom_buffer_ref());
        romdata = new Uint8Array(gens.HEAPU8.buffer, gens._get_rom_buffer_ref(), bytes.byteLength);
        console.log("romdata: " + romdata[0]);
        romdata.set(new Uint8Array(bytes));
        console.log("rom loaded.");
        gens._init();
        console.log("init");
        loop();
    });
});

let loop = function() {
    gens._loop();
    let vram = new Uint8Array(gens.HEAPU32.buffer, gens._get_frame_buffer_ref(), CANVAS_WIDTH * CANVAS_HEIGHT * 4);
    canvasImageData.data.set(vram);
    canvas_context.putImageData(canvasImageData, 0, 0);
    requestAnimationFrame(loop);
}
