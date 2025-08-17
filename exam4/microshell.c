#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int tmp0;
int tmp1;

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

void ft_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void ft_print(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("'%s'", argv[i]);	
		i++;
	}
	printf("\n");	
}

int ft_exec(char **argv, int i, char **env)
{
	(void)env;
	(void)i;
	int fd[2];
	int id1;
	int pipi = -1;
	int status = 0;

	// ft_print(argv);
	if (argv[i])
	{
		pipi = strcmp(argv[i], "|");
	}
	printf("pipi:%d\n", pipi);

	if (pipi == 0 && pipe(fd) == -1)
	{
		write(2,"error\n", 6);
		return -1;
	}
	ft_print(argv);

	id1 = fork();
	if (id1 == 0)
	{
		if (pipi == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		
		argv[i] = 0;
		ft_print(argv);
		
		execve(argv[0], argv, env);
		exit(1);
	}
	
	if (pipi == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
	
	waitpid(id1, &status, 0);
	return (0);
}

int ft_cd(char **argv, int i, char **env)
{
	(void)env;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;

	int i = 0;
	tmp1 = dup(1);
	tmp0 = dup(0);

	// int tmp1 = dup(1);
	// argv = argv+1;
	while (argv[i] && argv[++i])
	{
		argv = argv + i;
		// ft_print(argv);
		while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
			i++;
		if (strncmp(argv[i], "cd") == 0)
		{
			ft_cd(argv, i, env);
		}
		else
			ft_exec(argv, i, env);
	
	}
	// ft_err("test\n");
}