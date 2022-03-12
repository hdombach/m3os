#ifndef ARG_HPP
#define ARG_HPP

#include <string>
using namespace std;

/**
 * @brief A struct to easily parse the input arguments
 * 
 */
struct Arguments {
	string sourceFile;
};

Arguments getArg(int argc, char *argv[]);

#endif