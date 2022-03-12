#include <fstream>
#include "util.hpp"
#include <string>
#include <iostream>
#include "unistd.h"
using namespace std;

string readFile(string fileName) {
	string result;
	ifstream myFile;
	myFile.open(fileName);
	while (myFile) {
		result += myFile.get();
	}
	return result;
}

bool stringContains(std::string s, char c) {
	return s.find(c) != std::string::npos;
}

bool strcomp(const char *a, const char *b) {
	int c = 0;
	while (true) {
		if (a[c] == '\0' || b[c] == '\0') {
			return true;
		}
		if (a[c] != b[c]) {
			return false;
		}
		c++;
	}
}

bool strcomp(std::string a, std::string b) {
	return (a.find(b, 0) == 0);
}

string indentString(string s, int amount, string indentText) {
	string result = s;
	
	result.insert(0, indentText);

	for (int i = 0; i < result.length(); i++) {
		char c = result[i];
		if (c == '\n') {
			for (int j = 0; j < amount; j++) {
				result.insert(i + 1, indentText);
			}
		}
	}

	return result;
}

void debug(std::string s) {
	cout << s + "\n";
	usleep(100000);
};
