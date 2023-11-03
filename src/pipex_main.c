/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:16:21 by adiaz-uf          #+#    #+#             */
/*   Updated: 2023/09/27 18:45:46 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	char	*part_of_path;
	int		i;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK))
			ft_error("Permission denied", 13);
	}
	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	all_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		part_of_path = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(part_of_path, cmd);
		free(part_of_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	child1(int *fds, char **argv, char **envp)
{
	int		status;
	int		i;
	char	*path;
	char	**cmd;
	int		f;

	f = open(argv[1], O_RDONLY);
	if (f == -1)
		ft_error("No se ha podido abrir el fichero", 2);
	dup2(f, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	i = 0;
	cmd = ft_split(argv[2], ' ');
	path = get_path(cmd[0], envp);
	if (execve(path, cmd, envp))
	{
		ft_free(cmd);
		free(path);
		ft_error("Command not found", 22);
	}
}

void	child2(int *fds, char **argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;
	int		f;

	f = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f == -1)
		ft_error("No se ha podido abrir el fichero", 2);
	dup2(f, STDOUT_FILENO);
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	close(fds[0]);
	i = 0;
	cmd = ft_split(argv[3], ' ');
	path = get_path(cmd[0], envp);
	if (execve(path, cmd, envp))
	{
		ft_free(cmd);
		free(path);
		ft_error("Command not found", 22);
	}
}

void	pipex(char **ag, char **envp)
{
	int		fds[2];
	pid_t	c1;
	pid_t	c2;
	int		i;
	int		j;

	if (pipe(fds) == -1)
		ft_error("Pipe error", 32);
	c1 = fork();
	if (c1 < 0)
		ft_error("Error", 3);
	if (c1 == 0)
		child1(fds, ag, envp);
	c2 = fork();
	if (c2 < 0)
		ft_error("Error", 3);
	if (c2 == 0)
		child2(fds, ag, envp);
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	j;

	if (argc != 5)
		ft_error("Numero de argumentos incorrecto", 5);
	if (lookfor_command(envp, argv[2]) != 0)
		ft_error("Command not found", 22);
	if (lookfor_command(envp, argv[3]) != 0)
		ft_error("Command not found", 22);
	pipex(argv, envp);
	return (0);
}
