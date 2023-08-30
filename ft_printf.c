#include <stdarg.h>
#include <unistd.h>

int	put_str(const char *str)
{
	int	count;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = 0;
	while (*str)
		count += write(1, str++, 1);
	return (count);
}

void	put_nbr(int num, int base, int *count)
{
	long	val;
	const char	digit[] = "0123456789";

	if (num < 0)
	{
		// to prevent error from direct type casting of negative value
		val = num;
		val = -val;
		*count += write(1, "-", 1);
	}
	else
		val = num;
	if (val >= base)
		put_nbr(val / base, base, count);
	*count += write(1, &digit[val % base], 1);
}

void	put_hex(unsigned int num, unsigned int base, int *count)
{
	unsigned int	val;
	const char		digit[] = "0123456789abcdef";
	val = num;
	if (val >= base)
		put_hex(val / base, base, count);
	*count += write(1, &digit[val % base], 1);
}

int	ft_printf(const char *fmt, ...)
{
	int	count;
	va_list	args;

	count = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if ((*fmt == '%') && ((*(fmt + 1) == 'd') || (*(fmt + 1) == 's') || (*(fmt + 1) == 'x') || (*(fmt + 1) == '%')))
		{
			fmt++;
			if (*fmt == 's')
			{
				count += put_str(va_arg(args, char *));
				fmt++;
			}
			else if (*fmt == 'd')
			{
				put_nbr(va_arg(args, int), 10, &count);
				fmt++;
			}
			else if (*fmt == 'x')
			{
				put_hex(va_arg(args, unsigned int), 16, &count);
				fmt++;
			}
			else if (*fmt == '%')
			{
				write(1, fmt, 1);
				fmt++;
				continue ;
			}
		}
		else
			count += write(1, fmt++, 1);
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>
#include <limits.h>
int	main(void)
{
	int	count;

	count = printf("%s : %s\n", "abc", "");
	count = ft_printf("%s : %s\n", "abc", "");
	printf("count = %d\n", count);
	count =    printf("%d : %d\n", 42, 42);
	count = ft_printf("%d : %d\n", 42, 42);
	printf("count = %d\n", count);
	count = printf   ("%x : %x : %x \n", INT_MIN, INT_MAX, UINT_MAX);
	count = ft_printf("%x : %x : %x \n", INT_MIN, INT_MAX, UINT_MAX);
	printf("count = %d\n", count);
	printf   ("%%%s%%%d%%%x %%%s%%%d%%%x %%%s%%%d%%%x %%\n", "42", 42, 42 ,"-42", -42, -42 ,"0", 0, 0);
	ft_printf("%%%s%%%d%%%x %%%s%%%d%%%x %%%s%%%d%%%x %%\n", "42", 42, 42 ,"-42", -42, -42 ,"0", 0, 0);
	return (0);
}
*/
