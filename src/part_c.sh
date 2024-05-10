time clang -c Table.cpp -o s.o
time clang -c Structs.cpp -o s.o

time clang s.o t.o q1.o -o output.out -lstdc++