#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "banking/Transaction.h"
#include "banking/Account.h"

class TestableTransaction : public Transaction {
public:
    using Transaction::SaveToDataBase;
};

class MockTransaction : public TestableTransaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account&, Account&, int), (override));
};

TEST(TransactionTest, MakeThrowsIfSameAccount) {
    MockTransaction trans;
    Account acc1(1, 1000), acc2(1, 1000);
    EXPECT_THROW(trans.Make(acc1, acc2, 100), std::logic_error);
}

TEST(TransactionTest, MakeCallsSaveToDataBase) {
    MockTransaction trans;
    Account acc1(1, 1000), acc2(2, 1000);
    
    EXPECT_CALL(trans, SaveToDataBase(testing::Ref(acc1), testing::Ref(acc2), 200))
        .Times(1);
        
    trans.Make(acc1, acc2, 200);
}
