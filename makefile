main: main.o
	clang++ -o main main.o
clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
LLVM_PROFILE_FILE="main.profraw" ./main < shapes.txt > output.txt
xcrun llvm-profdata merge -sparse main.profraw -o main.profdata
xcrun llvm-cov show ./main -instr-profile=main.profdata
