#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include "banking/Transaction.h"
#include "banking/Account.h"

using ::testing::HasSubstr;

TEST(TransactionTest, MakeOutputsCorrectInfo) {
    Transaction trans;
    Account acc1(1, 1000), acc2(2, 1000);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    trans.Make(acc1, acc2, 200);  

    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_THAT(output, HasSubstr("1 send to 2 $200"));
    EXPECT_THAT(output, HasSubstr("Balance 1 is "));
    EXPECT_THAT(output, HasSubstr("Balance 2 is "));
}

TEST(TransactionTest, MakeThrowsIfSameAccount) {
    Transaction trans;
    Account acc1(1, 1000), acc2(1, 1000);
    EXPECT_THROW(trans.Make(acc1, acc2, 100), std::logic_error);
}

TEST(TransactionTest, MakeThrowsIfNegativeSum) {
    Transaction trans;
    Account acc1(1, 1000), acc2(2, 1000);
    EXPECT_THROW(trans.Make(acc1, acc2, -50), std::invalid_argument);
}
