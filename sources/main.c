/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:49:24 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 14:45:37 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.start_time = get_time();
	if (parser(ac, av) != 0)
		return (1);
	if (fill_data(av, &data) != 0)
		return (problem_clean(&data), 1);
	end_clean(&data);
	return (0);
}
