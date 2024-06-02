//
//  main.cpp
//  1
//
//  Created by Александр Цыплаков on 21.05.2023.
//

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>

std::queue<std::packaged_task<int()>> taskQueue;
std::mutex mutex;
std::condition_variable cv;

void workerThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [] { return !taskQueue.empty(); });

        std::packaged_task<int()> task = std::move(taskQueue.front());
        taskQueue.pop();

        lock.unlock();

        task(); // Выполнение задачи
    }
}

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

int main()
{
    std::thread worker(workerThread);

    // Создаем несколько packaged_task и помещаем их в очередь
    for (int i = 1; i <= 5; ++i)
    {
        std::packaged_task<int()> task(std::bind(factorial, i));
        std::future<int> future = task.get_future();

        std::unique_lock<std::mutex> lock(mutex);
        taskQueue.push(std::move(task));
        lock.unlock();

        cv.notify_one();

        std::cout << "Задача " << i << " добавлена в очередь." << std::endl;
        std::cout << "Ожидаем результат: " << future.get() << std::endl;
    }

    worker.join();
    return 0;
}
