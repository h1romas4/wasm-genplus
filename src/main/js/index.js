import genplus from '../c/genplus';

const CANVAS_WIDTH = 320;
const CANVAS_HEIGHT = 240;
const SOUND_FREQUENCY = 44100;

// emulator
let gens;
let romdata;
let vram_ref;

// canvas member
let canvas;
let canvasContext;
let canvasImageData;

// fps control
const FPS = 60;
const INTERVAL = 1000 / FPS;
let now;
let then;
let delta;

// audio member
let audioContext;

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
    canvasContext = canvas.getContext('2d');
    canvasImageData = canvasContext.createImageData(CANVAS_WIDTH, CANVAS_HEIGHT);
    // hit any key for audio context
    canvasContext.font = "48px serif";
    canvasContext.fillStyle = "#fff";
    canvasContext.fillText("Click!", 100, 100);
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
        vram_ref = gens._get_frame_buffer_ref();
        canvas.addEventListener('click', start, false);
    });
});

const start = function() {
    canvas.removeEventListener('click', start, false);
    // audio init
    audioContext = new AudioContext();
    // game loop
    then = Date.now();
    loop();
};

const loop = function() {
    requestAnimationFrame(loop);
    now = Date.now();
    delta = now - then;
    if (delta > INTERVAL) {
        // update
        gens._loop();
        then = now - (delta % INTERVAL);
        // sound
        let sampleSize = gens._sound();
        let audioBuffer = audioContext.createBuffer(2, sampleSize, SOUND_FREQUENCY);
        let audio_l = new Float32Array(gens.HEAPF32.buffer, gens._get_web_audio_l_ref(), sampleSize);
        let audio_r = new Float32Array(gens.HEAPF32.buffer, gens._get_web_audio_r_ref(), sampleSize);
        audioBuffer.getChannelData(0).set(audio_l);
        audioBuffer.getChannelData(1).set(audio_r);
        let source = audioContext.createBufferSource();
        source.buffer = audioBuffer;
        source.connect(audioContext.destination);
        source.start(0);
        // draw
        let vram = new Uint8ClampedArray(gens.HEAPU8.buffer, vram_ref, CANVAS_WIDTH * CANVAS_HEIGHT * 4);
        canvasImageData.data.set(vram);
        canvasContext.putImageData(canvasImageData, 0, 0);
    }
}
