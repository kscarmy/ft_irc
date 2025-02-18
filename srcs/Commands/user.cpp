/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/18 13:51:40 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	userHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);

	if (isUserLogged(clientFd, server))
	{
		sendMessage(clientFd, ERR_ALREADYREGISTRED(client.getNickName()));
		return ;
	}
	if (args.size() - 1 >= 4){
		client.setUserName(args[1]);
		client.setMode(0);
		if (args[4][0] == ':')
			args[4] = args[4].substr(1); // On enlève le premier caractère s'il s'agit d'un ':' pour le realname
		client.setRealName(args[4]);
		for (int i=0; i < (int)args.size() - 5; i++){
			client.setRealName(client.getRealName() + " " + args[5 + i]);
		}
		client.setUSER(true);
		
		return ;
	}
	sendMessage(clientFd, ERR_NEEDMOREPARAMS(client.getNickName(), "USER"));
}
