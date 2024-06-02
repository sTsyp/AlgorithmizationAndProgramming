#include <thread>
#include <iostream>
#include <chrono>
#include <random>

// Задание 1
void print_time() {
  auto time_now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(time_now);
  std::cout << std::ctime(&now_c) << std::endl;
}

// Задание 2
class PrintTime {
public:
  void operator()() const {
    std::time_t now = std::time(nullptr);
    std::cout << std::ctime(&now) << std::endl;
  }
};

// Задание 3
void get_time(std::chrono::system_clock::time_point& tp) {
  tp = std::chrono::system_clock::now();
}

void task() {
  std::chrono::system_clock::time_point tp1, tp2;
  get_time(tp1);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  get_time(tp2);
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
}

// Задание 4
void print_id(int id) {
  std::cout << "Thread " << id << " started" << std::endl;
}

// Задание 5
void print_random_numbers(int num) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);
  for (int i = 0; i < num; i++) {
    std::cout << distrib(gen) << " ";
  }
  std::cout << std::endl;
}

// Задание 6
void print_num(int num, int delay) {
  for (int i = 0; i < num; i++) {
    std::cout << i + 1 << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  std::cout << std::endl;
}

// Задание 7
void sum_array(const int* arr, int size, int& result) {
  result = 0;
  for (int i = 0; i < size; i++) {
    result += arr[i];
  }
}

int main() {
  // Задание 1: вызов функции print_time()
  std::thread t1(print_time);
  t1.join();

  // Задание 2: создание объекта класса PrintTime и вызов его метода
  PrintTime pt;
  std::thread t2(pt);
  t2.join();

  // Задание 3: запуск функции task() в новом потоке
  std::thread t3(task);
  t3.join();

  // Задание 4: запуск функции print_id() в нескольких потоках
  const int num_threads = 5;
  std::thread t4[num_threads];
  for (int i = 0; i < num_threads; i++) {
    t4[i] = std::thread(print_id, i);
  }
  for (int i = 0; i < num_threads; i++) {
    t4[i].join();
  }

  // Задание 5: запуск функции print_random_numbers() в новом потоке
  std::thread t5(print_random_numbers, 10);
  t5.join();

  // Задание 6: запуск функции print_num() в новом потоке
  std::thread t6(print_num, 10, 100);
  t6.join();

  // Задание 7: запуск функции sum_array() в новом потоке
  const int arr_size = 5;
  int arr[arr_size] = {1, 2, 3, 4, 5};
  int result = 0;
  std::thread t7(sum_array, arr, arr_size, std::ref(result));
  t7.join();
  std::cout << "Sum of array elements: " << result << std::endl;

  return 0;
}
