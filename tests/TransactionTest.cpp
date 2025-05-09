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

TEST(TransactionTest, RealTransactionSucceeds) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction t;
    t.set_fee(10);

    bool success = t.Make(from, to, 300);

    EXPECT_TRUE(success);
    EXPECT_EQ(from.GetBalance(), 1000 - 300 - 10);
    EXPECT_EQ(to.GetBalance(), 500 + 300);
}
}

