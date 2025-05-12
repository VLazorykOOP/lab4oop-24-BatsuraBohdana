#include <iostream>
#include <string>
using namespace std;

class NumberWords {
private:
    int* keys;
    string* values;
    int size;
    int count;
    int codeError;

public:
    NumberWords(int maxSize = 100) : size(maxSize), count(0), codeError(0) {
        keys = new int[size];
        values = new string[size];
    }

    ~NumberWords() {
        delete[] keys;
        delete[] values;
    }

    void addAssociation(int number, const string& word) {
        if (count < size) {
            keys[count] = number;
            values[count] = word;
            count++;
            codeError = 0;
        } else {
            codeError = -2; // масив повний
        }
    }

    string operator[](int number) {
        for (int i = 0; i < count; ++i) {
            if (keys[i] == number) {
                codeError = 0;
                return values[i];
            }
        }
        codeError = -1;
        return "Невідомо";
    }

    int getErrorCode() const { return codeError; }

    void printAll() const {
        cout << "Список чисел від 1 до 100:\n";
        for (int i = 0; i < count; ++i) {
            cout << keys[i] << " = " << values[i] << "\n";
        }
    }
};

// Генерація чисел від 1 до 100 з українським записом
NumberWords createNumberWordAssoc() {
    NumberWords nw;

    string ones[] = {
        "", "один", "два", "три", "чотири", "п’ять", "шість", "сім", "вісім", "дев’ять"
    };
    string teens[] = {
        "десять", "одинадцять", "дванадцять", "тринадцять", "чотирнадцять",
        "п’ятнадцять", "шістнадцять", "сімнадцять", "вісімнадцять", "дев’ятнадцять"
    };
    string tens[] = {
        "", "", "двадцять", "тридцять", "сорок", "п’ятдесят",
        "шістдесят", "сімдесят", "вісімдесят", "дев’яносто"
    };

    for (int i = 1; i <= 100; ++i) {
        string word;
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
        nw.addAssociation(i, word);
    }

    return nw;
}

int main() {
    NumberWords dict = createNumberWordAssoc();

    dict.printAll();

    int query;
    cout << "\nВведіть число (1-100): ";
    cin >> query;

    string result = dict[query];
    if (dict.getErrorCode() == 0) {
        cout << "Число " << query << " прописом: " << result << "\n";
    } else {
        cout << "Помилка: число не знайдено.\n";
    }

    return 0;
}
