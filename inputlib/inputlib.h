#include <sys/types.h>

#ifndef INPUTLIB_H
#define INPUTLIB_H

int  inputgii(const char *prompt, int *input);
int  inputgsi(const char *prompt, char **input);
int  inputgsin(const char *prompt, char **input, size_t max_length);

#endif // INPUTLIB_H