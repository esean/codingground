#include <iostream>

using namespace std;

class config {
    public:
        static config* getInstance();
        int getVal() { return val; }
        void setVal(int x) { val = x; }
    private:
        static config* m_inst;
        int val;
};

config* config::m_inst = nullptr;
config* config::getInstance() {
    if (m_inst == nullptr) {
        m_inst = new config();
    }
    return m_inst; 
}

int main()
{
    config::getInstance()->setVal(3);
    printf("int val = %d\n",config::getInstance()->getVal());
    
   return 0;
}

