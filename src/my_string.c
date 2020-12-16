#include <stdio.h>
#include "my_string.h"

unsigned int string_length(const char *str)
{
	int length = 0;
	while (*str++)
		++length;
	return length;
}

void string_reverse(char *str)
{
	unsigned int length = string_length(str);
	char tmp;
	unsigned int i, j;
	for (i = 0, j = length -1; i < j; ++i, --j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}

void string_cat(char *to, const char *from)
{
	int length = string_length(to);
	char *pos = to + length;
	
	while (*from)
		*pos++ = *from++;
	*pos = '\0';
}

int string_has_substring(char *str, char *sub)
{
	char *left, *right;
	for(; *str != '\0'; ++str)
	{
		if (*str == *sub)
		{
			for (left = str, right = sub;
				 *left && *right && *left++ == *right++;);
			if (*right == '\0')
				return 0;
		}
	}
	return 1;
}

unsigned int int_to_str(char *buffer, unsigned int size, int value)
{
	int digit;
	int i = 0;

	if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
	}
	else
	{
		while (value > 0 && i < size - 1)
		{
			digit = value % 10;
			value /= 10;

			buffer[i++] = '0' + digit;
		}
		buffer[i] = '\0';
		string_reverse(buffer);
	}
	return i;
}

