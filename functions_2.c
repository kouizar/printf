#include "main.h"

/*************************************************************************/
/************************* PRINT UNSIGNED NUMBER *************************/
/*************************************************************************/

/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	VOID(width);

	num = convert_size_unsign(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}

/******************************************************************/
/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/******************************************************************/

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: A va_list of arguments
 * @buffer: The buffer array used for printing
 * @flags: Active flags for calculation
 * @width: The width specification
 * @precision: The precision specification
 * @size: The size specifier
 * Return:   The number of characters printed
 */

int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}


/***********************************************************************/
/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/***********************************************************************/

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**************************************************************/
/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**************************************************************/

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */

int print_hexa(va_list args, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	VOID(width);

	num = convert_size_unsign(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}
