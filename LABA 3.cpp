//Создать класс ВitString для работы с битовыми строками длиной 64
//бита.Битовая строка должна быть представлена двумя полями типа unsigned
//long.Конструкторы инициализации должны обеспечивать инициализацию
//полей целыми числами любого типа и строкой типа string.Реализовать
//традиционные операции для работы с битами(and, or , xor, not).Для остальных
//действий реализовать перегруженные операции как методы класса.

#include <iostream>
#include <string>

class BitString {
public:
    // Constructors
    BitString() : m_high(0), m_low(0) {}
    BitString(unsigned long high, unsigned long low) : m_high(high), m_low(low) {}
    BitString(const std::string& str) {
        // Initialize the bit string from a string of 0's and 1's
        m_high = m_low = 0;
        int len = str.length();
        for (int i = 0; i < len; i++) {
            if (i < 32) {
                m_high <<= 1;
                m_high |= (str[i] - '0');
            }
            else {
                m_low <<= 1;
                m_low |= (str[i] - '0');
            }
        }
    }

    // Bitwise operations
    BitString operator~() const {
        return BitString(~m_high, ~m_low);
    }
    BitString operator&(const BitString& other) const {
        return BitString(m_high & other.m_high, m_low & other.m_low);
    }
    BitString operator|(const BitString& other) const {
        return BitString(m_high | other.m_high, m_low | other.m_low);
    }
    BitString operator^(const BitString& other) const {
        return BitString(m_high ^ other.m_high, m_low ^ other.m_low);
    }
    BitString operator<<(int n) const {
        if (n >= 64) {
            return BitString();
        }
        else if (n >= 32) {
            return BitString(m_low << (n - 32), 0);
        }
        else {
            return BitString((m_high << n) | (m_low >> (32 - n)), m_low << n);
        }
    }
    BitString operator>>(int n) const {
        if (n >= 64) {
            return BitString();
        }
        else if (n >= 32) {
            return BitString(0, m_high >> (n - 32));
        }
        else {
            return BitString(m_high >> n, (m_high << (32 - n)) | (m_low >> n));
        }
    }

    // Other methods
    std::string to_string() const {
        std::string str;
        for (int i = 0; i < 64; i++) {
            if (i < 32) {
                str += ((m_high & (1UL << (31 - i))) ? '1' : '0');
            }
            else {
                str += ((m_low & (1UL << (63 - i))) ? '1' : '0');
            }
        }
        return str;
    }

private:
    unsigned long m_high;
    unsigned long m_low;
};

// Example usage
int main() {
    BitString bs1(0x01234567, 0x89ABCDEF);
    std::cout << bs1.to_string() << std::endl;
    BitString bs2("1010101010101010101010101010101010101010101010101010101010101010");
    std::cout << bs2.to_string() << std::endl;
    BitString bs3 = bs1 & bs2;
    std::cout << bs3.to_string() << std::endl;
    BitString bs4 = bs1 << 8;
    std::cout << bs4.to_string() << std::endl;
    return 0;
}
