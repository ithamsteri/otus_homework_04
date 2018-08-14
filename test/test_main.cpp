#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../inc/print_ip.h"

TEST(lib, version) {
    EXPECT_GT(version(), 0);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}