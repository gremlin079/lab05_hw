#include <gtest/gtest.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(TransactionTest, RealTransactionSucceeds) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;
    from.Unlock();
    to.Unlock();
    bool result = transaction.Make(from, to, 300);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 1000);
    EXPECT_EQ(to.GetBalance(), 499);
}

TEST_F(TransactionTest, MakeThrowsIfSameAccount) {
    Account account(1, 1000);
    Transaction transaction;
    account.Unlock();
    EXPECT_THROW(transaction.Make(account, account, 300), std::logic_error);
}

TEST_F(TransactionTest, MakeThrowsIfNegativeSum) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;
    from.Unlock();
    to.Unlock();
    EXPECT_THROW(transaction.Make(from, to, -100), std::invalid_argument);
}

TEST_F(TransactionTest, MakeOutputsCorrectInfo) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;
    from.Unlock();
    to.Unlock();
    bool result = transaction.Make(from, to, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 1000);
    EXPECT_EQ(to.GetBalance(), 499);
}

TEST_F(TransactionTest, TransactionCallsChangeBalance) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;
    from.Lock();
    to.Lock();
    bool result = transaction.Make(from, to, 200);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 1000);
    EXPECT_EQ(to.GetBalance(), 499);
}

