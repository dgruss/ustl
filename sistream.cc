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
// sistream.cc
//

#include "sistream.h"
#include "sostream.h"
#include "ustring.h"
#include "utf8.h"

namespace ustl {

namespace ios {
    const char* c_DefaultDelimiters = " \t\n\r;:,.?";
}

istringstream::istringstream (void)
: istream (),
  m_Base (10),
  m_DecimalSeparator ('.'),
  m_ThousandSeparator ('\0')
{
    set_delimiters (ios::c_DefaultDelimiters);
}

istringstream::istringstream (const void* p, size_t n)
: istream (),
  m_Base (10),
  m_DecimalSeparator ('.'),
  m_ThousandSeparator ('\0')
{
    link (p, n);
    set_delimiters (ios::c_DefaultDelimiters);
}

istringstream::istringstream (const cmemlink& source)
: istream (),
  m_Base (10),
  m_DecimalSeparator ('.'),
  m_ThousandSeparator ('\0')
{
    link (source);
    set_delimiters (ios::c_DefaultDelimiters);
}

void istringstream::set_delimiters (const char* delimiters)
{
    strncpy (m_Delimiters, delimiters, c_MaxDelimiters);
}

inline bool istringstream::is_delimiter (char c) const
{
    return (NULL != memchr (m_Delimiters, c, c_MaxDelimiters));
}

char istringstream::skip_delimiters (void)
{
    char c = m_Delimiters[0];
    while (is_delimiter(c) && (remaining() || underflow()))
	istream::iread (c);
    return (c);
}

void istringstream::iread (int8_t& v)
{
    v = skip_delimiters();
}

void istringstream::iread (int32_t& v)
{
    int32_t base = m_Base;
    v = 0;
    char c = skip_delimiters();
    bool negative = (c == '-');
    if (negative && (remaining() || underflow()))
	istream::iread (c);
    if (c == '0') {
	base = 8;
	istream::iread (c);
	if (c == 'x') {
	    base = 16;
	    istream::iread (c);
	}
    }
    while (true) {
	register long digit;
	if (c >= '0' && c <= '9')
	    digit = c - '0';
	else if (c >= 'a' && c <= 'z' && c < base - 10 + 'a')
	    digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z' && c < base - 10 + 'a')
	    digit = c - 'A' + 10;
	else if (c == m_ThousandSeparator) {
	    istream::iread (c);
	    continue;
	} else
	    break;
	v *= base;
	v += digit;
	if (!remaining() && !underflow())
	    break;
	istream::iread (c);
    }
    ungetc();
    if (negative)
	v = -v;
}

#if HAVE_INT64_T
void istringstream::iread (int64_t& v)
{
    int64_t base = m_Base;
    v = 0;
    char c = skip_delimiters();
    bool negative = (c == '-');
    if (negative && (remaining() || underflow()))
	istream::iread (c);
    if (c == '0') {
	base = 8;
	istream::iread (c);
	if (c == 'x') {
	    base = 16;
	    istream::iread (c);
	}
    }
    while (true) {
	long long digit;
	if (c >= '0' && c <= '9')
	    digit = c - '0';
	else if (c >= 'a' && c <= 'z' && c < base - 10 + 'a')
	    digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z' && c < base - 10 + 'a')
	    digit = c - 'A' + 10;
	else if (c == m_ThousandSeparator) {
	    istream::iread (c);
	    continue;
	} else
	    break;
	v *= base;
	v += digit;
	if (!remaining() && !underflow())
	    break;
	istream::iread (c);
    }
    ungetc();
    if (negative)
	v = -v;
}
#endif

#if HAVE_LONG_LONG && (!HAVE_INT64_T || SIZE_OF_LONG_LONG > 8)
void istringstream::iread (long long& v)
{
    long long base = m_Base;
    v = 0;
    char c = skip_delimiters();
    bool negative = (c == '-');
    if (negative && (remaining() || underflow()))
	istream::iread (c);
    if (c == '0') {
	base = 8;
	istream::iread (c);
	if (c == 'x') {
	    base = 16;
	    istream::iread (c);
	}
    }
    while (true) {
	long long digit;
	if (c >= '0' && c <= '9')
	    digit = c - '0';
	else if (c >= 'a' && c <= 'z' && c < base - 10 + 'a')
	    digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z' && c < base - 10 + 'a')
	    digit = c - 'A' + 10;
	else if (c == m_ThousandSeparator) {
	    istream::iread (c);
	    continue;
	} else
	    break;
	v *= base;
	v += digit;
	if (!remaining() && !underflow())
	    break;
	istream::iread (c);
    }
    ungetc();
    if (negative)
	v = -v;
}
#endif

void istringstream::iread (wchar_t& v)
{
    uint8_t c;
    operator>> (*this, c);
    size_t cs = Utf8SequenceBytes (c);
    if (remaining() < cs && underflow() < cs)
	v = c;
    else {
	ungetc();
	istream_iterator<uint8_t> si (*this);
	v = *utf8in(si); // istream_iterator already read ahead.
    }
}

void istringstream::iread (double& v)
{
    register long base = m_Base;
    v = 0;
    char c = skip_delimiters();
    bool negative = (c == '-');
    bool beforedot = true;
    double divisor = 1.0;
    while (true) {
	register long digit;
	if (c >= '0' && c <= '9')
	    digit = c - '0';
	else if (c >= 'a' && c <= 'z' && c < base - 10 + 'a')
	    digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z' && c < base - 10 + 'a')
	    digit = c - 'A' + 10;
	else if (c == m_DecimalSeparator) {
	    beforedot = false;
	    istream::iread (c);
	    continue;
	} else if (c == m_ThousandSeparator) {
	    istream::iread (c);
	    continue;
	} else
	    break;
	if (beforedot) {
	    v *= base;
	    v += digit;
	} else {
	    divisor *= base;
	    v += digit / divisor;
	}
	if (!remaining() && !underflow())
	    break;
	istream::iread (c);
    }
    ungetc();
    if (negative)
	v = -v;
}

void istringstream::iread (bool& v)
{
    char c = skip_delimiters();
    v = (c == '1' || c == 't');
    if (c == 't' && (remaining() || underflow())) {
	istream::iread (c);
	if (c == 'r' && remaining() >= 2 * sizeof(char))
	    skip (2 * sizeof(char));
	else
	    ungetc();
    } else if (c == 'f' && (remaining() || underflow())) {
	istream::iread (c);
	if (c == 'a' && remaining() >= 3 * sizeof(char))
	    skip (3 * sizeof(char));
	else
	    ungetc();
    }
}

void istringstream::iread (string& v)
{
    v.clear();
    char prevc, quoteChar = 0, c = skip_delimiters();
    if (c == '\"' || c == '\'')
	quoteChar = c;
    else
	v += c;
    while (remaining() || underflow()) {
	prevc = c;
	istream::iread (c);
	if (!quoteChar && is_delimiter(c))
	    break;
	if (prevc == '\\') {
	    switch (c) {
		case 't':	c = '\t'; break;
		case 'n':	c = '\n'; break;
		case 'r':	c = '\r'; break;
		case 'b':	c = '\b'; break;
		case 'E':	c = 27;   break; // ESC sequence
		case '\"':	c = '\"'; break;
		case '\'':	c = '\''; break;
		case '\\':	c = '\\'; break;
	    };
	    *(v.end() - 1) = c;
	} else {
	    if (c == quoteChar)
		break;
	    v += c;
	}
    }
}

void istringstream::read (void* buffer, size_t sz)
{
    if (remaining() < sz && underflow(sz) < sz)
#ifdef WANT_STREAM_BOUNDS_CHECKING
	throw stream_bounds_exception ("read", "", pos(), sz - pos(), remaining());
#else
	assert (remaining() >= size());
#endif
    istream::read (buffer, sz);
}

void istringstream::read (memlink& buf)
{
    if (remaining() < buf.size() && underflow(buf.size()) < buf.size())
#ifdef WANT_STREAM_BOUNDS_CHECKING
	throw stream_bounds_exception ("read", "", pos(), buf.size() - pos(), remaining());
#else
	assert (remaining() >= buf.size());
#endif
    istream::read (buf);
}

} // namespace ustl

