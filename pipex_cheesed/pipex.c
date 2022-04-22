#include "pipex.h"

static int	ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		++len;
	return (len);
}

int main(int argc, char **argv)
{
	if (argc == 5)
	{
		char *arr[3];
		arr[0] = "touch";
		arr[1] = "script";
		arr[2] = NULL;
		int id1 = fork();
		if (id1 == 0)
			execve("/usr/bin/touch", arr, NULL);
		else
		{
			wait(NULL);
			int fd = open("script", O_RDWR);
			write(fd, "< ", 2);
			write(fd, argv[1], ft_strlen(argv[1]));
			write(fd, " ", 1);
			write(fd, argv[2], ft_strlen(argv[2]));
			write(fd," | ", 3);
			write(fd, argv[3], ft_strlen(argv[3]));
			write(fd, " > ", 3);
			write(fd, argv[4], ft_strlen(argv[4]));
			int id2 = fork();
			if (id2 == 0)
			{
				arr[0] = "bash";
				execve("/bin/bash", arr, NULL);
			}
			else
			{
				wait(NULL);
				arr[0] = "rm";
				execve("/bin/rm", arr, NULL);
			}
		}
	}
}