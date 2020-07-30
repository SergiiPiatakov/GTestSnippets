#include <gtest/gtest.h>
#include "calculator.h"


class CalculatorTest : public ::testing::Test
{
    public:
        CalculatorTest  () = default;
        ~CalculatorTest () = default;

        void SetUp      () override
        {
            ::testing::Test::SetUp ();
        }

        void TearDown   () override
        {
            ::testing::Test::TearDown ();
        }

    protected:
        Calculator      calculator;
};

TEST_F (CalculatorTest, Add_Case001_Success)
{
    // Arrange.
    const int etalon = 1;

    // Act.
    const int test = calculator.Add (0, 1);

    // Assert.
    EXPECT_EQ (etalon, test);
}

TEST_F (CalculatorTest, Add_Case002_Success)
{
    // Arrange.
    const int etalon = 5;

    // Act.
    const int test = calculator.Add (2, 3);

    // Assert.
    EXPECT_EQ (etalon, test);
}

