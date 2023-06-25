/**
 * Created by 史进 on 2023/6/5.
 *
 * 通用工具，包括move(), forward(), swap()等函数，以及pair等数据结构
 */
#ifndef SIMPLESTL_UTILITY_H
#define SIMPLESTL_UTILITY_H

#include <cstddef>

#include "type_traits.h"

namespace simple_stl{

    // move()：将左值转换为对应的右值引用类型
    template<class Tp>
    typename remove_reference<Tp>::type&& move(Tp&& _t) noexcept{
        typedef typename remove_reference<Tp>::type Up;
        return static_cast<Up&&>(_t);
    }

    // forward()：用来保存类型信息，返回实参的右值引用
    template <class Tp>
    inline Tp&& forward(typename remove_reference<_Tp>::type& _t) noexcept{
        return static_cast<Tp&&>(_t);
    }

    template <class Tp>
    inline Tp&& forward(typename remove_reference<_Tp>::type&& _t) noexcept{
        static_assert(!is_lvalue_reference<Tp>::value, "cannot forward an rvalue as an lvalue");
        return static_cast<Tp&&>(_t);
    }


    // swap()
    template<class Tp>
    void swap(Tp& _l, Tp& _r){
        Tp _t = move(_l);
        _l = move(_r);
        _r = move(_t);
    }

    template<class Tp, size_t Np>
    void swap(Tp (&_a)[Np], Tp (&_b)[Np]){
        for (size_t i = 0;  i!=Np ; ++i) {
            swap(_a[i], _b[i]);
        }
    }


    // pair数据结构
    template<class T1, class T2>
    struct pair{
         typedef T1 first_type;
         typedef T2 second_type;

         T1 first;
         T2 second;

         pair(pair const&) = default;
         pair(pair&&) = default;


        /** std::enable_if，满足条件时类型有效。
         *
         *  template <bool, typename T=void>
         *  struct enable_if {};
         *
         *  template <typename T>
         *  struct enable_if<true, T> {
         *      using type = T;
         *  };
         *
         * 只有当第一个模板参数为 true 时，type 才有定义，否则使用 type 会产生编译错误，
         * 并且默认模板参数可以让你不必指定类型。
         * */
        // 默认构造函数
        template<class U1 = T1, class U2 = T2, typename = typename enable_if<
                std::is_default_constructible<U1>::value &&
                std::is_default_constructible<U2>::value>::type>
        constexpr pair() : first(), second() {}

        // 参数能隐式转换
        template<class U1 = T1, class U2 = T2, typename enable_if<
                std::is_copy_constructible<U1>::value &&
                std::is_copy_constructible<U2>::value &&
                std::is_convertible<const U1&, T1>::value &&
                std::is_convertible<const U2&, T2>::value, int>::type = 0>
        constexpr pair(const T1& _t1, const T2& _t2) : first(_t1), second(_t2) {}

        // 参数不能隐式转换
        template<class U1 = T1, class U2 = T2, typename enable_if<
                std::is_copy_constructible<U1>::value &&
                std::is_copy_constructible<U2>::value &&
                (!std::is_convertible<const U1&, T1>::value ||
                 !std::is_convertible<const U2&, T2>::value), int>::type = 0>
        explicit constexpr pair(const T1& _t1, const T2& _t2) : first(_t1), second(_t2) {}

        // 参数能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1>::value &&
                std::is_constructible<T2, U2>::value &&
                std::is_convertible<U1&&, T1>::value &&
                std::is_convertible<U2&&, T2>::value, int>::type = 0>
        constexpr pair(U1&& _u1, U2&& _u2)
        : first(simple_stl::forward<U1>(_u1)),
        second(simple_stl::forward<U2>(_u2)) {}

        // 参数不能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1>::value &&
                std::is_constructible<T2, U2>::value &&
                (!std::is_convertible<U1&&, T1>::value ||
                 !std::is_convertible<U2&&, T2>::value), int>::type = 0>
        explicit constexpr pair(U1&& _u1, U2&& _u2)
        : first(simple_stl::forward<U1>(_u1)),
        second(simple_stl::forward<U2>(_u2)) {}


        // 参数能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1 const&>::value &&
                std::is_constructible<T2, U2 const&>::value &&
                std::is_convertible<U1 const&, T1>::value &&
                std::is_convertible<U2 const&, T2>::value, int>::type = 0>
        constexpr pair(pair<U1, U2> const& _p)
        : first(_p.first), second(_p.second) {}

        // 参数不能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1 const&>::value &&
                std::is_constructible<T2, U2 const&>::value &&
                (!std::is_convertible<U1 const&, T1>::value ||
                 !std::is_convertible<U2 const&, T2>::value), int>::type = 0>
        explicit constexpr pair(pair<U1, U2> const& _p)
        : first(_p.first), second(_p.second) {}


        // 参数能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1>::value &&
                std::is_constructible<T2, U2>::value &&
                std::is_convertible<U1, T1>::value &&
                std::is_convertible<U2, T2>::value, int>::type = 0>
        constexpr pair(pair<U1, U2> const& _p)
        : first(simple_stl::forward<U1>(_p.first)),
        second(simple_stl::forward<U2>(_p.second)) {}

        // 参数不能隐式转换
        template<class U1, class U2, typename enable_if<
                std::is_constructible<T1, U1>::value &&
                std::is_constructible<T2, U2>::value &&
                (!std::is_convertible<U1, T1>::value ||
                 !std::is_convertible<U2, T2>::value), int>::type = 0>
        explicit constexpr pair(pair<U1, U2> const& _p)
        : first(simple_stl::forward<U1>(_p.first)),
        second(simple_stl::forward<U2>(_p.second)){}

        ~pair() = default;


        pair& operator=(const pair& _r){
            if (this != &_r){
                first = _r.first;
                second = _r.second;
            }
            return *this;
        }

        pair& operator=(pair&& _r){
            if (this != &_r){
                first = simple_stl::forward<first_type>(_r.first);
                second = simple_stl::forward<second_type>(_r.second);
            }
            return *this;
        }

        template<class U1, class U2>
        pair& operator=(const pair<U1, U2>& _r){
            first = _r.first;
            second = _r.second;
            return *this;
        }

        template<class U1, class U2>
        pair& operator=(pair<U1, U2>&& _r){
            first = simple_stl::forward<U1>(_r.first);
            second = simple_stl::forward<U2>(_r.second);
            return *this;
        }

        void swap(pair& _r){
            simple_stl::swap(first, _r.first);
            simple_stl::swap(second, _r.second);
        }
    };

    // 重载比较运算符
    template<class T1, class T2>
    inline bool operator==(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
        return _l.first == _r.first && _l.second == _r.second;
    }

    template<class T1, class T2>
    inline bool operator!=(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
            return !(_l == _r);
//        return _l.first != _r.first || _l.second != _r.second;
    }

    template<class T1, class T2>
    inline bool operator<(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
        return _l.first < _r.first || (!(_r.first < _l.first) && _l.second < _r.second);
    }

    template<class T1, class T2>
    inline bool operator>(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
        return _r < _l;
    }

    template<class T1, class T2>
    inline bool operator>=(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
        return !(_l < _r);
    }

    template<class T1, class T2>
    inline bool operator<=(const pair<T1, T2>& _l, const pair<T1, T2>& _r){
        return !(_r < _l);
    }

    // 重载 simple_stl 的 swap
    template<class T1, class T2>
    inline void swap(pair<T1, T2>& _l, pair<T1, T2>& _r){
        _l.swap(_r);

    }

    template<class T1, class T2>
    inline pair<T1, T2> make_pair(T1&& first, T2&& second){
        return pair<T1, T2>(simple_stl::forward<T1>(first), simple_stl::forward<T2>(second));
    }

}   // simple_stl

#endif //SIMPLESTL_UTILITY_H
