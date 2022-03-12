#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

/**
 * @brief Read the text from a file.
 * 
 * @param filename
 * @return std::string The data from the file.
 */
std::string readFile(std::string filename);

bool stringContains(std::string s, char c);

bool strcomp(const char *a, const char *b);

bool strcomp(std::string a, std::string b);

std::string indentString(std::string s, int amount=1, std::string indentText="| ");

void debug(std::string s);


#endif
