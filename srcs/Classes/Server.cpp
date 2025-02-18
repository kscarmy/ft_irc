/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:38:35 by dbelpaum          #+#    #+#             */
/*   Updated: 2023/10/21 17:06:39 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"
#include "../../includes/ft_irc.hpp"

volatile bool keepRunning = true;

std::string intToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

void signalHandler(int signum) {
		if (DEBUG)
			std::cout << std::endl << "Signal " << signum << " reçu. Arrêt en cours..." << std::endl;
		keepRunning = false;
}

Server::Server(int port, std::string password)
{
	_errorInit = 0;
	this->_port = port;
	this->_password = password;
	this->_operPassword = OPER_PASSWORD;
    memset(&_address, 0, sizeof(_address));
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(port);
    _addrlen = sizeof(_address);
	_isRunning = true;
	_isBot = false;
	_botString = "jeannot le lapin";
	_botFound = "";
	_botStatus = 0;
	std::cout << GREEN << "Started IRC Server" << std::endl << YELLOW1 << "Listening on PORT " << _port << RESET << std::endl;
}

Server::~Server()	{}

void	Server::debug()
{
	if (DEBUG == 0)
		return ;
	std::cout << "Server {" << std::endl;

	std::cout << "	_port: " << _port << std::endl;
	std::cout << "	_password: " << _password << std::endl;
	std::cout << "	_socket_fd: " << _sock_fd << std::endl;
	
	std::cout << "}" << std::endl;
}

std::string Server::getPass() const {
	return _password;
}

int Server::getChannelClientCount(std::string channelName) {
	int ret=0;
	for (int i=0; i < MAX_USERS; i++){
		for (int j=0; j < (int)_Client[i].getClientChannel().size(); j++){
			if (_Client[i].getClientChannel()[j].getChannelName() == channelName)
				ret++;
		}
	}
	return ret;
}

bool Server::getIsBot() const {
	return _isBot;
}

std::string Server::getBotString() const {
	return _botString;
}

std::string Server::getBotFound() const {
	return _botFound;
}

void Server::setBotFound(std::string str) {
	_botFound = str;
}

void Server::setBotStatus(int status) {
	_botStatus = status;
}

int Server::getBotStatus() const {
	return _botStatus;
}

void Server::setIsBot(bool isBot) {
	_isBot = isBot;
}

void Server::setBotString(std::string botString) {
	_botString = botString;
}



std::string Server::getOperPass() const {
	return _operPassword;
}

bool Server::isUserOperIn(std::string nickname, std::string channelName)
{
	return (this->getClientByName(nickname).getOPER() || this->getClientByName(nickname).getClientChannelName(channelName).getClientChannelOperator());
}

void Server::setUserServerOper(std::string nickname, bool oper)
{
	this->getClientByName(nickname).setOPER(oper);
}

void Server::setUserOperIn(std::string nickname, std::string channelName, bool oper)
{
	this->getClientByName(nickname).getClientChannelName(channelName).setClientChannelOperator(oper);
}

void Server::sendToAllUsersOf(std::string channelName, std::string message)
{
	for (int i=0; i < MAX_USERS; i++)
		if (this->clientInChannel(_Client[i].getNickName(), channelName))
			sendMessage(_Client[i].getFd(), message);
}

void Server::sendToAllUserChannels(std::string nickname, std::string message)
{
	Client & client = this->getClientByName(nickname);
	for (int i=0; i < (int)client.getClientChannel().size(); i++)
		sendToAllUsersOf(client.getClientChannel()[i].getChannelName(), message);
}

void Server::addClient(int newClientFd, char * ipAddr) {
	if (DEBUG)
		std::cout << "addClient FD" << std::endl;
	for(int i = 0; i < MAX_USERS; i++){
		if (_Client[i].getIsSet() == false){
			_Client[i].setFd(newClientFd);
			_Client[i].setIsSet(true);
			_Client[i].setUserName(ipAddr);
			return ;
		}
	}
	if (DEBUG)
		std::cout << "Client not added !!! LIMIT !!!" << std::endl;
}

void Server::removeClientByFd( int fdToRemove) {
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getFd() == fdToRemove){
			_Client[i].setIsSet(false);
			_Client[i].setFd(-1);
			_Client[i].setPASS(false);
			_Client[i].setNICK(false);
			_Client[i].setUSER(false);
			_Client[i].setRealName("");
			_Client[i].setNickName("");
			_Client[i].setUserName("");
			_Client[i].setMode(-1);
			_Client[i].getClientChannel().clear();
			return ;
		}
	}
	if (DEBUG)
		std::cout << "Client not found for erase !!!" << std::endl;
}

bool Server::clientExists(std::string name)
{
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getNickName() == name)
			return true;
	}
	return false;
}

bool Server::clientInChannel(std::string nickname, std::string channelName)
{
	if (!this->clientExists(nickname) || !this->channelExists(channelName))
		return false;
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getNickName() == nickname){
			for (int j=0; j < (int)_Client[i].getClientChannel().size(); j++){
				if (_Client[i].getClientChannel()[j].getChannelName() == channelName)
					return true;
			}
		}
	}
	return false;
}

Channel& Server::getChannelByName(std::string name)
{
	for (int i=0; i < MAX_CHANNEL; i++){
		if (_Channel[i].getChannelName() == name)
			return _Channel[i];
	}
	return _Channel[0];
}

Client& 	Server::getClientByName(std::string name){
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getNickName() == name)
			return _Client[i];
	}
	return _Client[0];
}

void Server::removeClientFromChannel(std::string name, std::string channelName, Server &server)
{
	if (server.getClientByName(name).isInChannel(channelName))
		server.getClientByName(name).removeClientChannel(channelName);
	server.getChannelByName(channelName).removeClientFd(server.getClientByName(name).getFd());
}

int Server::getClientFdByNick(std::string Nick) const {
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getNickName() == Nick)
			return _Client[i].getFd();
	}
	return -1;
}

bool Server::clientInChannelOp(std::string name, std::string channelName)
{
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getNickName() == name){
			for (int j=0; j < (int)_Client[i].getClientChannel().size(); j++){
				if (_Client[i].getClientChannel()[j].getChannelName() == channelName && _Client[i].getClientChannel()[j].getClientChannelOperator() == true)
					return true;
			}
		}
	}
	return false;
}

int Server::getChannelCout() const {
	int ret =0;
	for (int i=0; i < MAX_CHANNEL; i++){
		if (_Channel[i].getIsSet() == true)
			ret++;
	}
	return ret;
}

Client& Server::getClientByFd(int fd){
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getFd() == fd)
			return _Client[i];
	}
	return _Client[0];
}


Channel* Server::getChannels(){
	return _Channel;
}

Client* Server::getClients(){
	return _Client;
}

size_t Server::getClientCount() const {
	size_t ret = 0;
    for (int i = 0; i < MAX_USERS; ++i) {
		if (_pollFd[i].fd > 0)
			++ret;
	}
	return ret;
}

ssize_t sendMessage(int fd, const std::string& message)
{
	if (DEBUG)
		std::cout << "sendMessage to : " << fd << " <" << message << std::endl;
	return send(fd, (message + "\r\n").c_str(), message.size() + 2, 0);
}

// void Server::addChannel(std::string name)
// {
// 	_ChannelList.push_back(Channel(name));
// 	std::cout << "Channel " << name << " created" << std::endl;
// }

void Server::addChannel(std::string name)
{
	for (int i=0; i < MAX_CHANNEL; i++){
		if (_Channel[i].getIsSet() == false){
			_Channel[i].setIsSet(true);
			_Channel[i].setChannelName(name);
			// _Channel[i].setTopic(topic);
			// _Channel[i].setSecret(password);
			if (DEBUG)
				std::cout << "Channel " << name << " created" << std::endl;
			return ;
		}
	}
	if (DEBUG)
		std::cout << "Channel not added !!! LIMIT !!!" << std::endl;
}

// std::vector<Channel> Server::getChannelList() {
// 	return _ChannelList;
// }

void Server::removeChannel(std::string name)
{
	Channel & channel = getChannelByName(name);
	if (channel.getIsSet() == false)
		return ;
	channel.setIsSet(false);
	channel.setChannelName("");
	channel.setTopic("");
	channel.setSecret("");
	channel.getClientFd().clear();
	if (DEBUG)
		std::cout << "Channel " << name << " removed" << std::endl;
}

bool Server::channelExists(std::string name)
{
	for (int i=0; i < MAX_CHANNEL; i++){
		if (_Channel[i].getChannelName() == name)
			return true;
	}
	return false;
}

void Server::initialize()
{
    if ((_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        _errorInit = 1;
		return ;
    }
    if (bind(_sock_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
        perror("bind failed");
        _errorInit = 1;
		return ;
    }
    if (listen(_sock_fd, MAX_USERS) < 0) {
        perror("listen failed");
        _errorInit = 1;
		return ;
    }
    memset(_pollFd, 0, sizeof(_pollFd));
    _pollFd[0].fd = _sock_fd;
    _pollFd[0].events = POLLIN;
}

void Server::run() {
    initialize();
	if (_errorInit)
		std::cout << std::endl << "Error while initializing !" << std::endl;
	else
		mainLoop();
	if (DEBUG)
		std::cout << "Nombre clients encore co" << getClientCount() << std::endl;
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getIsSet() == true){
			close(_Client[i].getFd());
		}
	}
	if (DEBUG)
		std::cout << "close _sock_fd" << std::endl;
	close (_sock_fd);
}

void Server::handleNewConnection()
{
    int new_socket = accept(_sock_fd, (struct sockaddr *)&_address, (socklen_t *)&_addrlen);
    if (new_socket < 0) {
        perror("accept failed");
        return;
    }
	// Get the client's IP address
    char clientIp[INET_ADDRSTRLEN]; // Buffer to store the IP address
    inet_ntop(AF_INET, &(_address.sin_addr), clientIp, INET_ADDRSTRLEN);
    if (DEBUG)
		std::cout << "New connection from IP: " << clientIp << std::endl;
	if (getClientCount() >= MAX_USERS){
		if (DEBUG)
			std::cout << "Too many clients connected" << std::endl;
		sendMessage(new_socket, "ERROR : Too many clients connected on the server");
		close(new_socket);
		return ;
	}

	addClient(new_socket, clientIp);
	getClientByFd(new_socket).debug();
    for (int j = 1; j < MAX_USERS; ++j) {
        if (_pollFd[j].fd == 0) {
            _pollFd[j].fd = new_socket;
            _pollFd[j].events = POLLIN;
            // sendWelcomeMessage(new_socket); //  MOTD A REMETTRE !
            if (DEBUG)
				std::cout << "[fd" << new_socket << "] has logged in." << std::endl;
            break;
        }
    }
}

std::string Server::getNickByFd(int fd)
{
	for (int i=0; i < (int)getClientCount(); i++)
		if (_Client[i].getFd() == fd)
			return _Client[i].getNickName();
	return "";
}

void Server::handleClientCommunication(int index)
{
	int pos = -1;
	memset(_buffer, 0, BUFFER_SIZE);
	for (int i=0; i < MAX_USERS; i++){
		if (_Client[i].getFd() == _pollFd[index].fd){
			pos = i;
			break;
		}
	}
    int bytesRead = recv(_pollFd[index].fd, _buffer, BUFFER_SIZE, 0);
	if (bytesRead > 0)
		_Client[pos].setBuff(_Client[pos].getBuff() + _buffer);
	if (DEBUG)
		std::cout << "handleClientCommunication : bytesRead = " << bytesRead << std::endl;
	for (int i=0; bytesRead > 0 && i < BUFFER_SIZE && i < (bytesRead + 1); i++){ // EOF TEST
		// std::cout << "i = " << i << " _buffer[i] = " << _buffer[i] << " value = " << (int)_buffer[i] << std::endl;
		if (_buffer[i] == 10){
			// std::cout << "Normal send" << std::endl;
			break ;
		}
		if (i == bytesRead){ // ctrl+D detecter (en gros on a pas la touche "ENTER" de pressee)
			// std::cout << "ctrl+D DETECTED" << std::endl;
			return ;
		}
	}
	// std::cout << "handleClientCommunication : OK" << std::endl;
    if (bytesRead <= 0)
	{
		close(_pollFd[index].fd);
		removeClientByFd(_pollFd[index].fd);
		if (DEBUG){
			std::cout << " EOF DETECTED" << std::endl;
    		std::cout << "[fd" << _pollFd[index].fd << "] disconnected." << std::endl;		//User Disconnected
		}
		_pollFd[index].fd = -1;
		return ;
    }
	if (DEBUG)
		std::cout << "Message received from [fd" << _pollFd[index].fd << "] : <" << _Client[pos].getBuff() << ">" << std::endl;
	// _buffer[bytesRead - 1] = '\0';	//bytesRead - 1 Pour enlever le \n reçu
	// if last char is \n
	if (_Client[pos].getBuff()[_Client[pos].getBuff().size() - 1] == '\n')
		_Client[pos].setBuff(_Client[pos].getBuff().substr(0, _Client[pos].getBuff().size() - 1));
	if (!(ParseFunctions::parse((std::string)_Client[pos].getBuff(), _pollFd[index].fd, *this)))
	{
		// anciennement l'envoi de message classique mtn géré par PRIVMSG
	}

	_Client[pos].setBuff("");
}

void Server::sendWelcomeMessage(int socket)
{
    sendMessage(socket, "Welcome !\n");
}

void Server::mainLoop()
{
	signal(SIGINT, signalHandler);
    while (keepRunning) {
        int result = poll(_pollFd, MAX_USERS, -1);
        if (result == -1)
            perror("poll() Stop ");
		else
		{
			for (int i = 0; i < MAX_USERS; ++i) {
				if (_pollFd[i].revents & POLLIN) {
					if (_pollFd[i].fd == _sock_fd) {
						handleNewConnection();
					} else {
						handleClientCommunication(i);
					}
				}
			}
		}
    }
}
