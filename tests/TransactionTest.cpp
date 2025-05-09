#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

// Фикстура для тестов Transaction
class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Тест: Проверка успешной транзакции
TEST_F(TransactionTest, RealTransactionSucceeds) {
    banking::Account from(1, 1000);
    banking::Account to(2, 500);
    banking::Transaction transaction;

    from.Unlock();
    to.Unlock();

    bool result = transaction.Make(from, to, 300);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 700); // 1000 - 300
    EXPECT_EQ(to.GetBalance(), 800);   // 500 + 300
}

// Тест: Проверка исключения при одинаковых счетах
TEST_F(TransactionTest, MakeThrowsIfSameAccount) {
    banking::Account account(1, 1000);
    banking::Transaction transaction;

    account.Unlock();
    EXPECT_THROW(transaction.Make(account, account, 300), std::runtime_error);
}

// Тест: Проверка исключения при отрицательной сумме
TEST_F(TransactionTest, MakeThrowsIfNegativeSum) {
    banking::Account from(1, 1000);
    banking::Account to(2, 500);
    banking::Transaction transaction;

    from.Unlock();
    to.Unlock();
    EXPECT_THROW(transaction.Make(from, to, -100), std::runtime_error);
}

// Тест: Проверка корректности транзакции без комиссии
TEST_F(TransactionTest, MakeOutputsCorrectInfo) {
    banking::Account from(1, 1000);
    banking::Account to(2, 500);
    banking::Transaction transaction;

    from.Unlock();
    to.Unlock();
    bool result = transaction.Make(from, to, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 900); // 1000 - 100
    EXPECT_EQ(to.GetBalance(), 600);   // 500 + 100
}



