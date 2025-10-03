#include <iostream>
using namespace std;
#define SQUARE(x) ((x)*(x))
#define SWAP(a,b) do{\
    auto temp  = b;\
    b =a;\
    a = temp;\
} while(0)
#define PRINT(x) cout<<#x<<":"<<x<<endl
#define DEBUG(x)\
do{\
PRINT(__FILE__);\
PRINT(__LINE__);\
PRINT(x);\
}while(0)
#define MAKE_VARIABLE(name,num) name##num
int main(){
    int a=2;
    int b = SQUARE(a);
    cout <<b<<endl;
    SWAP( a,b);
    DEBUG(a);
    DEBUG(b);
}