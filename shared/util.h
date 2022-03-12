#ifndef UTIL_H
#define UTIL_H

void *resize(void *old, int newSize);
char *readFile(char *filename);
void println(const char *format, ...);
int strcstr(char *a, char *b);

#endif
