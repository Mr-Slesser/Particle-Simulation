#include <gtest/gtest.h>

TEST(ExampleTest, testFourPositive)
{
    EXPECT_GT(4, 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}