#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

using namespace banking;

// Фикстура для тестов Transaction
class TransactionTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }
};

// Тест: Проверка, что транзакция успешно выполняется
TEST_F(TransactionTest, RealTransactionSucceeds) {
  Account from(1, 1000); // Счет-отправитель с балансом 1000
  Account to(2, 500);    // Счет-получатель с балансом 500
  Transaction transaction;

  // Убеждаемся, что счета разблокированы (на случай, если тесты изменяют состояние)
  from.Unlock();
  to.Unlock();

  // Выполняем транзакцию
  bool result = transaction.Make(from, to, 300);
  EXPECT_TRUE(result);
  EXPECT_EQ(from.GetBalance(), 700); // 1000 - 300
  EXPECT_EQ(to.GetBalance(), 800);   // 500 + 300
}

// Тест: Проверка, что транзакция выбрасывает исключение, если счета одинаковые
TEST_F(TransactionTest, MakeThrowsIfSameAccount) {
  Account account(1, 1000);
  Transaction transaction;

  account.Unlock(); // Убеждаемся, что счет разблокирован
  EXPECT_THROW(transaction.Make(account, account, 300), std::runtime_error);
}

// Тест: Проверка, что транзакция выбрасывает исключение при отрицательной сумме
TEST_F(TransactionTest, MakeThrowsIfNegativeSum) {
  Account from(1, 1000);
  Account to(2, 500);
  Transaction transaction;

  from.Unlock();
  to.Unlock();
  EXPECT_THROW(transaction.Make(from, to, -100), std::runtime_error);
}

// Тест: Проверка корректности комиссии транзакции
TEST_F(TransactionTest, MakeOutputsCorrectInfo) {
  Account from(1, 1000);
  Account to(2, 500);
  Transaction transaction;

  from.Unlock();
  to.Unlock();
  bool result = transaction.Make(from, to, 100);
  EXPECT_TRUE(result);
  // Предполагаем, что комиссия 1% от суммы (на основе типичной реализации)
  // Сумма 100, комиссия 1, списано 101
  EXPECT_EQ(from.GetBalance(), 899); // 1000 - 100 - 1
  EXPECT_EQ(to.GetBalance(), 600);   // 500 + 100
}



