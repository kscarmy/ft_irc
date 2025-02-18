/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:51:09 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 17:08:08 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

/********************************************/
/*					Macros					*/
/********************************************/
# define MAX_USERS 25
# define BUFFER_SIZE 1024
# define MAX_INVITS 10
# define MAX_CHANNEL 25
# define OPER_PASSWORD "admin"
# define SERVER_NAME "ft-irc"
# define DEBUG 0
# define ALLOWED_NICK_CHARS std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")


/********************************************/
/*		C++ Standard Library headers		*/
/********************************************/
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <string>
# include <cstring>
# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <poll.h>
# include <sstream>
# include <vector>
# include <csignal>



/********************************************/
/*				FT_IRC headers				*/
/********************************************/
# include "Server.hpp"
# include "colors.hpp"
# include "Client.hpp"
# include "ClientChannel.hpp"
# include "Channel.hpp"
# include "ParsingInput.hpp"
# include "serverReplies.hpp"

/********************************************/
/*				FT_IRC protos				*/
/********************************************/
ssize_t sendMessage(int fd, const std::string& message);
std::string intToString(int num);
bool isUserLogged( int clientFd, Server &server);

#endif