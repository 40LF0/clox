// main_test.cc
// Created by Seungyeon Chung on 2024.06.08.
//
// Entry point for googletest

#include <gtest/gtest.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}