#include <thread>
#include <mutex>
#include <future>
#include <iostream>
using namespace std;

class ThreadSafeLogger{

public:
    static void logger(const string& msg){
        static mutex mut;
        {
            unique_lock<mutex>lock (mut);
            cout <<msg<<endl;
        }
    }
    ThreadSafeLogger(const ThreadSafeLogger& )=delete;
    ThreadSafeLogger  & operator= (const ThreadSafeLogger&) =delete;
private:
    ThreadSafeLogger();
    ~ThreadSafeLogger();
};
int main(){
    mutex mut;
    int i=0;
    const int MAX_COUNT = 100;
    auto f = [&](size_t thread_id){
        int sum =0;
        while(true){
            {
            unique_lock<mutex> lock(mut);
            if(i ==MAX_COUNT)break;;
            sum+=i++;
            }
            this_thread::sleep_for(chrono::milliseconds(rand()%30));
            string msg = "id="+to_string(thread_id)+",i="+to_string(i)+",sum="+to_string(sum);
            ThreadSafeLogger::logger(msg);
        }
        return sum;
    };
    
    auto future1 = async(launch::async,f,1);
    auto future2 = async(launch::async,f,2);
    int sum1 = future1.get();
    int sum2 = future2.get();
    cout <<"sum1:"<<sum1;
    cout <<"sum2:"<<sum2;
}