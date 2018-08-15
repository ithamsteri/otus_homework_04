#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../inc/print_ip.h"

TEST(lib, version) {
    EXPECT_GT(version(), 0);
}

TEST(is_tuple, is_tuple_true) {
    using t0 = std::tuple<>;
    using t1 = std::tuple<int>;
    using t2 = std::tuple<int, int>;

    EXPECT_EQ(is_tuple<t0>::value, true);
    EXPECT_EQ(is_tuple<t1>::value, true);
    EXPECT_EQ(is_tuple<t2>::value, true);
}

TEST(is_tuple, is_tuple_false) {
    using t0 = std::array<int, 10>;
    using t1 = int;
    using t2 = std::string;

    EXPECT_EQ(is_tuple<t0>::value, false);
    EXPECT_EQ(is_tuple<t1>::value, false);
    EXPECT_EQ(is_tuple<t2>::value, false);
}

TEST(print_ip, string) {
    using value_t = std::string;

    value_t           value{"Test"};
    std::stringstream oss;

    ip::print_ip(oss, value);

    std::string reference{"Test"};
    std::string result{};
    oss >> result;

    EXPECT_EQ(reference, result);
}

TEST(print_ip, integral) {

}

TEST(print_ip, vector_list) {

}

TEST(print_ip, tuple) {

}

TEST(print_tuple, tuple) {

}

TEST(print_tuple, tuple_1_false) {

}

TEST(print_tuple, tuple_1_true) {

}

TEST(print_tuple, tuple_0) {

}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}