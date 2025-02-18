/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingInput.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:25:52 by guderram          #+#    #+#             */
/*   Updated: 2023/10/20 13:29:18 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ParsingInput.hpp"

bool isUserLogged( int clientFd, Server &server) {
	return (server.getClientByFd(clientFd).getNICK() && server.getClientByFd(clientFd).getUSER() && server.getClientByFd(clientFd).getPASS());
}

static bool letsSplit(char c){
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (true);
	return (false);
}


// fonction qui split args si il y a des espaces ou des retours a la ligne et supprime les retours a la ligne
static std::vector<std::string> split(const std::string& input) {
	std::vector<std::string> args;
	std::string arg;
	for (size_t i = 0; i < input.size(); i++) {
		if (letsSplit(input[i])) {
			if (!arg.empty()) {
				args.push_back(arg);
				arg.clear();
			}
		}
		else
			arg += input[i];
	}
	if (!arg.empty())
		args.push_back(arg);
	return (args);
}

// fonction qui verifie si args contient PASS ou NICK ou USER. peut contenir plusieurs fois PASS ou NICK ou USER, et dois donc lancer les fonctions avec les bons arguments. args[0] est forcement PASS ou NICK ou USER
static bool	handlePac(const std::vector<std::string> &args, int clientFd, Server &server) {
	if (DEBUG)
		std::cout << "handlePac" << std::endl;
	std::vector<std::string>::const_iterator it = args.begin();
	std::vector<std::string>::const_iterator ite = args.end();
	for (int i=0; i<(int)args.size(); i++)
		if (DEBUG)
			std::cout << "args[" << i << "] = <" << args[i] << ">" << std::endl;
	while (it != ite) {
		if (*it == "PASS") {
			if (it + 1 == ite)
				return (false);
			std::vector<std::string> pass;
			pass.push_back("PASS");
			pass.push_back(*(it + 1));
			for(int i=0; i<(int)args.size(); i++)
				if (DEBUG)
					std::cout << "args[" << i << "] = <" << args[i] << ">" << std::endl;
			passHandler(pass, clientFd, server);
		}
		else if (*it == "NICK") {
			if (it + 1 == ite)
				return (false);
			std::vector<std::string> nick;
			nick.push_back("NICK");
			nick.push_back(*(it + 1));
			nickHandler(nick, clientFd, server);
		}
		else if (*it == "USER") {
			if (it + 4 >= ite)
				return (false);
			std::vector<std::string> user;
			user.push_back("USER");
			user.push_back(*(it + 1));
			user.push_back(*(it + 2));
			user.push_back(*(it + 3));
			user.push_back(*(it + 4));
			userHandler(user, clientFd, server);
		}
		it++;
	}
	return (true);
}



bool ParseFunctions::parse(const std::string& input, int clientFd, Server &server) {
	if (input.empty())
		return (false);
	std::vector<std::string> args = split(input);
	// if (args[0] == "PASS")													// Password message
    //     passHandler(args, clientFd, server);	
	if (args[0] == "QUIT")												// Quit message // peut quitter avant detre log
        quitHandler(args, clientFd, server);
	// else if (server.getClientByFd(clientFd).getPASS() && args[0] == "NICK")	// Nick message
    //     nickHandler(args, clientFd, server);
	// else if (server.getClientByFd(clientFd).getNICK() && args[0] == "USER")	// User message
    //     userHandler(args,clientFd, server);
	// else 
	
	if (!isUserLogged(clientFd, server)){			
		handlePac(args, clientFd, server);
		if (isUserLogged(clientFd, server))
		{
			sendMessage(clientFd, RPL_WELCOME(server.getClientByFd(clientFd).getNickName()));
		}
		return (true);
	}

	if (args[0] == "PING")													// Ping request by irssi
		sendMessage(clientFd, RPL_PONG(SERVER_NAME));
	else if (args[0] == "JOIN")												// Join message
        joinHandler(args, clientFd, server);
	else if (args[0] == "PART")
		partHandler(args, clientFd, server);
	else if (args[0] == "NICK")
		nickHandler(args, clientFd, server);
	else if (args[0] == "USER")
		userHandler(args, clientFd, server);
	else if (args[0] == "MODE")												// Channel mode message
		modeHandler(args, clientFd, server);
	else if (args[0] == "TOPIC") 											// Topic message
        topicHandler(args,clientFd, server);
	else if (args[0] == "NAMES")											// Names message
        namesHandler(args, clientFd, server);
	else if (args[0] == "INVITE") 											// Invite message
        inviteHandler(args, clientFd, server);
    else if (args[0] == "KICK") 											// Kick message
        kickHandler(args, clientFd, server);
	else if (args[0] == "PRIVMSG") 											// Private message
		privmsgHandler(args, clientFd, server);
	else if (args[0] == "OPER") 											// Oper message
		operHandler(args, clientFd, server);
	else if (args[0] == "BOT") 												// Bot message
		botHandler(args, clientFd, server);
	else
		return (false);
	return (true);
}



