#include "main.h"

/**************************************************************/
/************************* PRINT CHAR *************************/
/**************************************************************/

/**
 * print_char - Prints a single character.
 * @args: List of arguments containing the character to print.
 * @buffer: Buffer array to handle printing.
 * @flags:  Calculates active flags (if any).
 * @width: The Width specifier (if any).
 * @precision: Precision specification (if any).
 * @size: Size specifier (if any).
 * Return: Number of characters printed.
 */

int print_char(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/******************************************************************/
/************************* PRINT A STRING *************************/
/******************************************************************/

/**
 * print_string - Prints a string to standard output.
 * @args: List of arguments.
 * @buffer: Buffer array used to handle the print.
 * @flags: Flags used to calculate active flags.
 * @width: Width specifier for formatting.
 * @precision: Precision specification for formatting.
 * @size: Size specifier for formatting.
 * Return: The number of characters printed.
 */

int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	VOID(buffer);
	VOID(flags);
	VOID(width);
	VOID(precision);
	VOID(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**********************************************************************/
/************************* PRINT PERCENT SIGN *************************/
/**********************************************************************/

/**
 * print_percent - Prints a percent sign to standard output.
 * @args: List of arguments (unused).
 * @buffer: Buffer array used to handle the print.
 * @flags: Flags used to calculate active flags (unused).
 * @width: Width specifier (unused).
 * @precision: Precision specification (unused).
 * @size: Size specifier (unused).
 * Return: The number of characters printed (always 1 for '%').
 */

int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	VOID(args);
	VOID(buffer);
	VOID(flags);
	VOID(width);
	VOID(precision);
	VOID(size);
	return (write(1, "%%", 1));
}

/**************************************************************/
/************************* PRINT INT **************************/
/**************************************************************/

/**
 * print_int - Prints an integer to standard output.
 * @args: List of arguments containing the integer to print.
 * @buffer: Buffer array used to handle the print.
 * @flags: Flags used to calculate active flags for formatting.
 * @width: Width specifier for formatting.
 * @precision: Precision specification for formatting.
 * @size: Size specifier for formatting.
 * Return: The number of characters printed.
 */
int print_int(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/****************************************************************/
/************************* PRINT BINARY *************************/
/****************************************************************/

/**
 * print_binary - Prints an unsigned binary representation of a number.
 * @args: List of arguments containing the unsigned integer to print.
 * @buffer: Buffer array used to handle the print.
 * @flags: Flags used to calculate active flags (unused).
 * @width: Width specifier (unused).
 * @precision: Precision specification (unused).
 * @size: Size specifier (unused).
 * Return: The number of characters printed.
 */
int print_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int number, divisor, i, sum;
	unsigned int binary_digits[32];
	int count;

	VOID(buffer);
	VOID(flags);
	VOID(width);
	VOID(precision);
	VOID(size);

	number = va_arg(args, unsigned int);
	divisor = 2147483648; /* (2 ^ 31) */
	binary_digits[0] = number / divisor;

	for (i = 1; i < 32; i++)
	{
		divisor /= 2;
		binary_digits[i] = (number / divisor) % 2;
	}

	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += binary_digits[i];

		if (sum || i == 31)
		{
			char digit_char = '0' + binary_digits[i];

			write(1, &digit_char, 1);
			count++;
		}
	}
	return (count);
}
