/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:32:11 by adiaz-uf          #+#    #+#             */
/*   Updated: 2023/09/27 18:32:16 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

void	ft_error(char *msg, int err);

void	ft_free(char **a);

void	ft_execve(char *path, char **cmd, char **envp);

int		find_path(char **env);
int		lookfor_command(char **env, char *command);

#endif
