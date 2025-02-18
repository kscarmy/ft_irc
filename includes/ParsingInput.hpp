/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingInput.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:25:46 by guderram          #+#    #+#             */
/*   Updated: 2023/10/13 15:53:13 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FUNCTIONS_HPP
# define PARSE_FUNCTIONS_HPP

# include "ft_irc.hpp"

void	passHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	nickHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	userHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	partHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	joinHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	kickHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	modeHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	namesHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	quitHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	topicHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	inviteHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	privmsgHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	operHandler(	std::vector<std::string> args, int clientFd, Server &server);
void 	botHandler(		std::vector<std::string> args, int clientFd, Server &server);

class ParseFunctions {
public:
    static bool parse(	const std::string& input, int clientFd, Server &server);
};

#endif // PARSE_FUNCTIONS_HPP
