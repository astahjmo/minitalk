/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:10:42 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/22 16:24:58 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fmt_to_char(char s)
{
	ft_putchar_fd(s, STDOUT_FILENO);
	ft_putchar_fd('\0', STDOUT_FILENO);
	return (1);
}
