#include <iostream>
#include <map>
#include <string>

class AssocArray {
private:
    std::map<int, std::string> assocMap;
    int codeError;

public:
    AssocArray() : codeError(0) {}

    void add(int number, const std::string& word) {
        assocMap[number] = word;
    }

    std::string operator[](int number) {
        if (assocMap.find(number) != assocMap.end()) {
            codeError = 0;
            return assocMap[number];
        } else {
            codeError = 1;
            return "Невідомо";
        }
    }

    std::string operator()(int number) {
        return (*this)[number];
    }

    int getCodeError() const {
        return codeError;
    }

    const std::map<int, std::string>& getMap() const {
        return assocMap;
    }

    void readFromStream(std::istream& in) {
        int number;
        std::string word;
        std::cout << "Введіть число та його назву (Ctrl+D для завершення):\n";
        while (in >> number >> word) {
            assocMap[number] = word;
        }
    }
};

// Оператор виводу поза класом
std::ostream& operator<<(std::ostream& out, const AssocArray& a) {
    for (const auto& pair : a.getMap()) {
        out << pair.first << " = " << pair.second << '\n';
    }
    return out;
}

// Оператор вводу поза класом
std::istream& operator>>(std::istream& in, AssocArray& a) {
    a.readFromStream(in);
    return in;
}

// Функція створення наповненого асоціативного масиву
AssocArray createNumberWordAssoc() {
    AssocArray arr;

    std::string ones[] = {
        "", "один", "два", "три", "чотири", "п’ять", "шість", "сім", "вісім", "дев’ять"
    };
    std::string teens[] = {
        "десять", "одинадцять", "дванадцять", "тринадцять", "чотирнадцять",
        "п’ятнадцять", "шістнадцять", "сімнадцять", "вісімнадцять", "дев’ятнадцять"
    };
    std::string tens[] = {
        "", "", "двадцять", "тридцять", "сорок", "п’ятдесят",
        "шістдесят", "сімдесят", "вісімдесят", "дев’яносто"
    };

    for (int i = 1; i <= 100; ++i) {
        std::string word;
        if (i == 100) {
            word = "сто";
        } else if (i >= 10 && i < 20) {
            word = teens[i - 10];
        } else {
            int t = i / 10;
            int o = i % 10;
            if (t > 0) word += tens[t];
            if (o > 0) {
                if (!word.empty()) word += " ";
                word += ones[o];
            }
        }
        arr.add(i, word);
    }

    return arr;
}

// Головна функція
int main() {
    AssocArray dict = createNumberWordAssoc();

    std::cout << "Асоціативний масив чисел:\n";
    std::cout << dict;

    int query;
    std::cout << "\nВведіть число для пошуку (1-100): ";
    std::cin >> query;

    std::string word = dict(query);

    if (dict.getCodeError() == 0) {
        std::cout << "Число " << query << " прописом: " << word << '\n';
    } else {
        std::cout << "Помилка: число не знайдено.\n";
    }

    return 0;
}

