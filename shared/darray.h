#ifndef DARRAY_H
#define DARRAY_H

struct Darray {
	int size;
	int allocSize;
	int itemSize;
	void *data;
};

struct Darray createDarray(int itemSize, int begginingSize);
void *get(struct Darray d, int index);

//sets an item in a darray
//struct Darray *d: darray to use
//int index: index of item to change
//void *newValue
//returns: 1 for success, 0 for fail
int set(struct Darray *d, int index, void *newValue);
void shift(struct Darray *d, int beginning, int amount);

//adds and item to the end of a darray
//struct Darray *d: the darray to add token
//void *item: the item to add
//returns: 1 for success, 0 for fail
int push(struct Darray *d, void *item);
void *pop(struct Darray *d);
void insertItem(struct Darray *d, void *item, int index);
void removeItem(struct Darray *d, int index);
void appendString(struct Darray *d, char *text);
void appendArray(struct Darray *d, struct Darray a);
void appendRepeating(struct Darray *d, void *value, int amount);


#endif
