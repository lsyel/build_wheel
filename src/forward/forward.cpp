#include <iostream>
using namespace std;
#define PRINT(x) cout<<#x<<":"<<x<<endl;


template <typename T>
struct my_remove_reference{
    typedef T type;
};

//模版特化
template <typename T>
struct my_remove_reference<T&>{
    typedef T type;
};

//模版特化
template <typename T>
struct my_remove_reference<T&&>{
    typedef T type;
};

template <typename T>
T&& my_forward(typename my_remove_reference<T>::type & argv){
    return static_cast<T&&> (argv); 
}
template <typename T>
T&& my_forward(typename my_remove_reference<T>::type && argv){
    return static_cast<T&&> (argv);
}

void print(int &x){
    cout <<"left value"<<endl;
}
void print(int && x){
    cout <<"right value"<<endl;
}

template <typename T>
void wrapper(T&& x){
    print(my_forward<T>(x));
}
int main(){
    int a =1;
    wrapper(a);
    wrapper(std::move(a));
}