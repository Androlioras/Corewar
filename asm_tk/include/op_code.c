#include "./include/user.h"
#include "./include/op.h"

unsigned char	op_code(char *str, t_asm *asm)
{
	unsigned char instruct;

	if (ft_strstr(str, "live") != NULL)
	{
		str[0]instruct = 0x01;
		return (instruct);
	}
	if (ft_strstr(str, "ld") != NULL)
	{
		instruct = 0x02;
		return (instruct);
	}
	if (ft_strstr(str, "st") != NULL)
	{
		instruct = 0x03;
		return (instruct);
	}
	if (ft_strstr(str, "add") != NULL)
	{
		instruct = 0x04;
		return (instruct);
	}
	if (ft_strstr(str, "sub") != NULL)
	{
		instruct = 0x05;
		return (instruct);
	}
	if (ft_strstr(str, "and") != NULL)
	{
		instruct = 0x06;
		return (instruct);
	}
	if (ft_strstr(str, "or") != NULL)
	{
		instruct = 0x07;
		return (instruct);
	}
	if (ft_strstr(str, "xor") != NULL)
	{
		instruct = 0x08;
		return (instruct);
	}
	if (ft_strstr(str, "zjmp") != NULL)
	{
		instruct = 0x09;
		return (instruct);
	}
	if (ft_strstr(str, "ldi") != NULL)
	{
		instruct = 0x0a;
		return (instruct);
	}
	if (ft_strstr(str, "sti") != NULL)
	{
		instruct = 0x0b;
		ft_calc(str, to_print)
		return (instruct);
	}
	if (ft_strstr(str, "fork") != NULL)
	{
		instruct = 0x0c;
		return (instruct);
	}
	if (ft_strstr(str, "lld") != NULL)
	{
		instruct = 0x0d;
		return (instruct);
	}
	if (ft_strstr(str, "lldi") != NULL)
	{
		instruct = 0x0e;
		return (instruct);
	}
	if (ft_strstr(str, "lfork") != NULL)
	{
		instruct = 0x0f;
		return (instruct);
	}
	if (ft_strstr(str, "aff") != NULL)
	{
		instruct = 0x10;
		return (instruct);
	}
	return (NULL);
}
