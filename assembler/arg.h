#ifndef ARG_H
#define ARG_H

struct Arguments {
	char *sourceFile;
};

struct Arguments getArg(int argc, char *argv[]);

#endif
