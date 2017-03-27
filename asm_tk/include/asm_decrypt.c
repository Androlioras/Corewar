#include "op.h"
#include "user.h"

void	op(int size, int *label)
{
	int flag;

	flag = 0;
	if (label == "live")
		flag = flag | 1;
	if (label == "ld")
		flag = flag | 2;
	if (label == "st")
		flag = flag | 4;
	if (label == "add")
		flag = flag | 8;
	if (label == "sub")
		flag = flag | 16;
	if (label == "and")
		flag = flag | 32;
	if (label == "or")
		flag = flag | 64;
	if (label == "xor")
		flag = flag | 128;
}

int main(int argc, char const *argv[])
{
	while (str[i])
	{
		if (ft_strstr(label, str))
			op(label);
		i++;
	}
	return (0);
}