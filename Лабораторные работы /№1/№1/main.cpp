#pragma optimize( "[optimization-list]", {off} )
#include <iostream> //input output
#include <iterator> //accessing elements in containers
#include <string> //working with strings
#include <vector> //working with vectors
#include <list> //a doubly linked list
#include <iomanip> //manipulator
#include <fstream> //reading and writing to a file
#include <algorithm>
#include <chrono>

using namespace std;
int sizes[10] = { 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

class TimeLogger //реализация работы со временем и запись отдельный файл
{
public:
    std::ofstream outstream;
 
    TimeLogger(const string& PATH) //конструктор принимает путь до файла куда кидаем
    {
        outstream.open(PATH); //открываем поток и задаем начальные значения
        frozen_time = std::chrono::steady_clock::now();
        current_time = std::chrono::steady_clock::now();
    }
 
    ~TimeLogger()//деструктор
    {
        outstream.close();//закрытие потока
    }
 
    void reset()//утанавливаем текущее время
    {
        set_ctime(std::chrono::steady_clock::now());
        set_ftime(std::chrono::steady_clock::now());
    }
    
    std::chrono::steady_clock::time_point get_ftime()//getr для получения frozen time
    {
        return frozen_time;
    }
    
    std::chrono::steady_clock::time_point get_ctime()//getr для получения frozen time
    {
        return current_time;
    }
    
    void set_ftime(std::chrono::steady_clock::time_point time)//setr для установления текущего времени
    {
        frozen_time = time;
    }
    
    void set_ctime(std::chrono::steady_clock::time_point time)
    {
        current_time = time;
    }
    
    void log(const string container_type, const int len, const string operation) //ввод в файл, считаем разницу зафиксированного времени и текущего
    {
        if (outstream.is_open()) //проверка на открытие
        {
            set_ctime(std::chrono::steady_clock::now());
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(get_ctime() - get_ftime());
            outstream << "container: " << container_type << "; size: " << len
                << "; operation: " << operation << "; " << "time:"
                << elapsed_ms.count() << ";\n";
        }
    }
    
private:
    std::chrono::steady_clock::time_point frozen_time;
    std::chrono::steady_clock::time_point current_time;
};
 
std::vector<int> integer_vec_reader(const string& PATH, const int len) //функции для считывания данных в
{
    std::ifstream instream(PATH);
    vector<int>result;
    if (instream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            string current;
            getline(instream, current);
            result.push_back(std::stoi(current));
        }
    }
    instream.close();
    return result;
}
 
std::list<int> integer_list_reader(const string& PATH, const int len)
{
    std::ifstream instream(PATH);
    std::list<int>result;
    if (instream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            string current;
            getline(instream, current);
            result.push_back(std::stoi(current));
        }
    }
    instream.close();
    return result;
}
 
std::vector<string>string_vec_reader(const string& PATH, const int len)
{
    std::ifstream instream(PATH);
    vector<string> result;
    if (instream.is_open())
    {
        string current;
        for (int i = 0; i < len; i++)
        {
            getline(instream, current);
            result.push_back(current);
        }
    }
    instream.close();
    return result;
}
 
std::list<string>string_list_reader(const string& PATH, const int len)
{
    std::ifstream instream(PATH);
    std::list<string> ans;
    if (instream.is_open())
    {
        string current;
        for (int i = 0; i < len; i++)
        {
            getline(instream, current);
            ans.push_back(current);
        }
    }
    instream.close();
    return ans;
}

int main()
{
    std::ifstream fout; //поток для ввода
    std::ifstream sout;
    fout.open("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt");
    sout.open("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt");
    TimeLogger logger("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/LOG.txt");
    
    //OPERATION : FIND
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        std::find(nums.begin(), nums.end(), nums[elem-1]); //ищем последний элемент из заполненного массива
        logger.log("vector<int>", elem, "std::find");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        std::find(nums.begin(), nums.end(), *next(nums.begin(), elem-1));
        logger.log("list<int>", elem, "std::find");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        std::find(nums.begin(), nums.end(), nums[elem - 1]);
        logger.log("vector<string>", elem, "std::find");
    }
    logger.outstream << endl;
    

    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        std::find(nums.begin(), nums.end(), *next(nums.begin(), elem - 1));
        logger.log("list<string>", elem, "std::find");
    }
    
    
    //OPERATION: SORT
    for (auto elem : sizes)
    {
        vector<int>nums = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        logger.reset();
        std::sort(nums.begin(), nums.end());
        logger.log("vector<int>", elem, "std::sort");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        nums.sort();
        logger.log("list<int>", elem, "std::sort");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        std::sort(nums.begin(), nums.end());
        logger.log("vector<string>", elem, "std::sort");
    }
    logger.outstream << endl;
 
    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        nums.sort();
        logger.log("list<string>", elem, "std::sort");
    }
    
    // POP_BACK
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_back();
        }
        logger.log("vector<int>", elem, "pop_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_back();
        }
        logger.log("list<int>", elem, "pop_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_back();
        }
        logger.log("vector<string>", elem, "pop_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_back();
        }
        logger.log("list<string>", elem, "pop_back()");
    }
    
    // POP_FRONT
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.erase(nums.begin());
        }
        logger.log("vector<int>", elem, "pop_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_front();
        }
        logger.log("list<int>", elem, "pop_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.erase(nums.begin());
        }
        logger.log("vector<string>", elem, "pop_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        for (int i = 0; i < elem; i++)
        {
            nums.pop_front();
        }
        logger.log("list<string>", elem, "pop_front()");
    }
    
    //PUSH_FRONT
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums_storage = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        vector<int>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.insert(nums.begin(), nums_storage[i]);
        }
        logger.log("vector<int>", elem, "push_front()");
    }
    logger.outstream << endl;
    
    //PUSH_FRONT IN RESERVE USING CASE сначала выделяем память, а потом добавляем
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums_storage = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        vector<int>nums;
        nums.reserve(elem);
        for (int i = 0; i < elem; i++)
        {
            nums.insert(nums.begin(), nums_storage[i]);
        }
        logger.log("vector<int>", elem, "push_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums_storage = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        list<int>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_front(*next(nums_storage.begin(), i));
        }
        logger.log("list<int>", elem, "push_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums_storage = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        vector<string>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.insert(nums.begin(), nums_storage[i]);
        }
        logger.log("vector<string>", elem, "push_front()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums_storage = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        list<string>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_front(*next(nums_storage.begin(), i));
        }
        logger.log("list<string>", elem, "push_front()");
    }
    logger.outstream << endl;
    
    //PUSH_BACK
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums_storage = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        vector<int>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_back(nums_storage[i]);
        }
        logger.log("vector<int>", elem, "push_back()");
    }
    logger.outstream << endl;
    
    //PUSH_BACK IN RESERVE USING CASE
    for (auto elem : sizes)
    {
        logger.reset();
        vector<int>nums_storage = integer_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        vector<int>nums;
        nums.reserve(elem);
        for (int i = 0; i < elem; i++)
        {
            nums.push_back(nums_storage[i]);
        }
        logger.log("vector<int>", elem, "push_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<int>nums_storage = integer_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/INTdata.txt", elem);
        list<int>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_back(*next(nums_storage.begin(), i));
        }
        logger.log("list<int>", elem, "push_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        vector<string>nums_storage = string_vec_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        vector<string>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_back(nums_storage[i]);
        }
        logger.log("vector<string>", elem, "push_back()");
    }
    logger.outstream << endl;
    
    for (auto elem : sizes)
    {
        logger.reset();
        list<string>nums_storage = string_list_reader("/Users/sashats/Documents/АиП/С++/Лабораторные работы /№1/№1/STRdata.txt", elem);
        list<string>nums;
        for (int i = 0; i < elem; i++)
        {
            nums.push_back(*next(nums_storage.begin(), i));
        }
        logger.log("list<string>", elem, "push_back()");
    }
    logger.outstream << endl;

    fout.close();
    sout.close();
    return 0;
}
