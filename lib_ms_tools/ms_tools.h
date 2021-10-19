/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:27:42 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 15:55:24 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOOLS_H
# define MS_TOOLS_H

# include "../libft/libft.h"

// tobi






// alice
char	*mst_word_replace(char *str, int start, char *del, char *repl);
int		mst_isequal_str(char *s1, char *s2);
char	*mst_get_next_word(char *str);
void	mst_free_char2(char **m);




#endif