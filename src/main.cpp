// main.cpp
#include <Arduino.h>
#include "Numeric.h"

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  // 各種数値型からNumericオブジェクトを生成
  Numeric byteNum = Numeric(static_cast<byte>(42));
  Numeric shortNum = Numeric(static_cast<short>(-32768));
  Numeric ushortNum = Numeric(static_cast<unsigned short>(65535));
  Numeric intNum = Numeric(42);
  Numeric uintNum = Numeric(static_cast<unsigned int>(42));
  Numeric longNum = Numeric(42L);
  Numeric ulongNum = Numeric(42UL);
  Numeric floatNum = Numeric(3.14f);
  Numeric doubleNum = Numeric(3.14);

  Serial.println("Numeric objects created from various numeric types:");
  Serial.print("byteNum: ");
  byteNum.print();
  Serial.print("shortNum: ");
  shortNum.print();
  Serial.print("ushortNum: ");
  ushortNum.print();
  Serial.print("intNum: ");
  intNum.print();
  Serial.print("uintNum: ");
  uintNum.print();
  Serial.print("longNum: ");
  longNum.print();
  Serial.print("ulongNum: ");
  ulongNum.print();
  Serial.print("floatNum: ");
  floatNum.print();
  Serial.print("doubleNum: ");
  doubleNum.print();

  // 算術演算
  Numeric a = 10;
  Numeric b = 3.14;

  Numeric sum = a + b;
  Numeric diff = a - b;
  Numeric prod = a * b;
  Numeric quot = a / b;

  Serial.println("\nArithmetic operations:");
  Serial.print("a = ");
  a.print();
  Serial.print("b = ");
  b.print();
  Serial.print("a + b = ");
  sum.print();
  Serial.print("a - b = ");
  diff.print();
  Serial.print("a * b = ");
  prod.print();
  Serial.print("a / b = ");
  quot.print();

  // 比較演算
  Serial.println("\nComparison operations:");
  Serial.print("a == b: ");
  Serial.println(a == b);
  Serial.print("a != b: ");
  Serial.println(a != b);
  Serial.print("a < b: ");
  Serial.println(a < b);
  Serial.print("a > b: ");
  Serial.println(a > b);
  Serial.print("a <= b: ");
  Serial.println(a <= b);
  Serial.print("a >= b: ");
  Serial.println(a >= b);

  // その他の演算
  Serial.println("\nOther operations:");
  Serial.print("abs(a) = ");
  a.abs().print();
  Serial.print("sqrt(a) = ");
  a.sqrt().print();
  Serial.print("pow(a, b) = ");
  a.pow(b).print();

  // 例外処理
  Serial.println("\nException handling:");
  try
  {
    Numeric c = a / Numeric(0);
  }
  catch (const Numeric::NumericException &e)
  {
    Serial.print("Caught exception: ");
    Serial.println(e.what());
  }

  try
  {
    Numeric d = Numeric(-1).sqrt();
  }
  catch (const Numeric::NumericException &e)
  {
    Serial.print("Caught exception: ");
    Serial.println(e.what());
  }
}

void loop()
{
  // nothing to do here
}