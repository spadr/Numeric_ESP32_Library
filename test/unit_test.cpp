// NumericTests.cpp
#include <Arduino.h>
#include "Numeric.h"
#include <unity.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_numeric_creation()
{
    Numeric a(5);
    TEST_ASSERT_EQUAL(5, a.to_int64());
    TEST_ASSERT_FALSE(a.is_float());

    Numeric b(3.14);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 3.14, b.to_double());
    TEST_ASSERT_TRUE(b.is_float());
}

void test_numeric_addition()
{
    Numeric a(5);
    Numeric b(3);
    Numeric c = a + b;
    TEST_ASSERT_EQUAL(8, c.to_int64());
    TEST_ASSERT_FALSE(c.is_float());

    Numeric d(2.5);
    Numeric e = a + d;
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 7.5, e.to_double());
    TEST_ASSERT_TRUE(e.is_float());
}

void test_numeric_subtraction()
{
    Numeric a(10);
    Numeric b(7);
    Numeric c = a - b;
    TEST_ASSERT_EQUAL(3, c.to_int64());
    TEST_ASSERT_FALSE(c.is_float());

    Numeric d(5.5);
    Numeric e = a - d;
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 4.5, e.to_double());
    TEST_ASSERT_TRUE(e.is_float());
}

void test_numeric_multiplication()
{
    Numeric a(6);
    Numeric b(7);
    Numeric c = a * b;
    TEST_ASSERT_EQUAL(42, c.to_int64());
    TEST_ASSERT_FALSE(c.is_float());

    Numeric d(2.5);
    Numeric e = a * d;
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 15.0, e.to_double());
    TEST_ASSERT_TRUE(e.is_float());
}

void test_numeric_division()
{
    Numeric a(20);
    Numeric b(4);
    Numeric c = a / b;
    TEST_ASSERT_EQUAL(5, c.to_int64());
    TEST_ASSERT_FALSE(c.is_float());

    Numeric d(10.0);
    Numeric e = d / b;
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 2.5, e.to_double());
    TEST_ASSERT_TRUE(e.is_float());

    bool exceptionThrown = false;
    try
    {
        Numeric f = a / Numeric(0);
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL_STRING("Division by zero", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);

    exceptionThrown = false;
    try
    {
        Numeric f = a / Numeric(0.0);
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL_STRING("Division by zero", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);
}

void test_numeric_comparison()
{
    Numeric a(5);
    Numeric b(7);
    TEST_ASSERT_TRUE(a < b);
    TEST_ASSERT_FALSE(a > b);
    TEST_ASSERT_TRUE(a <= b);
    TEST_ASSERT_FALSE(a >= b);
    TEST_ASSERT_FALSE(a == b);
    TEST_ASSERT_TRUE(a != b);

    Numeric c(3.14);
    Numeric d(3.14);
    TEST_ASSERT_TRUE(c == d);
}

void test_numeric_abs()
{
    Numeric a(-5);
    TEST_ASSERT_EQUAL(5, a.abs().to_int64());

    Numeric b(-3.14);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 3.14, b.abs().to_double());
}

void test_numeric_sqrt()
{
    Numeric a(16);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 4.0, a.sqrt().to_double());

    Numeric b(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.4142, b.sqrt().to_double());

    // 例外のテスト
    bool exceptionThrown = false;
    try
    {
        Numeric c = Numeric(-1.0).sqrt();
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL_STRING("Invalid operation", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);
}

void test_numeric_pow()
{
    Numeric a(2);
    Numeric b(3);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 8.0, a.pow(b).to_double());

    Numeric c(2.0);
    Numeric d(0.5);
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.4142, c.pow(d).to_double());
}

void test_numeric_exceptions()
{
    // OVERFLOW
    bool exceptionThrown = false;
    try
    {
        Numeric a = std::numeric_limits<int64_t>::max();
        Numeric b = 1;
        Numeric c = a + b;
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL(Numeric::NumericException::ErrorCode::OVERFLOW, e.getErrorCode());
        TEST_ASSERT_EQUAL_STRING("Numeric overflow", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);

    // UNDERFLOW
    exceptionThrown = false;
    try
    {
        Numeric a = std::numeric_limits<int64_t>::min();
        Numeric b = -1;
        Numeric c = a + b;
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL(Numeric::NumericException::ErrorCode::OVERFLOW, e.getErrorCode());
        TEST_ASSERT_EQUAL_STRING("Numeric overflow", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);

    // DIVISION_BY_ZERO
    exceptionThrown = false;
    try
    {
        Numeric a = 42;
        Numeric b = 0;
        Numeric c = a / b;
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL(Numeric::NumericException::ErrorCode::DIVISION_BY_ZERO, e.getErrorCode());
        TEST_ASSERT_EQUAL_STRING("Division by zero", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);

    // INVALID_OPERATION
    exceptionThrown = false;
    try
    {
        Numeric a = -1;
        Numeric b = a.sqrt();
    }
    catch (const Numeric::NumericException &e)
    {
        exceptionThrown = true;
        TEST_ASSERT_EQUAL(Numeric::NumericException::ErrorCode::INVALID_OPERATION, e.getErrorCode());
        TEST_ASSERT_EQUAL_STRING("Invalid operation", e.what());
    }
    TEST_ASSERT_TRUE(exceptionThrown);
}

void runTests()
{
    UNITY_BEGIN();
    RUN_TEST(test_numeric_creation);
    RUN_TEST(test_numeric_addition);
    RUN_TEST(test_numeric_subtraction);
    RUN_TEST(test_numeric_multiplication);
    RUN_TEST(test_numeric_division);
    RUN_TEST(test_numeric_comparison);
    RUN_TEST(test_numeric_abs);
    RUN_TEST(test_numeric_sqrt);
    RUN_TEST(test_numeric_pow);
    RUN_TEST(test_numeric_exceptions);
    UNITY_END();
}

void setup()
{
    delay(2000);
    runTests();
}

void loop()
{
    // Nothing to do here
}