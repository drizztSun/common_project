#include <stdio.h>
#include <emscripten/emscripten.h>

// *** emcc -o hello3.html hello3.c -O3 -s WASM=1 --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" ***

int main(int argc, char ** argv) {
    printf("Hello World\n");
}

#ifdef __cplusplus
extern "C" {
#endif

void EMSCRIPTEN_KEEPALIVE myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

#ifdef __cplusplus
}
#endif