#include <gtest/gtest.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

// Фикстура для тестов
class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Тест: Проверка успешной транзакции
TEST_F(TransactionTest, RealTransactionSucceeds) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();

    bool result = transaction.Make(from, to, 300);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 700); // 1000 - 300
    EXPECT_EQ(to.GetBalance(), 800);   // 500 + 300
}

// Тест: Проверка исключения при одинаковых счетах
TEST_F(TransactionTest, MakeThrowsIfSameAccount) {
    Account account(1, 1000);
    Transaction transaction;

    account.Unlock();
    EXPECT_THROW(transaction.Make(account, account, 300), std::runtime_error);
}

// Тест: Проверка исключения при отрицательной сумме
TEST_F(TransactionTest, MakeThrowsIfNegativeSum) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();
    EXPECT_THROW(transaction.Make(from, to, -100), std::runtime_error);
}

// Тест: Проверка корректности транзакции без комиссии
TEST_F(TransactionTest, MakeOutputsCorrectInfo) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();
    bool result = transaction.Make(from, to, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 900); // 1000 - 100
    EXPECT_EQ(to.GetBalance(), 600);   // 500 + 100
}



