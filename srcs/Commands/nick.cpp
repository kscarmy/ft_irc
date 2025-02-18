/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 15:08:53 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	nickHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);
	
	if (args.size() - 1 >= 1){
		for (unsigned int i=0; i < args[1].length(); i++){
			if (ALLOWED_NICK_CHARS.find(args[1][i]) == std::string::npos){
				sendMessage(clientFd, ERR_ERRONEUSNICKNAME(args[1]));
				return ;
			}
		}
		for (int i=0; i < MAX_USERS; i++){
			if (server.getClients()[i].getNickName() == args[1]){
				sendMessage(clientFd, ERR_NICKNAMEINUSE(client.getNickName(), args[1]));
				return ;
			}
		}
		client.setNickName(args[1]);
		sendMessage(clientFd, RPL_NICK(client.getNickName(), client.getUserName(), args[1]));
		if (isUserLogged(clientFd, server))
			sendMessage(clientFd, RPL_WELCOME(client.getNickName()));
		client.setNICK(true);
	}
	else
		sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "NICK"));
}