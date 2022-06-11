#include "gtest/gtest.h"
//#include "User.h"
//#include "Party.h"

TEST(HelloTest, BasicAssertions){
    //String not equal
    EXPECT_STRNE("hello", "world");
    // expect equality
    EXPECT_EQ(7*6, 42);
}

TEST(NoDramaTests, UserTest){
    //User
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
