#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class password_generator {
public:
    virtual std::string generate() = 0;
    virtual size_t length() const = 0;
    virtual std::string allowed_chars() const = 0;
    virtual void add(password_generator* gen) {}
    virtual ~password_generator() = default;
};

class basic_password_generator : public password_generator {
public:
    explicit basic_password_generator(size_t min_length) : min_length_(min_length) {}
    std::string generate() override {
        std::string password;
        password.reserve(min_length_);
        std::generate_n(std::back_inserter(password), min_length_, [this]() {
            static std::mt19937 eng{ std::random_device{}() };
            std::uniform_int_distribution<std::string::size_type> dist(0, allowed_chars_.size() - 1);
            return allowed_chars_[dist(eng)];
        });
        return password;
    }
    size_t length() const override {
        return min_length_;
    }
    std::string allowed_chars() const override {
        return allowed_chars_;
    }
protected:
    std::string allowed_chars_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t min_length_;
};

class digit_generator : public basic_password_generator {
public:
    explicit digit_generator(size_t min_length) : basic_password_generator(min_length) {
        allowed_chars_ = "0123456789";
    }
};

class symbol_generator : public basic_password_generator {
public:
    explicit symbol_generator(size_t min_length) : basic_password_generator(min_length) {
        allowed_chars_ = "!@#$%^&*()_-+={}[]\\|:;\"',.?/~`";
    }
};

class upper_letter_generator : public basic_password_generator {
public:
    explicit upper_letter_generator(size_t min_length) : basic_password_generator(min_length) {
        allowed_chars_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
};

class lower_letter_generator : public basic_password_generator {
public:
    explicit lower_letter_generator(size_t min_length) : basic_password_generator(min_length) {
        allowed_chars_ = "abcdefghijklmnopqrstuvwxyz";
    }
};

class composite_password_generator : public password_generator {
public:
    std::string generate() override {
        std::string password;
        for (auto& gen : generators_) {
            password += gen->generate();
        }
        std::shuffle(password.begin(), password.end(), std::mt19937{ std::random_device{}() });
        return password;
    }
    size_t length() const override {
        size_t total_length = 0;
        for (auto& gen : generators_) {
            total_length += gen->length();
        }
        return total_length;
    }
    std::string allowed_chars() const override {
        std::string allowed_chars;
        for (auto& gen : generators_) {
            allowed_chars += gen->allowed_chars();
        }
        return allowed_chars;
    }
    void add(password_generator* gen) override {
        generators_.push_back(gen);
    }
private:
    std::vector<password_generator*> generators_;
};

int main() {
    composite_password_generator password;

    // добавляем генераторы символов
    password.add(new digit_generator(2));
    password.add(new symbol_generator(2));
    password.add(new upper_letter_generator(2));
    password.add(new lower_letter_generator(2));

    std::cout << "Случайный пароль: " << password.generate() << '\n';

    return 0;
}
