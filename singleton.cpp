#include<iostream>
using namespace std;

class Singleton{
    Singleton *ref=nullptr;
    /// @brief 
    Singleton(){
        cout<<"Instance created for the first time\n";
    }
    public:
     Singleton* createInstance(){
        if(ref==nullptr){
            ref=new Singleton();
            return ref;
        }
        else{
            cout<<"already instantiated, no new instance created\n";
            return ref;

        }

    }
};

int main(){
    //Singleton *s=createInstance();
}