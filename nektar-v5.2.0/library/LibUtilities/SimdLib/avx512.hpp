///////////////////////////////////////////////////////////////////////////////
//
// File: avx512.cpp
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
// Department of Aeronautics, Imperial College London (UK), and Scientific
// Computing and Imaging Institute, University of Utah (USA).
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Description: Vector type using avx512 extension.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_LIB_LIBUTILITES_SIMDLIB_AVX512_H
#define NEKTAR_LIB_LIBUTILITES_SIMDLIB_AVX512_H

#if defined(__x86_64__)
#include <immintrin.h>
#if defined(__INTEL_COMPILER) && !defined(TINYSIMD_HAS_SVML)
#define TINYSIMD_HAS_SVML
#endif
#endif
#include "allocator.hpp"
#include "avx2.hpp"
#include "traits.hpp"
#include <vector>

namespace tinysimd
{

namespace abi
{

template <typename scalarType> struct avx512
{
    using type = void;
};

} // namespace abi

#if defined(__AVX512F__) && defined(NEKTAR_ENABLE_SIMD_AVX512)

// forward declaration of concrete types
template <typename T> struct avx512Long8;
struct avx512Double8;
struct avx512Mask;

namespace abi
{

// mapping between abstract types and concrete types
template <> struct avx512<double>
{
    using type = avx512Double8;
};
template <> struct avx512<std::int64_t>
{
    using type = avx512Long8<std::int64_t>;
};
template <> struct avx512<std::uint64_t>
{
    using type = avx512Long8<std::uint64_t>;
};
template <> struct avx512<bool>
{
    using type = avx512Mask;
};

} // namespace abi

// concrete types, could add enable if to allow only unsigned long and long...
template <typename T> struct avx512Long8
{
    static_assert(std::is_integral<T>::value && sizeof(T) == 8,
                  "8 bytes Integral required.");

    static constexpr unsigned int width     = 8;
    static constexpr unsigned int alignment = 64;

    using scalarType  = T;
    using vectorType  = __m512i;
    using scalarArray = scalarType[width];

    // storage
    vectorType _data;

    // ctors
    inline avx512Long8()                       = default;
    inline avx512Long8(const avx512Long8 &rhs) = default;
    inline avx512Long8(const vectorType &rhs) : _data(rhs)
    {
    }
    inline avx512Long8(const scalarType rhs)
    {
        _data = _mm512_set1_epi64(rhs);
    }
    explicit inline avx512Long8(scalarArray &rhs)
    {
        _data = _mm512_load_epi64(rhs);
    }

    // store
    inline void store(scalarType *p) const
    {
        _mm512_store_epi64(p, _data);
    }

    template <class flag,
              typename std::enable_if<is_requiring_alignment<flag>::value &&
                                          !is_streaming<flag>::value,
                                      bool>::type = 0>
    inline void store(scalarType *p, flag) const
    {
        _mm512_store_epi64(p, _data);
    }

    template <class flag,
              typename std::enable_if<!is_requiring_alignment<flag>::value,
                                      bool>::type = 0>
    inline void store(scalarType *p, flag) const
    {
        _mm512_storeu_epi64(p, _data);
    }

    inline void load(const scalarType *p)
    {
        _data = _mm512_load_epi64(p);
    }

    template <class flag,
              typename std::enable_if<is_requiring_alignment<flag>::value &&
                                          !is_streaming<flag>::value,
                                      bool>::type = 0>
    inline void load(const scalarType *p, flag)
    {
        _data = _mm512_load_epi64(p);
    }

    template <class flag,
              typename std::enable_if<!is_requiring_alignment<flag>::value,
                                      bool>::type = 0>
    inline void load(const scalarType *p, flag)
    {
        // even though the intel intrisic manual lists
        // __m512i _mm512_loadu_epi64 (void const* mem_addr)
        // it is not implemented in some compilers (gcc)
        // since this is a bitwise load with no extension
        // the following instruction is equivalent
        _data = _mm512_loadu_si512(p);
    }

    inline void broadcast(const scalarType rhs)
    {
        _data = _mm512_set1_epi64(rhs);
    }

    // subscript
    // subscript operators are convienient but expensive
    // should not be used in optimized kernels
    inline scalarType operator[](size_t i) const
    {
        alignas(alignment) scalarArray tmp;
        store(tmp, is_aligned);
        return tmp[i];
    }
};

template <typename T>
inline avx512Long8<T> operator+(avx512Long8<T> lhs, avx512Long8<T> rhs)
{
    return _mm512_add_epi64(lhs._data, rhs._data);
}

template <
    typename T, typename U,
    typename = typename std::enable_if<std::is_arithmetic<U>::value>::type>
inline avx512Long8<T> operator+(avx512Long8<T> lhs, U rhs)
{
    return _mm512_add_epi64(lhs._data, _mm512_set1_epi64(rhs));
}

////////////////////////////////////////////////////////////////////////////////

struct avx512Double8
{
    static constexpr unsigned int width     = 8;
    static constexpr unsigned int alignment = 64;

    using scalarType  = double;
    using vectorType  = __m512d;
    using scalarArray = scalarType[width];

    // storage
    vectorType _data;

    // ctors
    inline avx512Double8()                         = default;
    inline avx512Double8(const avx512Double8 &rhs) = default;
    inline avx512Double8(const vectorType &rhs) : _data(rhs)
    {
    }
    inline avx512Double8(const scalarType rhs)
    {
        _data = _mm512_set1_pd(rhs);
    }

    // store
    inline void store(scalarType *p) const
    {
        _mm512_store_pd(p, _data);
    }

    template <class flag,
              typename std::enable_if<is_requiring_alignment<flag>::value &&
                                          !is_streaming<flag>::value,
                                      bool>::type = 0>
    inline void store(scalarType *p, flag) const
    {
        _mm512_store_pd(p, _data);
    }

    template <class flag,
              typename std::enable_if<!is_requiring_alignment<flag>::value,
                                      bool>::type = 0>
    inline void store(scalarType *p, flag) const
    {
        _mm512_storeu_pd(p, _data);
    }

    template <class flag, typename std::enable_if<is_streaming<flag>::value,
                                                  bool>::type = 0>
    inline void store(scalarType *p, flag) const
    {
        _mm512_stream_pd(p, _data);
    }

    // load packed
    inline void load(const scalarType *p)
    {
        _data = _mm512_load_pd(p);
    }

    template <class flag,
              typename std::enable_if<is_requiring_alignment<flag>::value,
                                      bool>::type = 0>
    inline void load(const scalarType *p, flag)
    {
        _data = _mm512_load_pd(p);
    }

    template <class flag,
              typename std::enable_if<!is_requiring_alignment<flag>::value,
                                      bool>::type = 0>
    inline void load(const scalarType *p, flag)
    {
        _data = _mm512_loadu_pd(p);
    }

    // broadcast
    inline void broadcast(const scalarType rhs)
    {
        _data = _mm512_set1_pd(rhs);
    }

    // gather/scatter
    // template <typename T>
    // inline void gather(scalarType const* p, const avx2Int8<T>& indices)
    // {
    //     _data = _mm512_i32gather_pd(indices._data, p, 8);
    // }

    // template <typename T>
    // inline void scatter(scalarType* out, const avx2Int8<T>& indices) const
    // {
    //     _mm512_i32scatter_pd(out, indices._data, _data, 8);
    // }

    template <typename T>
    inline void gather(scalarType const *p, const avx512Long8<T> &indices)
    {
        _data = _mm512_i64gather_pd(indices._data, p, 8);
    }

    template <typename T>
    inline void scatter(scalarType *out, const avx512Long8<T> &indices) const
    {
        _mm512_i64scatter_pd(out, indices._data, _data, 8);
    }

    // fma
    // this = this + a * b
    inline void fma(const avx512Double8 &a, const avx512Double8 &b)
    {
        _data = _mm512_fmadd_pd(a._data, b._data, _data);
    }

    // subscript
    // subscript operators are convienient but expensive
    // should not be used in optimized kernels
    inline scalarType operator[](size_t i) const
    {
        alignas(alignment) scalarArray tmp;
        store(tmp, is_aligned);
        return tmp[i];
    }

    // unary ops
    inline void operator+=(avx512Double8 rhs)
    {
        _data = _mm512_add_pd(_data, rhs._data);
    }

    inline void operator-=(avx512Double8 rhs)
    {
        _data = _mm512_sub_pd(_data, rhs._data);
    }

    inline void operator*=(avx512Double8 rhs)
    {
        _data = _mm512_mul_pd(_data, rhs._data);
    }

    inline void operator/=(avx512Double8 rhs)
    {
        _data = _mm512_div_pd(_data, rhs._data);
    }
};

inline avx512Double8 operator+(avx512Double8 lhs, avx512Double8 rhs)
{
    return _mm512_add_pd(lhs._data, rhs._data);
}

inline avx512Double8 operator-(avx512Double8 lhs, avx512Double8 rhs)
{
    return _mm512_sub_pd(lhs._data, rhs._data);
}

inline avx512Double8 operator*(avx512Double8 lhs, avx512Double8 rhs)
{
    return _mm512_mul_pd(lhs._data, rhs._data);
}

inline avx512Double8 operator/(avx512Double8 lhs, avx512Double8 rhs)
{
    return _mm512_div_pd(lhs._data, rhs._data);
}

inline avx512Double8 sqrt(avx512Double8 in)
{
    return _mm512_sqrt_pd(in._data);
}

inline avx512Double8 abs(avx512Double8 in)
{
    return _mm512_abs_pd(in._data);
}

inline avx512Double8 log(avx512Double8 in)
{
#if defined(TINYSIMD_HAS_SVML)
    return _mm512_log_pd(in._data);
#else
    // there is no avx512 log intrinsic
    // this is a dreadful implementation and is simply a stop gap measure
    alignas(avx512Double8::alignment) avx512Double8::scalarArray tmp;
    in.store(tmp);
    tmp[0] = std::log(tmp[0]);
    tmp[1] = std::log(tmp[1]);
    tmp[2] = std::log(tmp[2]);
    tmp[3] = std::log(tmp[3]);
    tmp[4] = std::log(tmp[4]);
    tmp[5] = std::log(tmp[5]);
    tmp[6] = std::log(tmp[6]);
    tmp[7] = std::log(tmp[7]);
    avx512Double8 ret;
    ret.load(tmp);
    return ret;
#endif
}

inline void load_interleave(
    const double *in, size_t dataLen,
    std::vector<avx512Double8, allocator<avx512Double8>> &out)
{

    alignas(avx512Double8::alignment) size_t tmp[avx512Double8::width] = {
        0,           dataLen,     2 * dataLen, 3 * dataLen,
        4 * dataLen, 5 * dataLen, 6 * dataLen, 7 * dataLen};

    using index_t = avx512Long8<size_t>;
    index_t index0(tmp);
    index_t index1 = index0 + 1;
    index_t index2 = index0 + 2;
    index_t index3 = index0 + 3;

    // 4x unrolled loop
    constexpr uint16_t unrl = 4;
    size_t nBlocks          = dataLen / unrl;
    for (size_t i = 0; i < nBlocks; ++i)
    {
        out[unrl * i + 0].gather(in, index0);
        out[unrl * i + 1].gather(in, index1);
        out[unrl * i + 2].gather(in, index2);
        out[unrl * i + 3].gather(in, index3);
        index0 = index0 + unrl;
        index1 = index1 + unrl;
        index2 = index2 + unrl;
        index3 = index3 + unrl;
    }

    // spillover loop
    for (size_t i = unrl * nBlocks; i < dataLen; ++i)
    {
        out[i].gather(in, index0);
        index0 = index0 + 1;
    }
}

inline void deinterleave_store(
    const std::vector<avx512Double8, allocator<avx512Double8>> &in,
    size_t dataLen, double *out)
{
    // size_t nBlocks = dataLen / 4;

    alignas(avx512Double8::alignment) size_t tmp[avx512Double8::width] = {
        0,           dataLen,     2 * dataLen, 3 * dataLen,
        4 * dataLen, 5 * dataLen, 6 * dataLen, 7 * dataLen};
    using index_t = avx512Long8<size_t>;
    index_t index0(tmp);
    // index_t index1 = index0 + 1;
    // index_t index2 = index0 + 2;
    // index_t index3 = index0 + 3;

    // // 4x unrolled loop
    // for (size_t i = 0; i < nBlocks; ++i)
    // {
    //     in[i].scatter(out, index0);
    //     in[i+1].scatter(out, index1);
    //     in[i+2].scatter(out, index2);
    //     in[i+3].scatter(out, index3);
    //     index0 = index0 + 4;
    //     index1 = index1 + 4;
    //     index2 = index2 + 4;
    //     index3 = index3 + 4;
    // }

    // // spillover loop
    // for (size_t i = 4 * nBlocks; i < dataLen; ++i)
    // {
    //     in[i].scatter(out, index0);
    //     index0 = index0 + 1;
    // }

    for (size_t i = 0; i < dataLen; ++i)
    {
        in[i].scatter(out, index0);
        index0 = index0 + 1;
    }
}

////////////////////////////////////////////////////////////////////////////////

// mask type
// mask is a int type with special properties (broad boolean vector)
// broad boolean vectors defined and allowed values are:
// false=0x0 and true=0xFFFFFFFF
//
// VERY LIMITED SUPPORT...just enough to make cubic eos work...
//
struct avx512Mask : avx512Long8<std::uint64_t>
{
    // bring in ctors
    using avx512Long8::avx512Long8;

    static constexpr scalarType true_v  = -1;
    static constexpr scalarType false_v = 0;
};

inline avx512Mask operator>(avx512Double8 lhs, avx512Double8 rhs)
{
    __mmask8 mask = _mm512_cmp_pd_mask(lhs._data, rhs._data, _CMP_GT_OQ);
    return _mm512_maskz_set1_epi64(mask, avx512Mask::true_v);
}

inline bool operator&&(avx512Mask lhs, bool rhs)
{
    __m512i val_true = _mm512_set1_epi64(avx512Mask::true_v);
    __mmask8 mask    = _mm512_test_epi64_mask(lhs._data, val_true);
    unsigned int tmp = _cvtmask16_u32(mask);
    return tmp && rhs;
}

#endif // defined(__avx512__)

} // namespace tinysimd
#endif
