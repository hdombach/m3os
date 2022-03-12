#ifndef ARG_H
#define ARG_H

struct Arguments {
	char *sourceFile;
};

//loads the argumetns passed by the programming.
//loads default values for paramaters not passed.
struct Arguments getArg(int argc, char *argv[]);

#endif
