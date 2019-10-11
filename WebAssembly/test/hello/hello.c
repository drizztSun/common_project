#include <stdio.h>
// #include <emscripten/emscripten.h> 

// *** run command 'emcc hello.c -s WASM=1 -o hello.html' to compile ***
// -s WASM=1 — Specifies that we want wasm output. If we don’t specify this, Emscripten will just output asm.js, as it does by default.
// -o hello.html — Specifies that we want Emscripten to generate an HTML page to run our code in (and a filename to use), 
// as well as the wasm module and the JavaScript "glue" code to compile and instantiate the wasm so it can be used in the web environment.

// emcc hello.c -s WASM=1 -o hello.html
// emcc -o hello2.html hello2.c -O3 -s WASM=1 --shell-file html_template/shell_minimal.html

// -s WASM=1 — Specifies that we want wasm output. If we don’t specify this, Emscripten will just output asm.js, as it does by default.
// -o hello.html — Specifies that we want Emscripten to generate an HTML page to run our code in (and a filename to use), 
// as well as the wasm module and the JavaScript "glue" code to compile and instantiate the wasm so it can be used in the web environment.

// At this point in your source directory you should have:

// The binary wasm module code (hello.wasm)
// A JavaScript file containing glue code to translate between the native C functions, and JavaScript/wasm (hello.js)
// An HTML file to load, compile, and instantiate your wasm code, and display its output in the browser (hello.html)

int main(int argc, char ** argv) {

    printf("Hello world !!");

    return 0;
}


//If you have a function defined in your C code that you want to call as needed from JavaScript, 
// you can do this using the Emscripten ccall() function, and the EMSCRIPTEN_KEEPALIVE declaration 
// (which adds your functions to the exported functions list (see Why do functions in my C/C++ source code vanish 
// when I compile to JavaScript, and/or I get No functions to process?)). Let's look at how this works.

#ifdef __cplusplus
extern "C" {
#endif

// emcc -o hello3.html hello3.c -O3 -s WASM=1 --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
// (Note that we need to compile with NO_EXIT_RUNTIME, which is necessary as otherwise when main() exits the runtime would be shut down 
// — necessary for proper C emulation, e.g., atexits are called — and it wouldn't be valid to call compiled code.)
// Putting EMSCRIPTEN_KEEPALIVE before a function name stops this from happening. You also need to import the emscripten.h library to use EMSCRIPTEN_KEEPALIVE.

/*
int EMSCRIPTEN_KEEPALIVE add(int a, int b) {
    printf("a: %d, b : %d, a + b : %d", a, b, a + b);
    return a + b;
};*/


/* calling this component from html page
        <button class=".run" id="button"> Run </button>
        <script>
            document.getElementById("button").addEventlistener("click", function(){
                alert("Start calculating");
                var button = Module.ccall("print", null, null, null);
            });
        </script>
 */
/*
void EMSCRIPTEN_KEEPALIVE print() {
    print("my calcaulationg runs");
}*/

#ifdef __cplusplus
}
#endif

