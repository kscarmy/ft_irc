/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:52:30 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 14:24:16 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	partHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);

	if (args.size() < 2)
		return (void)sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "PART"));

	if (!server.channelExists(args[1]))
		return (void)sendMessage(clientFd, ERR_NOSUCHCHANNEL(client.getNickName(), args[1]));

	if (!server.clientInChannel(client.getNickName(), args[1]))
		return (void)sendMessage(clientFd, ERR_NOTONCHANNEL(client.getNickName(), args[1]));

	if (args.size() < 3)
		server.sendToAllUsersOf(args[1], RPL_PART(client.getNickName(), client.getUserName(), args[1], "Leaving"));
	else
	{
		std::string message = args[2];
		for (int i = 3; i < (int)args.size(); i++)
			message += " " + args[i];
		server.sendToAllUsersOf(args[1], RPL_PART(client.getNickName(), client.getUserName(), args[1], message));
	}
	server.removeClientFromChannel(client.getNickName(), args[1], server);
	if (server.getChannelByName(args[1]).getClientFd().size() == 0)
		server.removeChannel(args[1]);

}