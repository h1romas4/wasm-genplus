import genplus from '../c/genplus';

let romdata;

genplus.initialize().then(gens => {
    console.log(gens);
    // load rom
    fetch('./roms/sonic2.bin')
        .then(response => response.arrayBuffer())
        .then(bytes => {
            // create buffer from wasm
            console.log("ptr: " + gens._get_rom_buffer_ref());
            romdata = new Uint8Array(gens.HEAPU8.buffer, gens._get_rom_buffer_ref(), bytes.byteLength);
            console.log("romdata: " + romdata[0]);
            romdata.set(new Uint8Array(bytes));
            console.log("rom loaded.");
        })
        .then(results => {
            gens._init();
            console.log("init");
        });
});
