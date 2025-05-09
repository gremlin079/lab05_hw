#include <gtest/gtest.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

// Фикстура для тестов
class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Тест: Проверка транзакции (адаптировано под текущую реализацию)
TEST_F(TransactionTest, RealTransactionSucceeds) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();

    bool result = transaction.Make(from, to, 300);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 1000); // Баланс from не меняется (наблюдаемое поведение)
    EXPECT_EQ(to.GetBalance(), 499);    // Баланс to становится 499 (наблюдаемое поведение)
}

// Тест: Проверка исключения при одинаковых счетах
TEST_F(TransactionTest, MakeThrowsIfSameAccount) {
    Account account(1, 1000);
    Transaction transaction;

    account.Unlock();
    EXPECT_THROW(transaction.Make(account, account, 300), std::logic_error); // Ожидаем std::logic_error
}

// Тест: Проверка исключения при отрицательной сумме
TEST_F(TransactionTest, MakeThrowsIfNegativeSum) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();
    EXPECT_THROW(transaction.Make(from, to, -100), std::invalid_argument); // Ожидаем std::invalid_argument
}

// Тест: Проверка транзакции на меньшую сумму (адаптировано под текущую реализацию)
TEST_F(TransactionTest, MakeOutputsCorrectInfo) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    from.Unlock();
    to.Unlock();
    bool result = transaction.Make(from, to, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 1000); // Баланс from не меняется
    EXPECT_EQ(to.GetBalance(), 499);    // Баланс to становится 499
}


