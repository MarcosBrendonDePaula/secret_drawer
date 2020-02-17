#pragma once
#ifdef __linux__
    #include <iostream>
    #include <pthread.h>
    #include <map>
    #include <list>
    #include <unistd.h>
    #include <stdio.h>
    class Event
    {
        public:
            Event(int ID,void(*funcao)(void*),void *parametro);
            Event(int ID,void(*funcao)(void*));
            Event(int ID,void(*funcao)());
            int ID;
            void *parametros;
            void(*funcao)(void*);
    };
    
    class Events
    {
        public:
            static void* ExecutorF(void* arg);
            Events();
            void addEvent(Event *E);
            void sendSignal(int ID);
            Event* getEvent(int id);
            std::list<int> LEDP;
            bool Paralel;
        private:
            bool Debug;
            pthread_t executor;
            std::map<int,Event*> Leventos;
            bool rodando;
    };
#elif _WIN32
    #include <iostream>
    #include <map>
    #include <list>
    #include <process.h>
    #include <windows.h>
    #include <unistd.h>
    #include <stdio.h>
    class Event
    {
        public:
            Event(int ID,void(*funcao)(void*),void *parametro);
            Event(int ID,void(*funcao)(void*));
            Event(int ID,void(*funcao)());
            int ID;
            void *parametros;
            void(*funcao)(void*);
    };
    class Events
    {
        public:
            static void ExecutorF(void* arg);
            static void KeyMonitor(void* arg);
            void OnKeyMonitor(void(*funcao)(void*));
            Events();
            bool KeySMonitor=false;
            void addEvent(Event *E);
            void sendSignal(int ID);
            bool Paralel;
            Event* getEvent(int id);
        private:
            bool Debug;
            std::list<int> LEDP;
            std::map<int,Event*> Leventos;
            bool rodando;
    };
#endif
