#include <iostream>
#include <vector>
#include <cstring>
using namespace std;



class Shape {
    char * parr ;
public:
    Shape() {
        parr = new char[4];
        parr = "abc";
    };
    Shape(const char *source) {
        int len = std::strlen(source);
        parr = new char[(len+1)];
        std::strcpy(parr, source);
    };
    Shape(const Shape & src){
        int len = std::strlen(src.parr);
        parr = new char[(len+1)];
        std::strcpy(parr, src.parr);
    };

    virtual double Area() = 0;
};

double Shape::Area() {
    return 0;
}

class Circle : public Shape {
    double R1;


public:
    Circle(double r1) {
        R1 = r1;
    }

    double Area() {
        cout << "shape circle" << '\n';
        double S1 = 3.14 * R1 * R1;
        cout << S1 << endl;
        return S1;
    }


    Circle(const char source) : Shape(&source){
        int len = std::strlen(source);
        parr = new char[(len+1)];
        std::strcpy(parr, source);
    };

};

class Square: public Shape{
    
    double R2;

public:
        Square(double r2){
            R2 = r2;
        }

        double Area(){
            cout << "shape square" << '\n';
            double S2 = R2 * R2;
            cout << S2 << '\n';
            return S2;
        }
};

class Triangle: public Shape{
    
    double a;
    double h;

public:
        Triangle(double A, double H){
            a = A;
            h = H;
        }

        double Area(){
            cout << "shape triaangle" << '\n';
            double S3 = (a * h)/2;
            cout << S3 << '\n';
            return S3;
        }
};

int main() {
    Circle circle(7);
    circle.Area();
    
    Square square(9);
    square.Area();
    
    Triangle triangle(9, 10);
    triangle.Area();
    
    Shape* arr[3] = {&circle, &triangle, &square};
    //arr[0]->Area();
    //arr[1]->Area();
    //arr[2]->Area();

}
