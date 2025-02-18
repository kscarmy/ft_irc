/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/13 13:47:08 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	kickHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);
	if (args.size() >= 3){
		if (!server.channelExists(args[1])){
			sendMessage(clientFd, ERR_NOSUCHCHANNEL(client.getNickName(), args[1]));
			return ;
		}
		if (!server.clientInChannel(client.getNickName(), args[1])){
			sendMessage(clientFd, ERR_NOTONCHANNEL(client.getNickName(), args[1]));
			return ;
		}
		if (!server.clientInChannel(args[2], args[1])){
			sendMessage(clientFd, ERR_USERNOTINCHANNEL(client.getNickName(), args[1], args[2]));
			return ;
		}
		if (!server.isUserOperIn(client.getNickName(), args[1]) && !client.getOPER()){
			sendMessage(clientFd, ERR_CHANOPRIVSNEEDED(args[1], client.getNickName()));
			return ;
		}
		server.sendToAllUsersOf(args[1], RPL_KICK(client.getNickName(), client.getUserName(), args[1], args[2], ""));
		server.removeClientFromChannel(args[2], args[1], server);
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "KICK"));
}
