/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:46:42 by guderram          #+#    #+#             */
/*   Updated: 2023/10/20 13:36:38 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

static ssize_t sendMsgNoFormat(int fd, const std::string& message)
{
	if (DEBUG)
		std::cout << "sendMsgNoFormat to : " << fd << " <" << message << std::endl;
	return send(fd, message.c_str(), message.size(), 0);
}

void	penduStatus(int clientFd, int status)
{
	if (status == 0){
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 1){
		sendMsgNoFormat(clientFd, "+             +\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 2){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}	
	else if (status == 3){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|      |      |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}	
	else if (status == 4){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 5){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 6){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|      |      |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 7){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|     /|      |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 8){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|     /|\\     |\n");
		sendMsgNoFormat(clientFd, "|             |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 9){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|     /|\\     |\n");
		sendMsgNoFormat(clientFd, "|     /       |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
	else if (status == 10){
		sendMsgNoFormat(clientFd, "+------+------+\n");
		sendMsgNoFormat(clientFd, "|/     |     \\|\n");
		sendMsgNoFormat(clientFd, "|      O      |\n");
		sendMsgNoFormat(clientFd, "|     /|\\     |\n");
		sendMsgNoFormat(clientFd, "|     / \\     |\n");
		sendMsgNoFormat(clientFd, "|\\           /|\n");
		sendMsgNoFormat(clientFd, "===============\n");
	}
}

void	botStatus(int clientFd, Server &server){
	char *string = new char[server.getBotString().size() + 1];
	strcpy(string, server.getBotString().c_str());
	char *found = new char[server.getBotFound().size() + 1];
	strcpy(found, server.getBotFound().c_str());
	if (DEBUG)
	{
		std::cout << "botStatus : " << string << std::endl;
		std::cout << "botStatus : " << found << std::endl;
	}
	sendMsgNoFormat(clientFd, "~--~ Le Pendu ~--~\n");
	sendMsgNoFormat(clientFd, "Letters found : ");
	for(int i=0; i < (int)server.getBotFound().size(); i++){
		send(clientFd, &found[i], 1, 0);
		sendMsgNoFormat(clientFd, " ");
	}
	sendMsgNoFormat(clientFd, "\n");
	sendMsgNoFormat(clientFd, "Word status : ");
	for(int i=0; i < (int)server.getBotString().size(); i++){
		if (server.getBotFound().find(string[i]) != std::string::npos){
			send(clientFd, &string[i], 1, 0);
			// sendMsgNoFormat(clientFd, " ");
		}
		else if (string[i] != ' ')
			sendMsgNoFormat(clientFd, "_");
		else
			sendMsgNoFormat(clientFd, " ");
	}
	sendMsgNoFormat(clientFd, "\n");
	penduStatus(clientFd, server.getBotStatus());
	delete [] string;
	delete [] found;
	if (server.getBotStatus() >= 10){
		sendMsgNoFormat(clientFd, "You loose !\n");
		server.setBotStatus(0);
		server.setBotString("jeannot le lapin");
		server.setBotFound("");
	}
	sendMsgNoFormat(clientFd, "~--~  ~--~  ~--~\n\n\n");
}

void	botAddLetter(std::string letter, Server &server, int clientFd){
	if (server.getBotFound().find(letter) != std::string::npos){
		sendMsgNoFormat(clientFd, "Letter already found\n");
		return ;
	}
	if (server.getBotString().find(letter) == std::string::npos){
		server.setBotFound(server.getBotFound() + letter);
		sendMsgNoFormat(clientFd, "Letter not found\n");
		server.setBotStatus(server.getBotStatus() + 1);
		botStatus(clientFd, server);
		return ;
	}
	server.setBotFound(server.getBotFound() + letter);
	botStatus(clientFd, server);
}

void	tryWord(std::string word, Server &server, int clientFd){
	if (server.getBotString() == word){
		sendMsgNoFormat(clientFd, "You win !\n");
		server.setBotStatus(0);
		server.setBotString("jeannot le lapin");
		server.setBotFound("");
		return ;
	}
	else{
		sendMsgNoFormat(clientFd, "Wrong word !\n");
		server.setBotStatus(server.getBotStatus() + 1);
	}
	botStatus(clientFd, server);
}





void 	botHandler(std::vector<std::string> args, int clientFd, Server &server)
{
	std::string message;
	// std::cout << "BOT command received with arguments: " << args[1] << std::endl;
	if (DEBUG)
	{
		std::cout << "BOT : " << server.getBotString() << std::endl;
		std::cout << "BOT : " << server.getBotFound() << std::endl;
	}
	botStatus(clientFd, server);
	if (args.size() >= 3){
		if (args[1] == "CHANGE"){
			if (!server.getClientByFd(clientFd).getOPER()){
				sendMsgNoFormat(clientFd, "You are not OP\n");
				return ;
			}
			std::string string = args[2];
			for (int i=3; i < (int)args.size(); i++){
				string += " " + args[i];
			}
			server.setBotString(string);
			server.setBotFound("");
			server.setBotStatus(0);
			sendMsgNoFormat(clientFd, "Word changed\n");
			botStatus(clientFd, server);
			return ;
		}
	}
	if (args.size() == 2 && args[1].size() == 1){
		botAddLetter(args[1], server, clientFd);
		return ;
	}
	if (args.size() > 1)
		message = args[1];
	for (int i=2; i < (int)args.size(); i++){
		message += " " + args[i];
	}
	if (args.size() >= 2 && args[1].size() > 1){
		tryWord(message, server, clientFd);
		return ;
	}
	if (args.size() > 1)
		if (DEBUG)
			std::cout << "BOT command received with arguments: " << message << std::endl;
	sendMsgNoFormat(clientFd, "Essaie de deviner le mot en moins de 10 coups !\n");
	sendMsgNoFormat(clientFd, "Pour proposer une lettre : BOT <lettre>\n");
	sendMsgNoFormat(clientFd, "Pour proposer un mot : BOT <mot>\n");
	sendMsgNoFormat(clientFd, "Pour changer le mot (op only) : BOT CHANGE <mot>\n");
	return ;
}