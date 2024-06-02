//
//  main.cpp
//  кп4-5
//
//  Created by Александр Цыплаков on 02.12.2022.
//

#include <iostream>
#include <set>  // заголовочный файл множеств
#include <iterator>
#include <cstdlib>
using namespace std;
template<typename T>
class Set{
public:
    T* array;
    size_t size;
    size_t capacity;
    
    //пустой конструктор
    Set(){
        array = new T[1];
        size = 0;
        capacity = 1;
    }
    
    
    //инициализация
    Set(initializer_list<T>& lst){
        size = lst.size();
        capacity = 2 * size;
        array = new T[capacity];
        
        for (size_t i = 0; i < size;i++) {
            array[i] = *(lst.begin() + i);
        }
    }
    
    
    Set(const Set& s){ // копирования
        size = s.size; //копируем размерность множества
        array = new int[size];
        memcpy(array, s.array, sizeof(int) * size); //копируем данные
    }
    
    
    // функции члены класса
    size_t getSize() const{ // размерность множества
        return size;
    }
    
   
    void insert(const T element) { // добавление элемента
        if (size >= capacity) memory();
        array[size] = element;
        size += 1;
    }
    
    
    bool exclude(T n){ // удалить элемент
        if(this->isInSet(n).first){
            size_t position = isInSet(n).second;
            for (size_t i = position + 1; i < size; i++) {
                array[i - 1] = array[i];
            }
            --size;
            return true;
        }
        else{
            return false;
        }
    }
    
    
    bool isEmpty(){ //проверка на пустоту
        return size;
    }
    
    pair<bool, size_t> isInSet(T n){// есть такой элемент?
        for (size_t i = 0; i < size; i++) //ищем символ в массиве
            if (array[i] == n) return make_pair(true, i);
        return make_pair(false, -1);
    }
    
    
    // операторы члены класса
    Set& operator = (const Set& s){ // присваивание множеств
        //аналогично конструктору копирования
        size = s.size;
        array = new int[size];
        memcpy(array, s.array, sizeof(int) * size);
        return *this;
    }
    
    
    // выделение памяти
    void memory(){
        capacity *= 2;
        T* tmp = array;
        array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            array[i] = tmp[i];
        }
        delete[] tmp;
    }
        
    // операции ввода
   friend ostream& operator << (ostream& out, Set<T>& mySet) {
        for (size_t i = 0; i < mySet.size; i++) {
            out << mySet.array[i] << " ";
        }
        return out;
    }

    // операции вывода
    friend ifstream& operator >> (ifstream& in, const Set<T>& mySet) {
        for (size_t i = 0; i < mySet.size; i++) {
            in >> mySet.array[i];
        }
        return in;
    }

    // деструктор
    ~Set() {
        delete[] array;
    }
};

class Time {
public:
    int minute;
    int second;
    // конструктор
    Time() {
        minute = 0;
        second = 0;
    }

    Time(const int minute1, const int second1) {
        minute = minute1;
        second = second1;
    }
    //копирование
    Time(const Time& other) {
        minute = other.minute;
        second = other.second;
    }

    //перемещение
    Time(Time&& other){
        minute = other.minute;
        second = other.second;
        other.minute = 0;
        other.second= 0;
    }
    //назначение
    Time& operator=(const Time& other) {
        if (this != &other) {
            minute = other.minute;
            second = other.second;
        }
        return *this;
    }

    // операция назначения
    Time& operator=(Time&& other) {
        if (this != &other) {
            minute = other.minute;
            second = other.second;
            other.minute = 0;
            other.second = 0;
        }
        return *this;
    }

    //  операция ввода
    friend ostream& operator << (ostream& out, const Time& value) {
        out << value.minute << ":" << value.second;
        return out;
    }

    // операция вывода
    friend istream& operator >> (istream& in, Time& value) {
        in >> value.minute>> value.second;
        return in;
    }
};



int main(){
    setlocale(LC_ALL, "Russian");
    // testing program for container class
    initializer_list<double>q = {5.5, 15.5};
    Set<double> mySet1(q);
    cout << "Визуализация множества: ";
    cout << mySet1 << "\n";
    
    cout << "Принадлежит ли число 5.5 множеству(1 - принадлежит, 0 - нет)? ";
    cout << mySet1.isInSet(5.5).first << "\n";
    
    mySet1.insert(10);
    cout << "Добавляем во множество число: 10, получим: ";
    cout << mySet1 << "\n";

    mySet1.exclude(10);
    cout << "Удаляем добавленный элемент, получим: ";
    cout << mySet1 << "\n";

    cout << "Размер множества: ";
    cout << mySet1.getSize() << "\n";

    cout << "Проверка на пустоту, если пуст - 0, в обратном случае - 1: ";
    cout << mySet1.isEmpty() << "\n";

    initializer_list<float>w = {1e4, 1e5};
    Set<float> mySet2(w);
    cout << "Множество с типом данных float: ";
    cout << mySet2 << "\n";

    initializer_list<int>e = {2, 3};
    Set<int> mySet3(e);
    cout << "Множество с типом данных int: ";
    cout << mySet3 << "\n";

    cout <<"\nПроверка работы пользовательского класса\n";
    Time vremya(1, 11);
    cout << "Время: ";
    cout << vremya << "\n";

    initializer_list<Time>r = {Time(6,45),Time(1,31),Time(10,11)};
    Set<Time> mySet4(r);
    cout << "Истанцируем шаблон: ";
    cout << mySet4 << "\n";
    return 0;
}

