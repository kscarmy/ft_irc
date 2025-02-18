/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:40:50 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/08/14 18:02:57 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	Server server(std::atoi(av[1]), av[2]);
    server.run();
	std::cout << "Stopping server" << std::endl;
	return (0);
}