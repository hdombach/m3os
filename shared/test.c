#include "test.h"
#include "darray.h"
#include <stdio.h>
#include "util.h"
#include "string.h"

struct Darray tests;
void *tester;

void initTests() {
	//get size of function pointer
	tests = createDarray(sizeof(struct TestResult), 16);
}

void addTest(struct TestResult t) {
	push(&tests, &t);
}

void printTestResults() {
	int c = 0;
	struct TestResult result;
	int passed = 0;

	println("Starting tests.");

	while (c < tests.size) {
		result = *(struct TestResult *)get(tests, c);

		if (result.passed == 1) {
			printf("✅ ");
			passed ++;
		} else {
			printf("❌ ");
		}
		printf("%s.", result.name);

		if (result.passed == 1) {
			printf("\n");
		} else {
			printf(" %s\n", result.msg);
		}
		c++;
	}

	println("%d/%d tests passed.", passed, c);
}


//Tests for the shared folder

struct TestResult creatingDarray() {
	struct TestResult r;
	r.name = "Creating Darray";
	r.passed = 0;
	
	struct Darray d = createDarray(10, 16);
	if (d.allocSize != 16) {
		r.msg = "allocated size is not 16";
		return r;
	}
	if (d.itemSize != 10) {
		r.msg = "item size is not 10";
	}
	if (d.size != 0) {
		r.msg = "size is not 0";
	}
	r.passed = 1;
	return r;
}

struct TestResult gettingDarray() {
	struct TestResult r;
	r.name = "Getting from Darray";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 2);
	int *p = d.data;
	p++;
	int original = 5;
	memcpy(p, &original, sizeof(int));
	int v = *(int *)get(d, 1);
	if (v != 5) {
		r.msg = "Retrieved value is not 5";
		return r;
	}
	r.passed = 1;
	return r;
}

struct TestResult settingDarray() {
	struct TestResult r;
	r.name = "Setting a darray";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 5);
	int original = 912054;
	set(&d, 3, &original);
	int last = *(int *)get(d, 3);
	if (last != 912054) {
		r.msg = "Retrived value is not 912054";
		return r;
	}
	r.passed = 1;
	return r;
}

struct TestResult shiftingDarrayRight() {
	struct TestResult r;
	r.name = "Shifting darray right";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 3);
	int value = 10;
	appendRepeating(&d, &value, 3);
	value = 13;
	set(&d, 1, &value);
	value = 14;
	set(&d, 2, &value);

	shift(&d, 1, 2);

	if (d.size != 5) {
		r.msg = "size of darray is not 5";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 10) {
		r.msg = "item 0 of darray is not 10";
		return r;
	}
	value = *(int *)get(d, 3);
	if (value != 13) {
		r.msg = "item 3 of darray is not 13";
		return r;
	}
	value = *(int *)get(d, 4);
	if (value != 14) {
		r.msg = "ite 4 of darray is not 14";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult shiftingDarrayLeft() {
	struct TestResult r;
	r.name = "Shifting darray left";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 5);
	int value = 10;
	appendRepeating(&d, &value, 5);
	value = 11;
	set(&d, 3, &value);
	value = 12;
	set(&d, 4, &value);

	shift(&d, 1, -2);

	if (d.size != 3) {
		r.msg = "Size of darray is not 3";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 10) {
		r.msg = "item 0 of darray is not 10";
		return r;
	}
	value = *(int *)get(d, 1);
	if (value != 11) {
		r.msg = "item 1 of darray is not 11";
		return r;
	}
	value = *(int *)get(d, 2);
	if (value != 12) {
		r.msg = "item 2 of darray is not 12";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult pushingDarray() {
	struct TestResult r;
	r.name= "Pushing to darray.";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 3);
	int value = 10;
	push(&d, &value);
	value = 11;
	push(&d, &value);
	value = 12;
	push(&d, &value);

	if (d.size != 3) {
		r.msg = "Size of darray is not 3";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 10) {
		r.msg = "item 0 of darray is not 10";
		return r;
	}
	value = *(int *)get(d, 1);
	if (value != 11) {
		r.msg = "item 1 of darray is not 11";
		return r;
	}
	value = *(int *)get(d, 2);
	if (value != 12) {
		r.msg = "item 2 of darray is not 12";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult poppingDarray() {
	struct TestResult r;
	r.name = "Popping darray";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 3);
	int value = 10;
	push(&d, &value);
	value = 11;
	push(&d, &value);
	value = 12;
	push(&d, &value);

	if (d.size != 3) {
		r.msg = "size of darray is not 3";
		return r;
	}
	value = *(int *)pop(&d);
	if (value != 12) {
		println("popped value %d", value);
		r.msg = "popped item of darray is not 12";
		return r;
	}
	value = *(int *)pop(&d);
	if (value != 11) {
		r.msg = "popped item of darray is not 11";
		return r;
	}
	if (d.size != 1) {
		r.msg = "size of darray is not 1";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult insertingItem() {
	struct TestResult r;
	r.name = "Inserting item";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 3);

	int value = 10;
	push(&d, &value);
	value = 12;
	push(&d, &value);
	value = 11;
	insertItem(&d, &value, 1);

	if (d.size != 3) {
		r.msg = "Size of darray is not 3";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 10) {
		r.msg = "item 0 of darray is not 10";
		return r;
	}
	value = *(int *)get(d, 1);
	if (value != 11) {
		r.msg = "item 1 of darray is not 11";
		return r;
	}
	value = *(int *)get(d, 2);
	if (value != 12) {
		r.msg = "item 2 of darray is not 12";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult removingItem() {
	struct TestResult r;
	r.name = "Removing Item";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 3);
	int value = 100;
	push(&d, &value);
	value = 5921;
	push (&d, &value);
	value = 101;
	push(&d, &value);

	removeItem(&d, 1);

	if (d.size != 2) {
		r.msg = "size of darray is not 2";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 100) {
		r.msg = "item 0 of darray is not 100";
		return r;
	}
	value = *(int *)get(d, 1);
	if  (value != 101) {
		r.msg = "item 1 of darray is not 101";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult appendingString() {
	struct TestResult r;
	r.name = "Appending String in Darray";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(char), 20);
	appendString(&d, "this is a");
	appendString(&d, " complete sentance.");

	if (strcmp("this is a complete sentance.", d.data) != 0) {
		r.msg = "string does not match";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult appendingArray() {
	struct TestResult r;
	r.name = "Appending darray to darray";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 2);
	int value = 100;
	push(&d, &value);
	value = 101;
	push(&d, &value);

	struct Darray d2 = createDarray(sizeof(int), 2);
	value = 102;
	push(&d, &value);
	value = 103;
	push(&d, &value);

	appendArray(&d, d2);

	if (d.size != 4) {
		r.msg = "length of darray is not 4";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 100) {
		r.msg = "item 0 of darray is not 100";
		return r;
	}
	value = *(int *)get(d, 1);
	if (value != 101) {
		r.msg = "item 1 of darray is not 101";
		return r;
	}
	value = *(int *)get(d, 2);
	if (value != 102) {
		r.msg = "item 2 of darray is not 102";
		return r;
	}
	value = *(int *)get(d, 3);
	if (value != 103) {
		r.msg = "item 3 of darary is not 103";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult appendingRepeating() {
	struct TestResult r;
	r.name = "Appending repeating values";
	r.passed = 0;

	struct Darray d = createDarray(sizeof(int), 1);
	int value = 123;
	appendRepeating(&d, &value, 3);
	
	if (d.size != 3) {
		r.msg = "size of darray is not 3";
		return r;
	}
	value = *(int *)get(d, 0);
	if (value != 123) {
		r.msg = "item 0 of darray is not 123";
		return r;
	}
	value = *(int *)get(d, 1);
	if (value != 123) {
		r.msg = "item 1 of darary is not 123";
		return r;
	}
	value = *(int *)get(d, 2);
	if (value != 123) {
		r.msg = "item 2 of darray is not 123";
		return r;
	}

	r.passed = 1;
	return r;
}

void addUtilTests() {
	addTest(creatingDarray());
	addTest(gettingDarray());
	addTest(settingDarray());
	addTest(shiftingDarrayRight());
	addTest(shiftingDarrayLeft());
	addTest(pushingDarray());
	addTest(poppingDarray());
	addTest(insertingItem());
	addTest(removingItem());
	addTest(appendingString());
	addTest(appendingArray());
	addTest(appendingRepeating());
}
