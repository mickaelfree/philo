/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:17:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/25 01:32:50 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

//fonction a ajouert
void	ft_error(char *msg);
void	ft_free(char **tab);
size_t	ft_strlen(const char *str);
void	execute(char *av, char **env);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*find_path(char *cmd, char **env);
size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
