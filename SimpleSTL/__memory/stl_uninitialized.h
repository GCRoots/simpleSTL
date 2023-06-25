/**
 * Created by 史进 on 2023/6/2.
 *
 * 内存基本处理工具，作用于未初始化空间上
 *
 */
#ifndef SIMPLESTL_STL_UNINITIALIZED_H
#define SIMPLESTL_STL_UNINITIALIZED_H

#include "../iterator.h"
#include "../utility.h"
#include "stl_construct.h"

namespace simple_stl{

    /** uninitialized_copy() */
    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first, InputIterator last,
                             ForwardIterator result, __type_traits_s){
        // 调用copy函数
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first, InputIterator last,
                             ForwardIterator result, __false_type_s){
//        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        ForwardIterator stable = result;
        try {
            for( ; first!=last; ++first, ++result)
//                ::new ((void*)*result) value_type(*first);
                construct(&*result, *first);
        }catch(...){
            for ( ; stable!=result; ++stable)
                destroy(&*stable);
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator, class Tp>
    inline ForwardIterator
    __uninitialized_copy(InputIterator first, InputIterator last,
                         ForwardIterator result, Tp*){
        typedef typename __type_traits_s<Tp>::is_POD_type is_POD;
        return __uninitialized_copy_aux(first, last, result, is_POD());
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    uninitialized_copy(InputIterator first, InputIterator last,
                       ForwardIterator result){
        return __uninitialized_copy(first, last, result, value_type(first));
    }


    /** uninitialized_copy_n() */
    template<class InputIterator, class Size, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_n_aux(InputIterator first, Size n,
                               ForwardIterator result, __true_type_s){
        // 调用copy_n函数
    }

    template<class InputIterator, class Size, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_n_aux(InputIterator first, Size n,
                               ForwardIterator result, __true_type_s){
        ForwardIterator stable = result;
        try {
            for( ; n>0; ++first, ++result, --n)
                construct(&*result, *first);
        }catch(...){
            for ( ; stable!=result; ++stable)
                destroy(&*stable);
        }
        return result;
    }

    template<class InputIterator, class Size, class ForwardIterator, class Tp>
    inline ForwardIterator
    __uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result, Tp*){
        typedef typename __type_traits_s<Tp>::is_POD_type is_POD;
        return __uninitialized_copy_n_aux(first, n, result, is_POD());
    }

    template<class InputIterator, class Size, class ForwardIterator>
    inline ForwardIterator
    uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result){
        return __uninitialized_copy_n(first, n, result, value_type(first));
    }

    /** uninitialized_fill() */
    template<class ForwardIterator, class Tp>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                         const Tp& value, __true_type_s){
        // 调用fill函数
    }

    template<class ForwardIterator, class Tp>
    inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                         const Tp& value, __false_type_s){
        ForwardIterator stable = first;
        try {
            for( ; first!=last; ++first)
                construct(&*first, value);
        }catch(...){
            for ( ; stable!=first; ++stable)
                destroy(&*stable);
        }
    }

    template<class ForwardIterator, class Tp, class T>
    inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
                                   const Tp& value, T*){
        typedef typename __type_traits_s<T>::is_POD_type is_POD;
        __uninitialized_fill_aux(first, last, value, is_POD());
    }

    template<class ForwardIterator, class Tp>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                                   const Tp& value){
        __uninitialized_fill(first, last, value, value_type(first));
    }

    /** uninitialized_fill_n() */
    template<class ForwardIterator, class Size, class Tp>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                         const Tp& value, __true_type_s){
        // 调用fill_n函数
    }

    template<class ForwardIterator, class Size, class Tp>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                         const Tp& value, __false_type_s){
        ForwardIterator stable = first;
        try {
            for( ; n>0; ++first, --n)
                construct(&*first, value);
        }catch(...){
            for ( ; stable!=first; ++stable)
                destroy(&*stable);
        }
        return first;
    }

    template<class ForwardIterator, class Size, class Tp, class T>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n,
                                     const Tp& value, T*){
        typedef typename __type_traits_s<T>::is_POD_type is_POD;
        return __uninitialized_fill_n_aux(first, n, value, is_POD());
    }

    template<class ForwardIterator, class Size, class Tp>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                   const Tp& value){
        return __uninitialized_fill_n(first, n, value, value_type(first));
    }

    /** uninitialized_move() */
    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_move_aux(InputIterator first, InputIterator last,
                             ForwardIterator result, __type_traits_s){
        // 调用move函数
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_move_aux(InputIterator first, InputIterator last,
                             ForwardIterator result, __false_type_s){
//        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        ForwardIterator idx = result;
        try {
            for( ; first!=last; ++first, ++idx)
//                ::new ((void*)address_of(*idx)) value_type(move(*first));
                construct(&*idx, move(*first)

        }catch(...)
            destroy(result, idx)
        return idx;
    }

    template<class InputIterator, class ForwardIterator, class Tp>
    inline ForwardIterator
    __uninitialized_move(InputIterator first, InputIterator last,
                         ForwardIterator result, Tp*){
        typedef typename __type_traits_s<Tp>::is_POD_type is_POD;
        return __uninitialized_move_aux(first, last, result, is_POD());
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    uninitialized_move(InputIterator first, InputIterator last,
                       ForwardIterator result){
        return __uninitialized_move(first, last, result, value_type(first));
    }

    /** uninitialized_move_n() */
    template<class InputIterator, class Size, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_move_n_aux(InputIterator first, Size n,
                             ForwardIterator result, __type_traits_s){
        // 调用move_n函数
    }

    template<class InputIterator, class Size, class ForwardIterator>
    inline ForwardIterator
    __uninitialized_move_n_aux(InputIterator first, Size n,
                             ForwardIterator result, __false_type_s){
//        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        ForwardIterator idx = result;
        try {
            for( ; n>0; ++first, ++idx, --n)
//                ::new ((void*)address_of(*idx)) value_type(move(*first));
                construct(&*idx, move(*first)
        }catch(...)
        destroy(result, idx)
        return idx;
    }

    template<class InputIterator, class Size, class ForwardIterator, class Tp>
    inline ForwardIterator
    __uninitialized_move_n(InputIterator first, Size n,
                         ForwardIterator result, Tp*){
        typedef typename __type_traits_s<Tp>::is_POD_type is_POD;
        return __uninitialized_move_n_aux(first, n, result, is_POD());
    }

    template<class InputIterator,class Size, class ForwardIterator>
    inline ForwardIterator
    uninitialized_move_n(InputIterator first, Size n,
                       ForwardIterator result){
        return __uninitialized_move_n(first, n, result, value_type(first));
    }


}   // simple_stl

#endif //SIMPLESTL_STL_UNINITIALIZED_H
