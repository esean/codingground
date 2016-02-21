#include <iostream>
#include <stddef.h>
#include <assert.h>
#include <map>
#include <string>

using namespace std;

//----------------------------
// Generic singleton template
//
// NOTE: following #def controls if the
// singleton uses dynamic memory 'new'.
//
#define SINGLETON_USE_DYNAMIC_MEMORY
//
template<class T>
class singleton {
    public:
        static T* Instance() {
#ifdef SINGLETON_USE_DYNAMIC_MEMORY
		#warning "SINGLETON: using new"
            if (m_inst == NULL) m_inst = new T();
            assert(m_inst != NULL);
            return m_inst;
#else
		#warning "SINGLETON: not using new"
		static T inst;
		return &inst;
#endif
	}
    private:
#ifdef SINGLETON_USE_DYNAMIC_MEMORY
        static T* m_inst;
#endif
        singleton();
#ifdef SINGLETON_USE_DYNAMIC_MEMORY
        ~singleton() {
            delete m_inst;
        }
#else
        ~singleton();
#endif
        singleton(singleton const&);
        singleton& operator=(singleton const&);
};
#ifdef SINGLETON_USE_DYNAMIC_MEMORY
template<class T> T* singleton<T>::m_inst = NULL; 
#endif
//----------------------------

class config {
    public:
        string getVal(string s) { return m_map[s]; }
        void setKeyVal(string s, string v) { m_map[s] = v; }
        bool delKey(string s) { return m_map.erase(s); }
        // debug
        void dump_config() {
            for (map<string,string>::iterator it = m_map.begin(); it != m_map.end(); ++it)
                printf("config [%s]=[%s]\n",it->first.c_str(),it->second.c_str());
        }
    private:
        map<string,string> m_map;
};

typedef singleton<config> Config;

int main()
{
    Config::Instance()->setKeyVal("version","3");
    printf("config version = %s\n",Config::Instance()->getVal("version").c_str());
    Config::Instance()->dump_config();
    
    Config::Instance()->setKeyVal("version","5");
    Config::Instance()->setKeyVal("config","1.1");
    printf("config version = %s\n",Config::Instance()->getVal("version").c_str());
    Config::Instance()->dump_config();
     
    bool ok = Config::Instance()->delKey("version");
    printf("config remove version = %d\n",ok);
    ok = Config::Instance()->delKey("bump");
    printf("config remove bump = %d\n",ok);
    Config::Instance()->dump_config();
    
   return 0;
}


