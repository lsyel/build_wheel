#include "bits/stdc++.h"
using namespace std;
class Base{
public:
    Base(){
        //即使是派生类调用父类的构造方法，此时虚表指针仍指向父类虚函数表
        f();
    }
    virtual void f(){
        cout <<"base func"<<endl;
    }
};
class Derived: public Base{
public:
    Derived():Base(){
        //这里虚表指针重定向到派生类的虚函数表
    }
public:
    virtual void f(){
        cout <<"derived func"<<endl;
    }
private:
    int x{0};
};
int main(){
    Base * p = new Derived();//输出base func

}