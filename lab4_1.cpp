#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class VectorInt {
private:
    int* data;
    int size;
    int codeError;
    static int objectCount;

public:
    // Конструктори
    VectorInt() : size(1), codeError(0) {
        data = new int[1] {0};
        objectCount++;
    }

    VectorInt(int s) : size(s), codeError(0) {
        data = new int[s] {0};
        objectCount++;
    }

    VectorInt(int s, int value) : size(s), codeError(0) {
        data = new int[s];
        for (int i = 0; i < s; i++) data[i] = value;
        objectCount++;
    }

    VectorInt(const VectorInt& other) : size(other.size), codeError(other.codeError) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        objectCount++;
    }

    ~VectorInt() {
        delete[] data;
        objectCount--;
    }

    VectorInt& operator=(const VectorInt& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        codeError = other.codeError;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }

    VectorInt operator-() const {
        VectorInt temp(*this);
        for (int i = 0; i < size; i++) temp.data[i] = -data[i];
        return temp;
    }

    VectorInt& operator++() {
        for (int i = 0; i < size; i++) data[i]++;
        return *this;
    }

    VectorInt operator++(int) {
        VectorInt temp(*this);
        ++(*this);
        return temp;
    }

    VectorInt& operator--() {
        for (int i = 0; i < size; i++) data[i]--;
        return *this;
    }

    VectorInt operator--(int) {
        VectorInt temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const { return size == 0; }

    VectorInt operator~() const {
        VectorInt temp(*this);
        for (int i = 0; i < size; i++) temp.data[i] = ~data[i];
        return temp;
    }

    VectorInt operator+(const VectorInt& other) const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = data[i] + other.data[i];
        return temp;
    }

    VectorInt operator-(const VectorInt& other) const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = data[i] - other.data[i];
        return temp;
    }

    VectorInt operator*(int scalar) const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = data[i] * scalar;
        return temp;
    }

    VectorInt operator/(int scalar) const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = data[i] / scalar;
        return temp;
    }

    VectorInt operator%(int scalar) const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = data[i] % scalar;
        return temp;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 1;
            return data[size - 1];
        }
        return data[index];
    }

    bool operator==(const VectorInt& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorInt& other) const {
        return !(*this == other);
    }

    void operator()() const {
        std::cout << "Вектор має " << size << " елементів.\n";
    }

    static int getObjectCount() {
        return objectCount;
    }

    // Оголошення дружніх функцій
    friend std::ostream& operator<<(std::ostream& out, const VectorInt& v);
    friend std::istream& operator>>(std::istream& in, VectorInt& v);
};

int VectorInt::objectCount = 0;

// Дружні функції ПОЗА класом
std::ostream& operator<<(std::ostream& out, const VectorInt& v) {
    for (int i = 0; i < v.size; i++) out << v.data[i] << " ";
    return out;
}

std::istream& operator>>(std::istream& in, VectorInt& v) {
    for (int i = 0; i < v.size; i++) in >> v.data[i];
    return in;
}

// Тестування
int main() {
    VectorInt v1(5, 10);
    VectorInt v2(5, 2);
    VectorInt v3 = v1 + v2;

    std::cout << "v1: " << v1 << "\nv2: " << v2 << "\nv3 (v1 + v2): " << v3 << "\n";
    std::cout << "Кількість об'єктів: " << VectorInt::getObjectCount() << "\n";
    return 0;
}
