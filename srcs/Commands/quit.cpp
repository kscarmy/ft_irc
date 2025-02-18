/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 14:34:55 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	quitHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);

	if (args.size() >= 2)
	{
		std::string message = args[1];
		if (message[0] == ':')
			message = message.substr(1);
		for (int i=2; i < (int)args.size(); i++){
			message += " " + args[i];
		}
		server.sendToAllUserChannels(client.getNickName(), RPL_QUIT(client.getNickName(), client.getUserName(), message));
	}
	else
		server.sendToAllUserChannels(client.getNickName(), RPL_QUIT(client.getNickName(), client.getUserName(), "leaving"));
	
	if (DEBUG)
		std::cout << CLIENT_TAG(client.getNickName(), client.getUserName(), "")  << "Disconnected" << std::endl;		//User Disconnected
	close (clientFd);
	server.removeClientByFd(clientFd);
}
