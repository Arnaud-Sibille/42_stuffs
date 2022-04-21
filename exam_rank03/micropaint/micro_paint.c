#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int	ft_error()
{
	write(2, "Error: Operation file corrupted\n", 32);
	return (1);
}

void	ft_print_arr(char *drawing, int width, int height)
{
	for (int i = 0; i< width * height; ++i)
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
	float	rec_wi;
	float	rec_hei;
	char	ch;
	int		ret;

	while ((ret = fscanf(fp, "%c %f %f %f %f %c \n", &style, &x, &y, &rec_wi, &rec_hei, &ch)) == 6)
	{
		if (rec_wi <= 0 || rec_hei <= 0)
			return (1);
		if (style == 'r')
		{
			for (int abs = 0; abs < width; ++abs)
			{
				for (int ord = 0; ord < height; ++ord)
				{
					if ((float) abs >= x && (float) abs <= x + rec_wi && (float) ord >= y && (float) ord <= y + rec_hei)
					{
						if ((float) abs - x < 1 || x + rec_wi - (float) abs < 1 || (float) ord - y < 1 || y + rec_hei - (float) ord < 1)
							drawing[abs + width * ord] = ch;
					}
				}
			}
		}
		else if (style == 'R')
		{
			for (int abs = 0; abs < width; ++abs)
			{
				for (int ord = 0; ord < height; ++ord)
				{
					if ((float) abs >= x && (float) abs <= x + rec_wi && (float) ord >= y && (float) ord <= y + rec_hei)
					   drawing[abs + width * ord] = ch;	
				}
			}
		}
		else
			return (1);
	}
	if (ret != -1)
		return (1);
	ft_print_arr(drawing, width, height);
	return (0);
}

int	main(int argc, char **argv)
{
	int	width;
	int	height;
	char	backchar;

	if (argc == 2)
	{
		FILE *fp = fopen(argv[1], "r");
		if (!fp)
			return (ft_error());
		if (fscanf(fp, "%d %d %c \n", &width, &height, &backchar) != 3)
			return (ft_error());
		if (width <= 0 || width > 300 || height <= 0 || height > 300)
			return (ft_error());
		char *drawing = malloc(sizeof(char) * width * height);
		memset(drawing, backchar, width * height);
		if (ft_algo(fp, drawing, width, height) == 1)
			return (ft_error());
		fclose (fp);
	}
	else
	{
		write(2, "Error: argument\n", 16);
		return (1);
	}
	return (0);
}
