sh ../shared/build.sh

tag="nothing"
if [[ $1 ]]
then
	tag="$1"
fi

clang -g -rdynamic -D $tag *.c ../shared/*.o && ./a.out
