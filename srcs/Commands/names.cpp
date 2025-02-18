/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 09:03:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/13 15:27:02 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void 	namesHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	Client & client = server.getClientByFd(clientFd);
	
	if (args.size() >= 2){
		if (!server.channelExists(args[1]) || !server.clientInChannel(client.getNickName(), args[1])){	// Check si le client est dans le channel
			sendMessage(clientFd, ERR_NOTONCHANNEL(client.getNickName(), args[1]));
			return ;
		}
		for(int i=0; i < MAX_USERS; i++){
			for (int j=0; j < (int)server.getClients()[i].getClientChannel().size(); j++){
				if (server.getClients()[i].getClientChannel()[j].getChannelName() == args[1]){
					sendMessage(clientFd, server.getClients()[i].getNickName() + "\n");
				}
			} 
		}
		return ;
	}
	else if (args.size() == 1) {
		for (int i=0; i < MAX_USERS; i++){
			if (server.getClients()[i].getIsSet()){
				sendMessage(clientFd, server.getClients()[i].getNickName());
			}
		}
	}
}