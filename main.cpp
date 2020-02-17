#include <iostream>
#include "EasyLib/EasyMultServer.h"
#include "EasyLib/Events.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <map>

using namespace std;

EasyMultServer *servidor;
Events EventosServidor;
vector<string> Nomes;

map<string,string> Sorteado;
map<string,bool> IpAdicionado;
map<string,Nsock*> SockPnome;

void RequestProcess(void *arg);
void AcceptFunction(void *arg);
const vector<string> split(const string& s, const char& c);
void Sortear();

int main()
{
    Nomes.push_back("zed");
    Nomes.push_back("singed");
    Nomes.push_back("Volibear");
    Nomes.push_back("veigar");
    Nomes.push_back("kayle");
    Nomes.push_back("teemo");
    Nomes.push_back("master yi");
    Nomes.push_back("YASUO");
    servidor = new EasyMultServer(25565,&EventosServidor);
    if(!servidor->Start(&RequestProcess,20,&AcceptFunction))
    {
        return -1;
    }
    string input;
    while(input!="iniciar")
    {
        cin >> input;
    }
    Sortear();
    return 0;
}

void RequestProcess(void *arg)
{
    Nsock *Socket = (Nsock*)arg;
    string msg = Socket->getInput();
    if(msg.find("add,")==0)
    {
        if(IpAdicionado[Socket->getIP()])
        {
            Socket->SendMsg("Seu ip ja foi Adionado A lista");
            return;
        }
        vector<string> Dados{split(msg,',')};
        Nomes.push_back(Dados[1]);
        SockPnome[Dados[1]] = Socket;  
        IpAdicionado[Socket->getIP()]=true;
        Socket->SendMsg("Voce foi adicionado a lista Permaneca Conectado para o sorteio");
        return;
    }
}

void AcceptFunction(void *arg)
{
    Nsock *Socket = (Nsock*)arg;
    Socket->SendMsg("Envie 'add,seunome' para lhe adicionar a lista de sorteio");
}


const vector<string> split(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	return v;
}

void Sortear()
{
    vector<string> cartoes{Nomes};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cartoes.begin(),cartoes.end(),std::default_random_engine(seed));
    for(int i=0;i<cartoes.size();i++)
    {
        if(i==(cartoes.size()-1))
        {
            Sorteado[cartoes[i]]=cartoes[0];
        }else
        {
            Sorteado[cartoes[i]]=cartoes[i+1];
        }
    }
    for(auto i : Sorteado)
    {
        if(SockPnome[i.first]!=NULL)
            SockPnome[i.first]->SendMsg("Seu Amigo secreto eh: "+i.second);
    }
}