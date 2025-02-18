/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:10:55 by guderram          #+#    #+#             */
/*   Updated: 2023/10/19 12:01:26 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// Constructeurs
Client::Client(){
	this->_isSet = false;
	this->_fd = -1;
	this->_PASS = false;
	this->_NICK = false;
	this->_USER = false;
	this->_OPER = false;
	this->_NickName = "";
	this->_UserName = "";
	this->_RealName = "";
	this->_CurrentChannel = "";
	this->_buff = "";
	for (int i=0; i < MAX_INVITS; i++)
		this->_invitChannel[i] = "";
	this->_mode = -1;
	this->_ClientChannel = std::vector<ClientChannel>();
}

Client::Client(const int ClientFd)
    : _isSet(true), _fd(ClientFd), _PASS(false), _NICK(false), _USER(false), _OPER(false), _NickName(""), _UserName(""), _RealName(""), _CurrentChannel(""), _mode(-1){
	this->_isSet = false;
	this->_fd = -1;
	this->_PASS = false;
	this->_NICK = false;
	this->_USER = false;
	this->_OPER = false;
	this->_NickName = "";
	this->_UserName = "";
	this->_RealName = "";
	this->_CurrentChannel = "";
	this->_buff = "";
	for (int i=0; i < MAX_INVITS; i++)
		this->_invitChannel[i] = "";
	this->_mode = -1;
	this->_ClientChannel = std::vector<ClientChannel>();
}

Client::Client(const int ClientFd, std::string& userName, const std::string& nickName)
    : _fd(ClientFd), _NickName(nickName), _UserName(userName), _mode(-1) {}

Client::Client(const Client& other)
    : _fd(other._fd), _NickName(other._NickName), _UserName(other._UserName), _mode(other._mode), _ClientChannel(other._ClientChannel) {}

// Opérateur d'assignation
Client& Client::operator=(const Client& other) {
    if (this != &other) {
        _UserName = other._UserName;
        _NickName = other._NickName;
        _ClientChannel = other._ClientChannel;
    }
    return *this;
}

// Destructeur
Client::~Client() {
}

// Getters
std::string Client::getUserName() const {
    return _UserName;
}

std::string Client::getNickName() const {
    return _NickName;
}


int			Client::getFd() const {
    return _fd;
}

bool		Client::getPASS() const {
	return _PASS;
}

bool		Client::getNICK() const {
	return _NICK;
}

bool		Client::getUSER() const {
	return _USER;
}

std::string Client::getRealName() const {
	return _RealName;
}

int			Client::getMode() const {
	return _mode;
}

std::vector<ClientChannel> &	Client::getClientChannel(){
	return _ClientChannel;
}

bool		Client::getIsSet() const {
	return _isSet;
}

std::string Client::getCurrentChannel() const {
	return _CurrentChannel;
}

ClientChannel & Client::getClientChannelName(std::string channelName){
	for (int i=0; i < (int)_ClientChannel.size(); i++)	{
		if (_ClientChannel[i].getChannelName() == channelName)
			return _ClientChannel[i];
	}
	return _ClientChannel[0];
}

bool Client::isInChannel(std::string channelName) const{
	for (int i=0; i < (int)_ClientChannel.size(); i++)	{
		if (_ClientChannel[i].getChannelName() == channelName)
			return true;
	}
	return false;
}

bool Client::isInvited(std::string channelName) const{
	for (int i=0; i < MAX_INVITS; i++)	{
		if (_invitChannel[i] == channelName)
			return true;
	}
	return false;
}

bool Client::getOPER() const{
	return _OPER;
}

std::string Client::getBuff() const{
	return _buff;
}

// Setters
void Client::setUserName(const std::string& userName) {
    _UserName = userName;
}

void Client::setNickName(const std::string& nickName) {
    _NickName = nickName;
}

void Client::setPASS(bool pass) {
	_PASS = pass;
}

void Client::setNICK(bool nick) {
	_NICK = nick;
}

void Client::setUSER(bool user) {
	_USER = user;
}

void Client::setRealName(const std::string& realName) {
	_RealName = realName;
}

void Client::setMode(int mode) {
	_mode = mode;
}

void Client::setFd(int fd) {
	_fd = fd;
}

void Client::setIsSet(bool isSet) {
	_isSet = isSet;
}

void Client::setCurrentChannel(const std::string& currentChannel) {
	_CurrentChannel = currentChannel;
}

void Client::addInvite(const std::string& channelName) {
	for (int i=0; i < MAX_INVITS; i++)	{
		if (_invitChannel[i] == channelName)
			return ;
		if (_invitChannel[i] == "")	{
			_invitChannel[i] = channelName;
			return ;
		}
	}
}

void Client::removeInvite(const std::string& channelName) {
	for (int i=0; i < MAX_INVITS; i++)	{
		if (_invitChannel[i] == channelName)	{
			_invitChannel[i] = "";
			return ;
		}
	}
}

void Client::setOPER(bool oper) {
	_OPER = oper;
}

void Client::setBuff(const std::string& buff) {
	_buff = buff;
}

// Fonctions pour gérer les canaux
void Client::addClientChannel(bool clientChannelOperator, std::string channelName) {
    _ClientChannel.push_back(ClientChannel(clientChannelOperator, channelName));
	if (DEBUG)
		std::cout << "addClientChannel : " << _ClientChannel[0].getChannelName() << " " << _ClientChannel[0].getClientChannelOperator() << std::endl;
	for (int i=0; i < (int)_ClientChannel.size(); i++)	{
		if (_ClientChannel[i].getChannelName() == channelName)	{
			this->setCurrentChannel(channelName);
			break ;
		}
	}
	if (DEBUG)
		std::cout << "addClientChannel : " << _ClientChannel[0].getChannelName() << " " << _ClientChannel[0].getClientChannelOperator() << std::endl;
}

void Client::removeClientChannel(std::string channelName) {
	for (int i=0; i < (int)_ClientChannel.size(); i++)	{
		if (_ClientChannel[i].getChannelName() == channelName)	{
			_ClientChannel.erase(_ClientChannel.begin() + i);
			break ;
		}
	}
}


// Fonction qui donne les infos du client
void Client::debug(){
	if (DEBUG == 0)
		return ;
	std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
	std::cout << "isSet : " << _isSet << std::endl;
	std::cout << "fd : " << _fd << std::endl;
	std::cout << "PASS : " << _PASS << std::endl;
	std::cout << "NICK : " << _NICK << std::endl;
	std::cout << "USER : " << _USER << std::endl;
	std::cout << "UserName : " << _UserName << std::endl;
	std::cout << "NickName : " << _NickName << std::endl;
	std::cout << "RealName : " << _RealName << std::endl;
	std::cout << "Mode : " << _mode << std::endl;
	std::cout << "Channels : " << std::endl;
	for (int i=0; i < (int)_ClientChannel.size(); i++)	{
		std::cout << "Name	" << _ClientChannel[i].getChannelName() << std::endl;
		std::cout << "OP	" << _ClientChannel[i].getClientChannelOperator() << std::endl;
	}
	std::cout << "--------------------------------------------------------------" << std::endl;
}
