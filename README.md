# Numeric Library for ESP32: Safe and Reliable Arithmetic Operations

The ESP32 is a powerful microcontroller with ample computational resources, allowing for complex projects and sophisticated calculations. However, Arduino's diverse set of numeric types, while offering flexibility, can also introduce complexity and potential pitfalls for developers. Juggling `byte`, `int`, `long`, `float`, and `double`, each with its own range and behavior, can lead to subtle bugs, especially when dealing with overflow, underflow, or type conversions. 

The Numeric Library for ESP32 is designed to streamline your arithmetic operations and eliminate these headaches. By providing a **unified and type-safe interface**, it simplifies your code and ensures predictable behavior across all supported numeric types.

## Why Choose Numeric Library?

- **Overflow and Underflow Protection:** Forget about unexpected results caused by integer overflow and underflow. The library automatically detects these conditions and throws exceptions, preventing erroneous calculations and enhancing code reliability.
- **Type Safety:** Seamlessly work with various numeric types without the worry of implicit conversions or data loss. The library handles type conversions internally, maintaining data integrity and simplifying your code.
- **Unified Interface:** Enjoy a consistent and intuitive API for performing arithmetic operations, comparisons, and mathematical functions across all supported numeric types, reducing cognitive load and improving code readability.
- **Exception Handling:** Gracefully handle common errors like division by zero and invalid operations through informative exception messages, making debugging and error management a breeze. 
- **Memory Efficiency:** The library employs an optimized internal representation using a tagged union, minimizing memory usage without sacrificing functionality. This is especially beneficial for ESP32 projects with limited memory resources.

## Features

- 🔢 Supports a wide range of Arduino numeric types:
  - byte
  - short, unsigned short
  - int, unsigned int
  - long, unsigned long
  - float
  - double
- ➕➖✖️➗ Overloaded arithmetic operators (+, -, *, /)
- 🤝 Comparison operators (==, !=, <, >, <=, >=)
- 🧮 Mathematical functions (abs, sqrt, pow)

## Installation

### Using PlatformIO

1. Open your PlatformIO project.
2. Open the `platformio.ini` file.
3. Add the following line to the `lib_deps` section:
   ```
   lib_deps =
       https://github.com/spadr/Numeric_ESP32_Library.git
   ```
4. Save the `platformio.ini` file.
5. PlatformIO will automatically download and install the library.

### Manual Installation

1. Download the Numeric Library as a ZIP file from the GitHub repository.
2. Extract the ZIP file to the `lib` directory in your PlatformIO project.
3. The library should now be installed and ready to use.

## Usage Examples

**Basic Arithmetic Operations:**

```cpp
#include <Numeric.h>

Numeric a = 10;
Numeric b = 3.14;

Numeric sum = a + b;
Numeric diff = a - b;
Numeric product = a * b;
Numeric quotient = a / b;

sum.print();      // Output: 13.14
diff.print();     // Output: 6.86
product.print();  // Output: 31.4
quotient.print(); // Output: 3.1847133758
```

**Overflow Detection:**

```cpp
#include <Numeric.h>

try {
  Numeric maxInt = Numeric(std::numeric_limits<int64_t>::max());
  Numeric one = 1;
  Numeric result = maxInt + one; 
} catch (const Numeric::NumericException& e) {
  Serial.print("Error: ");
  Serial.println(e.what()); // Output: Error: Numeric overflow
}
```

**Mathematical Functions:**

```cpp
#include <Numeric.h>

Numeric x = 16;
Numeric sqrt_x = x.sqrt();  // Calculate square root
Numeric abs_x = x.abs();    // Calculate absolute value
Numeric pow_x = x.pow(2);   // Calculate x to the power of 2

sqrt_x.print(); // Output: 4
abs_x.print();  // Output: 16
pow_x.print();  // Output: 256
```

## Performance

While prioritizing safety and usability, the Numeric Library strives for efficiency. The use of a tagged union for internal representation minimizes memory overhead. However, due to explicit type checks and conversions, some operations may have a slight performance overhead compared to native Arduino types. 
## Contributing

Contributions to the Numeric Library are welcome! If you find a bug, have a feature request, or want to contribute improvements, please open an issue or submit a pull request on the GitHub repository. 

## License

The Numeric Library is released under the [GPL3 License](LICENSE).
```