//
//  main.cpp
//  кп1
//
//  Created by Александр Цыплаков on 22.03.2023.
//

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    // Создание телефонного справочника
    multimap<string, string> phonebook = { {"Ivanov", "111-111"}, {"Petrov", "222-222"}, {"Sidorov", "333-333"}, {"Ivanov", "444-444"}, {"Sidorov", "555-555"} };

    // Создание копии справочника
    multimap<string, string> copy(phonebook.begin(), phonebook.end());

    // Удаление 3 контактов по ключу
    phonebook.erase("Ivanov");
    phonebook.erase("Sidorov");
    phonebook.erase("Petrov");

    // Нахождение контакта по ключу и изменение номера телефона
    auto it = copy.find("Ivanov");
    if (it != copy.end())
    {
        it->second = "777-777";
    }

    // Создание карты "Избранные контакты" и добавление нескольких контактов
    map<string, string> favorites = { {"Smith", "123-456"}, {"Johnson", "789-012"} };
    favorites.insert({"Ivanov", "111-111"});
    favorites.insert({"Petrov", "222-222"});

    // Добавление новых контактов в телефонный справочник
    phonebook.insert({"Kuznetsov", "666-666"});
    phonebook.emplace("Novikov", "888-888");

    // Удаление дубликатов
    auto range = phonebook.equal_range("Ivanov");
    auto first = range.first;
    auto last = range.second;
    if (first != phonebook.end() && last != phonebook.end())
    {
        phonebook.erase(first, last);
    }

    return 0;
}

