/**
 * Created by 史进 on 2023/5/31.
 *
 * 迭代器设计，包括迭代器类型以及涉及迭代器的一些全局函数
 */
#ifndef SIMPLESTL_ITERATOR_H
#define SIMPLESTL_ITERATOR_H

#include <cstddef>
#include "type_traits.h"

namespace simple_stl{
    // 迭代器类型
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag: public input_iterator_tag{};
    struct bidirectional_iterator_tag: public forward_iterator_tag{};
    struct random_access_iterator_tag: public bidirectional_iterator_tag{};

    // iterator 模版基类，避免挂一漏万
    template<class Category, class T, class Distance=ptrdiff_t,
            class Pointer=T*, class Reference=T&>
    struct iterator{
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

//    // traits 萃取迭代器特性（旧）
//    template<class Iterator>
//    struct iterator_traits{
//        typedef typename Iterator::iterator_category    iterator_category;
//        typedef typename Iterator::value_type           value_type;
//        typedef typename Iterator::difference_type      difference_type;
//        typedef typename Iterator::pointer              pointer;
//        typedef typename Iterator::reference            reference;
//    };

    // 新版本 iterator_traits
    template<class T>
    struct __has_iterator_category{
    private:
        struct __two {char __lx; char __rx;};
        template <class U> static __two __test(...);
        template <class U> static char __test(typename U::iterator_category* = nullptr);
    public:
        static const bool value = sizeof(__test<T>(nullptr)) == 1;
    };

    template <class Iterator, bool> struct __iterator_traits {};
    template <class Iterator, bool> struct __iterator_traits_impl {};

    template <class Iterator>
    struct __iterator_traits_impl<Iterator, true>
    {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    template <class Iterator>
    struct __iterator_traits<Iterator, true>
            :  __iterator_traits_impl
                       <Iterator,
                               std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
                               std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value
                       >
    {};
    //  C++ STL的std::is_convertible模板用于检查是否可以将任何数据类型A隐式转换为任何数据类型B。
    //  它返回布尔值true或false。

    // traits 萃取迭代器特性
    template <class Iterator>
    struct iterator_traits: __iterator_traits<Iterator, __has_iterator_category<Iterator>::value> {};


    // 针对原生指针T*的traits偏特化版本
    template<class T>
    struct iterator_traits<T*>{
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    // 针对原生指针的const T*的traits偏特化版本
    template<class T>
    struct iterator_traits<const T*>{
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };


    // C++ STL的std::is_convertible模板用于检查是否可以将任何数据类型A隐式转换为任何数据类型B。
    // 该模板用于检查是否可以将数据类型 T::iterator_category 隐式转换为数据类型 U
    template <class T, class U, bool = __has_iterator_category<iterator_traits<T> >::value>
    struct __has_iterator_category_convertible_to : std::is_convertible<typename iterator_traits<T>::iterator_category, U>
    {};

    template <class T, class U>
    struct __has_iterator_category_convertible_to<T, U, false> : __false_type_s {};

    template <class Iterator>
    struct is_input_iterator : __has_iterator_category_convertible_to<Iterator, input_iterator_tag> {};

    template <class Iterator>
    struct is_output_iterator : __has_iterator_category_convertible_to<Iterator, output_iterator_tag> {};

    template <class Iterator>
    struct is_forward_iterator : __has_iterator_category_convertible_to<Iterator, forward_iterator_tag> {};

    template <class Iterator>
    struct is_bidirectional_iterator : __has_iterator_category_convertible_to<Iterator, bidirectional_iterator_tag> {};

    template <class Iterator>
    struct is_random_access_iterator : __has_iterator_category_convertible_to<Iterator, random_access_iterator_tag> {};

    template <class Iterator>
    struct is_iterator : bool_constant_s<is_input_iterator<Iterator>::value ||is_output_iterator<Iterator>::value> {};


    // 萃取迭代器的特性
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&){
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }


    // distance()函数组
    // input_iterator_tag版
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    __distance(InputIterator first, InputIterator last, input_iterator_tag){
        typename iterator_traits<InputIterator>::difference_type n(0);
        // 逐一累计距离
        for (;  first!=last ; ++first) {
            ++n;
        }
        return n;
    }

    // random_access_iterator_tag版
    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
        // 直接计算差值
        return last-first;
    }

    // 外露接口
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last){
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return __distance(first, last, category());
    }


    // advance()函数组
    // input_iterator_tag版
    template<class InputIterator, class Distance>
    inline void __advance(InputIterator& i, Distance n,
                          input_iterator_tag){
        // 单向，逐一前进
        while (n--) i++;
    }

    // bidirectional_iterator_tag版
    template<class BidirectionalIterator, class Distance>
    inline void __advance(BidirectionalIterator& i, Distance n,
                          bidirectional_iterator_tag){
        // 双向，逐一前进
        if (n >= 0)
            for (; n > 0; --n)
                ++i;
        else
            for (; n < 0; ++n)
                --i;
    }

    // random_access_iterator_tag版
    template<class RandomAccessIterator, class Distance>
    inline void __advance(RandomAccessIterator& i, Distance n,
                          random_access_iterator_tag){
        // 双向，跳跃前进
        i += n;
    }

    // 外露接口
    template<class InputIterator, class Distance>
    inline void advance(InputIterator& i, Distance n){
        __advance(i, n, iterator_category(i));
    }









}   // simple_stl

#endif //SIMPLESTL_ITERATOR_H
