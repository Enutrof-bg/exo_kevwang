#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void ft_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void ft_print(char **argv){


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
	int id1 = 0;
	int pip;
	if (argv[i])
		pip = strcmp(argv[i], "|");
	int fd[2];
	(void)env;
	(void)id1;
	(void)pip;
	(void)fd;
	int status;

	pipe(fd);

	
	id1 = fork();

	if (id1 == 0)
	{

		if (pip == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}	
		argv[i] = 0;
		execve(argv[0], argv, env);
		exit(0);
	}

	if (pip == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
	waitpid(id1, &status, 0);
	return (0);
}

int ft_cd(char **argv, int i)
{
	if (i != 2)
		ft_err("arg error\n");
	else if (chdir(argv[i]) == -1)
		ft_err("path error\n");
	return (0);
}

int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)env;
	int i = 0;
	while (argv[i] && argv[++i])
	{
		argv = argv + i;
		while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		{
			i++;
		}
		// ft_print(argv);
		if (strcmp(argv[0], "cd") == 0)
		{
			ft_cd(argv, i);
		}
		else
			ft_exec(argv, i, env);
		// ft_exec(argv, i, env);
	}
}