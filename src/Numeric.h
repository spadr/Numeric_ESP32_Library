#ifndef AUTO_NUMERIC_H
#define AUTO_NUMERIC_H

#include <Arduino.h>
#include <cmath>
#include <limits>
#include <type_traits>

class Numeric
{
public:
    class NumericException : public std::exception
    {
    public:
        enum class ErrorCode
        {
            NO_ERROR,
            OVERFLOW,
            UNDERFLOW,
            DIVISION_BY_ZERO,
            INVALID_OPERATION
        };

        NumericException(ErrorCode code) : errorCode(code) {}
        ErrorCode getErrorCode() const { return errorCode; }
        const char *what() const noexcept override
        {
            switch (errorCode)
            {
            case ErrorCode::OVERFLOW:
                return "Numeric overflow";
            case ErrorCode::UNDERFLOW:
                return "Numeric underflow";
            case ErrorCode::DIVISION_BY_ZERO:
                return "Division by zero";
            case ErrorCode::INVALID_OPERATION:
                return "Invalid operation";
            default:
                return "Unknown error";
            }
        }

    private:
        ErrorCode errorCode;
    };

    Numeric() : type(Type::Int), intValue(0) {}

    // 各型に対応するコンストラクタ
    Numeric(byte val) : type(Type::Int), intValue(val) {}
    Numeric(short val) : type(Type::Int), intValue(val) {}
    Numeric(unsigned short val) : type(Type::Int), intValue(val) {}
    Numeric(int val) : type(Type::Int), intValue(val) {}
    Numeric(unsigned int val) : type(Type::Int), intValue(val) {}
    Numeric(long val) : type(Type::Int), intValue(val) {}
    Numeric(unsigned long val) : type(Type::Int), intValue(val) {}
    Numeric(float val) : type(Type::Float), floatValue(val) {}
    Numeric(double val) : type(Type::Float), floatValue(val) {}
    Numeric(int64_t val) : type(Type::Int), intValue(val) {}

    Numeric(const Numeric &other) = default;
    Numeric(Numeric &&) noexcept = default;
    Numeric &operator=(const Numeric &) = default;
    Numeric &operator=(Numeric &&) noexcept = default;

    // 値を取得するための関数
    int64_t to_int64() const
    {
        if (type == Type::Float)
        {
            return static_cast<int64_t>(floatValue);
        }
        return intValue;
    }

    double to_double() const
    {
        if (type == Type::Int)
        {
            return static_cast<double>(intValue);
        }
        return floatValue;
    }

    // 演算子のオーバーロード
    Numeric operator+(const Numeric &other) const
    {
        if (type == Type::Float || other.type == Type::Float)
        {
            return Numeric(to_double() + other.to_double());
        }
        else
        {
            int64_t result = intValue + other.intValue;
            // オーバーフローチェック
            if ((intValue > 0 && other.intValue > 0 && result < 0) ||
                (intValue < 0 && other.intValue < 0 && result > 0))
            {
                throw NumericException(NumericException::ErrorCode::OVERFLOW);
            }
            return Numeric(result);
        }
    }

    Numeric operator-(const Numeric &other) const
    {
        if (type == Type::Float || other.type == Type::Float)
        {
            return Numeric(to_double() - other.to_double());
        }
        else
        {
            int64_t result = intValue - other.intValue;
            // オーバーフローチェック
            if ((intValue > 0 && other.intValue < 0 && result < 0) ||
                (intValue < 0 && other.intValue > 0 && result > 0))
            {
                throw NumericException(NumericException::ErrorCode::OVERFLOW);
            }
            return Numeric(result);
        }
    }

    Numeric operator*(const Numeric &other) const
    {
        if (type == Type::Float || other.type == Type::Float)
        {
            return Numeric(to_double() * other.to_double());
        }
        else
        {
            int64_t result = intValue * other.intValue;
            // オーバーフローチェック (簡易的なチェック)
            if (intValue != 0 && result / intValue != other.intValue)
            {
                throw NumericException(NumericException::ErrorCode::OVERFLOW);
            }
            return Numeric(result);
        }
    }

    Numeric operator/(const Numeric &other) const
    {
        if (other == 0)
        {
            throw NumericException(NumericException::ErrorCode::DIVISION_BY_ZERO);
        }
        if (type == Type::Float || other.type == Type::Float)
        {
            return Numeric(to_double() / other.to_double());
        }
        return Numeric(intValue / other.intValue);
    }

    // 比較演算子のオーバーロード
    bool operator==(const Numeric &other) const
    {
        if (type == Type::Float || other.type == Type::Float)
        {
            return std::abs(to_double() - other.to_double()) < std::numeric_limits<double>::epsilon();
        }
        return intValue == other.intValue;
    }

    bool operator!=(const Numeric &other) const { return !(*this == other); }
    bool operator<(const Numeric &other) const
    {
        return type == Type::Float || other.type == Type::Float ? to_double() < other.to_double() : intValue < other.intValue;
    }
    bool operator>(const Numeric &other) const { return other < *this; }
    bool operator<=(const Numeric &other) const { return !(other < *this); }
    bool operator>=(const Numeric &other) const { return !(*this < other); }

    // 数学関数
    Numeric abs() const
    {
        return type == Type::Float ? Numeric(std::abs(floatValue)) : Numeric(std::abs(intValue));
    }

    Numeric sqrt() const
    {
        if (to_double() < 0)
        {
            throw NumericException(NumericException::ErrorCode::INVALID_OPERATION);
        }
        return Numeric(std::sqrt(to_double()));
    }

    Numeric pow(const Numeric &exponent) const
    {
        return Numeric(std::pow(to_double(), exponent.to_double()));
    }

    // デバッグ用出力
    void print() const
    {
        if (type == Type::Float)
        {
            Serial.println(floatValue, 10);
        }
        else
        {
            Serial.println(intValue);
        }
    }

    bool is_float() const { return type == Type::Float; }

private:
    enum class Type
    {
        Int,
        Float
    };
    Type type;
    union
    {
        int64_t intValue;
        double floatValue;
    };
};

#endif // AUTO_NUMERIC_H