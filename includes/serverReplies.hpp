/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReplies.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:33:25 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/18 14:07:23 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_REPLIES_HPP
# define SERVER_REPLIES_HPP
# include "ft_irc.hpp"

/********************************************/
/*					Misc					*/
/********************************************/
# define CLIENT_TAG(nickname, username, command) (":" + nickname + "!~" + username + "@" + SERVER_NAME + " " + command)
# define FORMAT_REPLY(num_rply_numb, nickname) (std::string(":") + SERVER_NAME + " " + num_rply_numb + " " + nickname + " ")


/********************************************/
/*				RPL Replies					*/
/********************************************/
# define RPL_NICK(nickname, username, new_nickname) (CLIENT_TAG(nickname, username, "NICK") + " :" + new_nickname)
# define RPL_JOIN(nickname, username, channel) (CLIENT_TAG(nickname, username, "JOIN") + " :" + channel)
# define RPL_PRIVMSG(nickname, username, dest, msg) (CLIENT_TAG(nickname, username, "PRIVMSG ") + dest + " :" + msg)
# define RPL_PONG(nickname) (std::string(":") + SERVER_NAME + " PONG " + SERVER_NAME + " :" + SERVER_NAME)
# define RPL_TOPIC(nickname, username, channel, topic) (CLIENT_TAG(nickname, username, "TOPIC") + " " + channel + " " + topic)
# define RPL_OPER(nickname) (std::string(":") + SERVER_NAME + " 381 " + nickname + " :You are now an IRC operator")
# define RPL_QUIT(nickname, username, message) (CLIENT_TAG(nickname, username, "QUIT") + " :" + message)
# define RPL_KICK(nickname, username, channel, target, message) (CLIENT_TAG(nickname, username, "KICK ") + channel + " " + target + " :" + message)
# define RPL_MODE(nickname, username, channel, mode) (CLIENT_TAG(nickname, username, "MODE") + " " + channel + " " + mode)
# define RPL_INVITE(nickname, username, target, channel) (CLIENT_TAG(nickname, username, "INVITE ") + target + " :" + channel)
# define RPL_PART(nickname, username, channel, message) (CLIENT_TAG(nickname, username, "PART") + " " + channel + " " + message)

# define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the  " + SERVER_NAME + " IRC server " + nickname)
# define RPL_NAMREPLY(nickname, channel, list_client) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + list_client)
# define RPL_NOTOPIC(nickname, channel) (std::string(":") + SERVER_NAME + " 331 " + nickname + " " + channel + " :No topic is set")
# define RPL_ENDOFNAMES(nickname, channel) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of /NAMES list")
# define RPL_SHOWTOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " :" + topic)
# define RPL_INVITING(nickname, target, channel) (std::string(":") + SERVER_NAME + " 341 " + nickname + " " + target + " " + channel)
# define RPL_MODE_USER(nickname, username, target, mode) (CLIENT_TAG(nickname, username, "MODE ") + target + " " + mode)


/********************************************/
/*					ERRORS					*/
/********************************************/
# define ERR_NICKNAMEINUSE(nickname, newnickname) (std::string(":") + SERVER_NAME + " 433 " + nickname + " " + newnickname + " :Nickname is already in use")
# define ERR_ALREADYREGISTRED(nickname) (std::string(":") + SERVER_NAME + " 462 " + nickname + " :Already registred")
# define ERR_CHANNELISFULL(nickname, channel) (FORMAT_REPLY("471", nickname) + channel + " :Cannot join channel (+l)")
# define ERR_INVITEONLYCHAN(nickname, channel) (std::string(":") + SERVER_NAME + " 473 " + nickname + " " + channel + " :Cannot join channel (+i)")
# define ERR_ERRONEUSNICKNAME(nickname) (std::string(":") + SERVER_NAME + " 432 " + nickname + " :Erroneus nickname")
# define ERR_NEEDMOREPARAMS(nickname, command) (std::string(":") + SERVER_NAME + " 461 " + nickname + " " + command + " :Not enough parameters")
# define ERR_PASSWDMISMATCH(nickname) (std::string(":") + SERVER_NAME + " 464 " + nickname + " :Password incorrect")
# define ERR_NOTREGISTERED(nickname, command) (std::string(":") + SERVER_NAME + " 451 " + nickname + " " + command + " :You have not registered")
# define ERR_NOSUCHNICK(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 401 " + nickname + " " + other_nickname + " :No such nick")
# define ERR_NOSUCHCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 403 " + nickname + " " + channel + " :No such channel")
# define ERR_NOTONCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 442 " + nickname + " " + channel + " :You're not on that chanel")
# define ERR_CHANOPRIVSNEEDED(channel, nickname) (std::string(":") + SERVER_NAME + " 482 " + nickname + " " + channel + " :You're not channel operator")
# define ERR_USERNOTINCHANNEL(nickname, channel, target_nickname) (std::string(":") + SERVER_NAME + " 441 " + nickname + " " + target_nickname + " " + channel + " :They aren't on that channel")
# define ERR_MODEUNKNOWNFLAG(nickname) (std::string(":") + SERVER_NAME + " 501 " + nickname + " :Unknown MODE flag")
# define ERR_USERONCHANNEL(nickname, channel, target_nickname) (std::string(":") + SERVER_NAME + " 443 " + nickname + " " + target_nickname + " " + channel + " :is already on channel")
# define ERR_BADCHANNELKEY(nickname, channel) (FORMAT_REPLY("475", nickname) + channel + " :Cannot join channel (+k)")
# define ERR_USERSDONTMATCH(nickname) (std::string(":") + SERVER_NAME + " 502 " + nickname + " :Cant change mode for other users")
#endif