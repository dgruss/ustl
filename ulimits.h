// This file is part of the ustl library, an STL implementation.
// Copyright (C) 2003 by Mike Sharov <msharov@talentg.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the 
// Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
// Boston, MA  02111-1307  USA.
//
// ulimits.h
//

#ifndef ULIMITS_H_1C2192EA3821E0811BBAF86B0F048364
#define ULIMITS_H_1C2192EA3821E0811BBAF86B0F048364

namespace ustl {

/// \class numeric_limits ulimits.h ustl.h
/// Defines numeric limits for a type.
template <typename T> 
struct numeric_limits {
    /// Returns the minimum value for type T.
    static inline T min (void)		{ return (static_cast<T>(0)); }
    /// Returns the minimum value for type T.
    static inline T max (void)		{ return (static_cast<T>(0)); }
    /// Returns true if the type is signed.
    static inline bool is_signed (void)	{ return (false); }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <>
struct numeric_limits<bool> {
    static inline bool min (void)	{ return (false); }
    static inline bool max (void)	{ return ( true); }
    static inline bool is_signed (void)	{ return (false); }
};

template <>
struct numeric_limits<char> {
    static inline char min (void)	{ return (SCHAR_MIN); }
    static inline char max (void)	{ return (SCHAR_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<int> {
    static inline int min (void)	{ return (INT_MIN); }
    static inline int max (void)	{ return (INT_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<short> {
    static inline short min (void)	{ return (SHRT_MIN); }
    static inline short max (void)	{ return (SHRT_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<long> {
    static inline long min (void)	{ return (LONG_MIN); }
    static inline long max (void)	{ return (LONG_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<unsigned char> {
    static inline unsigned char min (void)	{ return (0); }
    static inline unsigned char max (void)	{ return (UCHAR_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};

template <>
struct numeric_limits<unsigned int> {
    static inline unsigned int min (void)	{ return (0); }
    static inline unsigned int max (void)	{ return (UINT_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};

template <>
struct numeric_limits<unsigned short> {
    static inline unsigned short min (void)	{ return (0); }
    static inline unsigned short max (void)	{ return (USHRT_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};

template <>
struct numeric_limits<unsigned long> {
    static inline unsigned long min (void)	{ return (0); }
    static inline unsigned long max (void)	{ return (ULONG_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};

#ifdef WCHAR_MAX
template <>
struct numeric_limits<wchar_t> {
    static inline wchar_t min (void)		{ return (0); }
    static inline wchar_t max (void)		{ return (WCHAR_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};
#endif

template <>
struct numeric_limits<float> {
    static inline float min (void)	{ return (FLT_MIN); }
    static inline float max (void)	{ return (FLT_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<double> {
    static inline double min (void)	{ return (DBL_MIN); }
    static inline double max (void)	{ return (DBL_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<long double> {
    static inline long double min (void){ return (LDBL_MIN); }
    static inline long double max (void){ return (LDBL_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

#ifdef HAVE_LONG_LONG
#ifndef LLONG_MAX
    #define ULLONG_MAX	UINT64_C(0xFFFFFFFFFFFFFFFF)
    #define LLONG_MAX	INT64_C(0x7FFFFFFFFFFFFFFF)
    #define LLONG_MIN	ULLONG_MAX
#endif

template <>
struct numeric_limits<long long> {
    static inline long long min (void)	{ return (LLONG_MIN); }
    static inline long long max (void)	{ return (LLONG_MAX); }
    static inline bool is_signed (void)	{ return (true); }
};

template <>
struct numeric_limits<unsigned long long> {
    static inline unsigned long long min (void)	{ return (0); }
    static inline unsigned long long max (void)	{ return (ULLONG_MAX); }
    static inline bool is_signed (void)		{ return (false); }
};
#endif
#endif // DOXYGEN_SHOULD_SKIP_THIS

} // namespace ustl

#endif

