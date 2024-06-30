#include <chrono>
#include <iostream>
#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>

int main() {
  //default ctor test
  const auto start_default_lst{ std::chrono::steady_clock::now() };
  QueueLstT<int> test;
  const auto end_default_lst{ std::chrono::steady_clock::now() };
  std::cout << "Default ctor lst: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_default_lst - start_default_lst) << std::endl;

  const auto start_default_arr{ std::chrono::steady_clock::now() };
  QueueArrT<int> test1;
  const auto end_default_arr{ std::chrono::steady_clock::now() };
  std::cout << "Default ctor arr: " << (end_default_arr - start_default_arr) << std::endl;


  //push tests
  const auto start_push_1{ std::chrono::steady_clock::now() };
  test.Push(1);
  const auto end_push_1{ std::chrono::steady_clock::now() };
  std::cout << "Push 1 el: " << (end_push_1 - start_push_1) << std::endl;

  const auto start_push_1_arr{ std::chrono::steady_clock::now() };
  test1.Push(1);
  const auto end_push_1_arr{ std::chrono::steady_clock::now() };
  std::cout << "Push 1 el arr: " << (end_push_1_arr - start_push_1_arr) << std::endl;

  const auto start_push_2{ std::chrono::steady_clock::now() };
  test.Push(2);
  test.Push(3);
  const auto end_push_2{ std::chrono::steady_clock::now() };
  std::cout << "Push 2 el: " << (end_push_2 - start_push_2) << std::endl;

  const auto start_push_2_arr{ std::chrono::steady_clock::now() };
  test1.Push(1);
  test1.Push(2);
  const auto end_push_2_arr{ std::chrono::steady_clock::now() };
  std::cout << "Push 2 el arr: " << (end_push_2_arr - start_push_2_arr) << std::endl;

  const auto start_push_5{ std::chrono::steady_clock::now() };
  test.Push(4);
  test.Push(5);
  test.Push(6);
  test.Push(7);
  test.Push(8);
  const auto end_push_5{ std::chrono::steady_clock::now() };
  std::cout << "Push 5 el: " << (end_push_5 - start_push_5) << std::endl;

  const auto start_push_20{ std::chrono::steady_clock::now() };
  for (int i = 0; i < 20; i++) {
    test.Push(i + 10);
  }
  const auto end_push_20{ std::chrono::steady_clock::now() };
  std::cout << "Push 20 el: " << (end_push_20 - start_push_20) << std::endl;

  const auto start_push_100{ std::chrono::steady_clock::now() };
  for (int i = 0; i < 100; i++) {
    test.Push(i + 20);
  }
  const auto end_push_100{ std::chrono::steady_clock::now() };
  std::cout << "Push 100 el: " << (end_push_100 - start_push_100) << std::endl;

  const auto start_push_100_arr{ std::chrono::steady_clock::now() };
  for (int i = 0; i < 100; i++) {
    test1.Push(i + 20);
  }
  const auto end_push_100_arr{ std::chrono::steady_clock::now() };
  std::cout << "Push 100 el arr: " << (end_push_100_arr - start_push_100_arr) << std::endl;

  const auto start_push_1000{ std::chrono::steady_clock::now() };
  for (int i = 0; i < 1000; i++) {
    test.Push(i + 20);
  }
  const auto end_push_1000{ std::chrono::steady_clock::now() };
  std::cout << "Push 1000 el: " << (end_push_1000 - start_push_1000) << std::endl;

  const auto start_push_1000_arr{ std::chrono::steady_clock::now() };
  for (int i = 0; i < 1000; i++) {
    test1.Push(i + 20);
  }
  const auto end_push_1000_arr{ std::chrono::steady_clock::now() };
  std::cout << "Push 1000 el arr: " << (end_push_1000_arr - start_push_1000_arr) << std::endl;

  //test copy ctor and move
  const auto start_copy{ std::chrono::steady_clock::now() };
  QueueLstT<int> meow(test);
  const auto end_copy{ std::chrono::steady_clock::now() };
  std::cout << "Copy ctor: " << (end_copy - start_copy) << std::endl;

  const auto start_move{ std::chrono::steady_clock::now() };
  QueueLstT<int> ss(std::move(meow));
  const auto end_move{ std::chrono::steady_clock::now() };
  std::cout << "Move ctor: " << (end_move - start_move) << std::endl;

  //test operator=
  const auto start_op{ std::chrono::steady_clock::now() };
  meow = ss;
  const auto end_op{ std::chrono::steady_clock::now() };
  std::cout << "empty = smth: " << (end_op - start_op) << std::endl;

  QueueLstT<int> a;
  a.Push(1);
  a.Push(2);
  a.Push(3);
  const auto start_op_1{ std::chrono::steady_clock::now() };
  meow = a;
  const auto end_op_1{ std::chrono::steady_clock::now() };
  std::cout << "max = min: " << (end_op_1 - start_op_1) << std::endl;

  meow.Pop();
  meow.Pop();
  meow.Pop();
  meow.Push(10);
  meow.Push(20);
  meow.Push(30);

  const auto start_op_2{ std::chrono::steady_clock::now() };
  meow = a;
  const auto end_op_2{ std::chrono::steady_clock::now() };
  std::cout << "same = same: " << (end_op_2 - start_op_2) << std::endl;

  for (int i = 0; i < 100; i++) {
    meow.Push(i + 10);
    a.Push(i + 20);
  }

  const auto start_op_3{ std::chrono::steady_clock::now() };
  meow = a;
  const auto end_op_3{ std::chrono::steady_clock::now() };
  std::cout << "same = same: " << (end_op_3 - start_op_3) << std::endl;

  a.Clear();
  a.Push(1);
  const auto start_op_4{ std::chrono::steady_clock::now() };
  a = meow;
  const auto end_op_4{ std::chrono::steady_clock::now() };
  std::cout << "min = max: " << (end_op_4 - start_op_4) << std::endl;

  const auto start_clear{ std::chrono::steady_clock::now() };
  a.Clear();
  const auto end_clear{ std::chrono::steady_clock::now() };
  std::cout << "Clear: " << (end_clear - start_clear) << std::endl;

  a.Push(1);
  const auto start_op_move{ std::chrono::steady_clock::now() };
  a = std::move(meow);
  const auto end_op_move{ std::chrono::steady_clock::now() };
  std::cout << "=move (eq to last =): " << (end_op_move - start_op_move) << std::endl;
}