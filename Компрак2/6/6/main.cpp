//
//  main.cpp
//  6
//
//  Created by Александр Цыплаков on 19.02.2023.
//

#include <iostream>
#include <string>

using namespace std;

class PassVal {
public:
    virtual ~PassVal() {}
    virtual bool val(const string& pass) = 0;
};

class LengthVal : public PassVal {
public:
    virtual bool val(const string& pass) {
        return pass.length() >= 10;
    }
};

class NotAlphVal : public PassVal {
public:
    NotAlphVal(PassVal* val) : val_(val) {}
    virtual ~NotAlphVal() { delete val_; }
    virtual bool val(const string& pass) {
        if (!val_->val(pass)) {
            return false;
        }
        for (char c : pass) {
            if (!isalpha(c)) {
                return true;
            }
        }
        return false;
    }
private:
    PassVal* val_;
};

class NumberVal : public PassVal {
public:
    NumberVal(PassVal* val) : val_(val) {}
    virtual ~NumberVal() { delete val_; }
    virtual bool val(const string& pass) {
        if (!val_->val(pass)) {
            return false;
        }
        for (char c : pass) {
            if (isdigit(c)) {
                return true;
            }
        }
        return false;
    }
private:
    PassVal* val_;
};

class BigSmallVal : public PassVal {
public:
    BigSmallVal(PassVal* val) : val_(val) {}
    virtual ~BigSmallVal() { delete val_; }
    virtual bool val(const string& pass) {
        if (!val_->val(pass)) {
            return false;
        }
        bool big = false;
        bool small = false;
        for (char c : pass) {
            if (isupper(c)) {
                big = true;
            } else if (islower(c)) {
                small = true;
            }
        }
        return big && small;
    }
private:
    PassVal* val_;
};

int main() {
    string pass;
    cout << "Enter password: ";
    cin >> pass;
    PassVal* val = new LengthVal();
    val = new NotAlphVal(val);
    val = new NumberVal(val);
    val = new BigSmallVal(val);
    if (val->val(pass)) {
        cout << "Password is valid." << endl;
    } else {
        cout << "Password is invalid." << endl;
    }
    delete val;
    return 0;
}


