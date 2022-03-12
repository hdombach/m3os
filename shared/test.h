#ifndef TEST_H
#define TEST_H

struct TestResult {
	int passed;
	char *msg;
	char *name;
	char *category;
};

void initTests();
void addTest(struct TestResult);
void addUtilTests();
void printTestResults();

#endif
