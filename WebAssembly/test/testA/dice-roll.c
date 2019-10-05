#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>

int main(int argc, char** argv) {
    printf("This is a entry of WebAssembly main function");
}

int EMSCRIPTEN_KEEPALIVE roll_dice() {
    srand( time(NULL));
    return rand() % 6 + 1;
}


// compile command 
// *** emcc dice-roll.c -s WASM=1 -O3 -o index.js ***

// emcc: Emscripten compiler
// dice-roll.c: C file to compile
// -s WASM=1 : force use WebAssembly
// -O3 : Opmtism 3
// -o : generate all files, to be need by WASM module

// need to run  source ./emsdk_env.sh

// How to start a webserver in 
// python3 -m http.server 8080 --bind 127.0.0.1