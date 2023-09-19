#include "main.h"

void print_buffer(char buffer[], int *buffe_index);

/***************************************************/
/***************_printf Function********************/
/***************************************************/

/**
 * _printf - Custom printf function
 * @format: Format
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buffe_index = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffe_index++] = format[i];
			if (buffe_index == BUFF_SIZE)
				print_buffer(buffer, &buffe_index);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buffe_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buffe_index);

	va_end(args);

	return (printed_chars);
}

/***************************************************/
/*************print_buffer Function*****************/
/***************************************************/

/**
 * print_buffer - Prints the contents of the buffer if it's not empty.
 * @buffer: A character array where data is stored for printing
 * @buffe_index: Pointer to the index at which to add the next character,
 *	represents the length of the buffer
 */
void print_buffer(char buffer[], int *buffe_index)
{
	if (*buffe_index > 0)
		write(1, &buffer[0], *buffe_index);

	*buffe_index = 0;
}
