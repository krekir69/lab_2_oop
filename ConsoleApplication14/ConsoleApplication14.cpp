#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
class CStr {
private:
    char* string;
    char* generate(int length)
    {
        if (length > 0 && length <= 20)
        {
            char* s = new char[length + 1];
            for (int i = 0; i < length;i++)
            {
                s[i] = 'a' + rand() % 26;
            }
            s[length] = '\0';
            return s;
        }
        else
            return 0;
    }
public:
    CStr& operator+=(CStr& obj);
    CStr() {
        int len = 1 + rand() % 20;
        string = generate(len);
    }
    CStr(const char* str) {
        string = new char[strlen(str) + 1];
        strcpy_s(string, strlen(str) + 1, str);
    }
    CStr(int length) {
        string = generate(length);
    }
    CStr(const CStr& obj) {
        string = new char[strlen(obj.string) + 1];
        strcpy_s(string, strlen(obj.string) + 1, obj.string);
    }
    ~CStr() {
        delete[] string;
    }
    CStr& operator=(const CStr& obj)
    {
        if (this != &obj) {
            delete[] string;
            int len = strlen(obj.string);
            string = new char[len + 1];
            strcpy_s(string, len + 1, obj.string);
        }
        return *this;
    }
    CStr& operator=(const char* str)
    {
        delete[] string;
        if (str == nullptr) {
            string = new char[1];
            string[0] = '\0';
        }
        else {
            int len = strlen(str);
            string = new char[len + 1];
            strcpy_s(string, len + 1, str);
        }
        return *this;
    }
    CStr operator+(const CStr& obj) const
    {
        int len1 = strlen(this->string);
        int len2 = strlen(obj.string);
        int newlen = len1 + len2;
        char* buff = new char[newlen + 1];
        strcpy_s(buff, newlen + 1, this->string);
        strcat_s(buff, newlen + 1, obj.string);
        CStr res(buff);
        delete[] buff;
        return res;
    }

    bool operator>(const CStr& obj) const;
    char& operator[](int index)
    {
        return string[index];
    }
    int get_length() const
    {
        return strlen(string);
    }
    friend ostream& operator<<(ostream& stream, CStr& obj);
    friend istream& operator>>(istream& stream, CStr& obj);
};
ostream& operator<<(ostream& stream, CStr& obj)
{
    stream << obj.string;
    return stream;
}
bool CStr::operator>( const CStr& obj) const
{
    return (strcmp(this->string, obj.string) > 0);
}
istream& operator>>(istream& stream, CStr& obj)
{

    const int BUF = 1024;
    char buffer[BUF];
    stream >> buffer;
    delete[] obj.string;
    int len = strlen(buffer);
    obj.string = new char[len + 1];
    strcpy_s(obj.string, len + 1, buffer);
    return stream;
}
CStr& CStr::operator+=(CStr& obj)
{
    int len1 = strlen(this->string);
    int len2 = strlen(obj.string);
    char* buff = new char[len1 + len2 + 1];
    strcpy_s(buff, len1 + len2 + 1, this->string);
    strcat_s(buff, len1 + len2 + 1, obj.string);
    delete[] string;
    string = buff;
    return *this;
}


template<typename T>
class TVector {
private:
    int length; 
    T* data;       

public:
   
    TVector(int len = 1) : length(len) {
        if (len == 0) {
            cout << "Длина должна быть больше 0" << endl;
            exit(1);
        }
        data = new T[length];
    }

    TVector(const TVector& other) : length(other.length) {
        data = new T[length];
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    ~TVector() {
        delete[] data;
    }

    void setLength(int newLength) {
        if (newLength == 0) {
            cout << "Длина должна быть больше 0" << endl;
            exit(1);
        }
        T* newData = new T[newLength];
        int copyLength = (newLength < length) ? newLength : length;
        for (int i = 0; i < copyLength; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        length = newLength;
    }

    TVector& operator=(const TVector& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new T[length];
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    TVector& operator+=(const TVector& other) {
        if (length != other.length) {
            cout << "Вектора должны иметь одинаковую длину" << endl;
            exit(1);
        } 
        for (int i = 0; i < length; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    T& operator[](int index) {
        if (index >= length)
        {
            cout << "Индекс вне диапазона" << endl;
            exit(1);
        } 
        return data[index];
    }

    const T& operator[](int index) const {
        if (index >= length) 
        {
            cout << "Индекс вне диапазона" << endl;
            exit(1);
        }
        return data[index];
    }

    friend ostream& operator<<(ostream& os, const TVector& vec) {
        os << "[";
        for (int i = 0; i < vec.length; ++i) {
            os << vec.data[i];
            if (i < vec.length - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend istream& operator>>(istream& is, TVector& vec) {
        for (int i = 0; i < vec.length; ++i) {
            is >> vec.data[i];
        }
        return is;
    }

    int getLength() const { return length; }
};


template<typename T>
class TMatrix {
private:
    int rows, cols;     
    TVector<T>* data;      

public:
    TMatrix(int r = 1, int c = 1) : rows(r), cols(c) {
        if (r == 0 || c == 0)
        {
            cout << "Число строк и столбцов должно быть больше 0" << endl;
            exit(1);
        } 
        data = new TVector<T>[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = TVector<T>(cols);
        }
    }

    TMatrix(const TMatrix& other) : rows(other.rows), cols(other.cols) {
        data = new TVector<T>[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = other.data[i];
        }
    }

    ~TMatrix() {
        delete[] data;
    }

    TMatrix& operator=(const TMatrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new TVector<T>[rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    TMatrix& operator+=(const TMatrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Матрицы должны иметь одинаковые размеры" << endl;
            exit(1);
            
        }
        for (int i = 0; i < rows; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    TVector<T>& operator[](int row) {
        if (row >= rows)
        {
            cout << "Индекс строки вне диапазона" << endl;
            exit(1);
        }
        return data[row];
    }

    const TVector<T>& operator[](int row) const {
        if (row >= rows) 
        {
            cout << "Индекс строки вне диапазона" << endl;
            exit(1);
        }
        return data[row];
    }

    friend ostream& operator<<(ostream& os, const TMatrix& mat) {
        for (int i = 0; i < mat.rows; ++i) {
            os << mat.data[i] << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, TMatrix& mat) {
        for (int i = 0; i < mat.rows; ++i) {
            is >> mat.data[i];
        }
        return is;
    }
};


int main() {
    setlocale(LC_ALL, "RU");
 
    
            cout << "Тестируем TVector<double>:" << endl;
        TVector<double> v1(3);
        v1[0] = 1.0; v1[1] = 2.0; v1[2] = 3.0;
        cout << "v1 = " << v1 << endl;
        TVector<int> arr[5];
        arr[2] = 25;
        arr[3] = 5;

        TVector<double> v2(v1); 
        v2[0] = 4.0; v2[1] = 5.0; v2[2] = 6.0;
        cout << "v2 = " << v2 << endl;

        v1 += v2;
        cout << "v1 + v2 = " << v1 << endl;
        
            cout << "\nТестируем TMatrix<int>:" << endl;
        TMatrix<int> m1(2, 3);
        m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
        m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
        cout << "m1 =" << endl << m1;

        TMatrix<int> m2(m1); 
        m2[0][0] = 7; m2[0][1] = 8; m2[0][2] = 9;
        m2[1][0] = 10; m2[1][1] = 11; m2[1][2] = 12;
        cout << "m2 =" << endl << m2;

        m1 += m2;
        cout << "m1 + m2 =" << endl << m1;

            cout << "\nТестирование TVector<CStr>" << endl;
        TVector<CStr> cv1(2);
        cv1[0] = CStr("Hello"); cv1[1] = CStr(" ");
        TVector<CStr> cv2(2);
        cv2[0] = CStr("WORLD"); cv2[1] = CStr("!");
        cout << "cv1 = " << cv1 << endl;
        cout << "cv2 = " << cv2 << endl;
        cv1 += cv2;
        cout << "cv1 + cv2 = " << cv1 << endl;
        cout << "cv1[0][0] = '" << cv1[0][0] << "'" << endl;

            cout << "\n Тестирование TMatrix<CStr>" << endl;
        TMatrix<CStr> cm1(2, 2);
        cm1[0][0] = CStr("A"); cm1[0][1] = CStr("B");
        cm1[1][0] = CStr("C"); cm1[1][1] = CStr("D");
        cout << "cm1 =" << endl << cm1;

        TMatrix<CStr> cm2(2, 2);
        cm2[0][0] = CStr("1"); cm2[0][1] = CStr("2");
        cm2[1][0] = CStr("3"); cm2[1][1] = CStr("4");
        cout << "cm2 =" << endl << cm2;
        cm1 += cm2;
        cout << "cm1 + cm2 =" << endl << cm1;

        cout << "cm1[0][0] = '" << cm1[0][0] << "'" << endl; 
   

    return 0;
}