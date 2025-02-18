/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:46:10 by guderram          #+#    #+#             */
/*   Updated: 2023/10/19 12:00:37 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

// Constructeurs
Channel::Channel() {
	_isSet = false;
	_isInviteOnly = false;
	_isTopicOpOnly = false;
	_isSecret = false;
	_userLimit = 0;
	_ChannelName = "";
	_Topic = "No topic is set";
	_Secret = "";
}

Channel::Channel(const std::string& channelName){
	_isSet = false;
	_isInviteOnly = false;
	_isTopicOpOnly = false;
	_isSecret = false;
	_userLimit = 0;
	_ChannelName = channelName;
	_Topic = "No topic is set";
	_Secret = "";
	}

Channel::Channel(const Channel& other)
    : _ChannelName(other._ChannelName), _clientFd(other._clientFd) {}

// Opérateur d'assignation
Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        _ChannelName = other._ChannelName;
        _clientFd = other._clientFd;
    }
    return *this;
}

// Destructeur
Channel::~Channel() {
}

// Getters

bool		Channel::getIsSet() const {
	return _isSet;
}

std::string Channel::getChannelName() const {
    return _ChannelName;
}

std::string Channel::getTopic() const {
	return _Topic;
}

std::string Channel::getSecret() const {
	return _Secret;
}

bool Channel::getInviteOnly() const {
	return _isInviteOnly;
}

bool Channel::getTopicOpOnly() const {
	return _isTopicOpOnly;
}

bool Channel::isSecret() const {
	return _isSecret;
}	

int Channel::getLimit() const {
	return _userLimit;
}
std::vector<int> & Channel::getClientFd(){
	return  _clientFd;
}

int Channel::getNbClients() const{
	return _clientFd.size();
}

int	Channel::getClientFd(int i) const{
	if (i < 0 || i >= (int)_clientFd.size())
		return (-1);
	return _clientFd[i];
}

// Setters

void Channel::setIsSet(bool isSet) {
	_isSet = isSet;
}

void Channel::setChannelName(const std::string& channelName) {
    _ChannelName = channelName;
}

void Channel::setTopic(const std::string& topic) {
	_Topic = topic;
}

void Channel::setSecret(const std::string& secret) {
	_Secret = secret;
}

void Channel::setInviteOnly(bool inviteOnly) {
	_isInviteOnly = inviteOnly;
}

void Channel::setTopicOpOnly(bool topicOpOnly) {
	_isTopicOpOnly = topicOpOnly;
}

void Channel::setIsSecret(bool secret) {
	_isSecret = secret;
}

void Channel::setLimit(int limit) {
	_userLimit = limit;
}

void Channel::setClientFd(const int clientFd){
	_clientFd.push_back(clientFd);
}

void Channel::removeClientFd(const int clientFd){
	for (int i=0; i < (int)_clientFd.size(); i++)	{
		if (_clientFd[i] == clientFd)	{
			_clientFd.erase(_clientFd.begin() + i);
			break ;
		}
	}
}

void Channel::sendToAll(const std::string & message)
{
	std::vector<int>::iterator it = this->_clientFd.begin();
	std::vector<int>::iterator ite = this->_clientFd.end();
	while (it != ite)
	{
		if (DEBUG)
			std::cout << "<Channel::sendToAll> Sending message to " << *it << std::endl;
		sendMessage(*it, message);
		it++;
	}
}

void Channel::sendToAll(const std::string & message, Server & server, std::string nicknameToIgnore)
{
	std::vector<int>::iterator it = this->_clientFd.begin();
	std::vector<int>::iterator ite = this->_clientFd.end();
	while (it != ite)
	{
		if (server.getClientByFd(*it).getNickName() == nicknameToIgnore)
		{
			it++;
			continue;
		}
		if (DEBUG)
			std::cout << "<Channel::sendToAll> Sending message to " << *it << std::endl;
		sendMessage(*it, message);
		it++;
	}
}
