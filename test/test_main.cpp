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

    auto r0 = is_tuple<t0>::value;
    auto r1 = is_tuple<t1>::value;
    auto r2 = is_tuple<t2>::value;

    EXPECT_TRUE(r0);
    EXPECT_TRUE(r1);
    EXPECT_TRUE(r2);
}

TEST(is_tuple, is_tuple_false) {
    using t0 = std::array<int, 10>;
    using t1 = int;
    using t2 = std::string;

    auto r0 = is_tuple<t0>::value;
    auto r1 = is_tuple<t1>::value;
    auto r2 = is_tuple<t2>::value;

    EXPECT_FALSE(r0);
    EXPECT_FALSE(r1);
    EXPECT_FALSE(r2);
}

TEST(print_ip, string) {
    using value_t = std::string;

    value_t value{"Test"};
    std::stringstream oss;

    ip::print_ip(oss, value);

    std::string reference{"Test"};
    std::string result{};
    oss >> result;

    EXPECT_EQ(reference, result);
}

namespace ip {
    template<typename T>
    std::string get_string(const T &value) {
        std::stringstream oss;
        std::string result{};
        ip::print_ip(oss, value);
        oss >> result;
        return result;
    }
}

TEST(print_ip, integral) {
    auto v0 = int8_t{-123};
    auto v1 = uint8_t{123};
    auto v2 = int16_t{-12345};
    auto v3 = uint16_t{12345};
    auto v4 = int32_t{-1234567890};
    auto v5 = uint32_t{1234567890};
    auto v6 = int64_t{-1234567890123456789};
    auto v7 = uint64_t{1234567890123456789};

    std::string ref_0{"133"};
    std::string ref_1{"123"};
    std::string ref_2{"207.199"};
    std::string ref_3{"48.57"};
    std::string ref_4{"182.105.253.46"};
    std::string ref_5{"73.150.2.210"};
    std::string ref_6{"238.221.239.11.130.22.126.235"};
    std::string ref_7{"17.34.16.244.125.233.129.21"};

    EXPECT_EQ(ip::get_string(v0), ref_0);
    EXPECT_EQ(ip::get_string(v1), ref_1);
    EXPECT_EQ(ip::get_string(v2), ref_2);
    EXPECT_EQ(ip::get_string(v3), ref_3);
    EXPECT_EQ(ip::get_string(v4), ref_4);
    EXPECT_EQ(ip::get_string(v5), ref_5);
    EXPECT_EQ(ip::get_string(v6), ref_6);
    EXPECT_EQ(ip::get_string(v7), ref_7);
}

TEST(print_ip, vector_list) {
    auto v0 = std::list<uint8_t>{1, 2, 3, 4, 5, 6};
    auto v1 = std::list<uint32_t>{7, 8, 9, 10, 11, 12, 13};
    auto v2 = std::vector<uint8_t>{14, 15, 16, 17, 18, 19};
    auto v3 = std::vector<uint32_t>{20, 21, 22, 23, 24, 25, 26};

    std::string ref_0{"1.2.3.4.5.6"};
    std::string ref_1{"0.0.0.7.0.0.0.8.0.0.0.9.0.0.0.10.0.0.0.11.0.0.0.12.0.0.0.13"};
    std::string ref_2{"14.15.16.17.18.19"};
    std::string ref_3{"0.0.0.20.0.0.0.21.0.0.0.22.0.0.0.23.0.0.0.24.0.0.0.25.0.0.0.26"};

    EXPECT_EQ(ip::get_string(v0), ref_0);
    EXPECT_EQ(ip::get_string(v1), ref_1);
    EXPECT_EQ(ip::get_string(v2), ref_2);
    EXPECT_EQ(ip::get_string(v3), ref_3);
}

TEST(print_ip, tuple) {
    auto v0 = std::tuple<>{};
    auto v1 = std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>{
            -123, 123, -12345, 12345, -1234567890, 1234567890, -1234567890123456789, 1234567890123456789};

    std::string ref_0{};
    std::string ref_1{
            "133.123.207.199.48.57.182.105.253.46.73.150.2.210.238.221.239.11.130.22.126.235.17.34.16.244.125.233.129.21"};

    EXPECT_EQ(ip::get_string(v0), ref_0);
    EXPECT_EQ(ip::get_string(v1), ref_1);
}


TEST(print_tuple, tuple) {
    using type = std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;
    type value{-123, 123, -12345, 12345, -1234567890, 1234567890, -1234567890123456789, 1234567890123456789};

    std::string ref{
            "133.123.207.199.48.57.182.105.253.46.73.150.2.210.238.221.239.11.130.22.126.235.17.34.16.244.125.233.129.21"};

    std::stringstream oss;
    std::string result{};
    print_tuple<type, std::tuple_size<type>::value>::print(oss, value);
    oss >> result;

    EXPECT_EQ(result, ref);
}

TEST(print_tuple, tuple_1_false) {
    using type = std::tuple<int8_t>;
    type value{123};

    std::string ref{"123."};

    std::stringstream oss;
    std::string result{};
    print_tuple<type, std::tuple_size<type>::value, false>::print(oss, value);
    oss >> result;

    EXPECT_EQ(result, ref);
}

TEST(print_tuple, tuple_1_true) {
    using type = std::tuple<int8_t>;
    type value{123};

    std::string ref{"123"};

    std::stringstream oss;
    std::string result{};
    print_tuple<type, std::tuple_size<type>::value, true>::print(oss, value);
    oss >> result;

    EXPECT_EQ(result, ref);
}

TEST(print_tuple, tuple_0) {
    using type = std::tuple<>;
    type value{};

    std::string ref{""};

    std::stringstream oss;
    std::string result{};
    print_tuple<type, std::tuple_size<type>::value>::print(oss, value);
    oss >> result;

    EXPECT_EQ(result, ref);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}