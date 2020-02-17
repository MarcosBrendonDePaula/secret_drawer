#pragma once
#ifdef _WIN32
	#include <winsock2.h>
	#include <process.h>
#elif __linux__
	#include<netinet/in.h>
	#include <arpa/inet.h>
	#include<pthread.h>
	#include<unistd.h>
#endif
#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include <cstring>
#include "Events.h"
#include <map>

using namespace std;
class Nsock{
	private:
		#ifdef _WIN32
			SOCKET cliente;
		#elif __linux__
			int cliente;
			pthread_t ThreadCliente;
		#endif
		struct sockaddr_in DadosCliente;
		list<string> Entrada;
		list<int> *ordem;
		list<char*> EntradaVetorizada;
		//vector<Nsock*> *conexoes;
		map<int,Nsock*> *connections;
		Events *Evs;
		char vazio[6];
		int erro;
	public:
		int id;
		int BufferSize;
		Nsock(list<int> *lista,map<int,Nsock*> *cn,Events *Evs);
		#ifdef _WIN32
			static void ReceiveFunction(void *arg);
			SOCKET* getClient();
		#elif __linux__
			static void* ReceiveFunction(void *arg);
			int* getClient();
		#endif
		struct sockaddr_in* getSocketInfo();
		int start();
		void Close();
		string getInput();
		char* getInputVector();
		int SendMsg(string msg);
		int SendMsg(char msg[],int size);
		const string getIP();
		const int getPort();
};