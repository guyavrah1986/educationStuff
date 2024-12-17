#include <iostream>
#include <vector>
#include <utility>	// for std::move
#include <cstring>

using namespace std;

class MyString
{
    public:
        MyString(const char* str)
        {
            cout << "Mystring::MyString" << endl;
            setString(str);
        }

        ~MyString()
        {
            if (nullptr != m_str)
            {   
                cout << "MyString::~MyString - deleted string:" << m_str << ", this is:" << this << ", address of m_str:" << static_cast<void*>(m_str) << endl;
                delete [] m_str;
            }
        }

        MyString(const MyString& other)
        {
            if (&other == this)
            {
                cout << "MyString::MyString - self copy, returning" << endl;
                return;
            }

            delete [] m_str;
            m_size = other.m_size;
            m_str = new char[m_size + 1];
            strcpy(m_str, other.m_str);


        }

        size_t GetSize() const
        {
            return m_size;
        }

        char* GetStr() const
        {
            return m_str;
        }

    private:
        void setString(const char* str)
        {
            if (nullptr != str)
            {
                m_size = strlen(str);
                m_str = new char[m_size + 1];
                strcpy(m_str, str);
                cout << "MyString::setString - set m_str to:" << m_str << ", this is:" << this << ", size:" << m_size << ", address of m_str:" << static_cast<void*>(m_str) << endl;
            }
        }


        char* m_str;
        size_t m_size;
};

class Intvec
{
public:
    explicit Intvec(size_t size = 0)
        : m_size(size), m_data(new int[m_size])
    {
        log("Intvec");
        cout << "Intvec::Intvec - initialized vector of size:" << m_size << endl;
    }

    ~Intvec()
    {
        log("Intvec::~Intvec");
        if (m_data)
        {
            delete[] m_data;
            m_data = 0;
        }
    }

    Intvec(const Intvec& other)
        : m_size(other.m_size), m_data(new int[m_size])
    {
        log("Intvec::Intvec(copy)");
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }

    Intvec& operator=(const Intvec& other)
    {
        log("Intvec::operator=");
        if (this == &other)
        {
            return *this;
        }
            
        // Clean up current data
        delete[] m_data;

        // Set values of other
        m_size = other.m_size;
        m_data = new int[m_size];
        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
            
        return *this;
    }

    Intvec& operator=(Intvec&& other)
    {
        log("move assignment operator");
        std::swap(m_size, other.m_size);
        std::swap(m_data, other.m_data);
        return *this;
    }
private:
    void log(const char* msg)
    {
        cout << "[" << this << "] " << msg << "\n";
    }

    size_t m_size;
    int* m_data;
};

void noMoveExample()
{
    Intvec v1(20);
    Intvec v2;

    cout << "assigning lvalue...\n";
    v2 = v1;
    cout << "ended assigning lvalue...\n";
}

void MoveExample()
{
    cout << "assigning rvalue...\n";
    Intvec v2;
    v2 = Intvec(33);
    cout << "ended assigning rvalue...\n";
}

void stdVectorExample()
{
    vector<int> v1 = {1, 2, 3, 4, 5};  // Original vector
    vector<int> v2 = v1;    // deep copy `v1` into `v2`

    cout << "v1 size: " << v1.size() << endl;  // v1 is still "valid" (with old data)
    cout << "v2 size: " << v2.size() << endl;

    vector<int> v3 = {1, 2, 3};  // Original vector
    vector<int> v4 = move(v3);    // Move `v3` into `v4`

    cout << "v3 size: " << v3.size() << endl; // v3 is now empty
    cout << "v4 size: " << v4.size() << endl;
}

void myStringExample()
{
    cout << "String - start" << endl;
    MyString myStr("hello");
    cout << "String - end" << endl;
}

int main(int argc, char** argv)
{
    /*
    noMoveExample();
    MoveExample();
    stdVectorExample();
    */
    myStringExample();
    return 0;
}