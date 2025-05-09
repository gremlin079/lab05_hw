#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "banking/Transaction.h"
#include "banking/Account.h"

class TransactionWrapper : public Transaction {
public:
    void TestableSaveToDataBase(Account& from, Account& to, int sum) {
        SaveToDataBase(from, to, sum);
    }
};

class MockTransaction : public TransactionWrapper {
public:
    MOCK_METHOD(void, TestableSaveToDataBase, (Account&, Account&, int));

    void SaveToDataBase(Account& from, Account& to, int sum) override {
        TestableSaveToDataBase(from, to, sum);
    }
};

TEST(TransactionTest, MakeCallsSaveToDataBase) {
    MockTransaction trans;
    Account acc1(1, 1000), acc2(2, 1000);
    
    EXPECT_CALL(trans, TestableSaveToDataBase(testing::Ref(acc1), testing::Ref(acc2), 200))
        .Times(1);
        
    trans.Make(acc1, acc2, 200);
}

TEST(TransactionTest, MakeThrowsIfSameAccount) {
    MockTransaction trans;
    Account acc1(1, 1000), acc2(1, 1000);
    EXPECT_THROW(trans.Make(acc1, acc2, 100), std::logic_error);
}
