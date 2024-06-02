#include <iostream>

class some{
    friend void set(int);
public:
    int a_;
protected:
    int b_;
private:
    int c_;
};
class child: public some {
public:
    void foo() {}
    
}

void set(int count)
{
    this->a_ = 0;
    this->b_ = 0;
    this->c_ = 0;
}

void func(some& obj)
{
    obj.a_ = 0;
    obj.b_ = 0;
    obj.c_ = 0;
}

int main()
{
    child A;
    A.a_;
    return 0;
}
