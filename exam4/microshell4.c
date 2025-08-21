#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_err(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void ft_err_2(char *str)
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

int ft_cd(char **argv, int i)
{
	if (i != 2)
	{
		ft_err_2("error: cd: bad arguments\n");
	}	
	else if(chdir(argv[1]) == -1)
	{
		ft_err_2("error: cd: cannot change directory to ");
		ft_err_2(argv[1]);
		ft_err_2("\n");
	}
	return (0);
}

int ft_exec(char **argv, int i, char **env)
{
	int fd[2];
	int id1 = -1;
	int pip = -1;
	int status = 0;

	if (argv[i])
		pip = strcmp(argv[i], "|");

	if (pipe(fd) == -1)
		ft_err("error: fatal\n");

	id1 = fork();
	if (id1 < 0)
		ft_err("error: fatal\n");
	if (id1 == 0)
	{
		if (pip == 0)
		{
			if (dup2(fd[1], 1) == -1)
				ft_err("error: fatal\n");
		}
		if (close(fd[1]) == -1)
			ft_err("error: fatal\n");
		if (close(fd[0]) == -1)
			ft_err("error: fatal\n");

		argv[i] = 0;

		if (execve(argv[0], argv, env) == -1)
		{
			ft_err_2("error: cannot execute ");
			ft_err_2(argv[0]);
			ft_err_2("\n");
		}
		exit (0);
	}
	if (dup2(fd[0], 0) == -1)
		ft_err("error: fatal\n");
	if (close(fd[1]) == -1)
		ft_err("error: fatal\n");
	if (close(fd[0]) == -1)
		ft_err("error: fatal\n");
	if (waitpid(id1, &status, 0) == -1)
		ft_err("error: fatal\n");
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

		i = 0;

		while (argv[i] && strcmp(argv[i], ";") == 0)
		{
			argv = argv + 1;
			// ft_print(argv);
		}
		while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		{
			i++;
		}

		// ft_print(argv);
		if (argv[0])
		{
			if (strcmp(argv[0], "cd") == 0)
				ft_cd(argv, i);
			else
				ft_exec(argv, i , env);
		}
	}
	return (0);
}

//test
// ./a.out ";" ";" ";" ";" ";" ";" ";"
// ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
// ./a.out /bin/echo WOOT "; bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
// ./a.out /bin/echo WOOT "; bin/echo NOPE;" "; ;" ";" /bin/echo YEAH "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e  "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e "|" /bin/cat -e