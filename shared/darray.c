#include "darray.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"

struct Darray createDarray(int itemSize, int begginingSize) {
	struct Darray result;

	result.size = 0;
	result.allocSize = begginingSize;
	result.itemSize = itemSize;
	result.data = malloc(begginingSize * itemSize);

	return result;
}

void *get(struct Darray d, int index) {
	if (index >= d.size) {
		return NULL;
	}
	return d.data + index * d.itemSize;
}

int set(struct Darray *d, int index, void *newValue) {
	if (index < d->size) {
		void *i = d->data + index * d->itemSize;
		memcpy(i, newValue, d->itemSize);
		return 1;
	} else {
		return 0;
	}
}


int push(struct Darray *d, void *item) {
	if (d->size >= d->allocSize) {
		d->allocSize *= 2;
		void *temp = malloc(d->allocSize * d->itemSize);
		memcpy(temp, d->data, d->size * d->itemSize);
		free(d->data);
		d->data = temp;
	}
	d->size++;
	if (item != NULL) {
		set(d, d->size - 1, item);
	} else {
		println("ERROR push was passed a null item");
		return 0;
	}
	return 1;
}

void *pop(struct Darray *d) {
	d->size--;
	return get(*d, d->size);
}

void shift(struct Darray *d, int beggining, int amount) {
	int c;
	int oldSize = d->size;
	if (amount > 0) {
		c = 0;
		while (amount > c) {
			push(d, 0);
			c++;
		}
		c = 0;
		while (oldSize - beggining >= c) {
			set(d, d->size - c, get(*d, oldSize - c));
			c++;
		}
	} else {
		c = amount;
		while (0 > c) {
			pop(d);
			c++;
		}
		c = 0;
		while (oldSize - beggining >= c) {
			set(d, beggining + amount + c, get(*d, beggining + c));
			c++;
		}
	}
	
}

void insertItem(struct Darray *d, void *item, int index) {
	shift(d, index, 1);
	set(d, index, item);
}

void removeItem(struct Darray *d, int index) {
	shift(d, index + 1, -1);
}

void appendString(struct Darray *d, char *text) {
	//get rid of terminating character
	if (d->size > 0) {
		pop(d);
	}
	int i = 0;
	char current;
	while (1) {
		current = text[i];
		push(d, &current);
		if (current == '\0') {
			break;
		}
		i++;
	}
}

void appendArray(struct Darray *d, struct Darray a) {
	int c = 0;
	while (a.size > c) {
		push(d, get(a, c));
		c++;
	}
}

void appendRepeating(struct Darray *d, void *value, int amount) {
	int c = 0;
	while (amount > c) {
		push(d, value);
		c++;
	}
}
