/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:00:27 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/12 21:10:09 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// UTILS
int		name_len(char *arg);
bool	check_char(char c, char *argv);

// BUILTINS
int		ft_pwd(t_env *env_list);
int		ft_echo(char **argv);
int		ft_env(char **argv, t_env **env_list);
int		ft_cd(char **argv, t_env **env_list);
int		ft_exit(char **argv, int err_num, t_env **env);
int		ft_unset(char **argv, t_env **env_list);
int		ft_export(char **argv, t_env **env_list);

#endif
