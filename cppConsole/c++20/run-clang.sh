CXX='clang++-9 -std=c++2a -fmodules-ts'

# $CSS -0 split main.cpp && \

$CXX -o split.pcm --precompile -x c++-module split.cpp && \
$CXX -o split -fprebuilt-module-path=. main.cpp split.cpp && \
./split
