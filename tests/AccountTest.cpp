#include <gtest/gtest.h>
#include "../Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(AccountTest, LockUnlock) {
    MockAccount acc(1, 1000);
    EXPECT_CALL(acc, Lock()).Times(1);
    EXPECT_CALL(acc, Unlock()).Times(1);
    acc.Lock();
    acc.Unlock();
}

TEST(AccountTest, ChangeBalanceFailsIfNotLocked) {
    Account acc(1, 1000);
    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
}
