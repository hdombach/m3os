DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
clang -c $DIR/util.c -o $DIR/util.o
clang -c $DIR/darray.c -o $DIR/darray.o
clang -c $DIR/error.c -o $DIR/error.o
clang -c $DIR/test.c -o $DIR/test.o
