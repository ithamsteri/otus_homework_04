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
 * Проверть является ли тип T типом std::tuple.
 * @retval true - тип T является типом std::tuple.
 * @retval false - тип T не является типом std::tuple.
 */
template<typename T>
constexpr bool is_tuple() {
    return is_tuple_imp<std::decay_t<T>>::value;
}

/**
 * Вывести строку в поток ostream.
 * @tparam T имеет тип std::string.
 * @param ostream ссылка на поток вывода.
 * @param value строка, которую нужно вывести в ostream.
 */
template<typename T>
typename std::enable_if_t<std::is_same<T, std::string>::value, void>
print_ip(std::ostream &ostream, const T &value) {
    ostream << value;
}

/**
 * Вывести целочисленное значение в формате ip в поток ostream.
 * @tparam T имеет любой внутренний целочисленный тип.
 * @param ostream ссылка на поток вывода.
 * @param value целочисленное значение, которое необходимо вывести в формате ip.
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
 * Вывести std::list или std::vector в формате ip в поток ostream.
 * @tparam T имеет тип std::list или std::vector.
 * @param ostream ссылка на поток вывода.
 * @param value значение, которое необходимо вывести в формате ip.
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
 * Класс, отвечающий за вывод типа std::tuple в поток ostream.
 * @tparam T имеет тип std::tuple.
 * @tparam N номер элемента кортежа.
 * @tparam is_first параметр, указывающий что это первый элемент кортежа (нужен чтобы не выводить лишнего символа '.').
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
 * Специализация класса print_tuple, отвечая за вывод 0-го элемента кортежа в поток ostream.
 * @tparam T имеет тип std::tuple.
 */
template<typename T>
struct print_tuple<T, 1, false> {
    static void print(std::ostream &ostream, const T &t) {
        print_ip(ostream, std::get<0>(t));
        ostream << ".";
    }
};

/**
 * Специализация класса print_tuple, отвечая за вывод 0-го элемента кортежа в поток ostream.
 * @tparam T имеет тип std::tuple.
 */
template<typename T>
struct print_tuple<T, 1, true> {
    static void print(std::ostream &ostream, const T &t) {
        print_ip(ostream, std::get<0>(t));
    }
};

/**
 * Специализация класса print_tuple, заглушка для пустого кортежа.
 * @tparam T имеет тип std::tuple<>.
 */
template<typename T>
struct print_tuple<T, 0> {
    static void print(std::ostream &ostream, const T &t) {
    }
};

/**
 * Вывести кортеж в поток ostream.
 * @tparam T имеет тип std::tuple.
 * @param ostream ссылка на поток вывода.
 * @param value значение, которое необходимо вывести в формате ip.
 */
template<typename T>
typename std::enable_if_t<is_tuple<T>(), void>
print_ip(std::ostream &ostream, const T &value) {
    print_tuple<T, std::tuple_size<T>::value>::print(ostream, value);
}
