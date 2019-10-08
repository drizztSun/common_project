#include <stdio.h>

// emcc -o hello2.html hello2.c -O3 -s WASM=1 --shell-file ../hello/html_template/shell_minimal.html

int main(int argc, char ** argv) {
    printf("Hello World\n");
}