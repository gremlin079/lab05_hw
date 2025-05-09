#include <gtest/gtest.h>
#include "banking/Transaction.h"
#include "banking/Account.h"

class MockTransaction : public Transaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account&, Account&, int), (override));
};

TEST(TransactionTest, MakeThrowsIfSameAccount) {
    Account acc1(1, 1000), acc2(1, 1000);
    Transaction t;
    EXPECT_THROW(t.Make(acc1, acc2, 100), std::logic_error);
}

TEST(TransactionTest, MakeThrowsIfSumNegative) {
    Account acc1(1, 1000), acc2(2, 1000);
    Transaction t;
    EXPECT_THROW(t.Make(acc1, acc2, -50), std::invalid_argument);
}

TEST(TransactionTest, MakeFailsIfFeeTooHigh) {
    Account acc1(1, 1000), acc2(2, 1000);
    Transaction t;
    t.set_fee(60);  // fee > sum / 2
    EXPECT_FALSE(t.Make(acc1, acc2, 100));
}
