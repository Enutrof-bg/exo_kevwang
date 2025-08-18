#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int ft_exec(char **argv, int i ,  char **env)
{
	int pip = -1;
	int status = 0;
	if (argv[i])
	{
		// pip = strcmp(argv[i], ";");
		// if (pip != 0)
		pip = strcmp(argv[i], "|");
		// if (pip)
		
	}
	// if (argv[i] && strcmp(argv[i], ";") == 0)
	// {
		// argv[i] = 0;
	// }

	int fd[2];
	int id1;

	if (pipe(fd) == -1)
		return ft_err("error: fatal\n");
	// printf("pip:%d\n", pip);

	id1 = fork();
	if (id1 < 0)
	{
		return ft_err("error: fatal\n");
	}
	if (id1 == 0)
	{
		if (pip == 0)
		{
			if (dup2(fd[1], 1) == -1)
				return ft_err("error: fatal\n");
			// close(fd[1]);
			// close(fd[0]);
		}
		if (close(fd[1]) == -1)
			return ft_err("error: fatal\n");
		if (close(fd[0]) == -1)
			return ft_err("error: fatal\n");
		argv[i] = 0;

		if (execve(argv[0], argv, env) == -1)
		{
			ft_err("error: cannot execute ");
			ft_err(argv[0]);
			ft_err("\n");
		}
		exit(0);

	}
	if (pip == 0)
	{
		if (dup2(fd[0], 0) == -1)
			return ft_err("error: fatal\n");
	}
	if (close(fd[1]) == -1)
		return ft_err("error: fatal\n");
	if (close(fd[0]) == -1)
		return ft_err("error: fatal\n");

	if (waitpid(id1, &status, 0) == -1)
		return ft_err("error: fatal\n");
	return (0);
}

int ft_cd(char **argv, int i)
{
	if (i != 2)
	{
		ft_err("error: cd: bad arguments\n");
	}
	else if(chdir(argv[1]) != 0)
	{
		ft_err("error: cd: cannot change directory to ");
		ft_err(argv[1]);
		ft_err("\n");
	}
	return (0);

}

int ft_last(char **argv, int i, char **env, int tmp)
{

	int id1 = -1;
	int status = 0;
	id1 = fork();
	if (id1 == 0)
	{
		argv[i] = 0;

		dup2(tmp, 0);
		execve(argv[0], argv, env);

	exit(0);
	}
	close(tmp);
	waitpid(id1, &status, 0);

	return (1);
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

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;
	int i = 0;
	int tmp = dup(0);
	while (argv[i] && argv[++i])
	{

		argv = argv +i;

		while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		{
			i++;
		}
		ft_print(argv);
		if (strcmp(argv[0], "cd") == 0)
			ft_cd(argv, i);
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
			ft_last(argv, i, env ,tmp);
		else
			ft_exec(argv, i, env);

	}


	return 0;
}