/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_increment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:53:47 by pohl              #+#    #+#             */
/*   Updated: 2020/02/20 10:02:01 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi_increment(const char *str, int *i)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\r' || str[*i] == '\f' || str[*i] == '\v'))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		result *= 10;
		result += str[*i] - 48;
		(*i)++;
	}
	return (result * sign);
}
