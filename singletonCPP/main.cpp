#include <iostream>
#include <stddef.h>
#include <assert.h>
// #include <vector>
#include <map>
#include <string>

using namespace std;

//----------------------------
// generic singleton template
template<class T>
class singleton {
    public:
        static T* Instance() {
            if (m_inst == NULL) m_inst = new T();
            assert(m_inst != NULL);
            return m_inst;
        }
    private:
        static T* m_inst;
        singleton();
        ~singleton();
        singleton(singleton const&);
        singleton& operator=(singleton const&);
};
template<class T> T* singleton<T>::m_inst = NULL; 
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

// template<typename T>
// class queue {
//     public:
//         void push(T x) { mQ.push_back(x); }
//         T pop() { 
//             T tmp = mQ.back();
//             mQ.pop_back();
//             return tmp;
//         }
//     private:
//         vector<T> mQ;
// };

typedef singleton<config> Config;

int main()
{
    Config::Instance()->setKeyVal("version","3");
    printf("config version = %s\n",Config::Instance()->getVal("version").c_str());
    Config::Instance()->dump_config();
    
    Config::Instance()->setKeyVal("version","5");
    printf("config version = %s\n",Config::Instance()->getVal("version").c_str());
    Config::Instance()->dump_config();
     
    bool ok = Config::Instance()->delKey("version");
    printf("config remove version = %d\n",ok);
    Config::Instance()->dump_config();
    
//   queue<int> Q;
//   Q.push(3);
//   Q.push(5);
//   printf("POP=%d\n",Q.pop());
//   printf("POP=%d\n",Q.pop());
   
   return 0;
}


