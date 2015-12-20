#include <iostream>

using namespace std;

// abstract base class w/ overloaded fcn
class number {
    public:
        virtual bool isNegative() = 0;
        virtual void setNum(int x) = 0;
        virtual void setNum(float x) = 0;
        virtual int getNum() = 0;
        virtual ~number() = 0;
};
number::~number() { printf("NUM: DEST\n"); }
int number::getNum() { printf("NUM: getNum()"); }

// create derived class with static member
class ca: number {
    public:
        ca() {}
        ca(int x) { u.val = x; }
        ca(float f) { u.valf = f; }
        ~ca() { printf("CA DEST\n"); }
        static int x;
        bool isNegative();
        void setNum(int x) { u.val = x; ca::x += 1;}
        void setNum(float x) { u.valf = x; ca::x += 1;}
        int getNum() { return u.val;}
        float getNumf() { return u.valf;}
    private:
        union {
            int val;
            float valf;
        } u;
};
bool ca::isNegative() {
    return (u.val < 0);
}

int ca::x = 0;

int main()
{
   ca x(5);
   printf("x.x = %d val=%d valf=%f (neg=%d)\n",x.x,x.getNum(),x.getNumf(),x.isNegative());
   x.setNum(3);
   printf("x.x = %d val=%d valf=%f (neg=%d)\n",x.x,x.getNum(),x.getNumf(),x.isNegative());
   x.setNum(-3);
   printf("x.x = %d val=%d valf=%f (neg=%d)\n",x.x,x.getNum(),x.getNumf(),x.isNegative());
   x.setNum(-0.3f);
   printf("x.x = %d val=%d valf=%f (neg=%d)\n",x.x,x.getNum(),x.getNumf(),x.isNegative());
   
   ca y(0.5f);
   printf("y.x = %d val=%d valf=%f (neg=%d)\n",y.x,y.getNum(),y.getNumf(),y.isNegative());
   
   return 0;
}


