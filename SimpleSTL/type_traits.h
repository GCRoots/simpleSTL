/**
 * Created by 史进 on 2023/5/13.
 *
 * 用于萃取类型信息
 */
#ifndef SIMPLESTL_TYPE_TRAITS_H
#define SIMPLESTL_TYPE_TRAITS_H

#include <type_traits>

namespace simple_stl{

    template <class T, T _v>
    struct integral_constant_s{
        static constexpr T value = _v;
    };

    template <bool _b>
    using bool_constant_s = integral_constant_s<bool, _b>;
    typedef bool_constant_s<true>   __true_type_s
    typedef bool_constant_s<false>  __false_type_s

    // 萃取类型信息
    template<class Type>
    struct __type_traits_s{
        typedef __true_type_s   this_dummy_member_must_be_first;

        typedef __false_type_s  have_trivial_default_constructor;
        typedef __false_type_s  have_trivial_copy_constructor;
        typedef __false_type_s  have_trivial_assignment_operator;
        typedef __false_type_s  have_trivial_destructor;
        typedef __false_type_s  is_POD_type;
    };

    // 为cpp基本类型提供特化版本
    // 包括：char, signed char, unsigned char, short, unsigned short, int, unsigned int,
    // long, unsigned long, float, double, long double
    template<> struct __type_traits_s<char>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<signed char>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<unsigned char>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<short>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<unsigned short>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<int>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<unsigned int>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<long>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<unsigned long>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<float>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<double>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    template<> struct __type_traits_s<long double>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };

    // 针对原生指针进行特化
    template<class T> struct __type_traits_s<T*>{
        typedef __true_type_s  have_trivial_default_constructor;
        typedef __true_type_s  have_trivial_copy_constructor;
        typedef __true_type_s  have_trivial_assignment_operator;
        typedef __true_type_s  have_trivial_destructor;
        typedef __true_type_s  is_POD_type;
    };


    template <class Tp> struct is_lvalue_reference      : public __false_type_s {};
    template <class Tp> struct is_lvalue_reference<Tp&> : public __true_type_s {};

    template <class Tp> struct is_rvalue_reference       : public __false_type_s {};
    template <class Tp> struct is_rvalue_reference<Tp&&> : public __true_type_s {};

    template <class Tp> struct is_reference       : public __false_type_s {};
    template <class Tp> struct is_reference<Tp&>  : public __true_type_s {};
    template <class Tp> struct is_reference<Tp&&> : public __true_type_s {};



    // remove_reference()
    template <class Tp> struct  remove_reference        {typedef  Tp type;};
    template <class Tp> struct  remove_reference<Tp&>   {typedef  Tp type;};
    template <class Tp> struct  remove_reference<Tp&&>  {typedef  Tp type;};

    template <bool, typename Tp=void>
    struct enable_if {};

    template <typename Tp>
    struct enable_if<true, Tp> {typedef Tp type;};




}   // simple_stl


#endif //SIMPLESTL_TYPE_TRAITS_H
