#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

template<typename T>
struct is_tuple_imp : std::false_type {};

template<typename... U>
struct is_tuple_imp<std::tuple<U...>> : std::true_type {};

/**
 * �������� �������� �� ��� T ����� std::tuple.
 * @retval true - ��� T �������� ����� std::tuple.
 * @retval false - ��� T �� �������� ����� std::tuple.
 */
template<typename T>
constexpr bool is_tuple() {
    return is_tuple_imp<std::decay_t<T>>::value;
}

/**
 * ������� ������ � ����� ostream.
 * @tparam T ����� ��� std::string.
 * @param ostream ������ �� ����� ������.
 * @param value ������, ������� ����� ������� � ostream.
 */
template<typename T>
typename std::enable_if_t<std::is_same<T, std::string>::value, void>
print_ip(std::ostream &ostream, const T &value) {
    ostream << value;
}

/**
 * ������� ������������� �������� � ������� ip � ����� ostream.
 * @tparam T ����� ����� ���������� ������������� ���.
 * @param ostream ������ �� ����� ������.
 * @param value ������������� ��������, ������� ���������� ������� � ������� ip.
 */
template<typename T>
typename std::enable_if_t<std::is_integral<T>::value, void>
print_ip(std::ostream &ostream, const T &value) {
    constexpr auto byte_Size = 8;

    for (auto i = 0; i < sizeof(T); ++i) {
        ostream << ((value >> byte_Size * (sizeof(T) - 1 - i)) & 0xFF);
        if (i != sizeof(T) - 1) {
            ostream << ".";
        }
    }
}

/**
 * ������� std::list ��� std::vector � ������� ip � ����� ostream.
 * @tparam T ����� ��� std::list ��� std::vector.
 * @param ostream ������ �� ����� ������.
 * @param value ��������, ������� ���������� ������� � ������� ip.
 */
template<typename T>
typename std::enable_if_t<std::is_same<T, std::vector<typename T::value_type>>::value || std::is_same<T, std::list<typename T::value_type>>::value, void>
print_ip(std::ostream &ostream, const T &value) {
    const auto size = value.size();
    for (auto  it   = value.begin();;) {
        print_ip(ostream, *it);
        if (++it != value.end()) {
            ostream << ".";
        } else {
            break;
        }
    }
}

/**
 * �����, ���������� �� ����� ���� std::tuple � ����� ostream.
 * @tparam T ����� ��� std::tuple.
 * @tparam N ����� �������� �������.
 * @tparam is_first ��������, ����������� ��� ��� ������ ������� ������� (����� ����� �� �������� ������� ������� '.').
 */
template<typename T, std::size_t N, bool is_first = true>
struct print_tuple {
    static void print(std::ostream &ostream, const T &t) {
        print_tuple<T, N - 1, false>::print(ostream, t);
        print_ip(ostream, std::get<N - 1>(t));
        if (!is_first) { ostream << "."; }
    }
};

/**
 * ������������� ������ print_tuple, ������� �� ����� 0-�� �������� ������� � ����� ostream.
 * @tparam T ����� ��� std::tuple.
 */
template<typename T>
struct print_tuple<T, 1, false> {
    static void print(std::ostream &ostream, const T &t) {
        print_ip(ostream, std::get<0>(t));
        ostream << ".";
    }
};

/**
 * ������������� ������ print_tuple, ������� �� ����� 0-�� �������� ������� � ����� ostream.
 * @tparam T ����� ��� std::tuple.
 */
template<typename T>
struct print_tuple<T, 1, true> {
    static void print(std::ostream &ostream, const T &t) {
        print_ip(ostream, std::get<0>(t));
    }
};

/**
 * ������������� ������ print_tuple, �������� ��� ������� �������.
 * @tparam T ����� ��� std::tuple<>.
 */
template<typename T>
struct print_tuple<T, 0> {
    static void print(std::ostream &ostream, const T &t) {
    }
};

/**
 * ������� ������ � ����� ostream.
 * @tparam T ����� ��� std::tuple.
 * @param ostream ������ �� ����� ������.
 * @param value ��������, ������� ���������� ������� � ������� ip.
 */
template<typename T>
typename std::enable_if_t<is_tuple<T>(), void>
print_ip(std::ostream &ostream, const T &value) {
    print_tuple<T, std::tuple_size<T>::value>::print(ostream, value);
}
