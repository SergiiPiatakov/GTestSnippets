#include <gtest/gtest.h>
#include "calculator.h"


TEST (CalculatorTest, Add_Success)
{
    // Arrange.
    Calculator calculator;
    const int etalon = 1;

    // Act.
    const int test = calculator.Add (0, 1);

    // Arrange.
    EXPECT_EQ (etalon, test);
}

