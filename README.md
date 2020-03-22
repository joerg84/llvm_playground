# LLVM Codegen Playground

## Compile C++ to LLVM IR
```
brew install llvm
clang test.cpp -S -emit-llvm -O3
```

## Interpret LLVM IR
```
export PATH="/usr/local/opt/llvm/bin:$PATH"
lli test.ll 
echo $?
 > 42
```
## compile LLVM IR to bin
```
llc -filetype=obj test.ll
clang test.o -o test
./test 
echo $?
> 42
```

## Generate LLVM IR Using IRBuilder
```
clang++ main.cpp `llvm-config --ldflags --system-libs  --cppflags --libs core executionengine interpreter mc support nativecodegen`
lli program.ll 
llc -filetype=obj program.ll 
clang program.o -o hello
```


https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
https://reviews.llvm.org/rL266379#change-NnvuDIEmk0CO
https://www.ibm.com/developerworks/library/os-createcompilerllvm1/index.html

Next: https://github.com/Legacy25/ValkyrieDB