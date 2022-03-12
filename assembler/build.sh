clang -c ../shared/util.c -o ../shared/util.o
clang -c ../shared/darray.c -o ../shared/darray.o
clang *.c ../shared/util.o ../shared/darray.o && ./a.out
