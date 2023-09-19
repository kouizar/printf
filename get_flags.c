#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string containing potential flags
 * @i: Pointer to the current position within the format string.
 * Return: A bitmask representing the active flags:
 */
int get_flags(const char *format, int *i)
{
    /* These are formatting flags */
    /* Flag positions:   1  2  4   8    16 */
    /* Corresponding flags: -  +  0   #   '  '  */


	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
