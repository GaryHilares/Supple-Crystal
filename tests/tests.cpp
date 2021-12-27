#include "../include/Utils/StringOps.hpp"
#include <gtest/gtest.h>

TEST(StringOps, ReplaceCharacters)
{
    std::string to_replace = "H3110 W0r1d!";
    std::string first_replacement = replaceAllOcurrencesOfCharacter(to_replace, '0', 'o');
    EXPECT_EQ(first_replacement, "H311o Wor1d!");
    std::string second_replacement = replaceAllOcurrencesOfCharacter(first_replacement, '1', 'l');
    EXPECT_EQ(second_replacement, "H3llo World!");
    std::string third_replacement = replaceAllOcurrencesOfCharacter(second_replacement, '3', 'e');
    EXPECT_EQ(third_replacement, "Hello World!");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}