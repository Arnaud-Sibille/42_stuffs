#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int	ft_strlen(char *s)
{
	int i = 0;
	for (; s[i]; i++)
		;
	return (i);
}

void	ft_putstr(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

int	ft_error()
{
	ft_putstr(2, "Error: Operation file corrupted\n");
	return (1);
}

void	ft_print_arr(char *drawing, int width, int height)
{
	for (int i = 0; i < width * height; ++i)
	{
		write(1, drawing + i, 1);
		if ((i + 1) % width == 0)
			write(1, "\n", 1);
	}
}

int	ft_algo(FILE *fp, char *drawing, int width, int height)
{
	char	style;
	float	x;
	float	y;
	float	rad;
	char	ch;
	int		ret;

	while ((ret = fscanf(fp, "%c %f %f %f %c \n", &style, &x, &y, &rad, &ch)) == 5)
	{
		if (rad <= 0)
			return (0);
		if (style == 'c')
		{
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					float	dist = sqrtf(powf(x - (float) i, 2.000) + powf(y - (float) j, 2.000));
					if ((dist <= rad) && (dist > rad - 1.000))
						drawing[i + j * width] = ch;
				}
			}
		}
		else if (style == 'C')
		{
			for (int abs = 0; abs < width; ++abs)
			{
				for (int ord = 0; ord < height; ++ord)
				{
					float dist = sqrtf(powf(x - (float) abs, 2.000) + powf(y - (float) ord, 2.000));
					if (dist <= rad)
						drawing[abs + ord * width] = ch;
				}
			}
		}
		else
			return (0);
	}
	if (ret != -1)
		return (0);
	ft_print_arr(drawing, width, height);
	return (1);
}

int main(int argc, char **argv)
{
	int	width;
	int	height;
	char	backchar;

	if (argc == 2)
	{
		FILE *fp = fopen(argv[1], "r");
		if (!fp)
			return (ft_error());
		if (fscanf(fp, "%d %d %c\n", &width, &height, &backchar) != 3)
			return (ft_error());
		if (height > 300 || height <= 0 || width > 300 || width <= 0)
			return (ft_error());
		char *drawing = malloc(sizeof(char) * height * width);
		memset(drawing, backchar,  height * width);
		if (!ft_algo(fp, drawing, width, height))
			return (ft_error());
		fclose(fp);
	}
	else
	{
		ft_putstr(2, "Error: argument\n");
		return (1);
	}
	return (0);
}
