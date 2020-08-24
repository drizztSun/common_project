#include<stdio.h>
#include <iostream>
char* caption = "C++ learning ";

class Tdpointer{
public:

    Tdpointer(): xp(0), yp(0) {}

    Tdpointer(int x, int y){
        std::cout << "Tdpointer constructor" << "\n";
        xp = x;
        this->yp = y;
    }

    ~Tdpointer() {
        std::cout<<"tdpointer destructor" << std::endl;
    }

    // copy-constructor
    Tdpointer(Tdpointer& a) {
        std::cout<<"copy-constructor"<<std::endl;
        this->xp = a.xp;
        this->yp = a.yp;
    }

    // move-constructor
    Tdpointer(Tdpointer&& a) {
        std::cout<<"move-constructor"<<std::endl;
        this->xp = a.xp;
        this->yp = a.yp;
        this->return_val = a.return_val;
        a.return_val = nullptr;
    }

    // assignment operator
    Tdpointer& operator=(const Tdpointer& a) {
        std::cout<<"assignment operator"<<std::endl;
        this->xp = a.xp;
        this->yp = a.yp;
    }

    int xp;
    int yp;
    Tdpointer* return_val;
};



int main(){
    printf("hello world\n");

    Tdpointer y(2, 3);
    {
        Tdpointer x(1, 2);

        Tdpointer b = x;

        Tdpointer c = Tdpointer(1, 10);

        b = y;
    }
    std::cout << "End of scope \n";     

    

    return 1;
}
