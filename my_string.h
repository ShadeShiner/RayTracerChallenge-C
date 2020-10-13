#ifndef MY_STRING_H
#define MY_STRING_H

unsigned int string_length(const char *str);

void string_reverse(char *str);

void string_cat(char *to, const char *from);

int string_has_substring(char *str, char *sub);

unsigned int int_to_str(char *buffer, unsigned int size, int value);

#endif
