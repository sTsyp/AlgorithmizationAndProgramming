//08.04.2023
//Цыплаков Александр Александрович
//БПМ214
//Вариант 3
#include <iostream>
#include <vector>
#include <string>
#include <memory>

//класс команды
class command {
public:
    virtual ~command() {}
    virtual void Execute() = 0;
    virtual void Unexecute() = 0;
};

// создание квадратной фигуры
class ссommand : public command {
public:
    ссommand(std::vector<int>& shapes, int id, int size)
        : shapes_(shapes), id_(id), size_(size) {}
    void Execute() override {
        shapes_.push_back(size_);
        std::cout << "Создание квадрата " << id_ << " размера " << size_ << std::endl;
    }
    void Unexecute() override {
        shapes_.pop_back();
        std::cout << "Отмена создания квадрата " << id_ << std::endl;
    }
private:
    std::vector<int>& shapes_;
    int id_;
    int size_;
};

//изменение размера квадрата
class scommand : public command {
public:
    scommand(std::vector<int>& shapes, int id, int size_delta)
        : shapes_(shapes), id_(id), size_delta_(size_delta), old_size_(0) {}
    void Execute() override {
        if (id_ >= 0 && id_ < shapes_.size()) {
            old_size_ = shapes_[id_];
            shapes_[id_] += size_delta_;
            std::cout << "Масштабированный " << id_ << " to size " << shapes_[id_] << std::endl;
        }
    }
    void Unexecute() override {
        if (id_ >= 0 && id_ < shapes_.size()) {
            shapes_[id_] = old_size_;
            std::cout << "Отмена масштабирования квадрата " << id_ << " to size " << shapes_[id_] << std::endl;
        }
    }
private:
    std::vector<int>& shapes_;
    int id_;
    int size_delta_;
    int old_size_;
};

//отмена и повтор команд
class invoker {
public:
    void ExecuteCommand(command* cmd) {
        cmd->Execute();
        executed_commands_.push_back(std::unique_ptr<command>(cmd));
        undone_commands_.clear();
    }
    void Undo() {
        if (!executed_commands_.empty()) {
            std::unique_ptr<command>& cmd = executed_commands_.back();
            cmd->Unexecute();
            undone_commands_.push_back(std::move(cmd));
            executed_commands_.pop_back();
        }
    }
    void Redo() {
        if (!undone_commands_.empty()) {
            std::unique_ptr<command>& cmd = undone_commands_.back();
            cmd->Execute();
            executed_commands_.push_back(std::move(cmd));
            undone_commands_.pop_back();
        }
    }
private:
    std::vector<std::unique_ptr<command>> executed_commands_;
    std::vector<std::unique_ptr<command>> undone_commands_;
};

int main() {
    std::vector<int> shapes;
    invoker invoker;
    int id = 0;

    // Создание квадрата
    invoker.ExecuteCommand(new ссommand(shapes, id++, 10));  // создание квадрата 0 размера 10
    invoker.ExecuteCommand(new ссommand(shapes, id++, 5));   // создание квадрата 1 размера 5

    // Изменение размера квадрата
    invoker.ExecuteCommand(new scommand(shapes, 0, 3)); // масштабированный квадрат 0 до размера 13
    invoker.ExecuteCommand(new scommand(shapes, 1, -2));// масштабированный квадрат 1 до размера 3

    // Отмена и повтор команд
    invoker.Undo();         // отмена масштабирования квадрата 1 до размера 5
    invoker.Redo();         // масштабирование квадрата 1 до размера 3
    invoker.Undo();         // отмена масштабирования квадрата 1 до размера 5
    invoker.Undo();         // отмена масштабирования квадрата 0 до размера 10
    invoker.Undo();         // отмена создания квадрата 1
    invoker.Undo();         // отмена создания квадрата 0

    return 0;
}
//В данной реализации паттерна определен абстрактный класс command, который определяет интерфейс команды, включающий методы Execute() и Unexecute(), которые выполняют и отменяют выполнение команды соответственно.Затем определены две конкретные команды: ссommand и scommand. Команда ссommand создает квадратную фигуру определенного размера, а команда scommand изменяет размер указанной квадратной фигуры на заданную величину.Класс invoker представляет собой объект, который выполняет команды, и имеет методы ExecuteCommand(), Undo() и Redo(), которые выполняют команды, отменяют последнюю выполненную команду и повторяют последнюю отмененную команду соответственно. В качестве аргумента ExecuteCommand() передается указатель на объект команды.В функции main() создаются объекты команд и вызываются методы ExecuteCommand(), Undo() и Redo() объекта invoker для демонстрации работы паттерна. Вектор shapes представляет коллекцию квадратных фигур.
