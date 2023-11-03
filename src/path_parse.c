/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:43 by adiaz-uf          #+#    #+#             */
/*   Updated: 2023/09/27 18:39:17 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*command_size(char *cmd)
{
	size_t	i;
	char	*raw_cmd;

	i = 0;
	while (cmd[i] != ' ')
		i++;
	raw_cmd = malloc((i + 1) * sizeof(char));
	ft_strlcat(raw_cmd, cmd, i + 1);
	return (raw_cmd);
}

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (i);
		}
	i++;
	}
	return (-1);
}

int	search_command(char **arr, char *cmd)
{
	int		exist;
	int		j;
	char	*commd;
	char	*commd2;
	char	*raw_cmd;

	j = 0;
	exist = -1;
	raw_cmd = command_size(cmd);
	while (arr[j] && exist != 0)
	{
		commd = ft_strjoin(arr[j], "/");
		commd2 = ft_strjoin(commd, raw_cmd);
		exist = access(commd2, F_OK);
		free(commd);
		free(commd2);
		if (exist == 0)
		{
			free(raw_cmd);
			return (0);
		}
		j++;
	}
	free(raw_cmd);
	return (exist);
}

int	lookfor_command(char **env, char *cmd)
{
	int		i;
	int		j;
	int		exist;
	char	**arr;

	j = 0;
	i = find_path(env);
	arr = ft_split(&env[i][5], ':');
	if (i == -1)
	{
		ft_free(arr);
		ft_error("No se ha localizado el PATH", 3);
	}
	exist = search_command(arr, cmd);
	if (ft_strlen(cmd) == 0)
		exist = 1;
	ft_free(arr);
	if (exist == 0)
		return (0);
	else
		ft_error("Command not found", 22);
	return (1);
}
