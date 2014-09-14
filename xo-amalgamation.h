// These warnings are for stb_image.c
#ifdef _MSC_VER
#pragma warning(push)          // push XO-AMALGAMATION-DISABLED-WARNINGS
#pragma warning(disable: 4251) // class needs to have dll-interface to be used by clients of class
#pragma warning(disable: 6001) // using uninitialized memory
#pragma warning(disable: 6246) // local declaration hides name in outer scope
#pragma warning(disable: 6262) // stack size
#pragma warning(disable: 6385) // reading invalid data
#endif

#ifndef ASSERT
	#define TEMP_ASSERT
	#ifdef _DEBUG
		#define ASSERT(condition) (void)0
	#else
		#define ASSERT(condition) assert(condition)
	#endif
#endif

#ifdef _WIN32
	#define XO_BUILD_DIRECTX 1
#else
	#define XO_BUILD_DIRECTX 0
#endif

#define XO_BUILD_OPENGL 1
#define PROJECT_XO 1

#ifdef _WIN32
#ifndef XOAPI
#define XOAPI __declspec(dllexport)
#else
#define XOAPI __declspec(dllimport)
#endif
#else
#define XOAPI
#endif


#ifdef _WIN32
#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <Shlobj.h>
#include <tchar.h>
#else
#define XO_BUILD_OPENGL 1
#ifdef ANDROID
// Android
#define XO_BUILD_OPENGL_ES 1
#include <jni.h>
#include <android/log.h>
#include <sys/atomics.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#endif
#ifdef XO_BUILD_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#endif
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#endif

#if XO_BUILD_DIRECTX
#include <D3D11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#endif

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <float.h>

#include <string>
#include <algorithm>
#include <limits>
#include <functional>


#ifndef _WIN32
typedef const wchar_t* LPCTSTR;
typedef const char* LPCSTR;
#endif

#if PROJECT_XO
#ifdef _WIN32
#define PAPI __declspec(dllexport)
#else
#define PAPI
#endif
#else
#ifdef _WIN32
#define PAPI __declspec(dllimport)
#else
#define PAPI
#endif
#endif

#define NO_XSTRING

#ifndef INLINE
#define INLINE inline
#endif

#ifndef _TCHAR_DEFINED
typedef char TCHAR;
#endif

#ifndef _INC_TCHAR
//#define _T(x) L ## x
#define _T(x) x
#endif


// Definitions fit for inclusion into any C++ project, for any architecture

// Found this in the Chrome sources, via a PVS studio blog post
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class.
// A common layout is this:
//   class Foo
//   {
//       DISALLOW_COPY_AND_ASSIGN(Foo);
//   public:
//       ...
//   }
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);               \
void operator=(const TypeName&)

#ifdef _MSC_VER
#define NORETURN __declspec(noreturn)
#else
#define NORETURN __attribute__ ((noreturn))
#endif

#ifdef _MSC_VER
#	if _M_X64
#		define ARCH_64 1
#	endif
#else
#	if __SIZEOF_POINTER__ == 8
#		define ARCH_64 1
#	endif
#endif


// This file contains macros for compiler-specific things such as specifying struct alignment

#ifdef _WIN32
#define ABC_ALIGN(alignment)			__declspec(align(alignment))
#define ABC_ALIGNED(type, alignment)	__declspec(align(alignment)) type
#else
#define ABC_ALIGN(alignment)			__attribute__ ((aligned(alignment)))
#define ABC_ALIGNED(type, alignment)	type __attribute__ ((aligned(alignment)))
#endif

#define ABC_ALIGNED_TYPE(_type, alignment) typedef _type ABC_ALIGN(alignment)


#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define GCC_DIAG_STR(s) #s
#define GCC_DIAG_JOINSTR(x,y) GCC_DIAG_STR(x ## y)
# define GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
# define GCC_DIAG_PRAGMA(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
# if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#  define GCC_DIAG_OFF(x)    GCC_DIAG_PRAGMA(push) \
GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#  define GCC_DIAG_ON(x)     GCC_DIAG_PRAGMA(pop)
# else
#  define GCC_DIAG_OFF(x)    GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#  define GCC_DIAG_ON(x)     GCC_DIAG_PRAGMA(warning GCC_DIAG_JOINSTR(-W,x))
# endif
#else
# define GCC_DIAG_OFF(x)
# define GCC_DIAG_ON(x)
#endif





// Necessary on some linux stdint.h, to get INT32_MAX etc.
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif


#ifdef _WIN32
// This block here is necessary to quiet macro redefinition warnings from including stdint.h and intsafe.h.
// Issue https://connect.microsoft.com/VisualStudio/feedback/details/621653/including-stdint-after-intsafe-generates-warnings
#pragma warning( push )
#pragma warning( disable: 4005 ) // macro redef.
#pragma warning( pop )
#else
#endif

typedef signed char		i8;			// preferred (i8)
typedef signed char		int8;
typedef signed char		int8_t;
typedef unsigned char	u8;			// preferred (u8)
typedef unsigned char	uint8;
typedef unsigned char	uint8_t;
typedef unsigned char	byte;
typedef int int32;					// preferred (int or int32) -- see also intr/intp below
typedef int INT32;
typedef int int32_t;
typedef short i16;					// preferred (i16)
typedef short int16_t;
typedef short int16;
typedef unsigned int u32;			// preferred (u32) -- see also intr/intp below
typedef unsigned int uint;
typedef unsigned int UINT;
typedef unsigned int uint32;
typedef unsigned int UINT32;
typedef unsigned int uint32_t;
typedef unsigned short u16;			// preferred (u16)
typedef unsigned short uint16;
typedef unsigned short uint16_t;


#ifdef _MSC_VER
typedef __int64 i64;				// preferred (i64) -- see also intr/intp below
typedef __int64 int64;
typedef __int64 int64_t;
typedef __int64 INT64;
typedef unsigned __int64 u64;		// preferred (u64) -- see also intr/intp below
typedef unsigned __int64 uint64;
typedef unsigned __int64 uint64_t;
typedef unsigned __int64 UINT64;
#else
typedef int64_t		i64;
typedef int64_t		int64;
typedef int64_t		INT64;
typedef uint64_t	u64;
typedef uint64_t	uint64;
typedef uint64_t	UINT64;
#endif

// These are suggestions by Charles Bloom:
// intr: size of register
// intp: size of pointer
// intp and intr are the same on Windows x86/x64, but not true for all architectures.
// Here we assume that pointer and register sizes are always the same.
#if ARCH_64
typedef int64 intr;
typedef int64 intp;
typedef uint64 uintr;
typedef uint64 uintp;
#else
typedef int32 intr;
typedef int32 intp;
typedef unsigned int uintr;
typedef unsigned int uintp;
#endif

typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;

typedef UINT8 BYTE;
typedef INT16 SHORT;
typedef UINT16 WORD;

#ifndef _WIN32
typedef UINT32 DWORD;
#endif

// These macros are an unfortunate necessity to deal with the confusion between LP64 and LLP64 models
// that Unix and Windows employ. Use these macros when declaring 64-bit integer constants.
#ifdef _MSC_VER
#	define CONST_I64(n) n ## ll
#	define CONST_U64(n) n ## ull
#else
#	if __WORDSIZE == 64
#		define CONST_I64(n) n ## l
#		define CONST_U64(n) n ## ul
#	else
#		define CONST_I64(n) n ## ll
#		define CONST_U64(n) n ## ull
#	endif
#endif

// Don't use these. Instead, use %lld and %llu. Those work for all platforms. Note that the 'd' and 'u' are essential.
// HOWEVER, if you need to scanf a 64-bit hex string, then you have to use PRIx64
#ifdef _WIN32
//#define PRIu64 "I64u"
//#define PRId64 "I64d"
#	ifndef PRIu64
#		define PRIu64 ((void) static_assert(false, "Use %llu instead"))
#	endif
#	ifndef PRIu64
#		define PRId64 ((void) static_assert(false, "Use %lld instead"))
#	endif
#	ifndef PRIX64
#		define  PRIX64  "I64X"
#		define wPRIX64 L"I64X"
#	endif
#else
#	ifndef PRIX64
//		The GCC stdint.h uses __WORDSIZE == 64 to determine whether int64_t is going to be "long int" or "long long int", so we do the same here.
#		if __WORDSIZE == 64
#			define  PRIX64  "lX"
#			define wPRIX64 L"lX"
#		else
#			define  PRIX64  "llX"
#			define wPRIX64 L"llX"
#		endif
#	endif
#endif


#ifdef _WIN32
#define INTMIN		_I32_MIN
#define INTMAX		_I32_MAX
#define INT8MIN		_I8_MIN
#define INT8MAX		_I8_MAX
#define INT16MIN	_I16_MIN
#define INT16MAX	_I16_MAX
#define INT32MIN	_I32_MIN
#define INT32MAX	_I32_MAX
#define INT64MIN	_I64_MIN
#define INT64MAX	_I64_MAX
#define UINT8MAX	_UI8_MAX
#define UINT16MAX	_UI16_MAX
#define UINT32MAX	_UI32_MAX
#define UINT64MAX	_UI64_MAX
#else
#define INTMIN		INT32_MIN
#define INTMAX		INT32_MAX
#define INT8MIN		INT8_MIN
#define INT8MAX		INT8_MAX
#define INT16MIN	INT16_MIN
#define INT16MAX	INT16_MAX
#define INT32MIN	INT32_MIN
#define INT32MAX	INT32_MAX
#define INT64MIN	INT64_MIN
#define INT64MAX	INT64_MAX
#define UINT8MAX	UINT8_MAX
#define UINT16MAX	UINT16_MAX
#define UINT32MAX	UINT32_MAX
#define UINT64MAX	UINT64_MAX
#endif



// The GCC docs show NORETURN after the function name, so I'm not sure that this works
PAPI			int			AbcPanicMsg(const char* file, int line, const char* msg);
PAPI NORETURN	void		AbcDie();

#define AbcAssert(f)			(void) ((f) || (AbcPanicMsg(__FILE__,__LINE__,#f), AbcDie(), 0) )			// Compiled in all builds
#define AbcVerify(f)			AbcAssert(f)																// Compiled in all builds. Different from AbcAssert to express intent, that this is logic altering.
#define AbcPanic(msg)			(void) (AbcPanicMsg(__FILE__,__LINE__,msg), AbcDie())						// Compiled in all builds
#define AbcPanicHere()			(void) (AbcPanicMsg(__FILE__,__LINE__,""), AbcDie())						// Compiled in all builds
#define AbcTodo()				(void) (AbcPanicMsg(__FILE__,__LINE__,"Not yet implemented"), AbcDie())		// Compiled in all builds

#ifdef _DEBUG
#define ABCASSERT(f) AbcAssert(f)
#else
#define ABCASSERT(f) ((void)0)
#endif

#define AbcCheckNULL( obj )					if ( !(obj) )	{ AbcPanicHere(); }
#define AbcCheckAlloc( buf )				if ( !(buf) )	{ AbcPanic("Out of memory"); }
#define AbcMemoryExhausted()				AbcPanic("Out of memory")
PAPI void* AbcMallocOrDie( size_t bytes );
PAPI void* AbcReallocOrDie( void* p, size_t bytes );


// If this returns false, then we are a headless process, for example a windows service.
// This means no user32.dll - no messagebox, etc.
PAPI bool AbcAllowGUI();
PAPI void AbcSetAllowGUI( bool allowGUI );

#ifndef ABCORE_INCLUDED_CONT_UTILS_H
#define ABCORE_INCLUDED_CONT_UTILS_H

// for std::swap, which is a very sensible function

// ---------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------
// Container Utilities.
// Specific utilities for my own STL-like containers.
// I don't like the STL much.
// ---------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------

/** Moves the item at index 'top' to position 0 of the list, and bumps everything else down.
This was created for keeping a small list of recently used items. It allows you the convenience of avoiding having
to keep a 'date' field around, and managing it's wrap-around.
**/
template< typename TVal >
void shuffle_to_top( int n, TVal* items, int itop )
{
if ( n == 0 || itop == 0 ) return;
TVal old_top = items[itop];

// bump down everything below itop
for ( int i = itop; i > 0; i-- ) items[i] = items[i - 1];

// and insert new top
items[0] = old_top;
}

template< typename TVect >
void shuffle_to_top_v( TVect& items, int itop )
{
if ( items.size() > 0 ) shuffle_to_top( items.size(), &items[0], itop );
}

/// Vector equality
template < typename TVect >
bool vect_equals( const TVect& a, const TVect& b )
{
if ( a.size() != b.size() ) return false;
for ( size_t i = 0; i < (size_t) a.size(); i++ )
if ( a[i] != b[i] ) return false;
return true;
}

// Returns the index of the first item, or -1 if not found
template <typename TVect, typename T>
int vect_indexof( const TVect& list, const T& val )
{
for ( intp i = 0; i < list.size(); i++ )
if ( list[i] == val )
return i;
return -1;
}

template<typename TVect, typename T>
void vect_insert_if_not_exist( TVect& set, const T& val )
{
if ( vect_indexof(set, val) == -1 ) set.push_back( val );
}

template<typename TVect, typename T>
void vect_erase_all_of( TVect& set, const T& val )
{
for ( intp i = set.size() - 1; i >= 0; i-- )
if ( set[i] == val )
set.erase(i);
}

template <typename TVect>
TVect vect_sum( const TVect& a, const TVect& b )
{
TVect res;
res.reserve( a.size() + b.size() );

for ( intp i = 0; i < a.size(); i++ )	res.push_back( a[i] );
for ( intp i = 0; i < b.size(); i++ )	res.push_back( b[i] );

return res;
}

/** Reverse for vector.
**/
template < typename TVect, typename TData >
void vect_reverse( TVect& target )
{
int lim = target.size() / 2;
for ( int i = 0; i < lim; i++ )
{
int j = target.size() - i - 1;
std::swap( target[i], target[j] );
}
}

// O(n^2)
template<typename TVect>
void vect_remove_duplicates( TVect& target )
{
for ( intp i = 0; i < target.size(); i++ )
{
for ( intp j = i + 1; j < target.size(); j++ )
{
if ( target[i] == target[j] )
{
target.erase(j);
j--;
}
}
}
}

/** find smallest item in a vector.
@return -1 If vector is empty, otherwise the index of the minimum value.
If there are duplicates, it will be the first instance of the minimum.
**/
template< typename TVect, typename TData >
int vect_least( const TVect& items )
{
if ( items.size() == 0 )
return -1;
TData v = items[0];
int index = 0;
for ( intp i = 0; i < items.size(); i++ )
{
if ( items[i] < v )
{
v = items[i];
index = i;
}
}
return index;
}

/** find greatest item in a vector.
@return -1 If vector is empty, otherwise the index of the maximum value.
If there are duplicates, it will be the first instance of the maximum.
**/
template< typename TVect, typename TData >
int vect_greatest( const TVect& items )
{
if ( items.size() == 0 )
return -1;
TData v = items[0];
int index = 0;
for ( intp i = 0; i < items.size(); i++ )
{
if ( v < items[i] )
{
v = items[i];
index = i;
}
}
return index;
}

template< typename TVect >
bool vect_is_sorted( const TVect& v )
{
for ( intp i = 1; i < v.size(); i++ )
{
if ( v[i] < v[i - 1] ) return false;
}
return true;
}

template< typename TData >
bool array_is_sorted( intp _size, const TData* a )
{
uintp size = _size;
for ( uintp i = 1; i < size; i++ )
{
if ( a[i] < a[i - 1] ) return false;
}
return true;
}

// SYNC-BMH-QSORT
template < typename TData >
void vect_sort_cx( TData* target, intp i, intp j, void* context, int (*compare) (void* context, const TData& a, const TData& b), int stackDepth = 0 )
{
if ( j <= i ) return;
if ( j == i + 1 )
{
// pair
if ( compare( context, target[j], target[i] ) < 0 )
std::swap( target[i], target[j] );
return;
}

// choose alternate pivot if we detect that the list is inversely sorted.
// not doing so will produce a stack overflow with even a relatively small set.
TData* pivot = target + i + ((j - i) / 2);
if ( stackDepth > 40 )
pivot = target + i + (rand() % (1 + j - i));

intp inI = i;
intp inJ = j;
i--;
j++;
while ( i < j )
{
j--;
while ( compare(context, *pivot, target[j]) < 0 && i < j )
j--;

if ( i != j )
i++;
while ( compare(context, target[i], *pivot) < 0 && i < j )
i++;

if ( i < j )
{
if ( pivot == target + i )		pivot = target + j;
else if ( pivot == target + j ) pivot = target + i;
std::swap( target[i], target[j] );
}
}
if ( inI < i )			vect_sort_cx<TData>( target, inI, i, context, compare, stackDepth + 1 );
if ( i + 1 < inJ )		vect_sort_cx<TData>( target, i + 1, inJ, context, compare, stackDepth + 1 );
}

// Wrap static TData::less_than function for use as a contexual compare() function
template< typename TData >
int less_than_2_compare( void* context, const TData& a, const TData& b )
{
return TData::less_than( a, b ) ? -1 : 0;
};

// Wrap a special TData::less_than providing class for use as a contexual compare() function
template< typename TData, typename TCompare >
int less_than_t_2_compare( void* context, const TData& a, const TData& b )
{
return TCompare::less_than( a, b ) ? -1 : 0;
};

template< typename TData >
int compare_default_contexual( void* context, const TData& a, const TData& b )
{
return a < b ? -1 : 0;
};

// We use the context to transmit the comparison function. The comparison function that the sorter
// sees is actually this function right here. This extra indirection is the price you pay for
// always supporting a context in the comparator, and also supporting context-less comparison function pointers.
template< typename TData >
int marshal_context_is_compare( void* context, const TData& a, const TData& b )
{
typedef int (*tcompare)(const TData& a, const TData& b);
return ((tcompare)context)( a, b );
};

/** Sort for vector.
TCompare is a struct/class that has a static function less_than, which
takes two argument and looks like "bool less_than(const TData& a, const TData& b)".
**/
template < typename TVect, typename TData, typename TCompare >
void vect_sort( TVect& target )
{
if ( target.size() == 0 ) return;
vect_sort_cx( &target[0], 0, target.size() - 1, NULL, &less_than_t_2_compare<TData, TCompare> );
}

template < typename TVect, typename TData >
void vect_sort( TVect& target )
{
if ( target.size() == 0 ) return;
vect_sort_cx( &target[0], 0, target.size() - 1, NULL, &less_than_2_compare<TData> );
}


template < typename TData >
void vect_sort( TData* target, int i, int j )
{
vect_sort_cx( &target[0], 0, j, NULL, &compare_default_contexual<TData> );
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Do not sort original data - sort a table that points into the original data

template<typename TData>
struct indirect_sort_context
{
const TData*	Data;
void*			OrgContext;
int				(*OrgCompare)(void* context, const TData& a, const TData& b);
};

template<typename TData, typename TOrder>
int indirect_compare( void* context, const TOrder& ia, const TOrder& ib )
{
indirect_sort_context<TData>* cx = (indirect_sort_context<TData>*) context;
return cx->OrgCompare( cx->OrgContext, cx->Data[ia], cx->Data[ib] );
}

template <typename TData, typename TOrder>
void vect_sort_indirect( const TData* target, TOrder* ordering, intp n, void* context, int (*compare) (void* context, const TData& a, const TData& b) )
{
indirect_sort_context<TData> wrappedcx;
wrappedcx.Data = target;
wrappedcx.OrgContext = context;
wrappedcx.OrgCompare = compare;

for ( TOrder k = 0; k < (TOrder) n; k++ ) ordering[k] = k;
vect_sort_cx( ordering, 0, n - 1, &wrappedcx, indirect_compare<TData,TOrder> );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Explicit half-instantiation of template utils, to reduce template ambiguity.
#define INSTANTIATE_VECTOR_FUNCTIONS(VECT) \
template <class T> VECT<T> operator+( const VECT<T>& a, const VECT<T>& b ) { return vect_sum< VECT<T> >(a, b); } \
\
template<typename TData>	void	reverse( VECT<TData>& target )					{ vect_reverse< VECT<TData>, TData >( target ); } \
template<typename TData>	int		greatest( const VECT<TData>& target )			{ return vect_greatest<VECT<TData>, TData>( target ); } \
template<typename TData>	int		least( const VECT<TData>& target )				{ return vect_least<VECT<TData>, TData>( target ); } \
template<typename TData>	void	remove_duplicates( const VECT<TData>& target )	{ return vect_remove_duplicates< VECT<TData> >( target ); } \
template<typename TData>	bool	is_sorted( const VECT<TData>& target )			{ return vect_is_sorted< VECT<TData> >( target ); } \
\
template<typename TData, typename TCompare>	void sort( VECT<TData>& target )					{ vect_sort_cx( target.data, 0, target.size() - 1, NULL, &less_than_t_2_compare<TData, TCompare> ); }\
template<typename TData>					void sort( VECT<TData>& target )					{ vect_sort_cx( target.data, 0, target.size() - 1, NULL, &compare_default_contexual<TData> ); }\
template<typename TData>					void sort( VECT<TData>& target, intp i, intp j )	{ vect_sort_cx( target.data, i, j, NULL, &compare_default_contexual<TData> ); }\
template<typename TData, typename TCompare>	void sort( VECT<TData>& target, intp i, intp j )	{ vect_sort_cx( target.data, i, j, NULL, &less_than_t_2_compare<TData, TCompare> ); }\
template<typename TData>					void sort( VECT<TData>& target, int (*compare) (const TData& a, const TData& b) )							{ vect_sort_cx( target.data, 0, target.size() - 1, compare, marshal_context_is_compare<TData> ); }\
template<typename TData>					void sort( VECT<TData>& target, void* context, int (*compare) (void* cx, const TData& a, const TData& b) ) { vect_sort_cx( target.data, 0, target.size() - 1, context, compare ); } \
template<typename TData, typename TOrder>	void sort_indirect( VECT<TData>& target, TOrder* ordering, void* context, int (*compare) (void* cx, const TData& a, const TData& b) ) { vect_sort_indirect( target.data, ordering, target.size(), context, compare ); }



#endif

#ifndef ABCORE_INCLUDED_PVECT_H
#define ABCORE_INCLUDED_PVECT_H

// Pointer to <> classes, without necessary compiler support for template specialization
// Note that all functions take "intp" values, but internally we store 32-bit integers.
// Should the day arrive when we need to store more than 4g items, then we'll change.


#ifndef PVECT_DECL_SPEC
#define PVECT_DECL_SPEC
#endif

//#define PVECT_RANGE_CHECK 1

#define PVINT int

class PVECT_DECL_SPEC pvoidvect
{
public:
// These data members are made public here so that the vector can be used as a plain array.
void**	data;
PVINT	count;
PVINT	capacity;

pvoidvect()
{
count = 0;
capacity = 0;
data = NULL;
}
explicit pvoidvect(intp _reserve)
{
count = 0;
capacity = 0;
data = NULL;
reserve(_reserve);
}

// copy constructor
pvoidvect(const pvoidvect& b)
{
data = NULL;
capacity = 0;
count = 0;
if (b.count > 0)
{
reserve(b.count);
// The data != NULL check is superfluous, but necessary to satisfy the VS 2012 static analyzer
if (data != NULL)
memcpy(data, b.data, sizeof(void*)*b.count);
}
count = b.count;
}

~pvoidvect()
{
if (data)
delete []data;
}

void hack( intp _count, intp _capacity, void** _data )
{
count = PVINT(_count);
capacity = PVINT(_capacity);
data = _data;
}

pvoidvect& operator=(const pvoidvect &b)
{
if ( this != &b )
{
if ( b.count != capacity ) clear();
if ( b.count > 0 )
{
reserve(b.count);
memcpy(data, b.data, sizeof(void*)*b.count);
}
count = b.count;
}
return *this;
}

bool operator==( const pvoidvect& b ) const
{
if ( count != b.count ) return false;
for ( PVINT i = 0; i < count; i++ )
if ( data[i] != b.data[i] ) return false;
return true;
}
bool operator!=( const pvoidvect& b ) const { return !(*this == b); }

// safe set. Will resize if necessary
void set(intp _pos, const void* a)
{
PVINT pos = PVINT(_pos);
if (pos >= count)
{
// Do we need to resize, or can we just up our count?
if (pos >= capacity)
resize(pos+1);
else
count = pos+1;
}
data[pos] = const_cast<void*>(a);
}

void insert(intp _pos, const void* a)
{
PVINT pos = PVINT(_pos);
if (pos >= capacity || count+1 > capacity)
reserve(_MAX_(capacity*2, pos+4));
PVINT nmove = count - pos;
if (nmove > 0)
memmove(&(data[pos+1]), &(data[pos]), nmove*sizeof(void*));
data[pos] = const_cast<void*>(a);
count++;
}

void erase(intp _pos1, intp _pos2 = -1)
{
PVINT pos1 = PVINT(_pos1);
PVINT pos2 = PVINT(_pos2);
if ( pos2 == -1 )			pos2 = pos1;
else if ( pos2 >= count )	pos2 = count -1;
ASSERT( pos1 >= 0 && pos1 <= pos2 );

PVINT nmove = (count - pos2) - 1;
if (nmove > 0)
memmove(&(data[pos1]), &(data[pos2+1]), nmove*sizeof(void*));
count -= 1 + (pos2 - pos1);
}

// Grift.... this causes no problems because we know that a void* is only 4 bytes.
void* pop_back()
{
if (count > 0)
count--;
return data[count];
}

void push_back(const void* a)
{
if (count >= capacity)
reserve( _MAX_(capacity*2, 2) );
data[count++] = const_cast<void*>(a);
}

#ifdef PVECT_RANGE_CHECK
const void* operator[](intp _i) const
{
PVINT i = PVINT(_i);
ASSERT( i >= 0 && i < count );
return data[_i];
}
#else
const void* operator[](intp _i) const { return data[_i]; }
#endif

#ifdef PVECT_RANGE_CHECK
void*& operator[](intp _i)
{
PVINT i = PVINT(_i);
ASSERT( i >= 0 && i < count );
return data[_i];
}
#else
void*& operator[](intp _i) { return data[_i]; }
#endif

void addn( intp n, void** p )
{
for ( intp i = 0; i < n; i++ ) push_back(p[i]);
}

void* front() const
{
return data[0];
}
void*& front()
{
return data[0];
}

void* back() const
{
return data[count-1];
}
void*& back()
{
return data[count-1];
}

bool contains( const void* t ) const { return find(t) != -1; }

// returns -1 on failure
intp find( const void* t ) const
{
for ( PVINT i = 0; i < count; i++ )
if ( data[i] == t ) return i;
return -1;
}

void nullfill()
{
for ( PVINT i = 0; i < count; i++ )
data[i] = NULL;
}

void clear()
{
delete[] data;
data = NULL;
count = 0;
capacity = 0;
}

// frees our heap storage and sets data to null (but does not touch capacity or count)
void dealloc()
{
delete[] data;
data = NULL;
}

// can be used to avoid reallocs
void clear_noalloc()
{
count = 0;
}

intp size() const { return count; }

// preserves existing entities but doesn't set count
void reserve( intp _newsize )
{
PVINT newsize = PVINT(_newsize);
if ( newsize <= capacity ) return;
PVINT oc = count;
resize(_MAX_(newsize, count));
count = oc;
}
// preserves existing entities and sets count to newsize
// does not realloc unless size is larger than existing capacity
void resize( intp newsize )
{
if ( newsize > capacity )
{
void** nd = new void*[newsize];
if (count > 0)
memcpy( nd, data, sizeof(void*) * count );
delete []data;
data = nd;
capacity = (PVINT) newsize;
}
count = (PVINT) newsize;
}

protected:
void add( const pvoidvect& a )
{
for ( PVINT i = 0; i < a.count; i++ )
push_back( a[i] );
}

template<typename TYPE> TYPE _MAX_( TYPE a, TYPE b ) { return a < b ? b : a; }
};


template < class T > class PVECT_DECL_SPEC pvect : public pvoidvect
{
public:
typedef pvoidvect	Base;
typedef T			TElem;

pvect() : Base() {}

explicit pvect(intp reserve) : Base(reserve) {}

pvect(const pvect& b) : Base(b) {}

pvect& operator=(const pvect &b) { return (pvect&) Base::operator=(b); }

bool operator==( const pvoidvect& b ) const { return Base::operator==(b); }
bool operator!=( const pvoidvect& b ) const { return Base::operator!=(b); }

void set(intp pos, const T a) { Base::set(pos, (const void*) a); }

void insert(intp pos, const T a) { Base::insert(pos, (const void*) a); }

void erase(intp pos1, intp pos2 = -1) { Base::erase(pos1, pos2); }

T pop_back()	{ return static_cast<T>(Base::pop_back()); }
T pop()			{ return static_cast<T>(Base::pop_back()); }

void push_back( const T a ) { Base::push_back( (const void*) a ); }

void addn( intp n, const T* p ) { Base::addn(n, (void**) p); }

pvect& operator+=( const T a ) { push_back( a ); return *this; }

pvect& operator+=( const pvect& a ) { add( a ); return *this; }

//const T operator[](intp i) const { return static_cast<const T>(Base::operator[](i)); }
const T operator[](intp i) const { return (const T) Base::operator[](i); }

T& operator[](intp i) { return (T&) Base::operator[](i); }

// sometimes it's not pretty to force a dereference in order to use operator[]
//const T get(intp i) const { return static_cast<const T>(Base::operator[](i)); }
const T get(intp i) const { return (const T) Base::operator[](i); }

T& get(intp i) { return (T&) Base::operator[](i); }

const T back() const { return (const T) Base::back(); }
T& back() { return (T&) Base::back(); }

const T front() const { return (const T) Base::front(); }
T& front() { return (T&) Base::front(); }

intp find( const T a ) const { return Base::find((const void*) a); }

void clear() { Base::clear(); }

// deletes void* storage, but does not call destructor.
void dealloc() { Base::dealloc(); }

void nullfill() { Base::nullfill(); }

intp size() const { return Base::size(); }

void reserve(intp newsize) { Base::reserve(newsize); }

void resize(intp newsize) { Base::resize(newsize); }
};

/** erase and delete for pvect
**/
template < typename TData >
void erase_delete( pvect<TData>& target, intp pos1, intp pos2 = -1 )
{
if ( pos2 == -1 )						pos2 = pos1;
else if ( pos2 >= target.count )		pos2 = target.count - 1;
ASSERT( pos1 >= 0 && pos1 <= pos2 );
for ( intp i = pos1; i <= pos2; i++ )
delete target[i];
target.erase( pos1, pos2 );
}

/** clear and delete all for pvect.
**/
template < typename TData >
void delete_all( pvect<TData>& target )
{
for ( intp i = 0; i < target.size(); i++ )
delete target[i];
target.clear();
}

/** concatenation for pvect.
**/
template < typename TData >
pvect<TData> operator+( const pvect<TData>& a, const pvect<TData>& b )
{
pvect<TData> c = a;
c += b;
return c;
}

/** Reverse for pvect.
**/
template < typename TData >
void reverse( pvect<TData>& target )
{
intp lim = target.size() / 2;
for ( intp i = 0; i < lim; i++ )
{
intp j = target.size() - i - 1;
TData tt = target[i];
target[i] = target[j];
target[j] = tt;
}
}

// Sort for pvect.
// These have to be custom written so that they can dereference the objects inside the pvect.

template <typename T> int pvect_compare_operator_lt( void* context, const T& a, const T& b )
{
return *a < *b ? -1 : 0;
}

// See marshal_context_is_compare in cont_utils.h for an explanation.
// We do the extra work of dereferencing
template <typename T>
int pvect_marshal_context_is_compare( void* context, const T& a, const T& b )
{
// It's easier to go from T* to TType than the other way around.
typedef decltype(*a) TType;
typedef int (*tcompare)(const TType& a, const TType& b);
return ((tcompare) context)( *a, *b );
}

struct pvect_double_context
{
void* Context;
void* Compare;
};

// We need two levels of indirection because we need to perform the dereference first
template <typename T>
int pvect_double_marshal_context_is_compare( void* context, const T& a, const T& b )
{
// save decltype() technique as above
typedef decltype(*a) TType;
typedef int (*tcompare)(void* context, const TType& a, const TType& b);

pvect_double_context* cxA = (pvect_double_context*) context;

return ((tcompare) cxA->Compare)( cxA->Context, *a, *b );
}

template <typename T> void sort( pvect<T*>& target )
{
vect_sort_cx<T*>( &target[0], 0, target.size() - 1, NULL, pvect_compare_operator_lt<T*> );
}

template <typename T> void sort( pvect<T*>& target, int (*compare) (const T& a, const T& b) )
{
vect_sort_cx<T*>( &target[0], 0, target.size() - 1, (void*) compare, pvect_marshal_context_is_compare<T*> );
}

template <typename T> void sort( pvect<T*>& target, void* context, int (*compare) (void* context, const T& a, const T& b) )
{
// double-trouble!
pvect_double_context cxA;
cxA.Compare = (void*) compare;
cxA.Context = context;
vect_sort_cx<T*>( &target[0], 0, target.size() - 1, &cxA, pvect_double_marshal_context_is_compare<T*> );
}

// Returns a copy of the pvect, sorted based on your comparison function
template< typename T >
pvect<T*> sorted_by( const pvect<T*>& unsorted, int (*compare) (const T& a, const T& b) )
{
pvect<T*> all = unsorted;
sort( all, compare );
return all;
}


template < typename TData >
void sort_insertion( pvect<TData>& target )
{
sort_insertion( target, 0, target.size() - 1 );
}

/** Very simple insertion sort for pvect.
The idea behind this is to avoid generating all the code needed for qsort,
when only a very simple sort for a tiny set is required.
**/
template < typename TData >
void sort_insertion( pvect<TData>& target, intp i, intp j )
{
pvect<TData> rep;
for ( intp k = i; k <= j; k++ )
{
TData a = target[k];
intp q;
for ( q = 0; q < rep.size(); q++ )
{
if ( *a < *rep[q] )
{
rep.insert( q, a );
break;
}
}
if ( q == rep.size() )
rep.push_back( a );
}
for ( intp k = i, s = 0; k <= j; k++, s++ )
target[k] = rep[s];
}

/** Generic sort item.
Most custom sorts can be made using the following structure that has
for it's template argument either a string, float, or integer.
The idea is that you use these to reduce bloat.
**/
template< typename ST >
struct sort_item
{
ST Key;
void* Object;
bool operator< ( const sort_item& b ) const
{
return Key < b.Key;
}
};


template< typename TData >
intp least( const pvect<TData>& items )
{
if ( items.size() == 0 ) { ASSERT(false); return -1; }
TData v = items[0];
intp index = 0;
for ( intp i = 0; i < items.size(); i++ )
{
if ( *items[i] < *v )
{
v = items[i];
index = i;
}
}
return index;
}

template< typename TData >
intp greatest( const pvect<TData>& items )
{
if ( items.size() == 0 ) { ASSERT(false); return -1; }
TData v = items[0];
intp index = 0;
for ( intp i = 0; i < items.size(); i++ )
{
if ( *v < *items[i] )
{
v = items[i];
index = i;
}
}
return index;
}

template<typename TData> void remove_duplicates( pvect<TData>& target )	{ return vect_remove_duplicates( target ); }


#undef PVINT
#endif



#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4345)	// POD type is default-initialized with () syntax
#endif


/*

This is a cut-down vector<>, but built for types that adhere to a specific protocol.

Benefits of using podvec:
* Memory move semantics. If you are storing a vector of XString objects, and the vector needs to grow,
then we don't need to realloc memory for the content of all those XString objects. Because we simply do a
memcpy, we avoid that.
This functionality is what you get from C++11 rvalue references, except we do it here without all
that pain - and this was written before C++11 was born.

Requirements for types for which podvec_ispod() is false:
1. A zero fill must initialize the object.
2. Nobody (including the class itself) may store internal pointers to the object. We need to be able to move objects around.
3. The destructor must be a no-op when the object has been zero-initialized. Whenever podvec needs to destroy an object,
it explicitly calls its destructor, and then does a memset(0) on the contents of the object's memory. This sequence
of events must leave the object in its initialized state (which is the same as constraint #1).
4. No support for polymorphic classes. That is anything with a virtual function (including a virtual destructor).

Additional requirements for types for which podvec_ispod() is true:
5. No constructor necessary.
6. No destructor necessary.
7. The object can be copied with memcpy. ie. The object doesn't "own" any pointers. A string is an example of a type
that violates this constraint, because if you memcpy'd a string into the vector, then you would end up with two
strings pointing to the same block of memory, and that memory would eventually be freed twice.

The lack of protected data members (count,capacity,data) makes it a little easier to deal with
when all you want is a managed array.

podvec_ispod() is opt-in, because the requirements are stricter.

Accessors and size() are signed pointer-sized, because historically I use "for (int i = 0; i < v.size(); i++)", and I don't want to break all of that
by littering signed/unsigned comparison warnings -- which is a warning always worth heeding.

In addition, signed comparisons are generally more robust, because you don't wrap around under zero.

Internally we store unsigned pointer-sized integers.
*/

template<typename T> bool podvec_ispod() { return false; }

template<typename T>
struct podvec
{
typedef T TElem;

uintp	count;
uintp	capacity;
T*		data;

static bool ispod()				{ return podvec_ispod<T>(); }
static void panic()				{ AbcPanicHere(); }

podvec()
{
construct();
}
podvec( const podvec& b )
{
construct();
*this = b;
}
podvec( std::initializer_list<T> list )
{
construct();
if ( ispod() )
{
resize_uninitialized( list.size() );
memcpy( data, list.begin(), sizeof(T) * list.size() );
}
else
{
resize( list.size() );
for ( size_t i = 0; i < list.size(); i++ )
data[i] = list.begin()[i];
}
}

~podvec()
{
clear();
}

void hack( intp _count, intp _capacity, T* _data )
{
count = _count;
capacity = _capacity;
data = _data;
}

intp size() const { return count; }

// We are consistent here with the stl's erase, which takes [start,last), where last is one beyond the last element to erase.
void erase( intp _start, intp _end = -1 )
{
uintp start = _start;
uintp end = _end;
if ( end == -1 ) end = start + 1;
if ( start == end ) return;			// on an empty set, you must be able to do erase(0,0), and have it be a nop
if ( start >= count )	panic();	// erase is rare enough that I feel it's worth it to pay this branch penalty for an early crash.
if ( end > count )		panic();
uintp remain = count - end;
for ( uintp i = start; i < end; i++ ) dtor( data[i] );
memmove( data + start, data + end, remain * sizeof(T) );
memset( data + start + remain, 0, (end - start) * sizeof(T) );
count = start + remain;
}

// written originally for adding bytes to a podvec<u8>. Will grow the buffer in powers of 2.
void addn( const T* arr, intp _n )
{
if ( isinternal(arr) ) panic();
uintp n = _n;
if ( count + n > capacity ) growfor( count + n );
if ( ispod() )	{ memcpy( data + count, arr, n * sizeof(T) ); count += n; }
else			{ for ( uintp i = 0; i < n; i++ ) data[count++] = arr[i]; }
}

T& add()
{
push( T() );
return back();
}

void resize( intp _inewsize )
{
resize_internal( _inewsize, true );
}

// This is intended to be the equivalent of a raw malloc(), for the cases where you don't
// want to pay the cost of zero-initializing the memory that you're about to fill up anyway.
void resize_uninitialized( intp _inewsize )
{
resize_internal( _inewsize, false );
}

void reserve( intp _newcap )
{
uintp newcap = _newcap;
if ( newcap <= count ) return;		// resize may not alter count, therefore we do nothing in this case
resizeto( newcap, true );
}

// This is intended to be the equivalent of a raw malloc(), for the cases where you don't
// want to pay the cost of zero-initializing the memory that you're about to fill up anyway.
void reserve_uninitialized( intp _newcap )
{
uintp newcap = _newcap;
if ( newcap <= count ) return;		// resize may not alter count, therefore we do nothing in this case
resizeto( newcap, false );
}

intp remaining_capacity() const
{
return capacity - count;
}

void fill( const T& v )
{
for ( uintp i = 0; i < count; i++ )
data[i] = v;
}

void insert( intp _pos, const T& v )
{
uintp pos = _pos;
if ( pos > count ) panic();
if ( isinternal(&v) )
{
T copy = v;
grow();
if ( count != capacity ) dtorz_block( 1, data + count );
memmove( data + pos + 1, data + pos, (count - pos) * sizeof(T) );
//memset( data + pos, 0, sizeof(T) );
ctor( data[pos] );
data[pos] = copy;
}
else
{
grow();
if ( count != capacity ) dtorz_block( 1, data + count );
memmove( data + pos + 1, data + pos, (count - pos) * sizeof(T) );
//memset( data + pos, 0, sizeof(T) );
ctor( data[pos] );
data[pos] = v;
}
count++;
}

void	push_back( const T& v )	{ push(v); }
void	pop_back()				{ count--; }
void	pop()					{ pop_back(); }
T		rpop()					{ T v = back(); pop(); return v; }

void push( const T& v )
{
if ( count == capacity )
{
if ( isinternal(&v) )
{
// aliased
T copy = v;
grow();
data[count++] = copy;
}
else
{
grow();
data[count++] = v;
}
}
else data[count++] = v;
}

void clear_noalloc() { count = 0; }
void clear()
{
for ( uintp i = 0; i < capacity; i++ ) dtor(data[i]);
free(data);
data = NULL;
count = capacity = 0;
}

intp		find( const T& v ) const		{ for ( uintp i = 0; i < count; i++ ) if (data[i] == v) return i; return -1; }
bool		contains( const T& v ) const	{ return find(v) != -1; }

T&			get( intp i )					{ return data[i]; }
const T&	get( intp i ) const				{ return data[i]; }
void		set( intp i, const T& v )		{ data[i] = v; }

T&			operator[]( intp i )			{ return data[i]; }
const T&	operator[]( intp i ) const		{ return data[i]; }

T&			front()							{ return data[0]; }
const T&	front() const					{ return data[0]; }
T&			back()							{ return data[count-1]; }
const T&	back() const					{ return data[count-1]; }

void operator+=( const T& v )			{ push(v); }
void operator+=( const podvec& b )		{ addn( b.data, b.count ); }

void operator=( const podvec& b )
{
if ( count != b.count )
{
clear();
resizeto( b.count, !ispod() );
}
count = b.count;
if ( ispod() )	{ memcpy( data, b.data, count * sizeof(T) ); }
else			{ for ( uintp i = 0; i < b.count; i++ ) data[i] = b.data[i]; }
}

void grow() { growfor( count + 1 ); }

protected:
void construct()
{
count = capacity = 0;
data = NULL;
}
void dtor( T& v )
{
if ( !ispod() )
v.T::~T();
}
void dtorz_block( uintp n, T* block )
{
if ( ispod() ) return;
for ( uintp i = 0; i < n; i++ )
block[i].T::~T();
memset( block, 0, sizeof(T) * n );
}
void ctor( T& v )
{
//if ( ispod() )
//	memset( &v, 0, sizeof(T) );
//else
//	new (&v) T();
// On debug builds the memset is awful
new (&v) T();
}
void ctor_block( uintp n, T* block )
{
if ( ispod() )
memset( block, 0, sizeof(T) * n );
else
{
for ( uintp i = 0; i < n; i++ )
new (&block[i]) T();
}
}

bool isinternal( const T* p ) const
{
return (uintp) (p - data) < capacity;
}

void growfor( uintp target )
{
// Regular growth rate is 2.0, which is what most containers (.NET, STL) use.
// There is no theoretical optimal. It's simply a trade-off between memcpy time and wasted VM.
uintp ncap = capacity ? capacity : 1;
while ( ncap < target )
ncap = ncap * 2;
if ( !try_resizeto( ncap, true ) )
{
/* Special out of memory behaviour when growing the vector.
When realloc fails, we try again to grow at a rate of 1.25 instead of our regular exponent of 2.
The exponent 1.25 is a thumbsuck. There is no theoretically optimal behaviour here.
This is only intended to save users when arrays are in the range of around 500MB or so, on a 32-bit machine.
In this type of scenario, moving from 500 to 562 is better than 500 to 1000.
Trying to recover from out of memory conditions is a dubious game. It's not worth it to try
too hard, because the user is likely going to run out in the near future in a place where
a realloc fail is not recoverable.
*/
ncap = capacity;
if ( ncap < 4 ) ncap = 4;
while ( ncap < target )
ncap = ncap + ncap / 4;
if ( !try_resizeto( ncap, true ) )
AbcMemoryExhausted();
}
}

void resize_internal( uintp newsize, bool initmem )
{
if ( newsize == count ) return;
if ( newsize == 0 )		{ clear(); return; }
if ( newsize < capacity ) dtorz_block( capacity - (uintp) newsize, data + newsize );
resizeto( newsize, initmem );
count = newsize;
}

void resizeto( uintp newcap, bool initmem )
{
if ( !try_resizeto( newcap, initmem ) )
AbcMemoryExhausted();
}

bool try_resizeto( uintp newcap, bool initmem )
{
if ( newcap == 0 )
return true;
T* newdata = (T*) realloc( data, newcap * sizeof(T) );
if ( newdata == NULL )
return false;
data = newdata;
if ( newcap > capacity && initmem )
{
//memset( data + capacity, 0, (newcap - capacity) * sizeof(T) );
ctor_block( newcap - capacity, data + capacity );
}
capacity = newcap;
return true;
}

const T* pbegin()	const { return data; }
const T* pend()		const { return data + capacity; }
};

template < typename T >
void delete_all( podvec<T>& target )
{
for ( intp i = 0; i < target.size(); i++ ) delete target[i];
target.clear();
}

template<typename T>
bool operator==( const podvec<T>& a, const podvec<T>& b )
{
uintp asize = a.size();
if ( asize != b.size() ) return false;
for ( uintp i = 0; i < asize; i++ )
{
if ( a.data[i] != b.data[i] ) return false;
}
return true;
}
template<typename T>
bool operator!=( const podvec<T>& a, const podvec<T>& b )
{
return !(a == b);
}

template<> inline bool podvec_ispod<int8>()		{ return true; }
template<> inline bool podvec_ispod<int16>()	{ return true; }
template<> inline bool podvec_ispod<int32>()	{ return true; }
template<> inline bool podvec_ispod<int64>()	{ return true; }
template<> inline bool podvec_ispod<uint8>()	{ return true; }
template<> inline bool podvec_ispod<uint16>()	{ return true; }
template<> inline bool podvec_ispod<uint32>()	{ return true; }
template<> inline bool podvec_ispod<uint64>()	{ return true; }
template<> inline bool podvec_ispod<float>()	{ return true; }
template<> inline bool podvec_ispod<double>()	{ return true; }

template<> inline bool podvec_ispod<bool>()		{ return true; }
template<> inline bool podvec_ispod<void*>()	{ return true; }

namespace std
{
template<typename T> inline void swap( podvec<T>& a, podvec<T>& b )
{
char tmp[sizeof(podvec<T>)];
memcpy( tmp, &a, sizeof(a) );
memcpy( &a, &b, sizeof(a) );
memcpy( &b, tmp, sizeof(a) );
}
}

INSTANTIATE_VECTOR_FUNCTIONS(podvec)

#ifdef _MSC_VER
#pragma warning(pop)
#endif



struct AbcMachineInformation
{
int		PhysicalCoreCount;	// On linux this is wrong, and simply equal to LogicalCoreCount
int		LogicalCoreCount;
uint64	PhysicalMemory;
};

PAPI void				AbcMachineInformationGet( AbcMachineInformation& info );
PAPI uint64				AbcPhysicalMemory(); // Wrapper around AbcMachineInformationGet()



#ifdef _WIN32
typedef DWORD					AbcProcessID;
typedef HANDLE					AbcForkedProcessHandle;
#else
typedef pid_t					AbcProcessID;
typedef FILE*					AbcForkedProcessHandle;
#endif

struct AbcProcessStatistics
{
uint64	UserCpuTimeMicroseconds;
uint64	KernelCpuTimeMicroseconds;
uint64	WorkingSetBytes;			// On linux, this is the same as MaxWorkingSetBytes
uint64	MaxWorkingSetBytes;
uint64	AddressSpaceCommittedBytes;	// I don't know how to get this number for linux, so it is always zero on linux.
};

PAPI bool				AbcProcessCreate( const char* cmd, AbcForkedProcessHandle* handle, AbcProcessID* pid );
PAPI bool				AbcProcessWait( AbcForkedProcessHandle handle, int* exitCode );
PAPI void 				AbcProcessCloseHandle( AbcForkedProcessHandle handle );
PAPI AbcProcessID		AbcProcessGetPID();
PAPI void				AbcProcessGetPath( char* path, size_t maxPath );		// Return full path of executing process, for example "c:\programs\notepad.exe"
#ifdef XSTRING_DEFINED
PAPI XString			AbcProcessGetPath();									// Return full path of executing process, for example "c:\programs\notepad.exe"
#endif
PAPI void				AbcProcessesEnum( podvec<AbcProcessID>& pids );
PAPI void				AbcProcessGetStatistics( AbcProcessStatistics& stats );
PAPI uint64				AbcProcessWorkingSetBytes();							// wrapper around AbcProcessGetStatistics. On linux, this is the same as AbcProcessMaxWorkingSetBytes().
PAPI uint64				AbcProcessMaxWorkingSetBytes();							// wrapper around AbcProcessGetStatistics
PAPI uint64				AbcProcessVirtualCommittedBytes();						// wrapper around AbcProcessGetStatistics. Only supported on Win32. Returns 0 on any other OS.



/*
Declare a thread function as follows:
AbcThreadReturnType AbcKernelCallbackDecl MyFunction( void* threadContext )

*/

#ifdef _WIN32
typedef HANDLE					AbcThreadHandle;
typedef DWORD					AbcThreadID;			// Use AbcThreadEqual to compare for equality
typedef DWORD					AbcThreadReturnType;
typedef LPTHREAD_START_ROUTINE	AbcThreadFunc;
#define AbcKernelCallbackDecl	WINAPI
#else
typedef pthread_t				AbcThreadHandle;
typedef pthread_t				AbcThreadID;			// Use AbcThreadEqual to compare for equality
typedef void*					AbcThreadReturnType;
typedef void* (*AbcThreadFunc)(void*);
#define AbcKernelCallbackDecl
#endif

// All of these are currently ignored on linux
enum AbcThreadPriority
{
AbcThreadPriorityIdle,
AbcThreadPriorityNormal,
AbcThreadPriorityHigh,
AbcThreadPriorityBackgroundBegin,
AbcThreadPriorityBackgroundEnd,
};

PAPI bool				AbcThreadCreate( AbcThreadFunc threadfunc, void* context, AbcThreadHandle& handle );
PAPI bool				AbcThreadJoin( AbcThreadHandle handle );
PAPI bool				AbcThreadJoinAndCloseHandle( AbcThreadHandle handle );
PAPI void				AbcThreadCloseHandle( AbcThreadHandle handle );
PAPI AbcThreadHandle	AbcThreadCurrent();
PAPI AbcThreadID		AbcThreadCurrentID();
PAPI bool				AbcThreadIDEqual( AbcThreadID a, AbcThreadID b );
// This is currently a no-op on linux
PAPI void				AbcThreadSetPriority( AbcThreadHandle handle, AbcThreadPriority priority );



#ifndef _WIN32
#endif

// We need to include "thread.h" for AbcGuardedCriticalSection::ThreadID

#ifdef _WIN32
typedef HANDLE					AbcMutex;
typedef CRITICAL_SECTION		AbcCriticalSection;
typedef HANDLE					AbcSemaphore;
#define AbcINFINITE				INFINITE
#else
typedef pthread_mutex_t			AbcMutex;
typedef pthread_mutex_t			AbcCriticalSection;
typedef sem_t					AbcSemaphore;
#define AbcINFINITE				-1
#endif

// A Windows CRITICAL_SECTION is re-enterable, but a pthread_mutex_t is not.
// This structure allows us to verify that Windows code is not re-entering.
struct AbcGuardedCriticalSection
{
AbcCriticalSection	CS;			// This must be first. TakeCriticalSection assumes this is true.
AbcThreadID			ThreadID;

bool				DebugIsInside() const	// This is not MT safe, but can be useful for debugging
{
return ThreadID == AbcThreadCurrentID();
}
};

PAPI void				AbcMutexCreate( AbcMutex& mutex, const char* name );
PAPI void				AbcMutexDestroy( AbcMutex& mutex );
PAPI bool				AbcMutexWait( AbcMutex& mutex, DWORD waitMS );
PAPI void				AbcMutexRelease( AbcMutex& mutex );

// On Windows CRITICAL_SECTION is re-enterable, but not so on linux (where we use a pthread mutex).
// So don't write re-entering code.
// This is a good principle to abide by regardless of your platform: http://cbloomrants.blogspot.com/2012/06/06-19-12-two-learnings.html
PAPI void				AbcCriticalSectionInitialize( AbcCriticalSection& cs, unsigned int spinCount = 0 );
PAPI void				AbcCriticalSectionInitialize( AbcGuardedCriticalSection& cs, unsigned int spinCount = 0 );
PAPI void				AbcCriticalSectionDestroy( AbcCriticalSection& cs );
PAPI void				AbcCriticalSectionDestroy( AbcGuardedCriticalSection& cs );
PAPI bool				AbcCriticalSectionTryEnter( AbcCriticalSection& cs );
PAPI void				AbcCriticalSectionEnter( AbcCriticalSection& cs );
PAPI void				AbcCriticalSectionLeave( AbcCriticalSection& cs );

PAPI void				AbcSemaphoreInitialize( AbcSemaphore& sem );
PAPI void				AbcSemaphoreDestroy( AbcSemaphore& sem );
PAPI bool				AbcSemaphoreWait( AbcSemaphore& sem, DWORD waitMS );
// On linux we can only release one semaphore at a time, so the 'count' > 1 is not atomic.
// Be careful not to architect your applications around that assumption.
// Also, this operation is O(count) on linux.
PAPI void				AbcSemaphoreRelease( AbcSemaphore& sem, DWORD count );

PAPI void				AbcSleep( int milliseconds );

// Use AbcPause() inside a spinlock: http://x86.renejeschke.de/html/file_module_x86_id_232.html
#ifdef _MSC_VER
#define 				AbcPause()		YieldProcessor()
#else
#define					AbcPause()		asm volatile("pause\n": : :"memory")
#endif

PAPI int				AbcLockFileLock( const char* path );	// Creates a 1 byte file and locks that 1 byte region. Returns -1 on failure. Does not block.
PAPI void				AbcLockFileRelease( int f );			// Releases a lockfile created with AbcLockFileLock

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: Get rid of these functions, and replace them with mintomic
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AbcInterlockedAdd		returns the PREVIOUS value
// AbcInterlockedOr			returns the PREVIOUS value
// AbcInterlockedAnd		returns the PREVIOUS value
// AbcInterlockedIncrement	returns the NEW value
// AbcInterlockedDecrement	returns the NEW value
// AbcCmpXChg				returns the PREVIOUS value
#ifdef _WIN32
inline void			AbcInterlockedSet( volatile unsigned int* p, int newval )				{ _InterlockedExchange( (volatile long*) p, (long) newval ); }
inline unsigned int	AbcInterlockedAdd( volatile unsigned int* p, int addval )				{ return (unsigned int) _InterlockedExchangeAdd( (volatile long*) p, (long) addval ); }
inline unsigned int	AbcInterlockedOr( volatile unsigned int* p, int orval )					{ return (unsigned int) _InterlockedOr( (volatile long*) p, (long) orval ); }
inline unsigned int	AbcInterlockedAnd( volatile unsigned int* p, int andval )				{ return (unsigned int) _InterlockedAnd( (volatile long*) p, (long) andval ); }
inline unsigned int	AbcInterlockedXor( volatile unsigned int* p, int xorval )				{ return (unsigned int) _InterlockedXor( (volatile long*) p, (long) xorval ); }
inline void			AbcSetWithRelease( volatile unsigned int* p, int newval )				{ *p = newval; _WriteBarrier(); }
inline unsigned int	AbcCmpXChg( volatile unsigned int* p, int newval, int oldval )			{ return _InterlockedCompareExchange( (volatile long*) p, (long) newval, (long) oldval ); }
inline unsigned int	AbcInterlockedIncrement( volatile unsigned int* p )						{ return (unsigned int) _InterlockedIncrement( (volatile long*) p ); }
inline unsigned int	AbcInterlockedDecrement( volatile unsigned int* p )						{ return (unsigned int) _InterlockedDecrement( (volatile long*) p ); }
#else
// Clang has __sync_swap(), which is what you want here when compiling with Clang
// #	ifdef ANDROID
// //inline void			AbcInterlockedSet( volatile unsigned int* p, int newval )				{ __atomic_swap( newval, (volatile int*) p ); }
// //inline void			AbcSetWithRelease( volatile unsigned int* p, int newval )				{ __atomic_store_n( p, newval, __ATOMIC_RELEASE ); }
// inline void			AbcInterlockedSet( volatile unsigned int* p, int newval )				{ *p = newval; }
// inline void			AbcSetWithRelease( volatile unsigned int* p, int newval )				{ *p = newval; __sync_synchronize(); }
// inline unsigned int AbcCmpXChg( volatile unsigned int* p, int newval, int oldval )			{ return __sync_val_compare_and_swap( p, oldval, newval ); }
// #	elif __GNUC__
inline void			AbcInterlockedSet( volatile unsigned int* p, int newval )				{ *p = newval; }
inline unsigned int	AbcInterlockedAdd( volatile unsigned int* p, int addval )				{ return __sync_fetch_and_add( p, addval ); }
inline unsigned int	AbcInterlockedOr( volatile unsigned int* p, int orval )					{ return __sync_fetch_and_or( p, orval ); }
inline unsigned int	AbcInterlockedAnd( volatile unsigned int* p, int andval )				{ return __sync_fetch_and_and( p, andval ); }
inline unsigned int	AbcInterlockedXor( volatile unsigned int* p, int xorval )				{ return __sync_fetch_and_xor( p, xorval ); }
inline void			AbcSetWithRelease( volatile unsigned int* p, int newval )				{ *p = newval; __sync_synchronize(); } // I think there is a better implementation of this, using __sync_lock_test_and_set followed by __sync_lock_release
inline unsigned int AbcCmpXChg( volatile unsigned int* p, int newval, int oldval )			{ return __sync_val_compare_and_swap( p, oldval, newval ); }
inline unsigned int	AbcInterlockedIncrement( volatile unsigned int* p )						{ return __sync_add_and_fetch( p, 1 ); }
inline unsigned int	AbcInterlockedDecrement( volatile unsigned int* p )						{ return __sync_sub_and_fetch( p, 1 ); }
//#	endif
#endif


PAPI void		AbcSpinLockWait( volatile unsigned int* p );		// Spins until we can set p from 0 to 1. Assumes your hold your lock for a handful of clock cycles.
PAPI void		AbcSpinLockRelease( volatile unsigned int* p );		// Sets p to 0 with release semantics.

/// Scope-based AbcSpinLock___
class TakeSpinLock
{
public:
volatile unsigned int* P;
TakeSpinLock( volatile unsigned int* p )
{
P = p;
AbcSpinLockWait(P);
}
~TakeSpinLock()
{
AbcSpinLockRelease(P);
}
};

/// Scope-based critical section acquisition
class PAPI TakeCriticalSection
{
public:
AbcGuardedCriticalSection*	CS;
bool						UseGuard;

TakeCriticalSection( AbcCriticalSection& cs );
TakeCriticalSection( AbcGuardedCriticalSection& cs );
~TakeCriticalSection();
};

struct AbcMutexStackEnter
{
AbcMutex* Mutex;
AbcMutexStackEnter( AbcMutex& m )
{
Mutex = &m;
AbcMutexWait( *Mutex, AbcINFINITE );
}
~AbcMutexStackEnter()
{
AbcMutexRelease( *Mutex );
}
};

/*

[2013-10-22 BMH] This thing needs proper testing. I am not sure that the semaphore semantics are as expected.

Simulates CreateEvent/SetEvent/Wait for linux.

I don't understand why people say you can use a condition variable to simulate a Windows Event.
In the condition variable scenario, the waiters need to lock the mutex, which means there can
only be a single thread waiting on the event at any particular time. This breaks one of the
primary	uses of an event: multiple workers waiting on a single event.

On Windows, we just use the native Events.

On linux, we use semaphores.

Regarding the 'persistent' parameter, we are trying to duplicate the semantics of
the Windows manual-reset event type.
The following documentation	is copied from MSDN:
If this parameter is TRUE, the function creates a manual-reset event object, which requires
the use of the ResetEvent function to set the event state to nonsignaled. If this parameter
is FALSE, the function creates an auto-reset event object, and system automatically resets
the event state to nonsignaled after a single waiting thread has been released.

Note that internally on linux, since we are using a semaphore, we cannot reproduce the
Windows functionality completely.

What we do on linux is instead a bit of a hack, but I have scanned through all of my present
usages of events on Windows, and this workaround will suffice for all of them.
I do fear somebody using this incorrectly in the future though. It would likely
introduce a subtle and hard to understand bug. I simply cannot find a pthreads
alternative though.

The technique we use is this (applies only when persistent = true):
1. The initial call to SetEvent() calls sem_post 32 times. The number 32 is chosen
to match the expected number of general purpose threads on a machine. There
is no way we can avoid the event from flipping in and out of the signaled state,
so all we're doing here is trying to ensure that performance is decent.
1. Whenever a thread is awakened, it immediately calls sem_post() again. The semaphore
number will thus hover around 32.

Note that this does mean that the event is going to flip in and out of the signaled state.
Unfortunately I cannot think of a bullet-proof way to implement this.

The destructor calls Destroy()
*/
struct PAPI AbcSyncEvent
{
#ifdef _WIN32
HANDLE				Event;
AbcSyncEvent()		: Event(0) {}
~AbcSyncEvent();
#else
static const int	PersistentPostCount = 32;
AbcSemaphore		Sem;
bool				Persistent;
bool				Initialized;
AbcSyncEvent();
~AbcSyncEvent();
#endif

void Initialize( bool persistent );
void Destroy();
void Signal();
bool Wait( DWORD waitMS );
};




inline i64 AbcFileTimeToMicroseconds( const FILETIME& ft )
{
u64 time = ((u64) ft.dwHighDateTime << 32) | ft.dwLowDateTime;
i64 stime = (i64) time;
return stime / 10;
}

inline double AbcFileTimeToUnixSeconds( const FILETIME& ft )
{
const i64 days_from_1601_to_1970 = 370 * 365 - 276;
const i64 microsecondsPerDay = 24 * 3600 * (i64) 1000000;
i64 micro = AbcFileTimeToMicroseconds( ft );
return (micro - (days_from_1601_to_1970 * microsecondsPerDay)) * (1.0 / 1000000.0);
}

PAPI double AbcTimeAccurateRTSeconds();




#ifdef _WIN32
#define ABC_DIR_SEP_STR		 "\\"
#define ABC_DIR_SEP_STR_W	L"\\"
#else
#define ABC_DIR_SEP_STR		 "/"
#define ABC_DIR_SEP_STR_W	L"/"
#endif

struct AbcFilesystemItem
{
const char* Root;		// Directory of file
const char* Name;		// Name of file
double		TimeModify;	// Seconds since unix epoch, UTC
bool		IsDir : 1;
};

/*
Enumerate files and directories inside the given directory.
The directory name must be pure, without any wildcards.
This function appends a '*' itself.
The callback must respond in the following ways
- If 'item' is a directory
Return true to cause the directory to be entered
Return false to skip entering the directory
- If 'item' is a file
Return true to cause iteration to continue
Return false to stop iteration of this directory
This function returns false if an error occurred other than "no files found"
*/
bool AbcFilesystemFindFiles( const char* dir, std::function<bool(const AbcFilesystemItem& item)> callback );

/*
* Copyright 2001-2004 Unicode, Inc.
*
* Disclaimer
*
* This source code is provided as is by Unicode, Inc. No claims are
* made as to fitness for any particular purpose. No warranties of any
* kind are expressed or implied. The recipient agrees to determine
* applicability of information provided. If this file has been
* purchased on magnetic or optical media from Unicode, Inc., the
* sole remedy for any claim will be exchange of defective media
* within 90 days of receipt.
*
* Limitations on Rights to Redistribute This Code
*
* Unicode, Inc. hereby grants the right to freely use the information
* supplied in this file in the creation of products supporting the
* Unicode Standard, and to make copies of this file in any form
* for internal or external distribution as long as this notice
* remains attached.
*/

/* ---------------------------------------------------------------------

Conversions between UTF32, UTF-16, and UTF-8.  Header file.

Several funtions are included here, forming a complete set of
conversions between the three formats.  UTF-7 is not included
here, but is handled in a separate source file.

Each of these routines takes pointers to input buffers and output
buffers.  The input buffers are const.

Each routine converts the text between *sourceStart and sourceEnd,
putting the result into the buffer between *targetStart and
targetEnd. Note: the end pointers are *after* the last item: e.g.
*(sourceEnd - 1) is the last item.

The return result indicates whether the conversion was successful,
and if not, whether the problem was in the source or target buffers.
(Only the first encountered problem is indicated.)

After the conversion, *sourceStart and *targetStart are both
updated to point to the end of last text successfully converted in
the respective buffers.

Input parameters:
sourceStart - pointer to a pointer to the source buffer.
The contents of this are modified on return so that
it points at the next thing to be converted.
targetStart - similarly, pointer to pointer to the target buffer.
sourceEnd, targetEnd - respectively pointers to the ends of the
two buffers, for overflow checking only.

These conversion functions take a ConversionFlags argument. When this
flag is set to strict, both irregular sequences and isolated surrogates
will cause an error.  When the flag is set to lenient, both irregular
sequences and isolated surrogates are converted.

Whether the flag is strict or lenient, all illegal sequences will cause
an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
must check for illegal sequences.

When the flag is set to lenient, characters over 0x10FFFF are converted
to the replacement character; otherwise (when the flag is set to strict)
they constitute an error.

Output parameters:
The value "sourceIllegal" is returned from some routines if the input
sequence is malformed.  When "sourceIllegal" is returned, the source
value will point to the illegal value that caused the problem. E.g.,
in UTF-8 when a sequence is malformed, it points to the start of the
malformed sequence.

Author: Mark E. Davis, 1994.
Rev History: Rick McGowan, fixes & updates May 2001.
Fixes & updates, Sept 2001.

------------------------------------------------------------------------ */

#ifndef CONVERT_UTF_INCLUDED
#define CONVERT_UTF_INCLUDED


/// Returns true if any characters in the string are greater than 127
inline bool IsHighAscii( const char* src )
{
while ( *src )
if ( *src++ < 0 ) return true;
return false;
}

/// Returns true if any characters in the string are greater than 127
inline bool IsHighAscii( const char* src, size_t maxLen )
{
size_t p = 0;
while ( src[p] && p < maxLen )
if ( src[p++] < 0 ) return true;
return false;
}

/// Returns true if all characters in the string are less than 128.
inline bool IsLowAscii( const wchar_t* src )
{
while ( *src )
if ( *src++ > 127 ) return false;
return true;
}

/// Returns true if all characters in the string are less than 128.
inline bool IsLowAscii( const wchar_t* src, size_t maxLen )
{
size_t p = 0;
while ( src[p] && p < maxLen )
if ( src[p++] > 127 ) return false;
return true;
}

#ifdef XSTRING_DEFINED
XStringA	PAPI ConvertHighAsciiToUTF8( const XStringA& src );
XStringA	PAPI ConvertUTF8ToHighAscii( const XStringA& src );
XStringW	PAPI ConvertUTF8ToWide( const XStringA& src );
XStringA	PAPI ConvertWideToUTF8( const XStringW& src );
#endif

#ifdef _STRING_
std::wstring	PAPI ConvertUTF8ToWide( const std::string& src );
std::string		PAPI ConvertWideToUTF8( const std::wstring& src );
#endif

/** Convert UTF16 to UTF8.
@param src Source buffer. May be NULL, which is equivalent to making srcLen = 0.
@param srcLen Length in characters of sources. If -1, then we determine the length by looking for a null terminator.
@param dst The destination buffer.
@param dstLen The length in characters of the destination buffer.
@param relaxNullTerminator If true, then we don't make sure that we can add a null terminator to dst.
**/
bool		PAPI ConvertWideToUTF8( const wchar_t* src, size_t srcLen, char* dst, size_t& dstLen, bool relaxNullTerminator = false );

/// Analogue of ConvertWideToUTF8
bool		PAPI ConvertUTF8ToWide( const char* src, size_t srcLen, wchar_t* dst, size_t& dstLen, bool relaxNullTerminator = false );

/** Returns the maximum number of UTF8 bytes necessary in order to represent any legal UTF16 string of the indicated number of UTF16 characters.

Maximum length of a UTF8 sequence is 4 bytes.
Maximum length of a UTF16 sequence is 2 bytes.
Therefore, when converting a UTF16 string to UTF8, in order to be safe against any possible inputs, you must allocate
N * 4 bytes, where N is the number of 16-bit characters. However, 4 byte UTF8 sequences are only necessary for values
of 0x10000 and greater. Likewise, UTF16 pairs are only necessary for values greater than or equal to 0x10000. So,
for values less than 0x10000, we have the maximum number of UTF8 bytes equal to N * 3. For values greater than or
equal to 0x10000, we need (N/2) * 4 = N * 2. So the maximum number of bytes necessary is N * 3.

**/
inline size_t MaximumUtf8FromUtf16( size_t utf16Len )
{
return utf16Len * 3;
}

inline size_t MaximumUtf8FromUtf32( size_t utf32Len )
{
return utf32Len * 4;
}

inline size_t MaximumUtf8FromWide( size_t wideLen )
{
return sizeof(wchar_t) == 2 ? MaximumUtf8FromUtf16(wideLen) : MaximumUtf8FromUtf32(wideLen);
}

inline size_t MaximumUtf16FromUtf8( size_t utf8Len )
{
return utf8Len * 2;
}

inline size_t MaximumUtf32FromUtf8( size_t utf8Len )
{
return utf8Len;
}

inline size_t MaximumWideFromUtf8( size_t utf8Len )
{
return sizeof(wchar_t) == 2 ? MaximumUtf16FromUtf8(utf8Len) : MaximumUtf32FromUtf8(utf8Len);
}

namespace Unicode
{

/* ---------------------------------------------------------------------
The following 4 definitions are compiler-specific.
The C standard does not guarantee that wchar_t has at least
16 bits, so wchar_t is no less portable than unsigned short!
All should be unsigned values to avoid sign extension during
bit mask & shift operations.
------------------------------------------------------------------------ */

typedef unsigned long	UTF32;	/* at least 32 bits */
typedef unsigned short	UTF16;	/* at least 16 bits */
typedef unsigned char	UTF8;	/* typically 8 bits */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR	(UTF32)0x0000FFFD
#define UNI_MAX_BMP				(UTF32)0x0000FFFF
#define UNI_MAX_UTF16			(UTF32)0x0010FFFF
#define UNI_MAX_UTF32			(UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32		(UTF32)0x0010FFFF

enum ConversionResult
{
ConversionOk, 						// Conversion successful.
ConversionResultSourceExhausted,	// Partial character in source, but hit end.
ConversionResultTargetExhausted,	// Insufficient room in target for conversion.
ConversionResultSourceIllegal		// Source sequence is illegal/malformed.
};

enum ConversionFlags
{
ConversionStrict = 0,
ConversionLenient
};

ConversionResult PAPI ConvertUTF8toUTF16 ( const UTF8** sourceStart, const UTF8* sourceEnd,
UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags );

ConversionResult PAPI ConvertUTF16toUTF8 ( const UTF16** sourceStart, const UTF16* sourceEnd,
UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags );

ConversionResult PAPI ConvertUTF8toUTF32 (	const UTF8** sourceStart, const UTF8* sourceEnd,
UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags );

ConversionResult PAPI ConvertUTF32toUTF8 ( const UTF32** sourceStart, const UTF32* sourceEnd,
UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags );

ConversionResult PAPI ConvertUTF16toUTF32 ( const UTF16** sourceStart, const UTF16* sourceEnd,
UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags );

ConversionResult PAPI ConvertUTF32toUTF16 ( const UTF32** sourceStart, const UTF32* sourceEnd,
UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags );

bool PAPI IsLegalUTF8Sequence( const UTF8 *source, const UTF8 *sourceEnd );

}

#endif



/*

Work/job queue
==============

* Multithreaded
* Simple FIFO
* Ring buffer

We follow ryg's recommendations here from http://fgiesen.wordpress.com/2010/12/14/ring-buffers-and-queues/
Particularly, ring size is always a power of 2, and we use at most N-1 slots. This removes the ambiguity caused
by a full buffer, wherein Head = Tail, which is the same as an empty buffer.

CAVEAT!

If you choose to use the semaphore, then ALL of your queue consumers MUST obey this pattern:
1 Wait for the semaphore to be signaled
2 Fetch one item from the queue
3 Go back to (1)

*/
class PAPI AbcQueue
{
public:
AbcCriticalSection	Lock;			// Lock on the queue data structures
AbcSemaphore		Semaphore;		// Can be used to wait for detection of a non-empty queue. Only valid if semaphore was enabled during call to Initialize(). Read CAVEAT.

AbcQueue();
~AbcQueue();
void	Initialize( bool useSemaphore, size_t itemSize );	// Every item must be the same size
void	Add( const void* item );							// Add to head. We copy in itemSize bytes, from base address 'item'
bool	PopTail( void* item );								// Pop the tail of the queue. Returns false if the queue is empty.
bool	PeekTail( void* item );								// Get the tail of the queue, but do not pop it. Obviously useless for multithreaded scenarios, unless you have acquired the lock.
int32	Size();

private:
bool				HaveSemaphore;
u32					Tail;
u32					Head;
u32					RingSize;				// Size of the ring buffer. Always a power of 2.
u32					ItemSize;
void*				Buffer;
u32					Mask() const				{ return RingSize - 1; }
void*				Slot( u32 pos ) const		{ return (byte*) Buffer + (pos * ItemSize); }
void				Increment( u32& i ) const	{ i = (i + 1) & Mask(); }
int32				SizeInternal() const		{ return (Head - Tail) & Mask(); }

void	Grow();
};

// Typed wrapper around AbcQueue
template<typename T>
class TAbcQueue
{
public:
TAbcQueue()							{ Q.Initialize( false, sizeof(T) ); }
void					Initialize( bool useSemaphore )		{ Q.Initialize( useSemaphore, sizeof(T) ); }
void					Add( const T& item )				{ Q.Add( &item ); }
bool					PopTail( T& item )					{ return Q.PopTail( &item ); }
bool					PeekTail( T& item )					{ return Q.PeekTail( &item ); }
T						PopTailR()							{ T t = T(); PopTail( t ); return t; }
T						PeekTailR()							{ T t = T(); PeekTail( t ); return t; }
int32					Size()								{ return Q.Size(); }
AbcCriticalSection&		LockObj()							{ return Q.Lock; }
AbcSemaphore&			SemaphoreObj()						{ return Q.Semaphore; }
private:
AbcQueue Q;
};



#define ABC_HAVE_ALIGNED_MALLOC 1
//#define ABC_HAVE_POSIX_MEMALIGN 1		// uncomment this once all posix systems support it (including Android)

#if defined(ABC_HAVE_ALIGNED_MALLOC)

#ifdef __cplusplus
#	define O_INLINE inline
#else
#	define O_INLINE
#endif

/*
How do we implement this manually?

Alignment must be a power of 2. If it is not, then AbcAlignedMalloc returns NULL.

Some examples illustrating 4 byte alignment, allocating 8 bytes of usable memory:

. Wasted byte at start
# Our byte that tells us how many bytes of wasted space before the usable memory
- Usable, aligned memory
* Wasted byte at end

Bytes before alignment point
1					#--------***			(# = 1) There are 3 bytes extra at the end of the usable space
2					.#--------**			(# = 2) There are 2 bytes extra at the end of the usable space
3					..#--------*			(# = 3) There is 1 byte extra at the end of the usable space
4					...#--------			(# = 4) Original malloc result was perfect. We had to burn 4 bytes. Zero bytes extra at the end of the usable space.

We always allocate (bytes + alignment), we always waste extract "alignment" bytes.
*/

O_INLINE void* AbcAlignedMalloc( size_t bytes, size_t alignment );
O_INLINE void* AbcAlignedRealloc( size_t original_block_bytes, void* block, size_t bytes, size_t alignment );
O_INLINE void  AbcAlignedFree( void* block );

O_INLINE void* AbcAlignedMalloc( size_t bytes, size_t alignment )
{
#ifdef _WIN32
return _aligned_malloc( bytes, alignment );
#elif defined(ABC_HAVE_POSIX_MEMALIGN)
void* p = NULL;
if ( 0 != posix_memalign( &p, alignment, bytes ) )
return NULL;
return p;
#else
size_t alignment_mask = alignment - 1;

// Ensure that alignment is a power of 2
if ( (alignment_mask & alignment) != 0 )
return NULL;

size_t raw		= (size_t) malloc( bytes + alignment );
size_t usable	= 0;
if ( raw )
{
usable = (raw + alignment) & ~alignment_mask;
*((unsigned char*) (usable - 1)) = (unsigned char) (usable - raw);
}
return (void*) usable;
#endif
}

// alignment must be the same as the original block
O_INLINE void* AbcAlignedRealloc( size_t original_block_bytes, void* block, size_t bytes, size_t alignment )
{
#ifdef _WIN32
return _aligned_realloc( block, bytes, alignment );
#else
void* p = AbcAlignedMalloc( bytes, alignment );
if ( !p )
return NULL;
memcpy( p, block, original_block_bytes );
AbcAlignedFree( block );
return p;
#endif
}

O_INLINE void AbcAlignedFree( void* block )
{
#ifdef _WIN32
_aligned_free( block );
#elif defined(ABC_HAVE_POSIX_MEMALIGN)
free( block );
#else
unsigned char* usable = (unsigned char*) block;
unsigned char* raw = usable - usable[-1];
free(raw);
#endif
}

#undef O_INLINE
#endif



namespace AbCore
{
typedef void* (*CxAllocFunc)	( void* context, size_t bytes );
typedef void (*CxFreeFunc)		( void* context, void* ptr );
inline void* CxAllocFunc_Default	( void* context, size_t bytes ) { return malloc(bytes); }
inline void CxFreeFunc_Default		( void* context, void* ptr )	{ free(ptr); }

struct ABC_ALIGN(16) Bytes16Aligned
{
int64 Space[4];
};

struct IAllocator
{
virtual void* Alloc( size_t bytes ) = 0;
virtual void Free( void* ptr ) = 0;
};

struct DefaultAllocator : public IAllocator
{
virtual void* Alloc( size_t bytes )		{ return malloc(bytes); }
virtual void Free( void* ptr )			{ return free(ptr); }
};

/** Allocator that initially uses a single fixed-size block off the stack, and thereafter goes to the general heap.
**/
struct SingleStackAllocator : public IAllocator
{
virtual void* Alloc( size_t bytes )
{
if ( bytes <= StackBlockSize ) { StackBlockSize = 0; return StackBlock; }
else return malloc(bytes);
}

virtual void Free( void* ptr )
{
if ( ptr != StackBlock )
free(ptr);
}

SingleStackAllocator( void* block, size_t bytes )
{
StackBlock = block;
StackBlockSize = bytes;
}

void Init( void* block, size_t bytes )
{
StackBlock = block;
StackBlockSize = bytes;
}

void* StackBlock;
size_t StackBlockSize;
};

template< typename TData >
class CxStack
{
public:
typedef unsigned int TRef;
AbCore::IAllocator*		Allocator;
TData*					Data;
TRef					Capacity, Count;

CxStack()
{
Allocator = NULL;
Data = NULL;
Count = 0;
Capacity = 0;
}

~CxStack()
{
Allocator->Free( Data );
}

TData& operator[]( int i ) { return Data[i]; }

TData& Back() { return Data[Count - 1]; }

void Clear()
{
Allocator->Free( Data );
Data = NULL;
Count = 0;
Capacity = 0;
}

TRef Size() { return Count; }

void Reserve( int n )
{
ABCASSERT( Capacity == 0 && Data == NULL );
Data = (TData*) Allocator->Alloc( n * sizeof(TData) );
Capacity = n;
}

void Resize( int n )
{
ABCASSERT( Count == 0 );
if ( (TRef) n > Capacity )
Grow( n );
Count = n;
}

void Push( const TData& d )
{
if ( Count == Capacity ) Grow(1);
Data[Count++] = d;
}

void Pop()
{
ABCASSERT( Count > 0 );
Count--;
}

protected:

void Grow( TRef needed )
{
TRef ocap = Capacity;
if ( Capacity == 0 ) Capacity = 1;
else Capacity = Capacity * 2;
if ( needed > Capacity )
Capacity = needed;
TData* d = (TData*) Allocator->Alloc( Capacity * sizeof(TData) );
memcpy( d, Data, ocap * sizeof(TData) );
Allocator->Free( Data );
Data = d;
}

};

/// Contiguous block of memory, initially on the stack, then on the heap
// NOTE! It's probably easier to use smallvec_stack. This was a dumb thing to create.
// Actually... not so entirely. This thing is in fact useful when you want the size of your stack buffer to be independent of the container.
// See also StackBufferT, below.
class StackBuffer
{
public:
typedef unsigned char byte;
byte*		Buffer;		// The buffer
size_t		Pos;		// The number of bytes appended
size_t		Capacity;	// Capacity of 'Buffer'
bool		OwnBuffer;	// If true, then our destructor does "free(Buffer)"

template< typename TBuf, size_t elements >
StackBuffer( TBuf (&stack_buffer)[elements] )
{
OwnBuffer = false;
Pos = 0;
Buffer = (byte*) stack_buffer;
Capacity = sizeof(stack_buffer[0]) * elements;
}

~StackBuffer()
{
if ( OwnBuffer ) free(Buffer);
}

void Reserve( size_t bytes )
{
if ( Pos + bytes > Capacity )
{
size_t ncap = Capacity * 2;
if ( ncap < Pos + bytes ) ncap = Pos + bytes;
byte* nbuf = (byte*) AbcMallocOrDie( ncap );
memcpy( nbuf, Buffer, Pos );
Capacity = ncap;
if ( OwnBuffer ) free(Buffer);
OwnBuffer = true;
Buffer = nbuf;
}
}

/// Current position
byte* Current()					{ return Buffer + Pos; }

template< typename T >
T* TCurrent()					{ return (T*) (Buffer + Pos); }

template< typename T >
T& TItem( int el )				{ return ((T*) Buffer)[el]; }

template< typename T >
int TSize() const				{ return int(Pos / sizeof(T)); }

void MoveCurrentPos( intp bytes )	{ Pos += bytes; ABCASSERT(Pos <= Capacity); }

byte* Add( size_t bytes )
{
Reserve( bytes );
byte* p = Buffer + Pos;
Pos += bytes;
return p;
}

void Add( const void* p, size_t bytes )
{
memcpy( Add(bytes), p, bytes );
}

template< typename T >
void AddItem( const T& v )
{
Add( &v, sizeof(v) );
}

};
}

//	Usage pattern:
//	func() {
//		StackBufferT<double,32> zbuf;
//		..
//		zbuf.Init(n);					-- Call Init ONCE
//		zbuf[i..n] = xyz;
//
//	You can also use the parameterized constructor, which simply calls Init()

template < typename VT, size_t TStaticSize >
class StackBufferT
{
DISALLOW_COPY_AND_ASSIGN(StackBufferT);
public:
u32 Count;
VT* Data;
VT	Static[TStaticSize];

StackBufferT()
{
// I considered leaving this uninitialized, but I don't think it's worth the robustness tradeoff
// One might be tempted to make Data = Static initially, but this opens one up to the possibility of forgetting to call Init()
// when the data size is indeed large enough. Your tests may not stress the oversize case, and you'll blow up when it's inconvenient.
Data = NULL;
}

StackBufferT( int s )
{
Data = NULL;
Init(s);
}

~StackBufferT()
{
if ( Data != Static ) delete[] Data;
}

void Init( int s )
{
Count = s;
if ( Count > TStaticSize )
Data = new VT[Count];
else
Data = Static;
}
void Fill( const VT& v )		{ for ( u32 i = 0; i < Count; i++ ) Data[i] = v; }

operator VT*()					{ return Data; }
};




inline int MemCmpBits( const void* a, const void* b, size_t bits )
{
size_t bytes = bits >> 3;
size_t remain = bits & 7;
if ( memcmp( a, b, bytes ) != 0 ) return 1;
if ( remain != 0 )
{
BYTE av = *(((BYTE*) a) + bytes);
BYTE bv = *(((BYTE*) b) + bytes);
for ( size_t i = 0; i < remain; i++ )
{
if ( (1 & (av >> i)) != (1 & (bv >> i)) )
return 1;
}
}
return 0;
}

/** A simple Bit Map.
The raw size of the map is always guaranteed to be on 128-bit boundaries,
which allows fast searching for on/off bits, using the raw map.

Usage:
Most functions require a static sized bitmap, ie create a bitmap of a specific size
using Resize(), then use Get() and Set().<br/>
However, the Add() function will intelligently increase the capacity
of the bitmap if necessary. For this purpose the bitmap holds a CapacityBits field,
which is used to grow the bitmap at a 2x rate, like vectors.
**/
class PAPI BitMap
{
public:

#ifdef _WIN64
typedef UINT64 TUnit;
#else
typedef UINT32 TUnit;
#endif

static const int UnitSize = sizeof(TUnit) * 8;
static const TUnit UnitFill = -1;

#ifndef MIN
template<typename TV> static TV MIN(TV a, TV b) { return a < b ? a : b; }
#endif
#ifndef MAX
template<typename TV> static TV MAX(TV a, TV b) { return a < b ? b : a; }
#endif

BitMap()
{
Construct();
}
BitMap( const BitMap& b )
{
Construct();
*this = b;
}
~BitMap()
{
Clear();
}

/** Necessary raw block byte alignment.
16 might seem wide, but it's in view of SSE optimizations. I think SSE4 has a count bits instruction that operates
on a 128 bit word.
WARNING: This is not currently used. If you DO use it, then remove the non-aligned BmpAlloc/BmpFree implementations.
**/
static const int Alignment = 16;

/** Set the buffer to an external source.
**/
void SetExternal( int bits, void* buffer, int allocatedBits )
{
ASSERT( allocatedBits >= 8 && allocatedBits % 8 == 0 );
CanFind = allocatedBits % (Alignment * 8) == 0;
Clear();
External = true;
SizeBytes = bits / 8;
CapacityBits = bits;
SizeBits = CapacityBits;
Map = (BYTE*) buffer;
}

BitMap& operator=( const BitMap& b )
{
ASSERT( !External && !b.External );
CapacityBits = b.SizeBits;
SizeBytes = b.SizeBytes;
SizeBits = b.SizeBits;
CanFind = b.CanFind;
BmpFree( Map );
Map = (BYTE*) BmpAlloc( SizeBytes );
memcpy( Map, b.Map, SizeBytes );
return *this;
}

/// Will shrink the bitmap to it's minimum required size (only necessary after using Add()).
void Shrink()
{
if ( External ) { ASSERT(false); return; }
if ( CapacityBits == SizeBits ) return;
if ( SizeBits == 0 ) { Clear(); return; }
Resize( SizeBits );
}

/// Size in bits
int Size() const { return SizeBits; }

/// Capacity in bits (used for testing)
int Capacity() const { return CapacityBits; }

/// Set size to zero and free memory.
void Clear()
{
if ( !External ) BmpFree( Map );
Map = NULL;
SizeBits = 0;
SizeBytes = 0;
CapacityBits = 0;
CanFind = true;
External = false;
}

/** Fill a block of bits with a value.
This will not automatically increase the size. If the specified bit range
is invalid, then the function takes no action and debug asserts.
**/
void Fill( int bitStart, int bitEndInclusive, bool value )
{
int bitEnd = bitEndInclusive;
if ( bitEnd < bitStart - 1 )	{ ASSERT(false); return; }
if ( bitStart < 0 )				{ ASSERT(false); return; }
if ( (UINT32) bitEnd >= SizeBits )		{ ASSERT(false); return; }

// this covers the case where we're writing within one byte.
if ( bitEnd - bitStart < 8 )
{
for ( UINT32 i = (UINT32) bitStart; i <= (UINT32) bitEnd; i++ )
Set( i, value );
return;
}

// set beginning odd bits
while ( bitStart % 8 != 0 )
{
Set( bitStart, value );
bitStart++;
}

UINT32 sbyte = bitStart / 8;
UINT32 ebyte = bitEnd / 8;
if ( (bitEnd + 1) % 8 == 0 ) ebyte++;
BYTE bval = value ? 0xFF : 0x00;
for ( UINT32 i = sbyte; i < ebyte; i++ )
Map[i] = bval;

// set end odd bits
while ( (bitEnd + 1) % 8 != 0 )
{
Set( bitEnd, value );
bitEnd--;
}
}

/** Resizes preserving existing data.
@return False only if there is a memory allocation failure.
**/
bool Resize( UINT32 bits, bool fillNewSectionWith = false )
{
if ( bits == 0 ) { Clear(); return true; }
if ( External ) { ASSERT(false); return false; }
if ( bits == SizeBits ) return true;

BYTE* oldMap = Map;
UINT32 oldBytes = SizeBytes;
UINT32 oldBits = SizeBits;
SizeBits = bits;
SizeBytes = (bits + 7) / 8;
CapacityBits = SizeBits;
CanFind = true;

// align size to next 128-bit boundary
UINT32 alignedSize = ((SizeBytes + Alignment - 1) / Alignment) * Alignment;
Map = (BYTE*) BmpAlloc( alignedSize );

if ( Map != NULL && oldMap != NULL )
{
UINT32 copy = MIN( oldBytes, SizeBytes );
memcpy( Map, oldMap, copy );
BmpFree( oldMap );
}

if ( Map != NULL && bits > oldBits )
{
Fill( oldBits, bits - 1, fillNewSectionWith );
}

return Map != NULL;
}

/** Add a bit.
This is the only function that will automatically increase the size of the bitmap.
**/
void Add( bool value )
{
if ( External ) { ASSERT(false); return; }
if ( SizeBits >= CapacityBits )
{
int oldSize = SizeBits;
int newSize = MAX( SizeBits * 2, 64u );
if ( !Resize( newSize ) ) return;
SizeBits = oldSize;
}
Set( SizeBits, value );
SizeBits++;
}

/// Alias for Add()
BitMap& operator+= ( bool value )
{
Add( value );
return *this;
}

/// Automatically grow if necessary
void SetAutoGrow( UINT32 bit, bool value, bool fillNewSectionWith = false )
{
if ( bit == SizeBits )
{
Add( value );
return;
}
else if ( bit >= SizeBits )
{
if ( bit >= CapacityBits )
{
UINT32 nCap = MAX( CapacityBits * 2, bit + 1 );
Resize( nCap, fillNewSectionWith );
}
SizeBits = bit + 1;
}
Set( bit, value );
}

/// Set a bit
void Set( UINT32 bit, bool value )
{
UINT32 pword = bit >> 5;
UINT32 pbit = bit & 31;
#ifdef _WIN32
if ( value )	_bittestandset( ((LONG*) Map) + pword, pbit );
else			_bittestandreset( ((LONG*) Map) + pword, pbit );
#else
if ( value )	((UINT32*)Map)[pword] |= (1 << pbit);
else			((UINT32*)Map)[pword] &= ~(1 << pbit);
#endif
}

/// Get a bit, but return the passed-in default value if the bit requested is larger than the table.
bool GetOrDefault( UINT32 bit, bool default_value ) const
{
if ( bit >= SizeBits ) return default_value;
return Get( bit );
}

/// Get a bit
bool Get( UINT32 bit ) const
{
ASSERT( bit < SizeBits );
UINT32 pword = bit >> 5;
UINT32 pbit = bit & 31;
#ifdef _WIN32
return 0 != _bittest( ((LONG*) Map) + pword, pbit );
#else
return 0 != (((UINT32*)Map)[pword] & (1 << pbit));
#endif
}

bool operator[]( UINT32 bit ) const { return Get(bit); }

/** Counts the number of true bits in the specified range.
This is not optimized, but in future I may indeed do that.
**/
int CountTrueBits( UINT32 fromBit = 0, UINT32 toBitInclusive = -1 ) const
{
if ( toBitInclusive == -1 ) toBitInclusive = SizeBits - 1;
UINT32 count = 0;
for ( UINT32 i = fromBit; i < toBitInclusive; i++ )
{
if ( Get(i) )
count++;
}
return count;
}

/** Counts the number of false bits in the specified range.
**/
int CountFalseBits( UINT32 fromBit = 0, UINT32 toBitInclusive = -1 ) const
{
if ( toBitInclusive == -1 ) toBitInclusive = SizeBits - 1;
UINT32 size = 1 + toBitInclusive - fromBit;
return size - CountTrueBits( fromBit, toBitInclusive );
}

/// Returns the raw map
void* GetMap() const { return Map; }

/// Linearly searches the map for the first true bit.
int FirstTrueBit( UINT32 firstBit = 0, UINT32 lastBitInclusive = -1 ) const { return FirstBit( true, firstBit, lastBitInclusive ); }

/// Linearly searches the map for the first false bit.
int FirstFalseBit( UINT32 firstBit = 0, UINT32 lastBitInclusive = -1 ) const { return FirstBit( false, firstBit, lastBitInclusive ); }

/** Linearly searches the map for the first true or false bit, and returns -1 if none is found.
@firstBit Begin searching at the indicated bit.
@lastBitInclusive Stop searching on the specified bit.
@return The first bit found in the requested state, or -1 if there is no such bit.
**/
UINT32 FirstBit( bool state, UINT32 firstBit = 0, UINT32 lastBitInclusive = -1 ) const
{
if ( !CanFind ) { ASSERT(false); return -1; }
if ( firstBit < 0 ) firstBit = 0;
if ( SizeBits == 0 ) return -1;
if ( lastBitInclusive == -1 ) lastBitInclusive = SizeBits - 1;
lastBitInclusive = MIN( lastBitInclusive, SizeBits - 1 );
// the second pass is for the following case:
// the bitmap looks like this: ([] denotes a 32-bit block).
// [01000..0][001000..0]
// and the search is ( true, 3 ).
// This causes us to begin our search on the first block, and then we
// false-positively exit on the first byte.. ergo the second pass.
for ( int pass = 0; pass < 2; pass++ )
{
if ( firstBit > lastBitInclusive ) return -1;
UINT32 searchBytes = 1 + (lastBitInclusive / 8);
TUnit* base = (TUnit*) Map;
base += firstBit / UnitSize;
TUnit* p = base;
TUnit* porg = base;
TUnit* pb = (TUnit*) Map;
TUnit* pt = (TUnit*) (Map + searchBytes);
if ( state )
{
for ( ; p < pt; p++ ) if ( *p != 0 ) break;
}
else
{
for ( ; p < pt; p++ ) if ( *p != UnitFill ) break;
}
UINT32 sbit = UINT32((p - pb) * UnitSize);
sbit = MAX( sbit, firstBit );
UINT32 ebit = MIN( sbit + UnitSize, lastBitInclusive + 1 );
if ( state )
{
for ( UINT32 i = sbit; i < ebit; i++ ) if ( Get(i) ) return i;
}
else
{
for ( UINT32 i = sbit; i < ebit; i++ ) if ( !Get(i) ) return i;
}
// this is the only condition necessitating a 2nd pass
if ( firstBit % UnitSize != 0 && p == porg )
{
firstBit = ((firstBit + UnitSize - 1) / UnitSize) * UnitSize;
continue;
}
return -1;
}
return -1;
}

protected:
bool External;
bool CanFind;	///< Only true if our data is aligned on 128 bits.
UINT32 CapacityBits;
UINT32 SizeBits;
UINT32 SizeBytes;
BYTE* Map;

void Construct()
{
External = false;
CanFind = false;
CapacityBits = 0;
SizeBytes = 0;
SizeBits = 0;
Map = NULL;
}

#if defined(ABC_HAVE_ALIGNED_MALLOC)
void* BmpAlloc( size_t bytes )
{
return AbcAlignedMalloc( bytes, Alignment );
}
void BmpFree( void* p )
{
return AbcAlignedFree( p );
}
#else
// This business of being 128-byte aligned is not actually necessary.. it's just a future looking thing
void* BmpAlloc( size_t bytes )
{
return malloc( bytes );
}
void BmpFree( void* p )
{
return free( p );
}
#endif

};


/** A free list, built on top of BitMap.

We run a secondary bitmap that records groups of 32 slots, marking a 1
if all 32 slots are occupied, and a zero otherwise. This allows us to
search for 1024 free slots with a single 32-bit integer comparison.
The reason for this is because every bit in the secondary map covers
32 bits in the main map, and 32 * 32 = 1024.

For a 64-bit map, this becomes 4096. I guess optimal performance depends
on the particular use case. Note that it will not be 64 * 64 until we have
made BitMap capable of using 64-bits... let's do it now...

We pad our main map's size up so that it fits the group size,
and we set the extra bits to 1, so that they are marked as 'used'.
**/
template< typename GType >
class TFreeList
{
public:
TFreeList()
{
Guess = 0;
Used = 0;
Size = 0;
External = false;
}

/// Group bits
static const int GBits = sizeof(GType) * 8;
static const GType GFull = -1;

void Reset()
{
if ( External )
{
Secondary.Clear();
Main.Clear();
Size = 0;
External = false;
}
else
{
Resize(0);
}
Used = 0;
Guess = 0;
}

int RequiredMainBits( int bits )
{
return ((bits + GBits - 1) / GBits) * GBits;
}

void Resize( int bits )
{
ResizeInternal( bits, true );
}

void SetMap( int bits, int used, const void* raw )
{
if ( External ) Reset();
ResizeInternal( bits, false );
memcpy( Main.GetMap(), raw, (bits + 7) / 8 );
SetOverBits( true );
Used = used;
RebuildSecondaryInternal();
}

/** Set the main map from an externally allocated memory block.
It is illegal to resize the bitmap when it is external. If you want to recycle the object,
call Clear(), which makes it non-external.
**/
bool SetMapExternal( int bits, int used, void* raw, int bitsReserved )
{
// bitsReserved is here for no purpose other than to ensure that you understand that you might
// needs to have extra bits on the end to pad things out to 32/64
if ( RequiredMainBits(bits) > bitsReserved ) { ASSERT(false); return false; }
Main.SetExternal( bits, raw, bitsReserved );
Size = bits;
External = true;
SetOverBits( true );
Used = used;
RebuildSecondaryInternal();
return true;
}

void* GetMain()
{
return Main.GetMap();
}

int Capacity() const { return Size; }
int SlotsUsed() const { return Used; }

bool Get( int slot ) const { return Main.Get(slot); }

/** Find a free item.

The item is marked non-free before the function returns.

@return A free item, or -1 if all items are used.
**/
int Acquire()
{
if ( Used == Size ) return -1;
int slot = -1;
if ( Guess >= 0 && Guess < Size )
{
if ( !Main.Get(Guess) )
slot = Guess;
}
if ( slot == -1 )
{
slot = Search();
}
if ( slot == -1 ) { ASSERT(false); return -1; } // this ought to be impossible.
Main.Set( slot, true );
Update( slot );
Used++;
Guess = slot + 1;
return slot;
}


void Release( int slot )
{
ASSERT( slot >= 0 && slot < Size );
ASSERT( Main.Get(slot) );
Main.Set( slot, false );
Update( slot );
Used--;
Guess = slot;
}

/** Rebuild the secondary map.
Use this only if you have updated the underlying bitmap (which you COULD only do if you were operating with external data).
You must respecify the number of free slots here.
**/
void RebuildSecondary( int used )
{
Used = used;
RebuildSecondaryInternal();
}

/// If you modify the underlying map, you better call RebuildSecondary afterwards.
BitMap& GetMainMap()
{
return Main;
}

protected:
int Guess;
int Size;
int GroupSize() { return Size / GBits; }
int Used;
bool External;
BitMap Main, Secondary;

void Update( int forBit )
{
GType* prim = (GType*) Main.GetMap();
int g = forBit / GBits;
Secondary.Set( g, prim[g] == GFull );
}

int Search()
{
int g = Secondary.FirstFalseBit( 0 );
if ( g < 0 ) { ASSERT(false); return -1; } // by design, should never happen, because we keep track of Used vs Size.
return Main.FirstFalseBit( g * GBits );
}

void SetOverBits( bool used )
{
// set the over bits (which pad our main buffer up to a GBit boundary)
for ( int i = Size; i < Main.Size(); i++ )
Main.Set( i, used );
}

void ResizeInternal( int bits, bool rebuild_secondary = true )
{
if ( External ) { ASSERT(false); return; }
//ASSERT( bits >= Size );
//Used = 0;
SetOverBits( false );
Size = bits;
int actual = ((bits + GBits - 1) / GBits) * GBits;
Main.Resize( actual, false );
SetOverBits( true );
if ( rebuild_secondary )
RebuildSecondaryInternal();
}

void RebuildSecondaryInternal()
{
int ns = Main.Size() / GBits;
Secondary.Resize( ns );
GType* mb = (GType*) Main.GetMap();
for ( int i = 0; i < ns; i++ )
{
Secondary.Set( i, mb[i] == GFull );
}
}

};

typedef TFreeList< UINT32 > FreeList32;
typedef TFreeList< UINT64 > FreeList64;

#ifdef _WIN64
typedef FreeList64 FreeList;
#else
typedef FreeList32 FreeList;
#endif


/* fhash - my final hash table (!).
I wrote this because I was sick of agonizing over the code bloat every time I wanted to add a new hash table.
So this basically uses a table of function pointers.

Examples
========

string -> string
----------------

namespace space { class mystring { uint32 GetHashCode() const {...} }; }

// This must be done in the global namespace
FHASH_SETUP_CLASS_GETHASHCODE( space::mystring, mystring );

fhashmap<mystring,mystring> t;
t.insert( "a", "A" );



ptr* -> int32			Using the address as the hash code
--------------------------------------------------------

struct myobj {}

// As always, this must be written in the global namespace
FHASH_SETUP_POINTER_ADDRESS( myobj );



object -> int32			Using a member function of the form "uint GetHashCode() const"
------------------------------------------------------------------------------------

struct myobj { uint32 GetHashCode() const {...}; }

FHASH_SETUP_CLASS_GETHASHCODE( myobj, myobj );



object -> int32			Using your own hash function
------------------------------------------------------

struct myobj {}


FHASH_SETUP_CLASS_CTOR_DTOR( myobj );	// For classes
FHASH_SETUP_POD_CTOR_DTOR( myobj );		// For PODs that you want default-initialized
FHASH_SETUP_TOR_NOP( myobj );			// For PODs that you want no initialization performed upon

template<> inline uint32 fhash_gethash(const myobj& obj) { return obj.x ^ obj.y; }


BMH
*/

#ifndef FHASHTABLE_H
#define FHASHTABLE_H


#ifndef FHASH_NORETURN
#	ifdef _MSC_VER
#		define FHASH_NORETURN __declspec(noreturn)
#	else
#		define FHASH_NORETURN __attribute__ ((noreturn))
#	endif
#endif

#ifndef PAPI
#define PAPI
#endif
#ifndef ASSERT
//#define ASSERT(condition) if !(condition) { int* p = 0; *p = 0; }
#define ASSERT(condition) (void)0
#endif
#ifndef NULL
#define NULL    0
#endif

#ifdef _MSC_VER
#ifndef __cplusplus_cli
// 7% speedup over __cdecl - but annoying warnings from CLR compilation
#define FHASH_CALL __fastcall
#else
#define FHASH_CALL
#endif
#else
#define FHASH_CALL
#endif

typedef signed char			int8;
typedef unsigned char		uint8;

typedef short				int16;
typedef unsigned short		uint16;

typedef          int		int32;
typedef unsigned int		uint32;

#ifdef _MSC_VER
typedef          __int64	int64;
typedef unsigned __int64	uint64;
#else
typedef int64_t				int64;
typedef uint64_t			uint64;
#endif

typedef unsigned char		fhashstate_t;
typedef unsigned char		byte;
typedef unsigned int		uint;
typedef uint32				fhashkey_t;

static const size_t fhash_npos = -1;
static const size_t fhash_min_autoshrink_count = 32;

inline size_t fhash_next_power_of_2( size_t v )
{
size_t s = 1;
while ( s < v ) s <<= 1;
return s;
}

inline FHASH_NORETURN void fhash_die()
{
*((int*)0) = 0;
while (1) {} // necessary to satisfy GCC
}

// _tor is ctor or dtor
enum fhash_tor_type
{
fhash_TOR_FUNC,	///< Function call
fhash_TOR_ZERO,	///< memset(0) -- illegal for dtor
fhash_TOR_NOP	///< nop
};

enum fhash_key_states
{
// can't have more than 4... only 2 bits available
fhash_Null = 0,
fhash_Full = 1,
fhash_Deleted = 2,
fhash_ERROR = 3
};

inline size_t fhash_state_array_size( size_t asize )
{
// every item needs 2 bits, so that's 16 items per int32
return (asize / 4) + 8;
}

// returns the state of a given position in the table
inline fhash_key_states fhash_get_state( fhashstate_t state_array[], size_t pos )
{
size_t        bytepos = pos >> 2;
unsigned char bitpos = pos & 3;
unsigned char masks[4] = { 3, 12, 48, 192 };
fhash_key_states ks = (fhash_key_states) ( (state_array[bytepos] & masks[bitpos]) >> (bitpos << 1) );
return ks;
}

inline void fhash_set_state( fhashstate_t state_array[], size_t pos, fhash_key_states newState )
{
size_t        bytepos = pos >> 2;
unsigned char bitpos = pos & 3;
unsigned char masks[4] = { (unsigned char) ~3, (unsigned char) ~12, (unsigned char) ~48, (unsigned char) ~192 };
unsigned char state = state_array[bytepos] & masks[bitpos];
state |= newState << (bitpos << 1);
state_array[bytepos] = state;
}

typedef void	(FHASH_CALL *fhash_func_xfer)			(void* dst, const void* src, size_t obj_size);
typedef void	(FHASH_CALL *fhash_func_ctor)			(void* obj);
typedef void	(FHASH_CALL *fhash_func_dtor)			(void* obj);
typedef int		(FHASH_CALL *fhash_func_keycmp)			(const void* a, const void* b);
typedef uint32	(FHASH_CALL *fhash_func_gethash)		(const void* obj, size_t obj_size);

inline void fhash_null_ctor(void* obj) {}
inline void fhash_null_dtor(void* obj) {}
inline void FHASH_CALL fhash_pod_move(void* dst, const void* src, size_t obj_size) { memcpy(dst, src, obj_size); }
inline void FHASH_CALL fhash_pod_copy(void* dst, const void* src, size_t obj_size) { memcpy(dst, src, obj_size); }

// Types of constructors and destructors required by your type
template< typename T > void fhash_tor_types( fhash_tor_type& ctor, fhash_tor_type& dtor ) { ctor = fhash_TOR_FUNC; dtor = fhash_TOR_FUNC; }

// Use operator= to copy a value
template< typename T >
void FHASH_CALL fhash_type_copy(void* dst, const void* src, size_t obj_size)
{
T* tdst = (T*) dst;
const T* tsrc = (const T*) src;
*tdst = *tsrc;
}

// Use operator= for pairs of tightly packed Key,Value objects
template< typename K, typename V >
void FHASH_CALL fhash_type_copy_pair(void* dst, const void* src, size_t obj_size)
{
K* kdst = (K*) dst;
V* vdst = (V*) (kdst + 1);
K* ksrc = (K*) src;
V* vsrc = (V*) (ksrc + 1);
*kdst = *ksrc;
*vdst = *vsrc;
}

template<typename TPod>
int FHASH_CALL fhash_pod_keycmp(const void* a, const void* b) { return !(*((const TPod*)a) == *((const TPod*)b)); }

template<typename T>
int FHASH_CALL fhash_keycmp(const void* a, const void* b) { return fhash_pod_keycmp<T>(a,b); }

inline uint32 fhash_gethash_int32(const void* obj) { return *((const uint32*)obj); }
inline uint32 fhash_gethash_int64(const void* obj) { uint64 v = *((const uint64*)obj); return uint32(v ^ (v >> 32)); }

#if ARCH_64
inline uint32 fhash_gethash_ptr(const void* ptr) { uint64 v = reinterpret_cast<uint64>(ptr); return uint32(v) ^ uint32(v >> 32); }
#else
inline uint32 fhash_gethash_ptr(const void* ptr) { return reinterpret_cast<uint32>(ptr); }
#endif

// Provide a specialization of these for your type
template< typename T > uint32 fhash_gethash(const T& obj);

template<> inline uint32 fhash_gethash(const int8& v)		{ return (uint32) v; }
template<> inline uint32 fhash_gethash(const uint8& v)		{ return (uint32) v; }
template<> inline uint32 fhash_gethash(const int16& v)		{ return (uint32) v; }
template<> inline uint32 fhash_gethash(const uint16& v)		{ return (uint32) v; }
template<> inline uint32 fhash_gethash(const int32& v)		{ return fhash_gethash_int32(&v); }
template<> inline uint32 fhash_gethash(const uint32& v)		{ return fhash_gethash_int32(&v); }
template<> inline uint32 fhash_gethash(const int64& v)		{ return fhash_gethash_int64(&v); }
template<> inline uint32 fhash_gethash(const uint64& v)		{ return fhash_gethash_int64(&v); }

template<typename T> uint32 FHASH_CALL fhash_gethash_gen_wrap(const void* v, size_t obj_size)
{
return fhash_gethash<T>( *((const T*)v) );
}

// hash the pointer itself - not what it points to
template<> inline uint32 FHASH_CALL fhash_gethash_gen_wrap<void*>(const void* v, size_t obj_size)
{
return fhash_gethash_ptr(v);
}

// constructor of your type
template< typename T > void fhash_ctor(T& obj);

// destructor of your type
template< typename T > void fhash_dtor(T& obj);

// Define NULL constructors and destructors for PODs
// Hm. probably better to initialize to zero than to leave uninitialized, because of partial writes.
#define FHASH_SETUP_POD_CTOR_DTOR(T) \
template<> inline void fhash_ctor(T& obj) { obj = T(); } \
template<> inline void fhash_dtor(T& obj) {}

#define FHASH_SETUP_TOR_NOP(T) \
template<> inline void fhash_ctor(T& obj) {} \
template<> inline void fhash_dtor(T& obj) {}

// POD, ctor=nop dtor=nop
#define FHASH_SETUP_POD(T) \
FHASH_SETUP_TOR_NOP(T) \
template<> inline void fhash_tor_types<T>( fhash_tor_type& ctor, fhash_tor_type& dtor ) { ctor = fhash_TOR_NOP; dtor = fhash_TOR_NOP; }

// Create pass-through placement new (and delete, to satisfy compiler) operators for the type
// Note: We memset(0) after destroying. This is because most destructors are not callable more than once, but we need to be.
// This won't work for everything, but at least it covers pointers inside objects.
#define FHASH_SETUP_CLASS_CTOR_DTOR(NST,T) \
inline void* operator new( size_t bytes, NST* pos ) { return pos; } \
inline void  operator delete( void* obj, NST* pos ) {} \
template<> inline void fhash_ctor(NST& obj) { new(&obj) NST(); } \
template<> inline void fhash_dtor(NST& obj) { obj.~T(); memset(&obj, 0, sizeof(obj)); }

FHASH_SETUP_POD(int8)
FHASH_SETUP_POD(int16)
FHASH_SETUP_POD(int32)
FHASH_SETUP_POD(int64)
FHASH_SETUP_POD(uint8)
FHASH_SETUP_POD(uint16)
FHASH_SETUP_POD(uint32)
FHASH_SETUP_POD(uint64)

// Setup for a class that has an "int GetHashCode() const" function,
// but doesn't need to be constructed or destructed. The omission of
// the constructor and destructor calls is a performance optimization.
#define FHASH_SETUP_POD_GETHASHCODE(T) \
FHASH_SETUP_TOR_NOP(T) \
template<> inline uint32 fhash_gethash(const T& obj) { return obj.GetHashCode(); }

// Setup for a class that has a regular constructor and destructor
// This is usable then as fhashmap<TheClass,Value>
// See also FHASH_SETUP_POINTER_GETHASHCODE, if you want to use a pointer to the class as the key
#define FHASH_SETUP_CLASS_GETHASHCODE(NST,T) \
FHASH_SETUP_CLASS_CTOR_DTOR(NST,T) \
template<> inline uint32 fhash_gethash(const NST& obj) { return obj.GetHashCode(); }

// Pointer to object that has an "int GetHashCode() const" function
// This is usable then as fhashmap<TheClass*,Value>
#define FHASH_SETUP_POINTER_GETHASHCODE(T) \
template<> inline void fhash_ctor<T*>(T*& obj)		{} \
template<> inline void fhash_dtor<T*>(T*& obj)		{} \
template<> inline uint32 fhash_gethash<T*>(T* const &obj)										{ return obj->GetHashCode();} \
template<> inline void fhash_tor_types<T*>( fhash_tor_type& ctor, fhash_tor_type& dtor )		{ ctor = fhash_TOR_NOP; dtor = fhash_TOR_NOP; } \
template<> inline int FHASH_CALL fhash_keycmp<T*>(const void* a, const void* b)					{ return **((T**) a) == **((T**) b) ? 0 : 1; }

// Pointer = object identity (and therefore hash value)
#define FHASH_SETUP_POINTER_ADDRESS(T) \
template<> inline void fhash_ctor<T*>(T*& obj)		{} \
template<> inline void fhash_dtor<T*>(T*& obj)		{} \
template<> inline uint32 fhash_gethash<T*>(T* const &obj)										{ return fhash_gethash_ptr(obj);} \
template<> inline void fhash_tor_types<T*>( fhash_tor_type& ctor, fhash_tor_type& dtor )		{ ctor = fhash_TOR_NOP; dtor = fhash_TOR_NOP; }

template< typename K > void FHASH_CALL fhash_type_ctor(void* obj) { fhash_ctor( *((K*) obj) ); }
template< typename K > void FHASH_CALL fhash_type_dtor(void* obj) { fhash_dtor( *((K*) obj) ); }

template< typename K, typename V >
void FHASH_CALL fhash_type_ctor_pair(void* obj)
{
K* kobj = (K*) obj;
V* vobj = (V*) (kobj + 1);
fhash_ctor( *kobj );
fhash_ctor( *vobj );
}

template< typename K, typename V >
void FHASH_CALL fhash_type_dtor_pair(void* obj)
{
K* kobj = (K*) obj;
V* vobj = (V*) (kobj + 1);
fhash_dtor( *kobj );
fhash_dtor( *vobj );
}

// Convenience method to delete all objects from a map<obj1*, obj2*>
template< typename TMap >
void fhash_delete_all_keys_and_values( TMap& m )
{
for ( typename TMap::iterator it = m.begin(); it != m.end(); it++ )
{
delete it.key();
delete it.val();
}
m.clear();
}

// Convenience method to delete all keys from a map<key*, ANYTHING>
template< typename TMap >
void fhash_delete_all_keys( TMap& m )
{
for ( typename TMap::iterator it = m.begin(); it != m.end(); it++ )
delete it.key();
m.clear();
}

// Convenience method to delete all values from a map<ANYTHING, value*>
template< typename TMap >
void fhash_delete_all_values( TMap& m )
{
for ( typename TMap::iterator it = m.begin(); it != m.end(); it++ )
delete it.val();
m.clear();
}

struct fhash_iface
{
size_t				Stride;
fhash_tor_type		NCTor;
fhash_tor_type		NDTor;
fhash_func_xfer		Move;
fhash_func_xfer		Copy;
fhash_func_ctor		Create;
fhash_func_dtor		Delete;
fhash_func_keycmp	KeyCmp;
fhash_func_gethash	GetHash;
bool BothNOP() const { return NCTor == fhash_TOR_NOP && NDTor == fhash_TOR_NOP; }
};

class PAPI fhashtable_base
{
public:

/** Provides a bi-directional iterator through the set.
A note on iterator consistency:
If you want to be able to iterate through a table and delete selected items from it,
then you must first disable the autoshrink mechanism. Failure to do so will result
in an invalid iterator.
**/
class iterator
{
public:
iterator()
{
_index = -1;
pos = fhash_npos;
end = false;
parent = 0;
}
iterator( const fhashtable_base *p, size_t itpos )
{
_index = -1;
pos = itpos;
end = pos == fhash_npos;
parent = p;
}
iterator(const iterator &copy)
{
_index = copy._index;
pos = copy.pos;
end = copy.end;
parent = copy.parent;
}
iterator(const fhashtable_base *p)
{
pos = 0;
_index = 0;
end = false;
parent = const_cast<fhashtable_base*>(p);
if (parent->mCount == 0 || parent->mSize == 0)
{
end = true;
}
else
{
// make iterator point to first object if it isn't already so
fhash_key_states state = fhash_get_state(parent->mState, pos);
if (state != fhash_Full)
(*this)++;
}
_index = 0;
}

bool operator==( const iterator& b )
{
if ( end && b.end ) return true;
if ( end != b.end ) return false;
return pos == b.pos;
}

bool operator!=( const iterator& b )
{
return !( *this == b );
}

void* operator->() const
{
return parent->dpos(pos);
}
void* operator*() const
{
return parent->dpos(pos);
}

// (int) --> postfix
/// Increment
iterator& operator++(int)
{
if (pos >= parent->mSize) return *this;
pos++;
while ( pos < parent->mSize && fhash_get_state(parent->mState, pos) != fhash_Full )
{
pos++;
}
_index++;
if (pos >= parent->mSize) end = true;
return *this;
}
// (int) --> postfix
/// Decrement
iterator& operator--(int)
{
if (pos == -1) return *this;
pos--;
while ( pos != -1 && fhash_get_state(parent->mState, pos) != fhash_Full )
{
pos--;
}
_index--;
if (pos == -1) end = true;
return *this;
}

/** Signals that iteration has ended.
This will be flagged on 3 occasions:
- The set is empty.
- Forward iteration with operator++ has caused us to step onto the last entity.
- Backward iteration with operator-- has caused us to step onto the first entity.

Note that in neither of two latter cases will the iterator point to an object that is
not inside the set / table.
**/
bool end;

/** Returns the index of the current object.
The index is zero for the element referred to after begin(), then incremented
for every operator++, and decremented for every operator--.

It does not have widespread use, but can be handy in some cases where the set must be
referred to as a vector.
**/
size_t index() const
{
return _index;
}

protected:
const fhashtable_base *parent;
size_t pos;
size_t _index; // valid range is [0, mCount]
};

fhashtable_base()
{
base_init();
}
fhashtable_base( const fhashtable_base& copy )
{
base_init();
mConfig = copy.mConfig;
*this = copy;
}
fhashtable_base& operator=( const fhashtable_base& copy )
{
if ( this == &copy ) return *this;

free_arrays();

mMask = copy.mMask;
mProbeOffset = copy.mProbeOffset;
mAutoShrink = copy.mAutoShrink;
mAge = copy.mAge;
mCount = copy.mCount;
mSize = copy.mSize;
mMaxCount = copy.mMaxCount;

if ( mCount == 0 )
{
mAge = 0;
mSize = 0;
}
else
{
size_t statesize = sizeof(fhashstate_t) * fhash_state_array_size(mSize);
mState = (fhashstate_t*) malloc( statesize );
if ( mState == NULL )
fhash_die();
memcpy( mState, copy.mState, statesize );
mData = (byte*) malloc( mConfig.Stride * mSize );
if ( mData == NULL )
fhash_die();

for ( size_t i = 0; i < mSize; i++ )
{
create_obj( dpos(i) );
if ( fhash_get_state(mState, i) == fhash_Full )
mConfig.Copy( dpos(i), copy.dpos(i), mConfig.Stride );
}
}

return *this;
}

~fhashtable_base()
{
free_arrays();
}

void init( const fhash_iface& f )
{
mConfig = f;
}

/// Clears the set
void clear()
{
free_arrays();
mSize = 0;
mMaxCount = 0;
mMask = 0;
mProbeOffset = 0;
mCount = 0;
mAge = 0;
}

/// Clears the set, but keeps our raw size the same
void clear_noalloc()
{
if ( mSize == 0 ) return;

ASSERT( fhash_Null == 0 );

if ( mConfig.BothNOP() )
{
// do nothing (such as for PODs)
}
else
{
for ( size_t i = 0; i < mSize; i++ )
{
if ( fhash_get_state(mState, i) == fhash_Full )
{
mConfig.Delete( dpos(i) );
mConfig.Create( dpos(i) );
}
}
}
memset( mState, 0, sizeof(fhashstate_t) * fhash_state_array_size(mSize) );

mCount = 0;
mAge = 0;
}

/// Number of elements in set
size_t size() const
{
return mCount;
}

/// Raw size of table
size_t raw_size() const
{
return mSize;
}

/** Resize the hashtable.
In general this is used to prepare the hashtable for a large number of insertions.
The hashtable is automatically resized during normal use.
There are some conditions that apply:
- If newsize == 0, the table is cleared.
- If 0 < newsize < 2 then newsize = 2.
- If newsize < mCount * mFillRatio then we debug assert, increase newsize, and proceed.
- If none of the above conditions apply, then newsize = NextPrime( newsize )
**/
void resize( size_t newsize )
{
if ( newsize < mCount * 2 )
newsize = mCount * 2;

if ( newsize == 0 ) { clear(); return; }

if ( newsize < 2 ) newsize = 2;
else newsize = fhash_next_power_of_2( newsize );

// save our current sate
byte			*odata = mData;
fhashstate_t	*ostate = mState;
size_t			 osize = mSize;

// allocate the new keys
mData = (byte*) malloc( newsize * mConfig.Stride );
mState = (fhashstate_t*) malloc( fhash_state_array_size(newsize) );
if ( mData == NULL || mState == NULL )
fhash_die();

// Make all the states null
memset( mState, 0, fhash_state_array_size(newsize) );

if ( mConfig.NCTor == fhash_TOR_NOP )		{}
else if ( mConfig.NCTor == fhash_TOR_ZERO )	memset( mData, 0, newsize * mConfig.Stride );
else
{
// Delay construction until after the move of the existing values. In that case, only slots that are not occupied need to be constructed.
// The delayed-construction thing could apply to the fhash_TOR_ZERO case too, but my guess is that it's probably better to let an efficient memset()
// do it's job - esp regarding write combining, etc.
//for ( size_t i = 0; i < newsize; i++ )
//	mConfig.Create( dpos(i) );
}

mCount = 0;
mSize = newsize;
mMaxCount = mSize >> 1;
mMask = mSize - 1;
mProbeOffset = mSize >> 1;
mAge = 0;

// Copy values
for ( size_t i = 0; i < osize; i++ )
if ( fhash_get_state( ostate, i ) == fhash_Full )
insert_no_check( false, odata + i * mConfig.Stride );

// Run constructors for new objects that were not copied
if ( mConfig.NCTor == fhash_TOR_FUNC )
{
for ( size_t i = 0; i < newsize; i++ )
if ( fhash_get_state( mState, i ) != fhash_Full )
mConfig.Create( dpos(i) );
}

// Run destructors for old objects that were not copied
if ( mConfig.NDTor == fhash_TOR_FUNC )
{
for ( size_t i = 0; i < osize; i++ )
if ( fhash_get_state( ostate, i ) == fhash_Null )
mConfig.Delete( odata + i * mConfig.Stride );
}

if (odata)	free(odata);
if (ostate) free(ostate);
}

void resize_for( size_t count )
{
return resize( count * 2 );
}

bool contains( const void* obj ) const
{
return _find( obj ) != fhash_npos;
}

iterator find( const void* obj )
{
return iterator( this, _find( obj ) );
}

/// \internal Searches linearly (for debugging this class)
bool linearfind( const void* obj ) const
{
for ( size_t i = 0; i < mSize; i++ )
{
if ( mConfig.KeyCmp( dpos(i), obj ) == 0 )
return true;
}
return false;
}

/// Returns the size of the data array + the size of the state array
size_t mem_usage() const
{
return mConfig.Stride * mSize + fhash_state_array_size(mSize);
}

/// Merge
fhashtable_base& operator+=( const fhashtable_base& b )
{
for ( iterator it = b.begin(); it != b.end(); it++ )
insert_check_exist( *it );
return *this;
}

/// Subtract
fhashtable_base& operator-=( const fhashtable_base& b )
{
for ( iterator it = b.begin(); it != b.end(); it++ )
_erase( *it );
return *this;
}

// Internal access
void* dpos( size_t i ) const { return mData + mConfig.Stride * i; }

/** Serializes the table to a file. Since this is a memory dump, it should only be used on tables whos elements contain no pointers.
After serialization the hash table is useless, and must not be touched again until after calling deserialize_pod.
@param mem The buffer in which to serialize.
@param bytes The size of the buffer. If the size is too small, then nothing will be written, and bytes will contain the necessary size.
**/
//void serialize_pod( void* mem, size_t& bytes )
//{
//	size_t s1 = mSize * sizeof(TData);
//	size_t s2 = stateArraySize( mSize ) * sizeof(fhashstate_t);
//	size_t required = s1 + s2;
//	if ( bytes < required )
//	{
//		bytes = required;
//		return;
//	}
//	if ( s1 + s2 == 0 ) return;
//	if ( mem == NULL ) { ASSERT(false); return; }
//	BYTE* bmem = (BYTE*) mem;
//	memcpy( bmem, mData, s1 );
//	memcpy( bmem + s1, mState, s2 );
//	free_arrays();
//}

/** Deserializes the table from a file.
No checks are made to ensure that you haven't touched the vector since it was serialized.
**/
//void deserialize_pod( const void* mem )
//{
//	ASSERT( mSize > 0 );
//	ASSERT( mData = NULL );

//	mState = new fhashstate_t[ stateArraySize(mSize) ];
//	mData = new TData[ mSize ];

//	size_t s1 = mSize * sizeof(TData);
//	size_t s2 = stateArraySize( mSize ) * sizeof(fhashstate_t);
//	if ( s1 + s2 == 0 ) return;
//	if ( mem == NULL ) { ASSERT(false); return; }
//	const BYTE* bmem = (const BYTE*) mem;
//	memcpy( mData, bmem, s1 );
//	memcpy( mState, bmem + s1, s2 );
//}

//size_t debug_table_pos( const TKey& obj, int i ) const
//{
//	fhashkey_t hkey = THashFunc::gethashcode( obj );
//	size_t pos = table_pos( hkey, i );
//	return pos;
//}

protected:

void base_init()
{
memset( &mConfig, 0, sizeof(mConfig) );
mData = NULL;
mState = NULL;
mMaxCount = 0;
mSize = 0;
mMask = 0;
mProbeOffset = 0;
mCount = 0;
mAge = 0;
mAutoShrink = true;
}

fhashkey_t get_hash_code( const void* obj ) const
{
return mConfig.GetHash( obj, mConfig.Stride );
}

/** Erases an item.
\return True if the item was found. False if the item was not found.
**/
bool _erase( const void* obj )
{
size_t pos = _find( obj );
if ( pos != fhash_npos )
{
mAge++;
mCount--;
fhash_set_state( mState, pos, fhash_Deleted );
delete_obj( dpos(pos) );
autoshrink();
return true;
}
else
return false;
}

void insert_check_resize()
{
if ( mCount >= mMaxCount )
resize( (mCount + 1) << 1 );
}

void copy_or_move( bool copy, void* dst, const void* obj )
{
if ( copy ) mConfig.Copy( dst, obj, mConfig.Stride );
else
{
// The ONLY path that hits this is when resizing the array, and copying over existing values. In that case, we have a target array of freshly constructed objects.
// We cannot simply memcpy over those fresh objects. We need to call their destructors first.
//if ( mConfig.NDTor == fhash_TOR_FUNC ) mConfig.Delete( dst );
// ALTERATION: We can simply memcpy over. The reason is because I've changed the initialization to delay running the constructors until after we've copied
// the existing values in. This is better because we avoid an unnecessary construction/destruction cycle.
mConfig.Move( dst, obj, mConfig.Stride );
}
}

/// Insert an item into the set without checking if it exists. Returns position of insertion.
size_t insert_no_check( bool copy, const void* obj )
{
insert_check_resize();
fhashkey_t hkey = get_hash_code( obj );
size_t pos = table_pos( hkey );
fhash_key_states state = fhash_get_state( mState, pos );
if ( state == fhash_Full )
{
// Search for an empty slot
uint i = 0;
while ( state == fhash_Full )
{
pos = table_pos( hkey, ++i );
state = fhash_get_state( mState, pos );
if ( i >= mSize ) ASSERT( false );
}
}
fhash_set_state( mState, pos, fhash_Full );
copy_or_move( copy, dpos(pos), obj );
mCount++;
return pos;
}

/** Insert an item into the set.

@param overwrite If true, then we overwrite any existing value for the specified key. This is a specialization
that is only applicable to hash maps (not hash sets).

@return fhash_npos if item already in table (only possible if overwrite is false).

**/
size_t insert_check_exist( const void* obj, bool overwrite = false )
{
insert_check_resize();

fhashkey_t hkey = get_hash_code( obj );

// We insert at the first deleted slot, or the first null slot, whichever comes first
// However, we must scan until (1. Find existing) or (2. Scanned entire table)
size_t pos = fhash_npos;
size_t pos_ins = fhash_npos; // remember the first fhash_Deleted position, because that is where we will insert, if we're not already existent
for ( uint i = 0; i != mSize; i++ )
{
pos = table_pos( hkey, i );
fhash_key_states ks = fhash_get_state( mState, pos );
if ( ks == fhash_Full )
{
if ( mConfig.KeyCmp( dpos(pos), obj ) == 0 )
{
// key already present
if ( overwrite )
{
copy_or_move( true, dpos(pos), obj );
return pos;
}
else
return fhash_npos;
}
}
else if ( ks == fhash_Null )
{
if ( pos_ins == fhash_npos ) pos_ins = pos;
break;
}
else /* if ( state == fhash_Deleted ) */
{
if ( pos_ins == fhash_npos ) pos_ins = pos;
}
}

// insert here
fhash_set_state( mState, pos_ins, fhash_Full );
copy_or_move( true, dpos(pos_ins), obj );
mCount++;
return pos_ins;
}

void free_arrays()
{
if ( mConfig.NDTor == fhash_TOR_NOP ) {}
else
{
for ( size_t i = 0; i < mSize; i++ )
mConfig.Delete( dpos(i) );
}

free(mData); mData = NULL;
free(mState); mState = NULL;
}

void delete_obj( void* obj )
{
if ( mConfig.NDTor == fhash_TOR_NOP ) return;
mConfig.Delete( obj );
}

void create_obj( void* obj )
{
if ( mConfig.NCTor == fhash_TOR_NOP ) return;
mConfig.Create( obj );
}

/// Returns the position of an item if existent
size_t _find( const void* obj ) const
{
if ( mSize == 0 ) return fhash_npos;
fhashkey_t hkey = get_hash_code( obj );
size_t pos = table_pos( hkey );
size_t first = pos;
// quick positive/empty check
fhash_key_states ks = fhash_get_state( mState, pos );
if ( ks == fhash_Full && mConfig.KeyCmp( dpos(pos), obj ) == 0 ) return pos;
else if ( ks == fhash_Null ) return fhash_npos;
else
{
// exhaustive
uint i = 0;
pos = table_pos( hkey, ++i );
while ( fhash_get_state(mState, pos) != fhash_Null )
{
if ( fhash_get_state(mState, pos) == fhash_Full && mConfig.KeyCmp( dpos(pos), obj ) == 0 ) return pos;
pos = table_pos( hkey, ++i );
if ( pos == first ) break;
}
return fhash_npos;
}
}

/// Erases all instances of key. Returns number of items erased.
size_t _erase_all( const void* obj )
{
if ( mSize == 0 ) return 0;
fhashkey_t hkey = get_hash_code( obj );
size_t pos = table_pos( hkey );
size_t first = pos;
size_t del = 0;
uint i = 0;
while ( true )
{
fhash_key_states state = fhash_get_state(mState, pos);
if ( state == fhash_Full && mConfig.KeyCmp( dpos(pos), obj ) == 0 )
{
del++;
delete_obj( dpos(pos) );
fhash_set_state( mState, pos, fhash_Deleted );
}
else if ( state == fhash_Null ) break;
pos = table_pos( hkey, ++i );
if ( pos == first ) break;
}
return del;
}

/// The hash function (optimization of generic table_pos with i = 0)
size_t table_pos( fhashkey_t key ) const
{
return (size_t) (fold(key) & mMask);
}

/// probe (when i = 0, this function must be identical to table_pos(key))
size_t table_pos( fhashkey_t key, uint i ) const
{
key = fold(key);
uint mul = key >> 1;
mul |= 1; // ensure multiplier is odd
return (size_t) ((key + i * mul) & mMask);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE: This code used to be inside table_pos, but it is invalid. It violates our "visit every slot exactly once" rule.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// This offset particularly helps speed up failed lookups when our table is a dense array of integers (consecutive hashes).
//// The layout in that case is that half of the table is completely occupied, and the other half (remember our fill factor -- there is always an 'other half')
//// is completely empty. This probe offset immediately sends us into the territory of the 'other half', thereby reducing the time that we spend walking through
//// the populated half.

//// The difference here seems to be negligible, but the simpler version should be better for future compilers.
//uint offset = i == 0 ? 0 : (uint) mProbeOffset;
////uint offset = ~(int(i - 1) >> 31) & mProbeOffset; // branch-less version
//return (size_t) ((key + offset + i * mul) & mMask);
///////////////////////////////////////////////////////////////////////////////


// Very simple mix function that at least gives us better behaviour when the only entropy is higher than our mask.
// This simplistic function probably causes evil behaviour in certain pathological cases, but it's better than not having it at all.
// This mixing solves cases such as values of the form 0x03000000, 0x04000000, 0x05000000. Without this folding
// function, those keys would all end up with the same table position, unless the table was larger than 0x0fffffff.
static fhashkey_t fold( fhashkey_t k )
{
uint32 u = k;
u = u ^ (u >> 16);
u = u ^ (u >> 8);
return u;
}

void autoshrink()
{
if ( (mAge & (32-1)) != 0 || !mAutoShrink ) return;

// Only shrink when we're more than 2x the size we need to be. The reason this is not
// simply 1x is to avoid possible ping-ponging during a repeated insert/erase pattern.
size_t necessary = fhash_next_power_of_2( mCount * 2 );

// I don't like having this heuristic here of fhash_min_autoshrink_count, but in all practicality, I have never made a hash table with such a huge key size
// that it would matter that you're storing 64 and not 32 or 16.
if ( mSize > necessary * 2 && mSize > fhash_min_autoshrink_count )
resize( 0 );
}

void move( void* dst, const void* src )
{
mConfig.Move( dst, src, mConfig.Stride );
}
void copy( void* dst, const void* src )
{
mConfig.Copy( dst, src, mConfig.Stride );
}

byte			*mData;			///< Key Array
fhashstate_t	*mState;		///< State Array (null, occupied, deleted)
unsigned int	mAge;			///< Incremented when item is erased
size_t			mMaxCount;		///< Maximum count before we must increase our raw size
size_t			mSize;			///< Size of table
size_t			mProbeOffset;	///< Initial offset of probe	(only used when not OHASH_PRIME_SIZE)
size_t			mMask;			///< Size of table - 1			(only used when not OHASH_PRIME_SIZE)
size_t			mCount;			///< Number of items in set
bool			mAutoShrink;	///< If true, then the table automatically shrinks itself when it's mAge reaches a certain limit

fhash_iface		mConfig;

public:

/** Enables or disables auto-shrinking.
Auto-shrinking needs to be disabled if you wish to iterate through the set and erase items as you are going.
**/
void auto_shrink( bool on )
{
if ( on == mAutoShrink ) return;
mAutoShrink = on;
if ( on ) autoshrink();
}

iterator begin() const	{ return iterator (this); }
iterator end() const	{ return iterator (this, fhash_npos); }

friend class fhashtable_base::iterator;
};

// This is basically just here for packing two things together in memory before calling into the base hash table
template< typename TKey, typename TVal >
struct fhash_pair
{
fhash_pair( const TKey& k, const TVal& v )
{
Key = k;
Val = v;
}
TKey Key;
TVal Val;
};

template< typename TKey >
void fhash_setup_set( fhash_iface& f )
{
f.Stride = sizeof(TKey);
fhash_tor_types<TKey>( f.NCTor, f.NDTor );
ASSERT( f.NDTor != fhash_TOR_ZERO ); // not allowed. use either FUNC or NOP for dtor
f.Create = &fhash_type_ctor<TKey>;
f.Delete = &fhash_type_dtor<TKey>;
f.Copy = &fhash_type_copy<TKey>;
f.Move = &fhash_pod_move;
f.KeyCmp = &fhash_keycmp<TKey>;
f.GetHash = &fhash_gethash_gen_wrap<TKey>;
}

inline fhash_tor_type fhash_reduce( fhash_tor_type a, fhash_tor_type b )
{
if ( a == fhash_TOR_NOP && b == fhash_TOR_NOP ) return fhash_TOR_NOP;
if ( a == fhash_TOR_FUNC || b == fhash_TOR_FUNC ) return fhash_TOR_FUNC;
return fhash_TOR_ZERO;
}

template< typename TKey, typename TVal >
void fhash_setup_map( fhash_iface& f, size_t msize )
{
f.Stride = msize;
fhash_tor_type ckey, dkey;
fhash_tor_type cval, dval;
fhash_tor_types<TKey>( ckey, dkey );
fhash_tor_types<TVal>( cval, dval );
ASSERT( dkey != fhash_TOR_ZERO && dval != fhash_TOR_ZERO ); // not allowed. use either FUNC or NOP for dtor
f.NCTor = fhash_reduce( ckey, cval );
f.NDTor = fhash_reduce( dkey, dval );
f.Create = &fhash_type_ctor_pair<TKey, TVal>;
f.Delete = &fhash_type_dtor_pair<TKey, TVal>;
f.Copy = &fhash_type_copy_pair<TKey, TVal>;
f.Move = &fhash_pod_move;
f.KeyCmp = &fhash_keycmp<TKey>;
f.GetHash = &fhash_gethash_gen_wrap<TKey>;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hash Map
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename TKey, typename TVal >
class fhashmap : public fhashtable_base
{
public:
typedef fhash_pair<TKey, TVal> TPair;
static const size_t TSize = sizeof(TKey) + sizeof(TVal);

fhashmap()
{
fhash_setup_map<TKey, TVal>( mConfig, sizeof(TKey) + sizeof(TVal) );
}

void insert( const TKey& key, const TVal& val, bool overwrite = true )
{
char t[TSize];
memcpy( t, &key, sizeof(TKey) );
memcpy( t + sizeof(TKey), &val, sizeof(TVal) );
insert_check_exist( t, overwrite );
}

bool erase( const TKey& key )
{
return _erase( &key );
}

bool contains( const TKey& key ) const { return _find(&key) != fhash_npos; }

TVal* getp( const TKey& key ) const
{
size_t pos = _find( &key );
if ( pos == fhash_npos ) return NULL;
return offset_val(dpos(pos));
}

TVal get( const TKey& key ) const
{
TVal* p = getp( key );
return p ? *p : TVal();
}

bool get( const TKey& key, TVal& val ) const
{
TVal* p = getp( key );
if ( p ) val = *p;
return p != NULL;
}

template<typename TContainer>
void keys( TContainer& keys ) const
{
for ( auto it = begin(); it != end(); it++ )
keys += it.key();
}

template<typename TContainer>
void values( TContainer& vals ) const
{
for ( auto it = begin(); it != end(); it++ )
vals += it.val();
}

// We do not allow assignment via operator[], because it is ambiguous. You don't know whether you're assigning
// an empty string or fetching a value without knowing whether your instance is const or now, and I've burned myself like that.
TVal operator[]( const TKey& key ) const
{
return get(key);
}

/////////////////////////////////////////////////////////////////////////////////////
// Iterator
/////////////////////////////////////////////////////////////////////////////////////

class iterator : public fhashtable_base::iterator
{
public:
typedef fhashtable_base::iterator base;
iterator() : base() {}
iterator( const fhashtable_base* p, size_t itpos ) : base(p,itpos) {}
iterator( const fhashtable_base* p ) : base(p) {}

const TKey& key() const	{ return *((const TKey*) parent->dpos(pos)); }
const TVal& val() const { return *((const TVal*) offset_val(parent->dpos(pos))); }
};

friend class iterator;

iterator begin() const	{ return iterator(this); }
iterator end() const	{ return iterator(this, fhash_npos); }

protected:
static TVal* offset_val( void* p ) { return (TVal*) ((char*) p + sizeof(TKey)); }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hash Set
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename TKey >
class fhashset : public fhashtable_base
{
public:
static const size_t TSize = sizeof(TKey);

fhashset()
{
fhash_setup_set<TKey>( mConfig );
}

void insert( const TKey& key )				{ insert_check_exist( &key, false ); }
bool erase( const TKey& key )				{ return _erase( &key ); }
bool contains( const TKey& key ) const		{ return _find(&key) != fhash_npos; }

fhashset& operator+=( const TKey& key )		{ insert(key); return *this; }
fhashset& operator-=( const TKey& key )		{ erase(key); return *this; }

/////////////////////////////////////////////////////////////////////////////////////
// Iterator
/////////////////////////////////////////////////////////////////////////////////////

class iterator : public fhashtable_base::iterator
{
public:
typedef fhashtable_base::iterator base;
iterator() : base() {}
iterator( const fhashtable_base* p, size_t itpos ) : base(p,itpos) {}
iterator( const fhashtable_base* p ) : base(p) {}

const TKey& operator*() const	{ return *((const TKey*) parent->dpos(pos)); }
};

friend class iterator;

iterator begin() const	{ return iterator(this); }
iterator end() const	{ return iterator(this, fhash_npos); }
};


#endif



// These types must always be resolvable by the linker as simply what you see here. No templates, and no constructors.
// Basically the only important thing here is the memory layout.

struct vec2
{
double x, y;
};

struct vec2f
{
float x, y;
};

struct vec3
{
double x, y, z;
};

struct vec3f
{
float x, y, z;
};

struct vec4
{
double x, y, z, w;
};

struct vec4f
{
float x, y, z, w;
};

template<typename T>	bool vec_IsNaN( T v )			{ return v != v; }
inline					bool vec_IsFinite( float v )	{ return v <= FLT_MAX && v >= -FLT_MAX; }
inline					bool vec_IsFinite( double v )	{ return v <= DBL_MAX && v >= -DBL_MAX; }


//#ifndef MIX_NO_AXIS_NAMES
//enum Axis {X=0, Y=1, Z=2, W=3};
//#define MIX_NO_AXIS_NAMES
//#endif
#define X (0)
#define Y (1)
#define Z (2)
#define W (3)

// in matrix, which column mean Right, Up, and Normal
#define UL_R (X)
#define UL_U (Y)
#define UL_N (Z)

#define XX row[0].x
#define XY row[0].y
#define XZ row[0].z
#define XW row[0].w

#define YX row[1].x
#define YY row[1].y
#define YZ row[1].z
#define YW row[1].w

#define ZX row[2].x
#define ZY row[2].y
#define ZZ row[2].z
#define ZW row[2].w

#define WX row[3].x
#define WY row[3].y
#define WZ row[3].z
#define WW row[3].w



/*
Why do we have VecBase2T and Vec2T ?
VecBase2T exists so that we can include it inside unions. Thus, it defines no constructors.
Users of these classes should not need to know about VecBase2T. They should simply use Vec2T.
Unless, of course, they need to include these things inside unions. In that case the facade breaks
down.
*/


#ifndef DEFINED_Vec2
#define DEFINED_Vec2

template <typename vreal>
class Vec2Traits
{
public:
static const TCHAR* StringFormat() { return _T("[ %g %g ]"); }
static const TCHAR* StringFormatBare() { return _T("%g %g"); }
static const char* StringAFormatBare() { return "%g %g"; }
};

template <>
class Vec2Traits<float>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.6g %.6g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.6g %.6g"); }
static const char* StringAFormatBare() { return "%.6g %.6g"; }
};

template <>
class Vec2Traits<double>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.10g %.10g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.10g %.10g"); }
static const char* StringAFormatBare() { return "%.10g %.10g"; }
};

// The "Base" class has no constructor, so that it can be included inside a union
// Inside the base class, we do not expose any functions that leak our type
// For example, we cannot expose component-wise multiply, because that would
// leak VecBase2T to the outside world.
template <typename vreal>
class VecBase2T
{
public:
static const int Dimensions = 2;
typedef vreal FT;

vreal x, y;

/////////////////////////////////////////////////////////////////////////////////////////////
// Mutating operations
/////////////////////////////////////////////////////////////////////////////////////////////

void set(const vreal _x, const vreal _y)
{
x = _x;
y = _y;
}

void normalize()
{
double r = 1.0 / sqrt(x * x + y * y);
x *= r;
y *= r;
}

void normalizeIfNotZero()
{
double lenSq = x * x + y * y;
if ( lenSq != 0 )
{
double r = 1.0 / sqrt(lenSq);
x *= r;
y *= r;
}
}

void scale(vreal _scale)
{
x *= _scale;
y *= _scale;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// const operations
/////////////////////////////////////////////////////////////////////////////////////////////

vreal operator&(const VecBase2T &b) const {
return x*b.x + y*b.y;
}
vreal dot(const VecBase2T &b) const {
return x*b.x + y*b.y;
}

// comparison operators
bool operator==(const VecBase2T& v) const
{
return x == v.x && y == v.y;
}
bool operator!=(const VecBase2T& v) const
{
return x != v.x || y != v.y;
}

vreal sizeSquared() const {
return x*x + y*y;
}
vreal size() const {
return sqrt(x*x + y*y);
}

vreal distance(const VecBase2T &b) const	{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y)); }
vreal distance2d(const VecBase2T &b) const	{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y)); }
vreal distance3d(const VecBase2T &b) const	{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y)); }
vreal distanceSQ(const VecBase2T &b) const	{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y); }

vreal distance2dSQ(const VecBase2T &b) const	{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y); }
vreal distance3dSQ(const VecBase2T &b) const	{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y); }

// makes sure all members are not NaN
bool checkNaN() const
{
if ( vec_IsNaN(x) || vec_IsNaN(y) )
return false;
return true;
}

/// Only valid for Vec2T<double>. Checks whether we won't overflow if converted to float.
bool checkFloatOverflow() const
{
if (	x > FLT_MAX || x < -FLT_MAX ||
y > FLT_MAX || y < -FLT_MAX ) return false;
return true;
}

void copyTo( vreal *dst ) const
{
dst[0] = x;
dst[1] = y;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Duplicated inside Vec2T
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
VecBase2T& operator-=(const VecBase2T &b)	{ x -= b.x; y -= b.y; return *this; }
VecBase2T& operator+=(const VecBase2T &b)	{ x += b.x; y += b.y; return *this; }
VecBase2T& operator*=(const VecBase2T &b)	{ x *= b.x; y *= b.y; return *this; }
VecBase2T& operator/=(const VecBase2T &b)	{ x /= b.x; y /= b.y; return *this; }
VecBase2T& operator/=(vreal s)				{ vreal r = 1.0 / s; 	x *= r; y *= r;	return *this; }
VecBase2T& operator*=(vreal s)				{						x *= s; y *= s; return *this; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

template <typename vreal>
class Vec2T : public VecBase2T<vreal>
{
public:
typedef vreal FT;
using VecBase2T<vreal>::x;
using VecBase2T<vreal>::y;

Vec2T()													{}
Vec2T( vreal _x, vreal _y )								{ x = _x; y = _y; }
Vec2T( const VecBase2T<vreal>& b )						{ x = b.x; y = b.y; }

static Vec2T Create( vreal x, vreal y )
{
Vec2T v;
v.x = x;
v.y = y;
return v;
}

/// Returns a vector that is [cos(angle), sin(angle)]
static Vec2T AtAngle( vreal angle )
{
return Vec2T::Create( cos(angle), sin(angle) );
}

const Vec2T& AsVec2() const { return *this; }
Vec2T& AsVec2()       { return *this; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Duplicated inside VecBase2T
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vec2T& operator-=(const Vec2T &b)		{ x -= b.x; y -= b.y; return *this; }
Vec2T& operator+=(const Vec2T &b)		{ x += b.x; y += b.y; return *this; }
Vec2T& operator*=(const Vec2T &b)		{ x *= b.x; y *= b.y; return *this; }
Vec2T& operator/=(const Vec2T &b)		{ x /= b.x; y /= b.y; return *this; }
Vec2T& operator/=(vreal s)				{ vreal r = 1.0 / s; 	x *= r; y *= r;	return *this; }
Vec2T& operator*=(vreal s)				{						x *= s; y *= s; return *this; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vec2T normalized() const
{
Vec2T copy = *this;
copy.normalize();
return copy;
}

Vec2T normalizedIfNotZero() const
{
Vec2T copy = *this;
copy.normalizeIfNotZero();
return copy;
}

// unary
Vec2T operator-() const  {  return Vec2T(-x, -y);  }

/// Returns the result of sprintf
int ToStringABare( char* buff, size_t buffChars ) const
{
return sprintf_s( buff, buffChars, Vec2Traits<vreal>::StringAFormatBare(), x, y );
}

#ifndef NO_XSTRING
/// Writes "[ %g %g ]"
XString ToString() const
{
XString s;
s.Format( Vec2Traits<vreal>::StringFormat(), x, y );
return s;
}

/// Writes "%g %g"
XString ToStringBare() const
{
XString s;
s.Format( Vec2Traits<vreal>::StringFormatBare(), x, y );
return s;
}

/// Writes "[ %g %g ]" or "%g %g"
XString ToString( int significant_digits, bool bare = false ) const
{
XString f, s;
if ( bare ) f.Format( _T("%%.%dg %%.%dg"), significant_digits, significant_digits );
else		f.Format( _T("[ %%.%dg %%.%dg ]"), significant_digits, significant_digits );
s.Format( f, x, y );
return s;
}

/// Parses "[ x y ]", "x y", "x,y"
bool Parse( const XString& str )
{
double a, b;
#ifdef LM_VS2005_SECURE
if ( _stscanf_s( str, _T("[ %lf %lf ]"), &a, &b ) != 2 )
{
if ( _stscanf_s( str, _T("%lf %lf"), &a, &b ) != 2 )
{
if ( _stscanf_s( str, _T("%lf, %lf"), &a, &b ) != 2 )
{
return false;
}
}
}
#else
if ( _stscanf( str, _T("[ %lf %lf ]"), &a, &b ) != 2 )
{
if ( _stscanf( str, _T("%lf %lf"), &a, &b ) != 2 )
{
if ( _stscanf( str, _T("%lf, %lf"), &a, &b ) != 2 )
{
return false;
}
}
}
#endif
x = (vreal) a;
y = (vreal) b;

return true;
}

static Vec2T FromString( const XString& str )
{
Vec2T v;
v.Parse( str );
return v;
}

#endif

};

template<typename vreal> inline Vec2T<vreal> operator*(const VecBase2T<vreal> &a, vreal s)							{ return Vec2T<vreal>(a.x * s,   a.y * s); }
template<typename vreal> inline Vec2T<vreal> operator*(vreal s, const VecBase2T<vreal> &a)							{ return Vec2T<vreal>(a.x * s,   a.y * s); }
template<typename vreal> inline Vec2T<vreal> operator*(const VecBase2T<vreal> &a, const VecBase2T<vreal> &b)		{ return Vec2T<vreal>(a.x * b.x, a.y * b.y); }
template<typename vreal> inline Vec2T<vreal> operator+(const VecBase2T<vreal> &a, const VecBase2T<vreal> &b)		{ return Vec2T<vreal>(a.x + b.x, a.y + b.y); }
template<typename vreal> inline Vec2T<vreal> operator-(const VecBase2T<vreal> &a, const VecBase2T<vreal> &b)		{ return Vec2T<vreal>(a.x - b.x, a.y - b.y); }
template<typename vreal> inline Vec2T<vreal> operator/(const VecBase2T<vreal> &a, const VecBase2T<vreal> &b)		{ return Vec2T<vreal>(a.x / b.x, a.y / b.y); }
template<typename vreal> inline Vec2T<vreal> operator/(const vreal s, const Vec2T<vreal> &b)						{ return Vec2T<vreal>(s   / b.x, s   / b.y ); }
template<typename vreal> inline vreal        dot(const VecBase2T<vreal>& a, const VecBase2T<vreal>& b)				{ return a.x * b.x + a.y * b.y; }
template<typename vreal> inline Vec2T<vreal> operator/(const VecBase2T<vreal> &a, const vreal s)					{ vreal rec = (vreal) 1.0 / s; return Vec2T<vreal>(a.x * rec, a.y * rec); }
template<typename vreal> inline Vec2T<vreal> normalize(const VecBase2T<vreal>& a)									{ Vec2T<vreal> copy = a; copy.normalized(); return copy; }
template<typename vreal> inline vreal        length(const VecBase2T<vreal>& a)										{ return a.size(); }
template<typename vreal> inline vreal        lengthSQ(const VecBase2T<vreal>& a)									{ return a.sizeSquared(); }

template <class vreal> INLINE bool
operator <= (const Vec2T<vreal>& v1, const Vec2T<vreal>& v2)
{
return v1.x <= v2.x && v1.y <= v2.y;
}

template <class vreal> INLINE bool
operator < (const Vec2T<vreal>& v1, const Vec2T<vreal>& v2)
{
return v1.x < v2.x && v1.y < v2.y;
}


template <class vreal> INLINE bool
operator > (const Vec2T<vreal>& v1, const Vec2T<vreal>& v2)
{
return v1.x > v2.x && v1.y > v2.y;
}

template <class vreal> INLINE bool
operator >= (const Vec2T<vreal>& v1, const Vec2T<vreal>& v2)
{
return v1.x >= v2.x && v1.y >= v2.y;
}

typedef Vec2T<double> Vec2d;
typedef Vec2T<float> Vec2f;
typedef Vec2d Vec2;

#ifdef DVECT_DEFINED
typedef dvect< Vec2f > Vec2fVect;
typedef dvect< Vec2d > Vec2dVect;
#endif

inline Vec2		ToVec2( vec2 v )  { return Vec2::Create( v.x, v.y ); }
inline Vec2		ToVec2( Vec2f v ) { return Vec2::Create( v.x, v.y ); }
inline Vec2f	ToVec2f( Vec2 v ) { return Vec2f::Create( (float) v.x, (float) v.y ); }

#endif // DEFINED_Vec2



// See Vec2.h for a readme of what we are doing here
#ifndef DEFINED_Vec3
#define DEFINED_Vec3

template <typename vreal>
class Vec3Traits
{
public:
static const TCHAR* StringFormat() { return _T("[ %g %g %g ]"); }
static const TCHAR* StringFormatBare() { return _T("%g %g %g"); }
static const char* StringAFormatBare() { return "%g %g %g"; }
};

template <>
class Vec3Traits<float>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.6g %.6g %.6g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.6g %.6g %.6g"); }
static const char* StringAFormatBare() { return "%.6g %.6g %.6g"; }
};

template <>
class Vec3Traits<double>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.10g %.10g %.10g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.10g %.10g %.10g"); }
static const char* StringAFormatBare() { return "%.10g %.10g %.10g"; }
};

// The "Base" class has no constructor, so that it can be included inside a union
// Inside the base class, we do not expose any functions that leak our type
// For example, we cannot expose component-wise multiply, because that would
// leak VecBase3T to the outside world.
template <typename vreal>
class VecBase3T
{
public:
static const int Dimensions = 3;
typedef vreal FT;

union
{
struct
{
vreal x,y,z;
};
struct
{
vreal v[3];
};
struct
{
VecBase2T<vreal> vec2;
};
struct
{
vreal n[3];
};
};

static VecBase3T create(vreal _x, vreal _y, vreal _z) { VecBase3T b = {_x,_y,_z}; return b; }

void set(const vreal _x, const vreal _y, const vreal _z) {		x = _x;		y = _y;		z = _z;	}

// fills all with _uniform
void set( const vreal _uniform ) 	{	x = _uniform;	y = _uniform;	z = _uniform;	}

void scale(vreal _scale)
{
x *= _scale;
y *= _scale;
z *= _scale;
}

vreal size() const								{ return sqrt(x*x + y*y + z*z); }
vreal sizeSquared() const						{ return x*x + y*y + z*z; }
vreal size2Squared() const						{ return x*x + y*y; }
vreal distance(const VecBase3T &b) const		{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z)); }
vreal distance3d(const VecBase3T &b) const		{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z)); }
vreal distance2d(const VecBase3T &b) const		{ return sqrt((b.x-x)*(b.x-x) + (b.y-y)*(b.y-y)); }
vreal distance3dSQ(const VecBase3T &b) const	{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z); }
vreal distanceSQ(const VecBase3T &b) const		{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z); }
vreal distance2dSQ(const VecBase3T &b) const	{ return (b.x-x)*(b.x-x) + (b.y-y)*(b.y-y); }

vreal	operator[](int i) const { return v[i]; }
vreal&	operator[](int i)		{ return v[i]; }

vreal	operator()(int i) const { return v[i]; }
vreal&	operator()(int i)		{ return v[i]; }

void cross(const VecBase3T &u, const VecBase3T &v)
{
x = u.y * v.z - u.z * v.y;
y = u.z * v.x - u.x * v.z;
z = u.x * v.y - u.y * v.x;
}

/// Clamps values individually
void clamp( vreal vmin, vreal vmax )
{
x = CLAMP( x, vmin, vmax );
y = CLAMP( y, vmin, vmax );
z = CLAMP( z, vmin, vmax );
}

// Returns false if any member is a NaN.
bool checkNaN() const
{
return !IsNan();
}

/// Returns true if any member is a NaN.
bool IsNan() const
{
return vec_IsNaN(x) || vec_IsNaN(y) || vec_IsNaN(z);
}

/// Only valid for VecBase3T<double>. Checks whether we won't overflow if converted to float.
bool checkFloatOverflow() const
{
if (	x > FLT_MAX || x < -FLT_MAX ||
y > FLT_MAX || y < -FLT_MAX ||
z > FLT_MAX || z < -FLT_MAX ) return false;
return true;
}

// sets all values to FLT_MIN
void setNull()
{
x = FLT_MIN;
y = FLT_MIN;
z = FLT_MIN;
}

bool isNull() const
{
return x == FLT_MIN && y == FLT_MIN && z == FLT_MIN;
}

void normalize()
{
vreal s = (vreal) 1.0 / sqrt(sizeSquared());
x *= s;
y *= s;
z *= s;
}

void copyTo( vreal *dst ) const
{
dst[0] = x;
dst[1] = y;
dst[2] = z;
}

// only normalizes if size is not zero. Returns 0 if size() > 0
// Sets vector to (1,0,0) if size is 0, and returns -1.
int normalizeCheck()
{
vreal s = sizeSquared();
if (s == 0)
{
x = 1;
y = 0;
z = 0;
return -1;
}
s = (vreal) 1.0 / sqrt(s);
x *= s;
y *= s;
z *= s;
return 0;
}

VecBase3T operator-() const { return VecBase3T::create(-x, -y, -z); }

// comparison operators
bool operator==(const VecBase3T& v) const { return x == v.x && y == v.y && z == v.z; }
bool operator!=(const VecBase3T& v) const { return x != v.x || y != v.y || z != v.z; }

vreal dot(const VecBase3T& b) const { return x * b.x + y * b.y + z * b.z; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Duplicated inside Vec3T
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
VecBase3T& operator+=(const VecBase3T &b)	{ x += b.x; y += b.y; z += b.z;						return *this; }
VecBase3T& operator-=(const VecBase3T &b)	{ x -= b.x; y -= b.y; z -= b.z;						return *this; }
VecBase3T& operator*=(const VecBase3T &b)	{ x *= b.x; y *= b.y; z *= b.z;						return *this; }
VecBase3T& operator*=(const vreal d)		{ 						x *= d;	y *= d; z *= d;		return *this; }
VecBase3T& operator/=(const vreal d)		{ vreal r = 1.0 / d;	x *= r; y *= r; z *= r;		return *this; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

template <typename vreal>
class Vec3T : public VecBase3T<vreal>
{
public:
typedef vreal FT;
using VecBase3T<vreal>::x;
using VecBase3T<vreal>::y;
using VecBase3T<vreal>::z;
using VecBase3T<vreal>::v;
using VecBase3T<vreal>::vec2;
using VecBase3T<vreal>::n;
using VecBase3T<vreal>::normalizeCheck;

Vec3T()													{}
Vec3T( vreal _x, vreal _y, vreal _z )					{ x = _x; y = _y; z = _z; }
Vec3T( const VecBase3T<vreal>& b )						{ x = b.x; y = b.y; z = b.z; }
Vec3T( const VecBase2T<vreal>& v2, const vreal _z )		{ x = v2.x, y = v2.y, z = _z; }
explicit Vec3T( vreal _uniform )						{ x = y = z = _uniform; }

static Vec3T Create( vreal x, vreal y, vreal z )
{
Vec3T v;
v.x = x;
v.y = y;
v.z = z;
return v;
}

static Vec3T null()
{
Vec3T v;
v.setNull();
return v;
}

/// Returns a vector that is [cos(angle), sin(angle), 0]
static Vec3T AtAngle( vreal angle )
{
return Vec3T::Create( cos(angle), sin(angle), 0 );
}

const Vec2T<vreal>& AsVec2() const    	{ return (const Vec2T<vreal>&) vec2; }
Vec2T<vreal>& AsVec2()          	{ return (Vec2T<vreal>&) vec2; }
const Vec3T<vreal>& AsVec3() const		{ return *this; }
Vec3T<vreal>& AsVec3()			{ return *this; }

Vec3T operator-() const { return Vec3T(-x, -y, -z); }

Vec3T projectionOn3dLine(const VecBase3T<vreal> &p1, const VecBase3T<vreal> &p2) const
{
double u = ((*this - p1) & (p2 - p1)) / (p2 - p1).sizeSquared();
return p1 + u*(p2-p1);
}

Vec3T normalized() const
{
Vec3T copy = *this;
copy.normalize();
return copy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Duplicated inside VecBase3T
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vec3T& operator+=(const Vec3T &b)	{ x += b.x; y += b.y; z += b.z;						return *this; }
Vec3T& operator-=(const Vec3T &b)	{ x -= b.x; y -= b.y; z -= b.z;						return *this; }
Vec3T& operator*=(const Vec3T &b)	{ x *= b.x; y *= b.y; z *= b.z;						return *this; }
Vec3T& operator*=(const vreal d)	{ 						x *= d;	y *= d; z *= d;		return *this; }
Vec3T& operator/=(const vreal d)	{ vreal r = 1.0 / d;	x *= r; y *= r; z *= r;		return *this; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// some swizzlers... i doubt these are used much
Vec2T<vreal>	xx() const		{ return Vec2T<vreal>(x, x); }
Vec2T<vreal>	yy() const		{ return Vec2T<vreal>(y, y); }
Vec2T<vreal>	xy() const		{ return Vec2T<vreal>(x, y); }
Vec2T<vreal>	yx() const		{ return Vec2T<vreal>(y, x); }
Vec3T			xxx() const		{ return Vec3T::Create(x, x, x); }
Vec3T			yyy() const		{ return Vec3T::Create(y, y, y); }
Vec3T			zzz() const		{ return Vec3T::Create(z, z, z); }
Vec3T			zyx() const		{ return Vec3T::Create(z, y, x); }

Vec3T        operator^(const VecBase3T<vreal>& v) const;
int MakeOrthonormalBasis(VecBase3T<vreal> & base1, VecBase3T<vreal> & base2);

int ToStringABare( char* buff, size_t buffChars ) const
{
return sprintf_s( buff, buffChars, Vec3Traits<vreal>::StringAFormatBare(), x, y, z );
}

#ifndef NO_XSTRING
/// Writes "[ %.8g %.8g %.8g ]"
XString ToString() const
{
XString s;
s.Format( Vec3Traits<vreal>::StringFormat(), x, y, z );
return s;
}

/// Writes "%lf %lf %lf"
XString ToStringBare() const
{
XString s;
s.Format( Vec3Traits<vreal>::StringFormatBare(), x, y, z );
return s;
}

XString ToString( int significant_digits, bool bare = false ) const
{
XString f, s;
if ( bare ) f.Format( _T("%%.%dg %%.%dg %%.%dg"), significant_digits, significant_digits, significant_digits );
else		f.Format( _T("[ %%.%dg %%.%dg %%.%dg ]"), significant_digits, significant_digits, significant_digits );
s.Format( f, x, y, z );
return s;
}

/// Parses "[ x y z ]", "x y z", "x,y,z"
bool Parse( const XString& str )
{
double a, b, c;
#ifdef LM_VS2005_SECURE
if ( _stscanf_s( str, _T("[ %lf %lf %lf ]"), &a, &b, &c ) != 3 )
{
if ( _stscanf_s( str, _T("%lf %lf %lf"), &a, &b, &c ) != 3 )
{
if ( _stscanf_s( str, _T("%lf, %lf, %lf"), &a, &b, &c ) != 3 )
{
return false;
}
}
}
#else
if ( _stscanf( str, _T("[ %lf %lf %lf ]"), &a, &b, &c ) != 3 )
{
if ( _stscanf( str, _T("%lf %lf %lf"), &a, &b, &c ) != 3 )
{
if ( _stscanf( str, _T("%lf, %lf, %lf"), &a, &b, &c ) != 3 )
{
return false;
}
}
}
#endif
x = (vreal) a;
y = (vreal) b;
z = (vreal) c;

return true;
}

static Vec3T FromString( const XString& str )
{
Vec3T v;
v.Parse( str );
return v;
}

#endif

};


template <class vreal> INLINE bool
operator < (const VecBase3T<vreal>& v1, const VecBase3T<vreal>& v2)
{
return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}

template <class vreal> INLINE bool
operator <= (const VecBase3T<vreal>& v1, const VecBase3T<vreal>& v2)
{
return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
}


template <class vreal> INLINE bool
operator > (const VecBase3T<vreal>& v1, const VecBase3T<vreal>& v2)
{
return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
}

template <class vreal> INLINE bool
operator >= (const VecBase3T<vreal>& v1, const VecBase3T<vreal>& v2)
{
return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
}

template<typename vreal> inline Vec3T<vreal> operator*(vreal s, const VecBase3T<vreal> &v)							{ return Vec3T<vreal>(v.x * s, v.y * s, v.z * s); }
template<typename vreal> inline Vec3T<vreal> operator*(const VecBase3T<vreal> &v, vreal s)							{ return Vec3T<vreal>(v.x * s, v.y * s, v.z * s); }
template<typename vreal> inline Vec3T<vreal> operator*(const VecBase3T<vreal> &a, const VecBase3T<vreal> &b)		{ return Vec3T<vreal>(a.x * b.x, a.y * b.y, a.z * b.z); }
template<typename vreal> inline Vec3T<vreal> operator/(const VecBase3T<vreal> &a, const VecBase3T<vreal> &b)		{ return Vec3T<vreal>(a.x / b.x, a.y / b.y, a.z / b.z); }
template<typename vreal> inline Vec3T<vreal> operator/(const VecBase3T<vreal> &a, vreal s)							{ vreal r = (vreal) 1.0 / s; return Vec3T<vreal>(a.x * r, a.y * r, a.z * r); }
template<typename vreal> inline Vec3T<vreal> operator+(const VecBase3T<vreal>& a, const VecBase3T<vreal>& b)		{ return Vec3T<vreal>(a.x + b.x, a.y + b.y, a.z + b.z ); }
template<typename vreal> inline Vec3T<vreal> operator-(const VecBase3T<vreal>& a, const VecBase3T<vreal>& b)		{ return Vec3T<vreal>(a.x - b.x, a.y - b.y, a.z - b.z ); }
template<typename vreal> inline vreal        dot(const VecBase3T<vreal>& a, const VecBase3T<vreal>& b)				{ return a.x * b.x + a.y * b.y + a.z * b.z; }
template<typename vreal> inline vreal        operator&(const VecBase3T<vreal>& a, const VecBase3T<vreal>& b)		{ return dot(a,b); }
template<typename vreal> inline Vec3T<vreal> normalize(const VecBase3T<vreal>& a)									{ Vec3T<vreal> copy = a; copy.normalize(); return copy; }
template<typename vreal> inline vreal        length(const VecBase3T<vreal>& a) 										{ return a.size(); }
template<typename vreal> inline vreal        lengthSQ(const VecBase3T<vreal>& a) 									{ return a.sizeSquared(); }

// cross
template<typename vreal> inline
Vec3T<vreal> Vec3T<vreal>::operator^(const VecBase3T<vreal>& v) const
{
return Vec3T<vreal>::Create( n[1]*v[2] - v[1]*n[2],
-n[0]*v[2] + v[0]*n[2],
n[0]*v[1] - v[0]*n[1] );
}


template <class vreal>
INLINE int Vec3T<vreal>::MakeOrthonormalBasis(VecBase3T<vreal> & base1, VecBase3T<vreal> & base2)
{

if (base1.normalizeCheck())
return -1;

if (base2.normalizeCheck())
return -1;

*this = base1 ^ base2;

// should be already normalized
if (normalizeCheck())
return -1;

base1 = base2 ^ *this;

// this too, should be already normalized
if (base1.normalizeCheck())
return -1;

return 0;
}

typedef Vec3T<double> Vec3d;
typedef Vec3T<float> Vec3f;
typedef Vec3d Vec3;

#ifdef OHASH_DEFINED
namespace ohash
{
template< class vreal >
class ohashfunc_Vec3T
{
public:
static ohash::hashkey_t gethashcode( const VecBase3T<vreal>& elem )
{
vreal sum = elem.x + elem.y + elem.z;
ohash::hashkey_t* hard = (ohash::hashkey_t*) &sum;
return *hard;
}
};

typedef ohashfunc_Vec3T<double> ohashfunc_Vec3;
typedef ohashfunc_Vec3T<double> ohashfunc_Vec3d;
typedef ohashfunc_Vec3T<float> ohashfunc_Vec3f;
}
#endif

inline Vec3		ToVec3( Vec3f v ) { return Vec3( v.x, v.y, v.z ); }
inline Vec3f	ToVec3f( Vec3 v ) { return Vec3f( (float) v.x, (float) v.y, (float) v.z ); }

#endif // DEFINED_Vec3




// See Vec2.h for a readme of what we are doing here
#ifndef DEFINED_Vec4
#define DEFINED_Vec4

template <class vreal>
class Vec4Traits
{
public:
static const TCHAR* StringFormat() { return _T("[ %g %g %g %g ]"); }
static const TCHAR* StringFormatBare() { return _T("%g %g %g %g"); }
static const char* StringAFormatBare() { return "%g %g %g %g"; }
};

template <>
class Vec4Traits<float>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.6g %.6g %.6g %.6g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.6g %.6g %.6g %.6g"); }
static const char* StringAFormatBare() { return "%.6g %.6g %.6g %.6g"; }
};

template <>
class Vec4Traits<double>
{
public:
static const TCHAR* StringFormat() { return _T("[ %.10g %.10g %.10g %.10g ]"); }
static const TCHAR* StringFormatBare() { return _T("%.10g %.10g %.10g %.10g"); }
static const char* StringAFormatBare() { return "%.10g %.10g %.10g %.10g"; }
};

// The "Base" class has no constructor, so that it can be included inside a union
// Inside the base class, we do not expose any functions that leak our type
// For example, we cannot expose component-wise multiply, because that would
// leak VecBase4T to the outside world.
template <class vreal>
class VecBase4T
{
public:
static const int Dimensions = 4;
typedef vreal FT;

union
{
vreal n[4];
struct
{
vreal x,y,z,w;
};
struct
{
VecBase3T<vreal> vec3;
};
struct
{
vreal r,g,b,a;
};
//struct
//{
//	vreal u,v,q,r;
//};
struct
{
VecBase2T<vreal> vec2;
VecBase2T<vreal> vec2_zw;
};
};

void set( vreal _x, vreal _y, vreal _z, vreal _w )
{
x = _x;
y = _y;
z = _z;
w = _w;
}

void scale(vreal _scale)
{
x *= _scale;
y *= _scale;
z *= _scale;
w *= _scale;
}

vreal size() const
{
return sqrt(sizeSquared());
}

vreal sizeSquared() const
{
return x*x + y*y + z*z + w*w;
}

void normalize()
{
double s = 1.0 / sqrt(x*x + y*y + z*z + w*w);
x *= s;
y *= s;
z *= s;
w *= s;
}

bool checkNaN() const
{
if ( vec_IsNaN(x) || vec_IsNaN(y) || vec_IsNaN(z) || vec_IsNaN(w))
return false;
return true;
}

vreal& operator[](int i)			{ return n[i]; };
const vreal& operator[](int i) const	{ return n[i]; }

vreal& operator()(int i)			{ return n[i]; };
const vreal& operator()(int i) const	{ return n[i]; }

const bool operator == ( const VecBase4T& v ) const
{
return x == v.x && y == v.y && z == v.z && w == v.w;
}

const bool operator != ( const VecBase4T &v ) const
{
return x != v.x || y != v.y || z != v.z || w != v.w;
}

};


template <class vreal>
class Vec4T : public VecBase4T<vreal>
{
public:
typedef vreal FT;
using VecBase4T<vreal>::x;
using VecBase4T<vreal>::y;
using VecBase4T<vreal>::z;
using VecBase4T<vreal>::w;
using VecBase4T<vreal>::n;
using VecBase4T<vreal>::vec2;
using VecBase4T<vreal>::vec3;

Vec4T() {}
Vec4T( const VecBase2T<vreal>& _v, vreal _z, vreal _w )		{ x = _v.x; y = _v.y; z = _z; w = _w; }
Vec4T( const VecBase3T<vreal>& _v, vreal _w )				{ x = _v.x; y = _v.y; z = _v.z; w = _w; }
Vec4T( const VecBase4T<vreal>& _v )							{ x = _v.x; y = _v.y; z = _v.z; w = _v.w; }
Vec4T( vreal _x, vreal _y, vreal _z, vreal _w )				{ x = _x; y = _y; z = _z; w = _w; }
explicit Vec4T( vreal uniform )								{ x = y = z = w = uniform; }

static Vec4T Create( vreal x, vreal y, vreal z, vreal w )
{
Vec4T v;
v.x = x;
v.y = y;
v.z = z;
v.w = w;
return v;
}

const Vec2T<vreal>&	AsVec2() const	{ return (const Vec2T<vreal>&) vec2; }
Vec2T<vreal>&	AsVec2()		{ return (Vec2T<vreal>&) vec2; }
const Vec3T<vreal>&	AsVec3() const	{ return (const Vec3T<vreal>&) vec3; }
Vec3T<vreal>&	AsVec3()		{ return (Vec3T<vreal>&) vec3; }
const Vec4T<vreal>&	AsVec4() const	{ return *this; }
Vec4T<vreal>&	AsVec4()		{ return *this; }

// lambda * v1 + (1 - lambda) * v2
static Vec4T Interpolate( const Vec4T &v1, const Vec4T &v2, vreal lambda )
{
return lambda * v1 + (1 - lambda) * v2;
}

// Assignment operators

Vec4T & operator += ( const Vec4T& v );     // incrementation by a Vec4T
Vec4T & operator -= ( const Vec4T& v );     // decrementation by a Vec4T
Vec4T & operator *= ( const vreal d );     // multiplication by a constant
Vec4T & operator /= ( const vreal d );     // division by a constant

// special functions

Vec4T normalized() const
{
Vec4T copy = *this;
copy.normalize();
return copy;
}

void copyTo( vreal *dst ) const
{
dst[0] = x;
dst[1] = y;
dst[2] = z;
dst[3] = w;
}


//    Vec4T& ApplyFunc(ulFuncPtrf fct);  // apply a func. to each component
void Homogenize( void );

Vec4T& operator *= (const Vec4T& v);
Vec4T& operator /= (const Vec4T& v);

// this *= s;
void scale(vreal s);

// this = v * s
void scale(const Vec4T &v, vreal s);
// this += v
void add(const Vec4T & v);
// this = v1 + v2
void add(const Vec4T & v1, const Vec4T & v2);


// min of all components
vreal Min() const;

// min abs of all components
vreal MinAbs() const;
// maximum of all components
vreal Max() const;
// max abs of components
vreal MaxAbs() const;

void Maximize( const Vec4T& rhs )
{
x = ( x > rhs.x ) ? x : rhs.x;
y = ( y > rhs.y ) ? y : rhs.y;
z = ( z > rhs.z ) ? z : rhs.z;
w = ( w > rhs.w ) ? w : rhs.w;
}
void Minimize( const Vec4T& rhs )
{
x = ( x < rhs.x ) ? x : rhs.x;
y = ( y < rhs.y ) ? y : rhs.y;
z = ( z < rhs.z ) ? z : rhs.z;
w = ( w < rhs.w ) ? w : rhs.w;
}
// this = -v
void negate(const Vec4T &v);
// this = -this
void negate();
// this -= v
void sub(const Vec4T &v);

// this = v1 - v2
void sub(const Vec4T &v1, const Vec4T &v2);
// this *= v
void mult(const Vec4T &v);
// this = v1 * v2
void mult(const Vec4T &v1, const Vec4T &v2);
//  this = v1 + lambda * v2;
void displace(const Vec4T &v1, const Vec4T &v2, vreal lambda);

//  this += lambda * v;
void displace(const Vec4T &v, vreal lambda);


vreal distance3d(const Vec4T &b) const		{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z)); }
vreal distance2d(const Vec4T &b) const		{ return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y)); }

vreal distance3dSQ(const Vec4T &b) const	{ return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z); }
vreal distance2dSQ(const Vec4T &b) const	{ return (b.x-x)*(b.x-x) + (b.y-y)*(b.y-y); }

// mag(this - other)
vreal distance(const Vec4T &b) const
{
return sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z) + (w-b.w)*(w-b.w));
}

// mag(this - other) ^2
vreal distanceSQ(const Vec4T &b) const
{
return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) + (z-b.z)*(z-b.z) + (w-b.w)*(w-b.w);
}

/// Clamps values individually
void clamp( vreal vmin, vreal vmax );

/// Only valid for Vec4T<double>. Checks whether we won't overflow if converted to float.
bool checkFloatOverflow() const
{
if (	x > FLT_MAX || x < -FLT_MAX ||
y > FLT_MAX || y < -FLT_MAX ||
z > FLT_MAX || z < -FLT_MAX ||
w > FLT_MAX || w < -FLT_MAX ) return false;
return true;
}

int ToStringABare( char* buff, size_t buffChars ) const
{
return sprintf_s( buff, buffChars, Vec4Traits<vreal>::StringAFormatBare(), x, y, z, w );
}

#ifdef XSTRING_DEFINED
/// Writes "[ %g %g %g %g ]"
XString ToString() const
{
XString s;
s.Format( Vec4Traits<vreal>::StringFormat(), x, y, z, w );
return s;
}

/// Writes "%g %g %g %g"
XString ToStringBare() const
{
XString s;
s.Format( Vec4Traits<vreal>::StringFormatBare(), x, y, z, w );
return s;
}

XString ToString( int significant_digits, bool bare = false ) const
{
XString f, s;
if ( bare ) f.Format( _T("%%.%dg %%.%dg %%.%dg %%.%dg"), significant_digits, significant_digits, significant_digits, significant_digits );
else		f.Format( _T("[ %%.%dg %%.%dg %%.%dg %%.%dg ]"), significant_digits, significant_digits, significant_digits, significant_digits );
s.Format( f, x, y, z, w );
return s;
}

/// Parses "[ x y z w ]", "z y z w", "x,y,z,w"
bool Parse( const XString& str )
{
double a, b, c, d;
#ifdef LM_VS2005_SECURE
if ( _stscanf_s( str, _T("[ %lf %lf %lf %lf ]"), &a, &b, &c, &d ) != 4 )
{
if ( _stscanf_s( str, _T("%lf %lf %lf %lf"), &a, &b, &c, &d ) != 4 )
{
if ( _stscanf_s( str, _T("%lf, %lf, %lf, %lf"), &a, &b, &c, &d ) != 4 )
{
return false;
}
}
}
#else
if ( _stscanf( str, "[ %lf %lf %lf %lf ]", &a, &b, &c, &d ) != 4 )
{
if ( _stscanf( str, "%lf %lf %lf %lf", &a, &b, &c, &d ) != 4 )
{
if ( _stscanf( str, "%lf, %lf, %lf, %lf", &a, &b, &c, &d ) != 4 )
{
return false;
}
}
}
#endif

x = (vreal) a;
y = (vreal) b;
z = (vreal) c;
w = (vreal) d;

return true;
}

static Vec4T FromString( const XString& str )
{
Vec4T v;
v.Parse( str );
return v;
}

#endif

};


template <class vreal> INLINE
void Vec4T<vreal>::clamp( vreal vmin, vreal vmax )
{
x = CLAMP(x, vmin, vmax);
y = CLAMP(y, vmin, vmax);
z = CLAMP(z, vmin, vmax);
w = CLAMP(w, vmin, vmax);
}


template <class vreal> INLINE void Vec4T<vreal>::Homogenize( void )
{
double u = 1.0 / w;
x = (vreal)(x*u);
y = (vreal)(y*u);
z = (vreal)(z*u);
}


// =====================================
// Assignment operators
// =====================================

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator += (const Vec4T<vreal>& v)
{
x += v.x;
y += v.y;
z += v.z;
w += v.w;
return *this;
}

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator -= (const Vec4T<vreal>& v)
{
x -= v.x;
y -= v.y;
z -= v.z;
w -= v.w;
return *this;
}

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator *= (const Vec4T<vreal>& v)
{
x *= v.x;
y *= v.y;
z *= v.z;
w *= v.w;
return *this;
}

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator /= (const Vec4T<vreal>& v)
{
x /= v.x;
y /= v.y;
z /= v.z;
w /= v.w;
return *this;
}

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator *= (vreal s)
{
x *= s;
y *= s;
z *= s;
w *= s;
return *this;
}

template <class vreal> INLINE Vec4T<vreal>&
Vec4T<vreal>::operator /= (vreal d)
{
double u = 1.0 / d;
x = (vreal)(x*u);
y = (vreal)(y*u);
z = (vreal)(z*u);
w = (vreal)(w*u);
return *this;
}

template <class vreal> INLINE Vec4T<vreal>
operator + (const Vec4T<vreal>& v)
{
return v;
}

template <class vreal> INLINE Vec4T<vreal>
operator - (const Vec4T<vreal>& v)
{
return Vec4T<vreal>::Create(-v.x, -v.y, -v.z, -v.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator + (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return Vec4T<vreal>::Create(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator - (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return Vec4T<vreal>::Create(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
}

template <class vreal> INLINE vreal
operator & (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

template <class vreal> INLINE Vec4T<vreal>
operator * (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return Vec4T<vreal>::Create(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z, v1.w*v2.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator / (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return Vec4T<vreal>(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z, v1.w/v2.w);
}

template <class vreal> INLINE int
operator < (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z && v1.w < v2.w;
}

template <class vreal> INLINE int
operator <= (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z && v1.w <= v2.w;
}

// Hardcode mixing of floats/doubles
// double *
template <class vreal> INLINE Vec4T<vreal>
operator * (const Vec4T<vreal>& v, double s)
{
return Vec4T<vreal>::Create(s*v.x, s*v.y, s*v.z, s * v.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator * (double s, const Vec4T<vreal>& v)
{
return Vec4T<vreal>::Create(s*v.x, s*v.y, s*v.z, s*v.w);
}

// float *
template <class vreal> INLINE Vec4T<vreal>
operator * (const Vec4T<vreal>& v, float s)
{
return Vec4T<vreal>::Create(s*v.x, s*v.y, s*v.z, s * v.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator * (float s, const Vec4T<vreal>& v)
{
return Vec4T<vreal>::Create(s*v.x, s*v.y, s*v.z, s*v.w);
}

template <class vreal> INLINE Vec4T<vreal>
operator / (const Vec4T<vreal>& v, vreal s)
{
return Vec4T<vreal>::Create(v.x/s, v.y/s, v.z/s, v.w/s);
}

template <class vreal> INLINE bool
operator == (const Vec4T<vreal>& v1, const Vec4T<vreal>& v2)
{
return v1.x==v2.x && v1.y==v2.y && v1.z == v2.z && v1.w == v2.w;
}

template <class vreal> INLINE vreal
dot (const VecBase4T<vreal>& v1, const VecBase4T<vreal>& v2)
{
return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

template <class vreal> INLINE Vec4T<vreal>
normalize( const Vec4T<vreal>& a )
{
return a.normalized();
}

template <class vreal> INLINE vreal
length( const VecBase4T<vreal>& a )
{
return a.size();
}

template <class vreal> INLINE vreal
lengthSQ( const VecBase4T<vreal>& a )
{
return a.sizeSquared();
}

typedef Vec4T<double> Vec4d;
typedef Vec4T<float> Vec4f;
typedef Vec4d Vec4;

inline Vec4		ToVec4( Vec4f v ) { return Vec4::Create( v.x, v.y, v.z, v.w ); }
inline Vec4f	ToVec4f( Vec4 v ) { return Vec4f::Create( (float) v.x, (float) v.y, (float) v.z, (float) v.w ); }

#endif // DEFINED_Vec4



#ifndef DEFINED_Mat4
#define DEFINED_Mat4

template <class FT>
class Mat4T
{
public:
VecBase4T<FT> row[4];

Mat4T(void)
{
Identity();
}

// Don't initialize to identity
Mat4T( int uninit )
{
}

Mat4T(	FT a0, FT b0, FT c0, FT d0,
FT a1, FT b1, FT c1, FT d1,
FT a2, FT b2, FT c2, FT d2,
FT a3, FT b3, FT c3, FT d3)
{
XX = a0;
XY = b0;
XZ = c0;
XW = d0;

YX = a1;
YY = b1;
YZ = c1;
YW = d1;

ZX = a2;
ZY = b2;
ZZ = c2;
ZW = d2;

WX = a3;
WY = b3;
WZ = c3;
WW = d3;
}


FT&	m(int i, int j)			{ return row[i][j]; }
FT	m(int i, int j) const	{ return row[i][j]; }

FT Determinant() const;

/// Returns the diagonal
Vec4T<FT> Diagonal() const { return Vec4T<FT>( row[0].x, row[1].y, row[2].z, row[3].w ); }

Mat4T Transposed(void) const {
Mat4T t;
t.XX = XX;
t.YX = XY;
t.ZX = XZ;
t.WX = XW;

t.XY = YX;
t.YY = YY;
t.ZY = YZ;
t.WY = YW;

t.XZ = ZX;
t.YZ = ZY;
t.ZZ = ZZ;
t.WZ = ZW;

t.XW = WX;
t.YW = WY;
t.ZW = WZ;
t.WW = WW;
return t;
}

Mat4T Inverted() const {
Mat4T mr;
mr = *this;
mr.Invert();
return mr;
}

void Zero()
{
XX = 0;
XY = 0;
XZ = 0;
XW = 0;

YX = 0;
YY = 0;
YZ = 0;
YW = 0;

ZX = 0;
ZY = 0;
ZZ = 0;
ZW = 0;

WX = 0;
WY = 0;
WZ = 0;
WW = 0;
}

void Identity()
{
XX = 1;
XY = 0;
XZ = 0;
XW = 0;

YX = 0;
YY = 1;
YZ = 0;
YW = 0;

ZX = 0;
ZY = 0;
ZZ = 1;
ZW = 0;

WX = 0;
WY = 0;
WZ = 0;
WW = 1;
}


Mat4T operator*(const FT d) const
{
Mat4T b;
b.XX = XX * d;
b.XY = XY * d;
b.XZ = XZ * d;
b.XW = XW * d;

b.YX = YX * d;
b.YY = YY * d;
b.YZ = YZ * d;
b.YW = YW * d;

b.ZX = ZX * d;
b.ZY = ZY * d;
b.ZZ = ZZ * d;
b.ZW = ZW * d;

b.WX = WX * d;
b.WY = WY * d;
b.WZ = WZ * d;
b.WW = WW * d;

return b;
}

void Translate( const Vec3T<FT>& vec, bool post = true )
{
Translate(vec.x, vec.y, vec.z, post);
}

void Translate( double x, double y, double z, bool post = true )
{
Mat4T tm;
tm.XW = x;
tm.YW = y;
tm.ZW = z;
if (post)
*this = (*this) * tm;
else
*this = tm * (*this);
}

void Scale( const Vec3T<FT>& vec, bool post = true )
{
Scale(vec.x, vec.y, vec.z, post);
}

// equivalent to a glScale3d
void Scale( FT x, FT y, FT z, bool post = true )
{
Mat4T m;
m.XX = x;
m.YY = y;
m.ZZ = z;
if (post)
*this = (*this) * m;
else
*this = m * (*this);
}

// equivalent to glRotated(), except RADIANS
void Rotate( FT angle, FT x, FT y, FT z, bool post = true )
{
Vec3 v(x,y,z);
v.normalize();
x = v.x;
y = v.y;
z = v.z;
Mat4T r;
FT c = cos(angle);
FT s = sin(angle);
FT cm1 = 1 - c;
// row 0
r.XX = x*x*cm1 + c;
r.XY = x*y*cm1 - z*s;
r.XZ = x*z*cm1 + y*s;
r.XW = 0;
// row 1
r.YX = y*x*cm1 + z*s;
r.YY = y*y*cm1 + c;
r.YZ = y*z*cm1 - x*s;
r.YW = 0;
// row 2
r.ZX = z*x*cm1 - y*s;
r.ZY = z*y*cm1 + x*s;
r.ZZ = z*z*cm1 + c;
r.ZW = 0;
// row 3
r.WX = 0;
r.WY = 0;
r.WZ = 0;
r.WW = 1;
if (post)
*this = (*this) * r;
else
*this = r * (*this);
}



void Invert()
{
/************************************************************
*
* input:
* mat - pointer to array of 16 floats (source matrix)
* output:
* dst - pointer to array of 16 floats (invert matrix)
*
*************************************************************/
//void Invert2( float *mat, float *dst)
//Streaming SIMD Extensions - Inverse of 4x4 Matrix
//7
//{
FT dst[16];
FT tmp[12]; /* temp array for pairs */
FT src[16]; /* array of transpose source matrix */
FT det; /* determinant */
/* transpose matrix */
/*for ( int i = 0; i < 4; i++) {
src[i] = row[i].x;
src[i + 4] = row[i].y;
src[i + 8] = row[i].z;
src[i + 12] = row[i].w;
}*/
// transpose
src[0] = XX;
src[1] = YX;
src[2] = ZX;
src[3] = WX;

src[4] = XY;
src[5] = YY;
src[6] = ZY;
src[7] = WY;

src[8] = XZ;
src[9] = YZ;
src[10] = ZZ;
src[11] = WZ;

src[12] = XW;
src[13] = YW;
src[14] = ZW;
src[15] = WW;

/* calculate pairs for first 8 elements (cofactors) */
tmp[0] = src[10] * src[15];
tmp[1] = src[11] * src[14];
tmp[2] = src[9] * src[15];
tmp[3] = src[11] * src[13];
tmp[4] = src[9] * src[14];
tmp[5] = src[10] * src[13];
tmp[6] = src[8] * src[15];
tmp[7] = src[11] * src[12];
tmp[8] = src[8] * src[14];
tmp[9] = src[10] * src[12];
tmp[10] = src[8] * src[13];
tmp[11] = src[9] * src[12];
/* calculate first 8 elements (cofactors) */
dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
dst[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
dst[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
dst[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
dst[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
/* calculate pairs for second 8 elements (cofactors) */
tmp[0] = src[2]*src[7];
tmp[1] = src[3]*src[6];
tmp[2] = src[1]*src[7];
tmp[3] = src[3]*src[5];
tmp[4] = src[1]*src[6];
tmp[5] = src[2]*src[5];
tmp[6] = src[0]*src[7];
tmp[7] = src[3]*src[4];
tmp[8] = src[0]*src[6];
tmp[9] = src[2]*src[4];
tmp[10] = src[0]*src[5];
tmp[11] = src[1]*src[4];
/* calculate second 8 elements (cofactors) */
dst[8] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
dst[9] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
dst[10]-= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
dst[11]-= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
dst[12]-= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
dst[13]-= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
dst[14]-= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
dst[15]-= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
/* calculate determinant */
det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
/* calculate matrix inverse */
det = 1/det;
for ( int j = 0; j < 16; j++) {
dst[j] *= det;
}
memcpy((void*) this, dst, 16*sizeof(FT));
}

#ifndef NO_XSTRING
XString ToString() const
{
XString s;
s.Format(_T("[ %f %f %f %f;\n  %f %f %f %f;\n  %f %f %f %f;\n  %f %f %f %f ]"),
XX, XY, XZ, XW,
YX, YY, YZ, YW,
ZX, ZY, ZZ, ZW,
WX, WY, WZ, WW );
return s;
}
#endif

/*friend double Difference( const Mat4T<FT>& a, const Mat4T<FT>& b );

friend Mat4T operator - (const Mat4T& a);         // -m1
friend Mat4T operator + (const Mat4T& a, const Mat4T& b);		// m1 + m2
friend Mat4T operator - (const Mat4T& a, const Mat4T& b);		// m1 - m2
friend Mat4T operator * (const Mat4T& b, const Mat4T& a);		// m1 * m2
friend Mat4T operator * (const Mat4T& a, const FT d);			// m1 * d
friend Mat4T operator * (const FT d, const Mat4T& a);			// d * m1
friend Mat4T operator / (const Mat4T& a, const FT d);			// m1 / d
friend int operator == (const Mat4T& a, const Mat4T& b);		// m1 == m2 ?
friend int operator != (const Mat4T& a, const Mat4T& b);		// m1 != m2 ?
//friend Vec4T<FT> operator * ( const Vec4T<FT>& v, const Mat4T& a );    // v * m1
//friend Vec4T<FT> operator * ( const Mat4T& a, const Vec4T<FT>& v );    // m1 * v */

};

template <class FT>
INLINE FT Mat4T<FT>::Determinant() const
{
FT sub1 = YY * (ZZ * WW - ZW * WZ) -
YZ * (ZY * WW - ZW * WY) +
YW * (ZY * WZ - ZZ * WY);

FT sub2 = YX * (ZZ * WW - ZW * WZ) -
YZ * (ZX * WW - ZW * WX) +
YW * (ZX * WZ - ZZ * WX);

FT sub3 = YX * (ZY * WW - ZW * WY) -
YY * (ZX * WW - ZW * WX) +
YW * (ZX * WY - ZY * WX);

FT sub4 = YX * (ZY * WZ - ZZ * WY) -
YY * (ZX * WZ - ZZ * WX) +
YZ * (ZX * WY - ZY * WX);
FT det = XX * sub1 - XY * sub2 + XZ * sub3 - XW * sub4;
return det;
}

template <class FT>
INLINE Mat4T<FT> operator + (const Mat4T<FT>& a, const Mat4T<FT>& b)
{
Mat4T<FT> c;

c.XX = a.XX + b.XX;
c.XY = a.XY + b.XY;
c.XZ = a.XZ + b.XZ;
c.XW = a.XW + b.XW;

c.YX = a.YX + b.YX;
c.YY = a.YY + b.YY;
c.YZ = a.YZ + b.YZ;
c.YW = a.YW + b.YW;

c.ZX = a.ZX + b.ZX;
c.ZY = a.ZY + b.ZY;
c.ZZ = a.ZZ + b.ZZ;
c.ZW = a.ZW + b.ZW;

c.WX = a.WX + b.WX;
c.WY = a.WY + b.WY;
c.WZ = a.WZ + b.WZ;
c.WW = a.WW + b.WW;

return c;
}


template <class FT>
INLINE Mat4T<FT> operator - (const Mat4T<FT>& a, const Mat4T<FT>& b)
{
Mat4T<FT> c;

c.XX = a.XX - b.XX;
c.XY = a.XY - b.XY;
c.XZ = a.XZ - b.XZ;
c.XW = a.XW - b.XW;

c.YX = a.YX - b.YX;
c.YY = a.YY - b.YY;
c.YZ = a.YZ - b.YZ;
c.YW = a.YW - b.YW;

c.ZX = a.ZX - b.ZX;
c.ZY = a.ZY - b.ZY;
c.ZZ = a.ZZ - b.ZZ;
c.ZW = a.ZW - b.ZW;

c.WX = a.WX - b.WX;
c.WY = a.WY - b.WY;
c.WZ = a.WZ - b.WZ;
c.WW = a.WW - b.WW;

return c;
}


template <class FT>
INLINE Mat4T<FT> operator * (const Mat4T<FT>& b, const Mat4T<FT>& a)
{
Mat4T<FT> c;

c.XX = a.XX * b.XX + a.YX * b.XY + a.ZX * b.XZ + a.WX * b.XW;
c.XY = a.XY * b.XX + a.YY * b.XY + a.ZY * b.XZ + a.WY * b.XW;
c.XZ = a.XZ * b.XX + a.YZ * b.XY + a.ZZ * b.XZ + a.WZ * b.XW;
c.XW = a.XW * b.XX + a.YW * b.XY + a.ZW * b.XZ + a.WW * b.XW;

c.YX = a.XX * b.YX + a.YX * b.YY + a.ZX * b.YZ + a.WX * b.YW;
c.YY = a.XY * b.YX + a.YY * b.YY + a.ZY * b.YZ + a.WY * b.YW;
c.YZ = a.XZ * b.YX + a.YZ * b.YY + a.ZZ * b.YZ + a.WZ * b.YW;
c.YW = a.XW * b.YX + a.YW * b.YY + a.ZW * b.YZ + a.WW * b.YW;

c.ZX = a.XX * b.ZX + a.YX * b.ZY + a.ZX * b.ZZ + a.WX * b.ZW;
c.ZY = a.XY * b.ZX + a.YY * b.ZY + a.ZY * b.ZZ + a.WY * b.ZW;
c.ZZ = a.XZ * b.ZX + a.YZ * b.ZY + a.ZZ * b.ZZ + a.WZ * b.ZW;
c.ZW = a.XW * b.ZX + a.YW * b.ZY + a.ZW * b.ZZ + a.WW * b.ZW;

c.WX = a.XX * b.WX + a.YX * b.WY + a.ZX * b.WZ + a.WX * b.WW;
c.WY = a.XY * b.WX + a.YY * b.WY + a.ZY * b.WZ + a.WY * b.WW;
c.WZ = a.XZ * b.WX + a.YZ * b.WY + a.ZZ * b.WZ + a.WZ * b.WW;
c.WW = a.XW * b.WX + a.YW * b.WY + a.ZW * b.WZ + a.WW * b.WW;

return c;
}



template <class FT>
INLINE Mat4T<FT> operator * (const Mat4T<FT>& a, const FT d)
{
Mat4T<FT> b;
b.XX = a.XX * d;
b.XY = a.XY * d;
b.XZ = a.XZ * d;
b.XW = a.XW * d;

b.YX = a.YX * d;
b.YY = a.YY * d;
b.YZ = a.YZ * d;
b.YW = a.YW * d;

b.ZX = a.ZX * d;
b.ZY = a.ZY * d;
b.ZZ = a.ZZ * d;
b.ZW = a.ZW * d;

b.WX = a.WX * d;
b.WY = a.WY * d;
b.WZ = a.WZ * d;
b.WW = a.WW * d;

return b;
}

template <class FT>
INLINE Mat4T<FT> operator * (const FT d, const Mat4T<FT>& a)
{ return a*d; }


template <class FT>
INLINE Vec3T<FT> operator * (const Vec3T<FT>& v3, const Mat4T<FT>& m4)
{
// multiply v3 as though it were v4 with w = 1
Vec4T<FT> v4;
Vec3T<FT> ret;
v4.x = v3.x;
v4.y = v3.y;
v4.z = v3.z;
v4.w = 1.0f;
v4 = v4 * m4;
v4.Homogenize();

ret.x = v4.x;
ret.y = v4.y;
ret.z = v4.z;
return( ret );
}

template <class FT>
INLINE Vec3T<FT> operator * (const Mat4T<FT>& m4, const Vec3T<FT>& v3)
{
// multiply v3 as though it were v4 with w = 1
Vec4T<FT> v4;
Vec3T<FT> ret;
v4.x = v3.x;
v4.y = v3.y;
v4.z = v3.z;
v4.w = 1.0f;
v4 = m4 * v4;
v4.Homogenize();

ret.x = v4.x;
ret.y = v4.y;
ret.z = v4.z;
return( ret );
}

template <class FT>
INLINE Vec4T<FT> operator * ( const Vec4T<FT>& v, const Mat4T<FT>& a )
{
return Vec4T<FT> (
v.x * a.XX + v.y * a.YX + v.z * a.ZX + v.w * a.WX,
v.x * a.XY + v.y * a.YY + v.z * a.ZY + v.w * a.WY,
v.x * a.XZ + v.y * a.YZ + v.z * a.ZZ + v.w * a.WZ,
v.x * a.XW + v.y * a.YW + v.z * a.ZW + v.w * a.WW );
}

template <class FT>
INLINE Vec4T<FT> operator * ( const Mat4T<FT>& a, const Vec4T<FT>& v )
{
return Vec4T<FT> (
v.x * a.XX + v.y * a.XY + v.z * a.XZ + v.w * a.XW,
v.x * a.YX + v.y * a.YY + v.z * a.YZ + v.w * a.YW,
v.x * a.ZX + v.y * a.ZY + v.z * a.ZZ + v.w * a.ZW,
v.x * a.WX + v.y * a.WY + v.z * a.WZ + v.w * a.WW );
}



template <class FT>
INLINE Mat4T<FT> operator / (const Mat4T<FT>& a, const FT d)
{
Mat4T<FT> b;
FT u = 1 / d;
b.XX = a.XX * u;
b.XY = a.XY * u;
b.XZ = a.XZ * u;
b.XW = a.XW * u;

b.YX = a.YX * u;
b.YY = a.YY * u;
b.YZ = a.YZ * u;
b.YW = a.YW * u;

b.ZX = a.ZX * u;
b.ZY = a.ZY * u;
b.ZZ = a.ZZ * u;
b.ZW = a.ZW * u;

b.WX = a.WX * u;
b.WY = a.WY * u;
b.WZ = a.WZ * u;
b.WW = a.WW * u;

return b;
}

template <class FT>
INLINE bool operator == (const Mat4T<FT>& a, const Mat4T<FT>& b)
{
// I don't care about the IEEE == semantics
return memcmp( &a, &b, sizeof(a) ) == 0;
/*
return (
(b.XX == a.XX) &&
(b.XY == a.XY) &&
(b.XZ == a.XZ) &&
(b.XW == a.XW) &&

(b.YX == a.YX) &&
(b.YY == a.YY) &&
(b.YZ == a.YZ) &&
(b.YW == a.YW) &&

(b.ZX == a.ZX) &&
(b.ZY == a.ZY) &&
(b.ZZ == a.ZZ) &&
(b.ZW == a.ZW) &&

(b.WX == a.WX) &&
(b.WY == a.WY) &&
(b.WZ == a.WZ) &&
(b.WW == a.WW));
*/
}

template <class FT>
INLINE bool operator != (const Mat4T<FT>& a, const Mat4T<FT>& b)
{ return !(a == b); }

// sum of component absolute differences
template <class FT>
double Difference( const Mat4T<FT>& a, const Mat4T<FT>& b )
{
double d = 0;
FT *ap = (FT*) &a;
FT *bp = (FT*) &b;
for (int i = 0; i < 16; i++)
d += fabs(ap[i] - bp[i]);
return d;
}


typedef Mat4T<float> Mat4f;
typedef Mat4T<double> Mat4d;
typedef Mat4T<double> Mat4;

#endif // DEFINED_Mat4

#undef XX
#undef XY
#undef XZ
#undef XW

#undef YX
#undef YY
#undef YZ
#undef YW

#undef ZX
#undef ZY
#undef ZZ
#undef ZW

#undef WX
#undef WY
#undef WZ
#undef WW

#undef UL_R
#undef UL_U
#undef UL_N

#undef X
#undef Y
#undef Z
#undef W

/*
xxHash - Extremely Fast Hash algorithm
Header File
Copyright (C) 2012-2014, Yann Collet.
BSD 2-Clause License (http://www.opensource.org/licenses/bsd-license.php)

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

You can contact the author at :
- xxHash source repository : http://code.google.com/p/xxhash/
*/

/* Notice extracted from xxHash homepage :

xxHash is an extremely fast Hash algorithm, running at RAM speed limits.
It also successfully passes all tests from the SMHasher suite.

Comparison (single thread, Windows Seven 32 bits, using SMHasher on a Core 2 Duo @3GHz)

Name            Speed       Q.Score   Author
xxHash          5.4 GB/s     10
CrapWow         3.2 GB/s      2       Andrew
MumurHash 3a    2.7 GB/s     10       Austin Appleby
SpookyHash      2.0 GB/s     10       Bob Jenkins
SBox            1.4 GB/s      9       Bret Mulvey
Lookup3         1.2 GB/s      9       Bob Jenkins
SuperFastHash   1.2 GB/s      1       Paul Hsieh
CityHash64      1.05 GB/s    10       Pike & Alakuijala
FNV             0.55 GB/s     5       Fowler, Noll, Vo
CRC32           0.43 GB/s     9
MD5-32          0.33 GB/s    10       Ronald L. Rivest
SHA1-32         0.28 GB/s    10

Q.Score is a measure of quality of the hash function.
It depends on successfully passing SMHasher test set.
10 is a perfect score.
*/


#if defined (__cplusplus)
extern "C" {
#endif


/*****************************
Type
*****************************/
typedef enum { XXH_OK=0, XXH_ERROR } XXH_errorcode;



/*****************************
Simple Hash Functions
*****************************/

unsigned int       XXH32 (const void* input, unsigned int len, unsigned int seed);
unsigned long long XXH64 (const void* input, unsigned int len, unsigned long long seed);

/*
XXH32() :
Calculate the 32-bits hash of sequence of length "len" stored at memory address "input".
The memory between input & input+len must be valid (allocated and read-accessible).
"seed" can be used to alter the result predictably.
This function successfully passes all SMHasher tests.
Speed on Core 2 Duo @ 3 GHz (single thread, SMHasher benchmark) : 5.4 GB/s
Note that "len" is type "int", which means it is limited to 2^31-1.
If your data is larger, use the advanced functions below.
XXH64() :
Calculate the 64-bits hash of sequence of length "len" stored at memory address "input".
*/



/*****************************
Advanced Hash Functions
*****************************/

void*         XXH32_init   (unsigned int seed);
XXH_errorcode XXH32_update (void* state, const void* input, unsigned int len);
unsigned int  XXH32_digest (void* state);

void*         		XXH64_init   (unsigned long long seed);
XXH_errorcode 		XXH64_update (void* state, const void* input, unsigned int len);
unsigned long long  XXH64_digest (void* state);

/*
These functions calculate the xxhash of an input provided in several small packets,
as opposed to an input provided as a single block.

It must be started with :
void* XXHnn_init()
The function returns a pointer which holds the state of calculation.

This pointer must be provided as "void* state" parameter for XXHnn_update().
XXHnn_update() can be called as many times as necessary.
The user must provide a valid (allocated) input.
The function returns an error code, with 0 meaning OK, and any other value meaning there is an error.
Note that "len" is type "int", which means it is limited to 2^31-1.
If your data is larger, it is recommended to chunk your data into blocks
of size for example 2^30 (1GB) to avoid any "int" overflow issue.

Finally, you can end the calculation anytime, by using XXHnn_digest().
This function returns the final nn-bits hash.
You must provide the same "void* state" parameter created by XXHnn_init().
Memory will be freed by XXHnn_digest().
*/


int           XXH32_sizeofState(void);
XXH_errorcode XXH32_resetState(void* state, unsigned int seed);

#define       XXH32_SIZEOFSTATE 48
typedef struct { long long ll[(XXH32_SIZEOFSTATE+(sizeof(long long)-1))/sizeof(long long)]; } XXH32_stateSpace_t;

int           XXH64_sizeofState(void);
XXH_errorcode XXH64_resetState(void* state, unsigned long long seed);

#define       XXH64_SIZEOFSTATE 88
typedef struct { long long ll[(XXH64_SIZEOFSTATE+(sizeof(long long)-1))/sizeof(long long)]; } XXH64_stateSpace_t;

/*
These functions allow user application to make its own allocation for state.

XXHnn_sizeofState() is used to know how much space must be allocated for the xxHash nn-bits state.
Note that the state must be aligned to access 'long long' fields. Memory must be allocated and referenced by a pointer.
This pointer must then be provided as 'state' into XXHnn_resetState(), which initializes the state.

For static allocation purposes (such as allocation on stack, or freestanding systems without malloc()),
use the structure XXHnn_stateSpace_t, which will ensure that memory space is large enough and correctly aligned to access 'long long' fields.
*/


unsigned int       XXH32_intermediateDigest (void* state);
unsigned long long XXH64_intermediateDigest (void* state);
/*
This function does the same as XXHnn_digest(), generating a nn-bit hash,
but preserve memory context.
This way, it becomes possible to generate intermediate hashes, and then continue feeding data with XXHnn_update().
To free memory context, use XXHnn_digest(), or free().
*/


#if defined (__cplusplus)
}
#endif


typedef VecBase2T<float> xoVecBase2f;
typedef VecBase3T<float> xoVecBase3f;
typedef VecBase4T<float> xoVecBase4f;

typedef Vec2T<float> xoVec2f;
typedef Vec3T<float> xoVec3f;
typedef Vec4T<float> xoVec4f;

#define XO_MAT4F_DEFINED
typedef Mat4T<float> xoMat4f;


#define FMT_STRING xoString
#define FMT_STRING_BUF(s)	(s.Z)
#define FMT_STRING_LEN(s)	(s.Length())


#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable: 4345 )	// POD constructed with () is default-initialized
#endif

class xoPool;

// This has no constructors or destructors so that we can put it in unions, etc. We know that there is no implicit
// memory management going on here.
class XOAPI xoStringRaw
{
public:
char*	Z;

intp	Length() const;
void	CloneFastInto( xoStringRaw& b, xoPool* pool ) const;
void	Discard();
u32		GetHashCode() const;
intp	Index( const char* find ) const;
intp	RIndex( const char* find ) const;

bool	operator==( const char* b ) const;
bool	operator!=( const char* b ) const			{ return !(*this == b); }
bool	operator==( const xoStringRaw& b ) const;
bool	operator!=( const xoStringRaw& b ) const	{ return !(*this == b); }

bool	operator<( const xoStringRaw& b ) const;

protected:
static xoStringRaw Temp( char* b );

void	Alloc( uintp chars );
void	Free();
};

// This is the classic thing you'd expect from a string. The destructor will free the memory.
class XOAPI xoString : public xoStringRaw
{
public:
xoString();
xoString( const xoString& b );
xoString( const xoStringRaw& b );
xoString( const char* z, intp maxLength = -1 );	// Calls Set()
~xoString();

void				Set( const char* z, intp maxLength = -1 );	// checks maxLength against strlen(z) and clamps automatically
void				ReplaceAll( const char* find, const char* replace );
podvec<xoString>	Split( const char* splitter ) const;
xoString			SubStr( intp start, intp end ) const;	// Returns [start .. end - 1]

xoString&	operator=( const xoString& b );
xoString&	operator=( const xoStringRaw& b );
xoString&	operator=( const char* b );
xoString&	operator+=( const xoStringRaw& b );
xoString&	operator+=( const char* b );

static xoString		Join( const podvec<xoString>& parts, const char* joiner );

};

FHASH_SETUP_CLASS_GETHASHCODE( xoString, xoString );

XOAPI xoString operator+( const char* a, const xoStringRaw& b );
XOAPI xoString operator+( const xoStringRaw& a, const char* b );
XOAPI xoString operator+( const xoStringRaw& a, const xoStringRaw& b );

// Use this when you need a temporary 'xoString' object, but you don't need any heap allocs or frees
class XOAPI xoTempString : public xoString
{
public:
xoTempString( const char* z );
~xoTempString();
};

#ifdef _WIN32
#pragma warning( pop )
#endif


// If you don't want to use XStringA, then you must define FMT_STRING to be some kind of string class
// that can construct itself from const char*.

// To use std::string, do the following before including fmt.h:
// #define FMT_STRING          std::string
// #define FMT_STRING_BUF(s)   (s).c_str()
// #define FMT_STRING_LEN(s)   (s).Length()

#ifndef FMT_STRING
#define FMT_STRING			XStringA
#define FMT_STRING_BUF(s)	static_cast<const char*>(s)
#define FMT_STRING_LEN(s)	(s).Length()
#endif

/*

fmt: (Yet another) typesafe, cross-platform (Windows,linux) printf replacement.

This thing uses snprintf as a backend, so all of the regular formatting commands
that you expect from the printf family of functions works.

Usage:
fmt( "%v %v", "abc", 123 ) --> "abc 123"				<== Use %v as a generic value type
fmt( "%s %d", "abc", 123 ) --> "abc 123"				<== Specific value types are fine too, unless they conflict with the provided type, in which case they are overridden
fmt( "%v", std::string("abc") ) --> "abc"				<== std::string
fmt( "%v", std::wstring("abc") ) --> "abc"				<== std::wstring
fmt( "%v", XStringA("abc") ) --> "abc"					<== XStringA
fmt( "%v", XStringW("abc") ) --> "abc"					<== XStringW
fmt( "%.3f", 25.5 ) --> "25.500"						<== Use format strings as usual

Known unsupported features:
* Positional arguments
* %*s (integer width parameter)	-- wouldn't be hard to add. Presently ignored.

Exclusively returns FMT_STRING.

By providing a cast operator to fmtarg, you can get an arbitrary type supported as an argument (provided it fits into one of the moulds of the printf family of arguments).

*/

class PAPI fmtarg
{
public:
enum Types
{
TNull,	// Used as a sentinel to indicate that no parameter was passed
TCStr,
TWStr,
TI32,
TU32,
TI64,
TU64,
TDbl,
};
union
{
const char*		CStr;
const wchar_t*	WStr;
int32_t			I32;
uint32_t		UI32;
int64_t			I64;
uint64_t		UI64;
double			Dbl;
};
Types Type;

fmtarg()								: Type(TNull), CStr(NULL) {}
fmtarg( const char* v )					: Type(TCStr), CStr(v) {}
fmtarg( const wchar_t* v )				: Type(TWStr), WStr(v) {}
#ifdef XSTRING_DEFINED
fmtarg( const XStringT<char>& v )		: Type(TCStr), CStr((const char*) v) {}
fmtarg( const XStringT<wchar_t>& v )	: Type(TWStr), WStr((const wchar_t*) v) {}
#endif
fmtarg( const std::string& v )			: Type(TCStr), CStr(v.c_str()) {}
fmtarg( const std::wstring& v )			: Type(TWStr), WStr(v.c_str()) {}
fmtarg( int32_t v )						: Type(TI32), I32(v) {}
fmtarg( uint32_t v )					: Type(TU32), UI32(v) {}
#ifdef _MSC_VER
fmtarg( long v )						: Type(TI32), I32(v) {}
fmtarg( unsigned long v )				: Type(TU32), UI32(v) {}
#endif
fmtarg( int64_t v )						: Type(TI64), I64(v) {}
fmtarg( uint64_t v )					: Type(TU64), UI64(v) {}
fmtarg( double v )						: Type(TDbl), Dbl(v) {}
};

/* This can be used to add custom formatting tokens.
The only supported characters that you can use are "Q" and "q". These were
added for escaping SQL identifiers and strings.
*/
struct fmt_context
{
// Return the number of characters written, or -1 if outBufSize is not large enough to hold
// the number of characters that you need to write. Do not write a null terminator.
typedef intp (*WriteSpecialFunc)( char* outBuf, intp outBufSize, const fmtarg& val );

WriteSpecialFunc Escape_Q;
WriteSpecialFunc Escape_q;

fmt_context()
{
Escape_Q = NULL;
Escape_q = NULL;
}
};

PAPI FMT_STRING fmt_core( const fmt_context& context, const char* fmt, intp nargs, const fmtarg** args );

PAPI FMT_STRING fmt( const char* fs );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11, const fmtarg& a12 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11, const fmtarg& a12, const fmtarg& a13 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11, const fmtarg& a12, const fmtarg& a13, const fmtarg& a14 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11, const fmtarg& a12, const fmtarg& a13, const fmtarg& a14, const fmtarg& a15 );
PAPI FMT_STRING fmt( const char* fs, const fmtarg& a1, const fmtarg& a2, const fmtarg& a3, const fmtarg& a4, const fmtarg& a5, const fmtarg& a6, const fmtarg& a7, const fmtarg& a8, const fmtarg& a9, const fmtarg& a10, const fmtarg& a11, const fmtarg& a12, const fmtarg& a13, const fmtarg& a14, const fmtarg& a15, const fmtarg& a16 );

/*
PAPI FMT_STRING fmt( const char* fs,
const fmtarg& a1 = fmtarg(),
const fmtarg& a2 = fmtarg(),
const fmtarg& a3 = fmtarg(),
const fmtarg& a4 = fmtarg(),
const fmtarg& a5 = fmtarg(),
const fmtarg& a6 = fmtarg(),
const fmtarg& a7 = fmtarg(),
const fmtarg& a8 = fmtarg(),
const fmtarg& a9 = fmtarg(),
const fmtarg& a10 = fmtarg(),
const fmtarg& a11 = fmtarg(),
const fmtarg& a12 = fmtarg(),
const fmtarg& a13 = fmtarg(),
const fmtarg& a14 = fmtarg(),
const fmtarg& a15 = fmtarg(),
const fmtarg& a16 = fmtarg());
*/

// Clang will need -Wno-variadic-macros
// I believe the use of __VA_ARGS__ is cross-platform enough for our needs
#define fmtout( fs, ... )			fmt_write(stdout, fmt(fs, __VA_ARGS__))
#define fmtoutf( file, fs, ... )	fmt_write(file, fmt(fs, __VA_ARGS__))

// We cannot do fmtout and fmtoutf with macros, because you cannot use __VA_ARGS__ inside a nested macro.
// It's hard to explain in a few short words, but this was the old version, an it's pre-processed output
// #define fmtout( fs, ... )           fputs(FMT_STRING_TO_C(fmt(fs, __VA_ARGS__)), stdout)		--> fputs(static_cast<const char*>(fmt("Hello!", )), (&__iob_func()[1]));
// Notice the trailing comma. That trailing comma is NOT present if you don't have the FMT_STRING_TO_C there.

// The approach of making this proper function has the added advantage that we can write strings with null characters in them
// Returns the number of characters written (ie the result of fwrite).
PAPI size_t fmt_write( FILE* file, const FMT_STRING& s );

/*  cross-platform "snprintf"

destination			Destination buffer
count				Number of characters available in 'destination'. This must include space for the null terminating character.
format_str			The format string
return
-1				Not enough space
0..count-1		Number of characters written, excluding the null terminator. The null terminator was written though.
*/
PAPI int fmt_snprintf( char* destination, size_t count, const char* format_str, ... );

// Identical in all respects to fmt_snprintf, except that we deal with wide character strings
PAPI int fmt_swprintf( wchar_t* destination, size_t count, const wchar_t* format_str, ... );


typedef unsigned char	byte;
typedef unsigned char	u8;
typedef unsigned char	uint8;
typedef unsigned int	u32;
typedef unsigned int	uint32;
typedef int				int32;
typedef unsigned short	uint16;

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

// This executes in ALL BUILDS (not just debug).
#define XOASSERT(x)			AbcAssert(x)

#ifdef _DEBUG
#define XOVERIFY(x)			XOASSERT(x)
#define XOASSERTDEBUG(x)	XOASSERT(x)
#else
#define XOVERIFY(x)			((void)(x))
#define XOASSERTDEBUG(x)	((void)0)
#endif

void*		xoMallocOrDie( size_t bytes );
void*		xoReallocOrDie( void* buf, size_t bytes );
xoString	xoCacheDir();

#define XOCHECKALLOC(x)		XOASSERT((x) != NULL)
#define XOPANIC(msg)		AbcPanic(msg)
#define XOTODO				XOPANIC("not yet implemented")
#define XOTODO_STATIC		static_assert(false, "Implement me");

enum xoPlatform
{
xoPlatform_WinDesktop		= 1,
xoPlatform_Android			= 2,
xoPlatform_LinuxDesktop		= 4,
xoPlatform_All			= 1 | 2 | 4,
};

#if defined(_WIN32)
#define XO_PLATFORM_ANDROID			0
#define XO_PLATFORM_WIN_DESKTOP		1
#define XO_PLATFORM_LINUX_DESKTOP	0
#define XO_PLATFORM					xoPlatform_WinDesktop
#define XOTRACE_WRITE				OutputDebugStringA
#elif defined(ANDROID)
#define XO_PLATFORM_ANDROID			1
#define XO_PLATFORM_WIN_DESKTOP		0
#define XO_PLATFORM_LINUX_DESKTOP	0
#define XO_PLATFORM					xoPlatform_Android
#define XOTRACE_WRITE(msg)			__android_log_write(ANDROID_LOG_INFO, "xo", msg)
#elif defined(__linux__)
#define XO_PLATFORM_ANDROID			0
#define XO_PLATFORM_WIN_DESKTOP		0
#define XO_PLATFORM_LINUX_DESKTOP	1
#define XO_PLATFORM					xoPlatform_LinuxDesktop
#define XOTRACE_WRITE(msg)			fputs(msg, stderr)
#else
#ifdef _MSC_VER
#pragma error( "Unknown xoDom platform" )
#else
#error Unknown xoDom platform
#endif
#endif


// The default styles for tags are defined inside xoDoc::InitializeDefaultTagStyles()

#define XO_TAGS_DEFINE \
XX(NULL, 0) \
XY(Body) \
XY(Div) \
XY(Text) \
XY(Lab) \
XY(END) \

#define XX(a,b) xoTag##a = b,
#define XY(a) xoTag##a,
enum xoTag {
XO_TAGS_DEFINE
};
#undef XX
#undef XY

extern const char* xoTagNames[xoTagEND + 1];


// This is the bottom-level include file that many other xo headers include. It should
// strive to remain quite small.


class xoBox;
class xoBox16;
class xoBoxF;
class xoDomEl;
class xoDomNode;
class xoDomText;
class xoDoc;
class xoEvent;
class xoImage;
class xoImageStore;
class xoLayout;
class xoLayout2;
class xoPool;
class xoDocGroup;
class xoRenderDoc;
class xoRenderer;
class xoRenderDomEl;
class xoRenderDomNode;
class xoRenderDomText;
struct xoRenderCharEl;
class xoRenderBase;
class xoRenderGL;
class xoRenderDX;
class xoString;
class xoStringTable;
class xoStyle;
class xoSysWnd;
class xoFont;
class xoFontStore;
class xoGlyphCache;
class xoTextureAtlas;
#ifndef XO_MAT4F_DEFINED
class xoMat4f;
#endif

typedef int32 xoPos;								// fixed-point position
static xoPos xoPosNULL = INT32MAX;
static const u32 xoPosShift = 8;					// 24:8 fixed point coordinates used during layout
static const u32 xoPosMask = (1 << xoPosShift) - 1;	// 255

// An ID that is internal to xo - i.e. it is not controllable by external code.
// This ID is an integer that you can use to reference a DOM element. These IDs are recycled.
typedef int32 xoInternalID;
static const xoInternalID xoInternalIDNull = 0;		// Zero is always an invalid DOM element ID
static const xoInternalID xoInternalIDRoot = 1;		// The root of the DOM tree always has ID = 1

typedef int32 xoFontID;
static const xoFontID xoFontIDNull = 0;				// Zero is always an invalid Font ID

// Handle to a texture that is (maybe) resident in the graphics driver.
// xo supports the concept of the graphics device being "lost", so just because you have
// a non-zero xoTextureID, does not mean that the ID is valid. Prior to drawing the scene,
// the texture loading functions must check whether the ID is still valid or not.
// Note that there is a lot of unsigned arithmetic used by the texture management facilities,
// so this data type must remain unsigned.
typedef uint32 xoTextureID;
static const xoTextureID xoTextureIDNull = 0;		// Zero is always an invalid Texture ID

// Maximum number of texture units that we will try to use
static const u32 xoMaxTextureUnits = 8;

inline int32	xoIntToPos( int real )			{ return real << xoPosShift; }
inline int32	xoRealx256ToPos( int32 real )	{ return int32(real * ((1 << xoPosShift) / 256)); } // Since xoPosShift = 256, xoRealx256ToPos simplifies out to identity
inline int32	xoRealToPos( float real )		{ return int32(real * (1 << xoPosShift)); }
inline int32	xoDoubleToPos( double real )	{ return int32(real * (1 << xoPosShift)); }
inline float	xoPosToReal( int32 pos )		{ return pos * (1.0f / (1 << xoPosShift)); }
inline double	xoPosToDouble( int32 pos )		{ return pos * (1.0 / (1 << xoPosShift)); }
inline int32	xoPosRound( int32 pos )			{ return pos + (1 << (xoPosShift-1)) & ~xoPosMask; }
inline int32	xoPosRoundDown( int32 pos )		{ return pos & ~xoPosMask; }
inline int32	xoPosRoundUp( int32 pos )		{ return pos + ((1 << xoPosShift) - 1) & ~xoPosMask; }
inline float	xoRound( float real )			{ return floor(real + 0.5f); }

// These purposefully do not pass by reference, because of this: http://randomascii.wordpress.com/2013/11/24/stdmin-causing-three-times-slowdown-on-vc/
template<typename T>	T xoClamp( T v, T vmin, T vmax )	{ return (v < vmin) ? vmin : (v > vmax) ? vmax : v; }
template<typename T>	T xoMin( T a, T b )					{ return a < b ? a : b; }
template<typename T>	T xoMax( T a, T b )					{ return a < b ? b : a; }

enum xoCloneFlags
{
xoCloneFlagEvents = 1,		// Include events in clone
};

static const int XO_MAX_TOUCHES = 10;

enum xoMainEvent
{
xoMainEventInit = 1,
xoMainEventShutdown,
};

enum xoRenderResult
{
// SYNC-JAVA
xoRenderResultNeedMore,
xoRenderResultIdle
};

//struct xoVec2
//{
//	float x,y;
//};
inline xoVec2f XOVEC2(float x, float y) { return xoVec2f(x,y); }

//struct xoVec3
//{
//	float x,y,z;
//};
inline xoVec3f XOVEC3(float x, float y, float z) { return xoVec3f(x,y,z); }

//struct xoVec4
//{
//	float x,y,z,w;
//};
inline xoVec4f XOVEC4(float x, float y, float z, float w) { return xoVec4f(x,y,z,w); }

class XOAPI xoPoint
{
public:
xoPos	X, Y;

xoPoint() : X(0), Y(0) {}
xoPoint( xoPos x, xoPos y ) : X(x), Y(y) {}

void		SetInt( int32 x, int32 y )				{ X = xoRealToPos((float) x); Y = xoRealToPos((float) y); }
bool		operator==( const xoPoint& p ) const	{ return X == p.X && Y == p.Y; }
bool		operator!=( const xoPoint& p ) const	{ return !(*this == p); }
xoPoint		operator+( const xoPoint& p ) const		{ return xoPoint(X + p.X, Y + p.Y); }
xoPoint		operator-( const xoPoint& p ) const		{ return xoPoint(X - p.X, Y - p.Y); }
xoPoint&	operator+=( const xoPoint& p )			{ X += p.X; Y += p.Y; return *this; }
xoPoint&	operator-=( const xoPoint& p )			{ X -= p.X; Y -= p.Y; return *this; }
};

/*
Why does this class have a copy constructor and assignment operator?
Without those, we get data alignment exceptions (signal 7) when running on my Galaxy S3.
I tried explicitly raising the alignment of xoBox to 8 and 16 bytes, but that did not help.
Unfortunately I have not yet had the energy to open up the assembly and see what the compiler is doing wrong.
This is documented inside xo/docs/android.md

There are some magic values in here:
xoBox is used to represent the content-box of a node.
One thing that comes up frequently is that a box has a well defined Left, but no Right. Or vice versa, or any combination thereof.
So, xoPosNULL is treated like a NaN. If either Left or Right is xoPosNULL, then WidthOrNull is xoPosNULL.
Likewise for HeightOrNull.
*/
class XOAPI xoBox
{
public:
xoPos	Left, Right, Top, Bottom;

xoBox() : Left(0), Right(0), Top(0), Bottom(0) {}
xoBox( const xoBox& b ) : Left(b.Left), Right(b.Right), Top(b.Top), Bottom(b.Bottom) {}
xoBox( xoPos left, xoPos top, xoPos right, xoPos bottom ) : Left(left), Right(right), Top(top), Bottom(bottom) {}

#ifdef _WIN32
xoBox( RECT r ) : Left(r.left), Right(r.right), Top(r.top), Bottom(r.bottom) {}
operator RECT() const { RECT r = {Left, Top, Right, Bottom}; return r; }
#endif

void	SetInt( int32 left, int32 top, int32 right, int32 bottom );
void	ExpandToFit( const xoBox& expando );
void	ClampTo( const xoBox& clamp );
xoBox	ShrunkBy( const xoBox& margins );
xoBoxF	ToRealBox() const;

xoPos	Width() const							{ return Right - Left; }
xoPos	Height() const							{ return Bottom - Top; }
xoPos	WidthOrNull() const						{ return (Left == xoPosNULL || Right == xoPosNULL) ? xoPosNULL : Right - Left; }
xoPos	HeightOrNull() const					{ return (Top == xoPosNULL || Bottom == xoPosNULL) ? xoPosNULL : Bottom - Top; }
void	Offset( int32 x, int32 y )				{ Left += x; Right += x; Top += y; Bottom += y; }
void	Offset( xoPoint p )						{ Offset( p.X, p.Y ); }
xoBox	OffsetBy( int32 x, int32 y )			{ return xoBox(Left + x, Top + y, Right + x, Bottom + y); }
xoBox	OffsetBy( xoPoint p )					{ return xoBox(Left + p.X, Top + p.Y, Right + p.X, Bottom + p.Y); }
bool	IsInsideMe( xoPoint p ) const			{ return p.X >= Left && p.Y >= Top && p.X < Right && p.Y < Bottom; }
bool	IsAreaZero() const						{ return Width() == 0 || Height() == 0; }

bool operator==( const xoBox& b ) { return Left == b.Left && Right == b.Right && Top == b.Top && Bottom == b.Bottom; }
bool operator!=( const xoBox& b ) { return !(*this == b); }

// $XO_GCC_ALIGN_BUG
xoBox&	operator=( const xoBox& b ) { Left = b.Left; Right = b.Right; Top = b.Top; Bottom = b.Bottom; return *this; }
};

class XOAPI xoBox16
{
public:
uint16	Left;
uint16	Top;
uint16	Right;
uint16	Bottom;

xoBox16() : Left(0), Right(0), Top(0), Bottom(0) {}
xoBox16( const xoBox& b ) : Left(b.Left), Right(b.Right), Top(b.Top), Bottom(b.Bottom) {}
xoBox16( const xoBox16& b ) : Left(b.Left), Right(b.Right), Top(b.Top), Bottom(b.Bottom) {}
xoBox16( xoPos left, xoPos top, xoPos right, xoPos bottom ) : Left(left), Right(right), Top(top), Bottom(bottom) {}

xoBoxF	ToRealBox() const;
};

class XOAPI xoBoxF
{
public:
float	Left, Right, Top, Bottom;

xoBoxF() : Left(0), Right(0), Top(0), Bottom(0) {}
xoBoxF( float left, float top, float right, float bottom ) : Left(left), Right(right), Top(top), Bottom(bottom) {}
};

struct XOAPI xoRGBA
{
union {
struct {
#if ENDIANLITTLE
uint8 a, b, g, r;
#else
uint8 r: 8;
uint8 g: 8;
uint8 b: 8;
uint8 a: 8;
#endif
};
uint32 u;
};
static xoRGBA RGBA(uint8 r, uint8 g, uint8 b, uint8 a) { xoRGBA c; c.r = r; c.g = g; c.b = b; c.a = a; return c; }
};

// This is non-premultipled alpha
struct XOAPI xoColor
{
union {
struct {
#if ENDIANLITTLE
uint8 b, g, r, a;
#else
uint8 a: 8;
uint8 r: 8;
uint8 g: 8;
uint8 b: 8;
#endif
};
uint32 u;
};

void	Set( uint8 _r, uint8 _g, uint8 _b, uint8 _a ) { r = _r; g = _g; b = _b; a = _a; }
uint32	GetRGBA() const { xoRGBA x; x.r = r; x.g = g; x.b = b; x.a = a; return x.u; }
xoVec4f	GetVec4sRGB() const;
xoVec4f	GetVec4Linear() const;

bool	operator==( const xoColor& x ) const { return u == x.u; }
bool	operator!=( const xoColor& x ) const { return u != x.u; }

static bool		Parse( const char* s, intp len, xoColor& v );
static xoColor	RGBA( uint8 _r, uint8 _g, uint8 _b, uint8 _a )		{ xoColor c; c.Set(_r,_g,_b,_a); return c; }
static xoColor	Make( uint32 _u )									{ xoColor c; c.u = _u; return c; }
};

XOAPI float	xoSRGB2Linear( uint8 srgb );
XOAPI uint8	xoLinear2SRGB( float linear );

struct xoStyleID
{
uint32		StyleID;

xoStyleID()				: StyleID(0)	{}
explicit	xoStyleID( uint32 id )	: StyleID(id)	{}

operator	uint32 () const { return StyleID; }
};

struct xoJob
{
void*	JobData;
void (*JobFunc)( void* jobdata );
};

struct XOAPI xoRenderStats
{
uint32	Clone_NumEls;		// Number of DOM elements cloned

void Reset();
};

enum xoTexFormat
{
xoTexFormatInvalid = 0,
xoTexFormatRGBA8 = 1,
xoTexFormatGrey8 = 2
};

XOAPI size_t xoTexFormatChannelCount( xoTexFormat f );
XOAPI size_t xoTexFormatBytesPerChannel( xoTexFormat f );
XOAPI size_t xoTexFormatBytesPerPixel( xoTexFormat f );

/* Base of all textures
This structure must remain zero-initializable
Once a texture has been uploaded, you may not change width, height, or channel count.
*/
class XOAPI xoTexture
{
public:
uint32		TexWidth;
uint32		TexHeight;
xoBox		TexInvalidRect;		// Invalid rectangle, in integer texel coordinates.
xoTextureID	TexID;				// ID of texture in renderer.
xoTexFormat	TexFormat;
void*		TexData;
int			TexStride;

xoTexture()					{ TexWidth = TexHeight = 0; TexInvalidRect = xoBox(0,0,0,0); TexFormat = xoTexFormatInvalid; TexID = xoTextureIDNull; TexData = NULL; TexStride = 0; }
void	TexInvalidate()				{ TexInvalidRect = xoBox(0, 0, TexWidth, TexHeight); }
void	TexValidate()				{ TexInvalidRect = xoBox(0, 0, 0, 0); }
void*	TexDataAt( int x, int y )	{ return ((char*) TexData) + y * TexStride + x * xoTexFormatBytesPerPixel(TexFormat); }
void*	TexDataAtLine( int y )		{ return ((char*) TexData) + y * TexStride; }
size_t	TexBytesPerPixel() const	{ return xoTexFormatBytesPerPixel(TexFormat); }
void	FlipVertical();
};

// Base of GL and DX shader programs
class xoProgBase
{
public:
};

enum xoShaders
{
xoShaderInvalid,
xoShaderFill,
xoShaderFillTex,
xoShaderRect,
xoShaderTextRGB,
xoShaderTextWhole
// We may someday want to have slots down here available for application-defined custom shaders
};

// A single instance of this is accessible via xoGlobal()
struct xoGlobalStruct
{
int							TargetFPS;
int							NumWorkerThreads;		// Read-only. Set during xoInitialize().
int							MaxSubpixelGlyphSize;	// Maximum font size where we will use sub-pixel glyph textures
bool						PreferOpenGL;			// Prefer OpenGL over DirectX. If this is true, then on Windows OpenGL will be tried first.
bool						EnableVSync;			// This is only respected during device initialization, so you must set it at application start. It raises latency noticeably. This has no effect on DirectX windowed rendering.
bool						EnableSubpixelText;		// Enable sub-pixel text rendering. Assumes pixels are the standard RGB layout. Enabled by default on Windows desktop only.
bool						EnableSRGBFramebuffer;	// Enable sRGB framebuffer (implies linear blending)
bool						EnableKerning;			// Enable kerning on text
bool						RoundLineHeights;		// Round text line heights to integer amounts, so that text line separation is not subject to sub-pixel positioning differences.
bool						SnapBoxes;				// Round certain boxes up to integer pixels.
// From the perspective of having the exact same layout on multiple devices, it seems desirable to operate
// in subpixel coordinates always. However, this ends up producing ugly visuals, for example when
// you have a box with a single pixel border, and it is not aligned to a pixel boundary, then you get
// the border smudged across two pixels.
bool						SnapSubpixelHorzText;	// When rendering subpixel text, snap glyphs to whole pixels, instead of sub-pixel horizontal positioning.
// This not only determines layout behaviour, but also how our subpixel glyphs are rasterized.
//bool						EmulateGammaBlending;	// Only applicable when EnableSRGBFramebuffer = true, this tries to emulate gamma-space blending. You would turn this on to get consistent blending on all devices. FAILED EXPERIMENT - BAD IDEA.
float						SubPixelTextGamma;		// Tweak freetype's gamma when doing sub-pixel text rendering. Should be no need to use anything other than 1.0
float						WholePixelTextGamma;	// Tweak freetype's gamma when doing whole-pixel text rendering. Should be no need to use anything other than 1.0
float						EpToPixel;				// Eye Pixel to Pixel.
xoTextureID					MaxTextureID;			// Used to test texture ID wrap-around. Were it not for testing, this could be 2^32 - 1
xoColor						ClearColor;				// glClearColor

// Debugging flags. Enabling these should make debugging easier.
// Some of them may turn out to have a small enough performance hit that you can
// leave them turned on always.
// NOPE.. it's just too confusing to have this optional. It's always on.
//bool						DebugZeroClonedChildList;	// During a document clone, zero out ChildByInternalID before populating. This will ensure that gaps are NULL instead of random memory.

pvect<xoDocGroup*>			Docs;				// Only Main thread is allowed to touch this.
TAbcQueue<xoDocGroup*>		DocAddQueue;		// Documents requesting addition
TAbcQueue<xoDocGroup*>		DocRemoveQueue;		// Documents requesting removal
TAbcQueue<xoEvent>			EventQueue;			// Global event queue, consumed by the one-and-only UI thread
TAbcQueue<xoJob>			JobQueue;			// Global job queue, consumed by the worker thread pool
xoFontStore*				FontStore;			// All fonts known to the system.
xoGlyphCache*				GlyphCache;			// This might have to move into a less global domain.
};

XOAPI xoGlobalStruct*	xoGlobal();
XOAPI void				xoInitialize();
XOAPI void				xoShutdown();
XOAPI void				xoProcessDocQueue();
XOAPI void				xoParseFail( const char* msg, ... );
XOAPI void				XOTRACE( const char* msg, ... );
XOAPI void				NUTIME( const char* msg, ... );
#if XO_PLATFORM_WIN_DESKTOP
XOAPI void				xoRunWin32MessageLoop();
#elif XO_PLATFORM_LINUX_DESKTOP
XOAPI void				xoRunXMessageLoop();
#endif

// Various tracing options. Uncomment these to enable tracing of that class of events.
//#define XOTRACE_RENDER_ENABLE
#define XOTRACE_LAYOUT_WARNINGS_ENABLE
//#define XOTRACE_LAYOUT_VERBOSE_ENABLE
//#define XOTRACE_EVENTS_ENABLE
//#define XOTRACE_LATENCY_ENABLE

#ifdef XOTRACE_RENDER_ENABLE
#define XOTRACE_RENDER(msg, ...) NUTIME(msg, ##__VA_ARGS__)
#else
#define XOTRACE_RENDER(msg, ...) ((void)0)
#endif

#ifdef XOTRACE_LAYOUT_WARNINGS_ENABLE
#define XOTRACE_LAYOUT_WARNING(msg, ...) NUTIME(msg, ##__VA_ARGS__)
#else
#define XOTRACE_LAYOUT_WARNING(msg, ...) ((void)0)
#endif

#ifdef XOTRACE_LAYOUT_VERBOSE_ENABLE
#define XOTRACE_LAYOUT_VERBOSE(msg, ...) NUTIME(msg, ##__VA_ARGS__)
#else
#define XOTRACE_LAYOUT_VERBOSE(msg, ...) ((void)0)
#endif

#ifdef XOTRACE_EVENTS_ENABLE
#define XOTRACE_EVENTS(msg, ...) NUTIME(msg, ##__VA_ARGS__)
#else
#define XOTRACE_EVENTS(msg, ...) ((void)0)
#endif

#ifdef XOTRACE_LATENCY_ENABLE
#define XOTRACE_LATENCY(msg, ...) NUTIME(msg, ##__VA_ARGS__)
#else
#define XOTRACE_LATENCY(msg, ...) ((void)0)
#endif


// A memory pool
class XOAPI xoPool
{
public:
xoPool();
~xoPool();

void	SetChunkSize( size_t size );

void*	Alloc( size_t bytes, bool zeroInit );

template<typename T>
T*		AllocT( bool zeroInit ) { return (T*) Alloc( sizeof(T), zeroInit ); }

template<typename T>
T*		AllocNT( size_t count, bool zeroInit ) { return (T*) Alloc( count * sizeof(T), zeroInit ); }

void	FreeAll();
void	FreeAllExceptOne();

protected:
size_t			ChunkSize;
size_t			TopRemain;
podvec<void*>	Chunks;
podvec<void*>	BigBlocks;
};

// A vector that allocates its storage from a xoPool object
template<typename T>
class xoPoolArray
{
public:
xoPool*		Pool;
T*			Data;
uintp		Count;
uintp		Capacity;

xoPoolArray()
{
Pool = NULL;
Data = NULL;
Count = 0;
Capacity = 0;
}

xoPoolArray& operator+=( const T& v )
{
add( &v );
return *this;
}

T& operator[]( intp _i )
{
return Data[_i];
}

const T& operator[]( intp _i ) const
{
return Data[_i];
}

T& back()
{
return Data[Count - 1];
}

const T& back() const
{
return Data[Count - 1];
}

void pop()
{
XOASSERTDEBUG(Count > 0);
Count--;
}

T& add( const T* v = NULL )
{
if ( Count == Capacity )
grow();

if ( v )
Data[Count++] = *v;
else
Data[Count++] = T();

return Data[Count - 1];
}

intp size() const { return Count; }

void resize( intp n )
{
if ( n != Count )
{
clear();
if ( n != 0 )
{
growto( n );
Count = n;
}
}
}

void reserve( intp n )
{
if ( n > (intp) Capacity )
growto( n );
}

void clear()
{
Data = NULL;
Count = 0;
Capacity = 0;
}

protected:
void grow()
{
uintp ncap = std::max(Capacity * 2, (uintp) 2);
growto( ncap );
}

void growto( uintp ncap )
{
T* ndata = (T*) Pool->Alloc( sizeof(T) * ncap, false );
XOCHECKALLOC(ndata);
memcpy( ndata, Data, sizeof(T) * Capacity );
memset( ndata + Capacity, 0, sizeof(T) * (ncap - Capacity) );
Capacity = ncap;
Data = ndata;
}
};

// Last-in-first-out buffer. This is used instead of stack storage.
// There is a hard limit here - the buffer size you request is
// allocated up front. The assumed usage is identical to that of a stack.
// This was created to lessen the burden on the actual thread stack during
// layout.
// You must free objects in the reverse order that you allocated them.
class XOAPI xoLifoBuf
{
public:
xoLifoBuf();
xoLifoBuf( size_t size );	// This simply calls Init(size)
~xoLifoBuf();

// Initialize the buffer.
// This will panic if the buffer is not empty.
void	Init( size_t size );

// Allocate a new item.
// It is legal to allocate 0 bytes. You can then us Realloc to grow. Regardless
// of the size of your initial allocation, you must always call Free() on anything
// that you have Alloc'ed.
// This will panic if the buffer size is exhausted.
void*	Alloc( size_t bytes );

// Grow the most recently allocated item to the specified size.
// This will panic if buf is not the most recently allocated item, or if the buffer size is exhausted.
void	Realloc( void* buf, size_t bytes );

// This is a less safe version of Realloc. The only check it performs is whether we will run out of space.
void	GrowLast( size_t moreBytes );

// Free the most recently allocated item
// This will panic if buf is not the most recently allocated item, and buf is not null.
void	Free( void* buf );

private:
podvec<intp>	ItemSizes;
void*			Buffer;
intp			Size;
intp			Pos;
};

// Vector that uses xoLifoBuf for storage. This is made for PODs - it does not do
// object construction or destruction.
template<typename T>
class xoLifoVector
{
public:
xoLifoVector( xoLifoBuf& lifo )
{
Lifo = &lifo;
}
~xoLifoVector()
{
Lifo->Free( Data );
}

void AddN( intp numElementsToAdd )
{
if ( Data == nullptr )
Data = (T*) Lifo->Alloc( numElementsToAdd * sizeof(T) );
else
Lifo->GrowLast( numElementsToAdd * sizeof(T) );
Count += numElementsToAdd;
}

void Push( const T& t )
{
intp c = Count;
AddN( 1 );
Data[c] = t;
}

T& Back()
{
return Data[Count - 1];
}

xoLifoVector& operator+=( const T& t )
{
Push( t );
return *this;
}

T& operator[]( intp i ) { return Data[i]; }

private:
xoLifoBuf*	Lifo;
T*			Data = nullptr;
intp		Count = 0;
};


template<typename T>
void xoClonePvectPrepare( pvect<T>& dst, const pvect<T>& src, xoPool* pool )
{
if ( src.count != 0 ) dst.data = (void**) pool->Alloc( sizeof(T) * src.count, true );
dst.count = src.count;
dst.capacity = src.capacity;
}

template<typename T>
void xoClonePodvecPrepare( podvec<T>& dst, const podvec<T>& src, xoPool* pool )
{
if ( src.count != 0 ) dst.data = (T*) pool->Alloc( sizeof(T) * src.count, true );
dst.count = src.count;
dst.capacity = src.capacity;
}

//template<typename T>
//void xoClonePodvecWithCloneFastInto( podvec<T>& dst, const podvec<T>& src, xoPool* pool )
//{
//	xoClonePodvecPrepare( dst, src, pool );
//	for ( uintp i = 0; i < src.count; i++ )
//	{
//		src[i].CloneFastInto( dst[i], pool );
//	}
//}

template<typename T>
void xoClonePodvecWithMemCopy( podvec<T>& dst, const podvec<T>& src, xoPool* pool )
{
xoClonePodvecPrepare( dst, src, pool );
memcpy( dst.data, src.data, src.size() * sizeof(T) );
}

//template<typename T, size_t N>
//void xoCloneStaticArrayWithCloneFastInto( T (&dst)[N], const T (&src)[N], xoPool* pool )
//{
//	for ( size_t i = 0; i < N; i++ )
//		src[i].CloneFastInto( dst[i], pool );
//}

template<typename T, size_t N>
void xoCloneStaticArrayWithCloneSlowInto( T (&dst)[N], const T (&src)[N] )
{
for ( size_t i = 0; i < N; i++ )
src[i].CloneSlowInto( dst[i] );
}



// It will be good if we can keep these inside 32 bits, for easy masking of handlers. If not, just use as many 32-bit words as necessary.
enum xoEvents
{
xoEventTouch		= BIT(0),
xoEventMouseMove	= BIT(1),
xoEventWindowSize	= BIT(2),
xoEventTimer		= BIT(3),
xoEventClick		= BIT(4),
};

/* User interface event (keyboard, mouse, touch, etc).
*/
class XOAPI xoEvent
{
public:
xoDocGroup*		DocGroup;
void*			Context;
xoDomEl*		Target;
xoEvents		Type;
int				PointCount;					// Mouse = 1	Touch >= 1
xoVec2f			Points[XO_MAX_TOUCHES];

xoEvent();
~xoEvent();

void MakeWindowSize( int w, int h );
};

typedef std::function<bool(const xoEvent& ev)> xoEventHandlerLambda;

typedef bool (*xoEventHandlerF)(const xoEvent& ev);

XOAPI bool xoEventHandler_LambdaStaticFunc(const xoEvent& ev);

enum xoEventHandlerFlags
{
xoEventHandlerFlag_IsLambda = 1,
};

class XOAPI xoEventHandler
{
public:
uint32				Mask;
uint32				Flags;
void*				Context;
xoEventHandlerF		Func;

xoEventHandler();
~xoEventHandler();

bool	Handles( xoEvents ev ) const	{ return !!(Mask & ev); }
bool	IsLambda() const				{ return !!(Flags & xoEventHandlerFlag_IsLambda); }
void	SetLambda()						{ Flags |= xoEventHandlerFlag_IsLambda; }
};



// The list of styles that are inherited by child nodes lives in xoInheritedStyleCategories

// Represents a size that is zero, pixels, eye pixels, points, percent.
// TODO: em
// Zero is represented as 0 pixels
// See "layout" documentation for explanation of units.
struct XOAPI xoSize
{
enum	Types { NONE = 0, PX, PT, EP, PERCENT };
float 	Val;
Types 	Type;

static xoSize	Make( Types t, float v )	{ xoSize s = {v, t}; return s; }
static xoSize	Percent( float v )			{ xoSize s = {v, PERCENT}; return s; }
static xoSize	Points( float v )			{ xoSize s = {v, PT}; return s; }
static xoSize	Pixels( float v )			{ xoSize s = {v, PX}; return s; }
static xoSize	EyePixels( float v )		{ xoSize s = {v, EP}; return s; }
static xoSize	Zero()						{ xoSize s = {0, PX}; return s; }
static xoSize	Null()						{ xoSize s = {0, NONE}; return s; }

static bool		Parse( const char* s, intp len, xoSize& v );
};

// Convenience struct used during layout computation
struct XOAPI xoStyleBox
{
// This order (left,top,right,bottom) must be consistent with the order presented inside XO_STYLE_DEFINE
union
{
struct
{
xoSize	Left, Top, Right, Bottom;
};
xoSize All[4];
};

static bool			Parse( const char* s, intp len, xoStyleBox& v );
static xoStyleBox	Make( xoSize left, xoSize top, xoSize right, xoSize bottom )	{ xoStyleBox b; b.Left = left; b.Top = top; b.Right = right; b.Bottom = bottom; return b; }
static xoStyleBox	MakeUniform( xoSize all )										{ xoStyleBox b; b.Left = all; b.Top = all; b.Right = all; b.Bottom = all; return b; }
static xoStyleBox	MakeZero() { xoStyleBox b; b.SetZero(); return b; }
void SetZero() { Left = Top = Right = Bottom = xoSize::Pixels(0); }
};

enum xoDisplayType
{
xoDisplayBlock,
xoDisplayInline
};

enum xoFlowDirection
{
xoFlowDirectionNormal,
xoFlowDirectionReversed
};

enum xoFlowAxis
{
xoFlowAxisVertical,		// Vertical is the default
xoFlowAxisHorizontal
};

enum xoTextAlignVertical
{
xoTextAlignVerticalBaseline,	// Baseline is default
xoTextAlignVerticalTop			// This is unlikely to be useful, but having it proves that we *could* make other rules if proved useful
};

enum xoVerticalBindings
{
xoVerticalBindingNULL,
xoVerticalBindingTop,			// Top of parent's content box
xoVerticalBindingCenter,		// Center of parent's content box
xoVerticalBindingBottom,		// Bottom of parent's content box
xoVerticalBindingBaseline,		// Parent's baseline
};

enum xoHorizontalBindings
{
xoHorizontalBindingNULL,
xoHorizontalBindingLeft,		// Left of parent's content box
xoHorizontalBindingCenter,		// Center of parent's content box
xoHorizontalBindingRight,		// Right of parent's content box
};

enum xoPositionType
{
// All of these definitions are the same as HTML's
xoPositionStatic,		// Default, regular position
xoPositionAbsolute,		// Absolute, relative to previous explicitly parent that was anything other than "Static". Does not affect flow of subsequent siblings.
xoPositionRelative,		// Like Absolute, but does affect flow. Flow is the "ghost" of where we would have been, before being moved relatively.
xoPositionFixed,		// Fixed, according to root device coordinate system. In other words, completely independent of DOM hierarchy.
};

enum xoBoxSizeType
{
xoBoxSizeContent,
xoBoxSizeBorder,
xoBoxSizeMargin			// Created initially for the <body> element
};

enum xoBreakType
{
xoBreakNULL,
xoBreakBefore,			// Break flow before element
xoBreakAfter			// Break flow after element
};

// The following attributes are "bind sources". You bind a position of your own to a position on your parent node.
// The "bind targets" that you can bind to on your parent node are the same properties that can be used as bind sources.
// So if you bind left:right, then you are binding your left edge to your parent content box's right edge.
// If you bind vcenter:vcenter, then you bind your vertical center to the vertical center of your parent context box.
// * Left
// * HCenter
// * Right
// * Top
// * VCenter
// * Bottom
// * Baseline

// The order of the box components (left,top,right,bottom) must be consistent with the order in xoStyleBox
// In addition, all 'box' types must fall between Margin_Left and Border_Bottom. This is simply for sanity. It is verified
// inside xoStyle.SetBox()
#define XO_STYLE_DEFINE \
XX(NULL, 0) \
XY(Color) \
XY(Display) \
XY(Background) \
XY(BackgroundImage) \
XY(Text_Align_Vertical) \
\
XY(Break) \
XY(Dummy3_UseMe) \
\
XY(Margin_Left) \
XY(Margin_Top) \
XY(Margin_Right) \
XY(Margin_Bottom) \
\
XY(Padding_Left) \
XY(Padding_Top) \
XY(Padding_Right) \
XY(Padding_Bottom) \
\
XY(Border_Left) \
XY(Border_Top) \
XY(Border_Right) \
XY(Border_Bottom) \
\
XY(BorderColor_Left) \
XY(BorderColor_Top) \
XY(BorderColor_Right) \
XY(BorderColor_Bottom) \
\
XY(Width) \
XY(Height) \
\
XY(Top) \
XY(VCenter) \
XY(Bottom) \
XY(Baseline) \
XY(Left) \
XY(HCenter) \
XY(Right) \
\
XY(FontSize) \
XY(FontFamily) \
\
XY(BorderRadius) \
XY(Position) \
XY(Flow_Axis) \
XY(Flow_Direction_Horizontal) \
XY(Flow_Direction_Vertical) \
XY(BoxSizing) \
XY(END)

#define XX(a,b) xoCat##a = b,
#define XY(a) xoCat##a,
enum xoStyleCategories {
XO_STYLE_DEFINE
xoCatFIRST = xoCatColor,
};
#undef XX
#undef XY

static_assert( xoCatMargin_Left % 4 == 0, "Start of boxes must be multiple of 4" );

inline xoStyleCategories xoCatMakeBaseBox( xoStyleCategories c ) { return (xoStyleCategories) (c & ~3); }

// Styles that are inherited by default
// Generally it is text styles that are inherited
// Inheritance means that child nodes inherit the styles of their parents
const int						xoNumInheritedStyleCategories = 4;
extern const xoStyleCategories	xoInheritedStyleCategories[xoNumInheritedStyleCategories];

/* Single style attribute (such as Margin-Left, Width, FontSize, etc).
This must be zero-initializable (i.e. with memset(0)).
It must remain small.
Currently, sizeof(xoStyleAttrib) = 8.
*/
class XOAPI xoStyleAttrib
{
public:
enum Flag
{
// This means that the attribute takes its value from its closest ancestor in the DOM tree.
// Some styles are inherited by default (the list specified inside xoInheritedStyleCategories).
FlagInherit = 1
};

uint8				Category;		// type xoStyleCategories
uint8				SubType;
uint8				Flags;
uint8				Unused2;
union
{
uint32			ValU32;
float			ValF;
};

xoStyleAttrib();

void SetInherit( xoStyleCategories cat );

void SetColor( xoStyleCategories cat, xoColor val )				{ SetU32( cat, val.u ); }
void SetSize( xoStyleCategories cat, xoSize val )				{ SetWithSubtypeF( cat, val.Type, val.Val ); }
void SetDisplay( xoDisplayType val )							{ SetU32( xoCatDisplay, val ); }
void SetBorderRadius( xoSize val )								{ SetSize( xoCatBorderRadius, val ); }
void SetPosition( xoPositionType val )							{ SetU32( xoCatPosition, val ); }
void SetFont( xoFontID val )									{ SetU32( xoCatFontFamily, val ); }
void SetBackgroundImage( const char* image, xoDoc* doc )		{ SetString( xoCatBackgroundImage, image, doc ); }
void SetBreak( xoBreakType type )								{ SetU32( xoCatBreak, type); }
void SetFlowAxis( xoFlowAxis axis )								{ SetU32( xoCatFlow_Axis, axis ); }
void SetFlowDirectionHorizonal( xoFlowDirection dir )			{ SetU32( xoCatFlow_Direction_Horizontal, dir ); }
void SetFlowDirectionVertical( xoFlowDirection dir )			{ SetU32( xoCatFlow_Direction_Vertical, dir ); }
void SetBoxSizing( xoBoxSizeType type )							{ SetU32( xoCatBoxSizing, type ); }
void SetTextAlignVertical( xoTextAlignVertical align )			{ SetU32( xoCatText_Align_Vertical, align ); }
void SetLeft( xoHorizontalBindings bind )						{ SetU32( xoCatLeft, bind ); }
void SetHCenter( xoHorizontalBindings bind )					{ SetU32( xoCatHCenter, bind ); }
void SetRight( xoHorizontalBindings bind )						{ SetU32( xoCatRight, bind ); }
void SetTop( xoVerticalBindings bind )							{ SetU32( xoCatTop, bind ); }
void SetVCenter( xoVerticalBindings bind )						{ SetU32( xoCatVCenter, bind ); }
void SetBottom( xoVerticalBindings bind )						{ SetU32( xoCatBottom, bind ); }
void SetBaseline( xoVerticalBindings bind )						{ SetU32( xoCatBaseline, bind ); }

// Generic Set() that is used by template code
void Set( xoStyleCategories cat, xoColor val )					{ SetColor( cat, val ); }
void Set( xoStyleCategories cat, xoSize val )					{ SetSize( cat, val ); }
void Set( xoStyleCategories cat, xoDisplayType val )			{ SetDisplay( val ); }
void Set( xoStyleCategories cat, xoPositionType val )			{ SetPosition( val ); }
void Set( xoStyleCategories cat, xoBreakType val )				{ SetBreak( val ); }
void Set( xoStyleCategories cat, xoFlowAxis val )				{ SetFlowAxis( val ); }
void Set( xoStyleCategories cat, xoFlowDirection val )			{ SetU32( cat, val ); }
void Set( xoStyleCategories cat, xoBoxSizeType val )			{ SetBoxSizing( val ); }
void Set( xoStyleCategories cat, xoTextAlignVertical val )		{ SetU32( cat, val ); }
void Set( xoStyleCategories cat, xoHorizontalBindings val )		{ SetU32( cat, val ); }
void Set( xoStyleCategories cat, xoVerticalBindings val )		{ SetU32( cat, val ); }
void Set( xoStyleCategories cat, xoFontID val )					{ SetFont( val ); }
void Set( xoStyleCategories cat, const char* val, xoDoc* doc )	{ SetString( cat, val, doc ); }

bool					IsNull() const							{ return Category == xoCatNULL; }
bool					IsInherit() const						{ return Flags == FlagInherit; }

xoStyleCategories		GetCategory() const						{ return (xoStyleCategories) Category; }
xoSize					GetSize() const							{ return xoSize::Make( (xoSize::Types) SubType, ValF ); }
xoColor					GetColor() const						{ return xoColor::Make( ValU32 ); }
xoDisplayType			GetDisplayType() const					{ return (xoDisplayType) ValU32; }
xoPositionType			GetPositionType() const					{ return (xoPositionType) ValU32; }
xoBreakType				GetBreakType() const					{ return (xoBreakType) ValU32; }
int						GetStringID() const						{ return (int) ValU32; }
xoFlowAxis				GetFlowAxis() const						{ return (xoFlowAxis) ValU32; }
xoFlowDirection			GetFlowDirectionMajor() const			{ return (xoFlowDirection) ValU32; }
xoFlowDirection			GetFlowDirectionMinor() const			{ return (xoFlowDirection) ValU32; }
xoBoxSizeType			GetBoxSizing() const					{ return (xoBoxSizeType) ValU32; }
xoTextAlignVertical		GetTextAlignVertical() const			{ return (xoTextAlignVertical) ValU32; }
xoHorizontalBindings	GetHorizontalBinding() const			{ return (xoHorizontalBindings) ValU32; }
xoVerticalBindings		GetVerticalBinding() const				{ return (xoVerticalBindings) ValU32; }

const char*				GetBackgroundImage( xoStringTable* strings ) const;
xoFontID				GetFont() const;

protected:
void SetString( xoStyleCategories cat, const char* str, xoDoc* doc );
void SetU32( xoStyleCategories cat, uint32 val );
void SetWithSubtypeU32( xoStyleCategories cat, uint8 subtype, uint32 val );
void SetWithSubtypeF( xoStyleCategories cat, uint8 subtype, float val );
};

/* Collection of style attributes (border-width-left, color, etc)
This container is simple and list-based.
There is a different container called xoStyleSet that is more performant,
built for use during rendering.
*/
class XOAPI xoStyle
{
public:
podvec<xoStyleAttrib>	Attribs;

bool					Parse( const char* t, xoDoc* doc );
bool					Parse( const char* t, intp maxLen, xoDoc* doc );
const xoStyleAttrib*	Get( xoStyleCategories cat ) const;
void					SetBox( xoStyleCategories cat, xoStyleBox val );
void					GetBox( xoStyleCategories cat, xoStyleBox& box ) const;
void					SetUniformBox( xoStyleCategories cat, xoStyleAttrib val );
void					SetUniformBox( xoStyleCategories cat, xoColor color );
void					SetUniformBox( xoStyleCategories cat, xoSize size );
void					Set( xoStyleAttrib attrib );
void					Set( xoStyleCategories cat, xoStyleBox val );	// This overload is identical to SetBox, but needs to be present for templated parsing functions
//void					Compute( const xoDoc& doc, const xoDomEl& node );
void					Discard();
void					CloneSlowInto( xoStyle& c ) const;
void					CloneFastInto( xoStyle& c, xoPool* pool ) const;

// Setter functions with 2 parameters
#define NUSTYLE_SETTERS_2P \
XX(BackgroundColor,		xoColor,	SetColor,	xoCatBackground) \
XX(Width,				xoSize,		SetSize,	xoCatWidth) \
XX(Height,				xoSize,		SetSize,	xoCatHeight) \
XX(Left,				xoSize,		SetSize,	xoCatLeft) \
XX(Right,				xoSize,		SetSize,	xoCatRight) \
XX(Top,					xoSize,		SetSize,	xoCatTop) \
XX(Bottom,				xoSize,		SetSize,	xoCatBottom) \

// Setter functions with 1 parameter
#define NUSTYLE_SETTERS_1P \
XX(Position,			xoPositionType,	SetPosition) \

#define XX(name, type, setfunc, cat)	void Set##name( type value );
NUSTYLE_SETTERS_2P
#undef XX

#define XX(name, type, setfunc)			void Set##name( type value );
NUSTYLE_SETTERS_1P
#undef XX

protected:
//void					MergeInZeroCopy( int n, const xoStyle** src );
void					SetBoxInternal( xoStyleCategories catBase, xoStyleBox val );
};

FHASH_SETUP_CLASS_CTOR_DTOR(xoStyle, xoStyle);

/* A bag of styles in a performant container.

Analysis of storage (assuming xoCatEND = 128)

Number of attributes	Size of Lookup			Size of Attribs		Total marginal size
1 << 2 = 4				128 * 2 / 8 = 32		4 * 8   = 32		32 + 32    = 64
1 << 4 = 16				128 * 4 / 8 = 64		16 * 8  = 128		64 + 128   = 192
1 << 8 = 256			128 * 8 / 8 = 128		256 * 8 = 2048		128 + 2048 = 2176

One very significant optimization that remains here is to not grow Attrib[] so heavily.
Growing from 16 to 256 is an insane leap.

Idea: There are some attributes that need only a few bits. Instead of packing each of these
into 8 bytes, we can instead store groups of attributes in special 8 byte blocks.

More Idea: I think I might end up writing a very specialized container for this stuff.. where we
separate things out into really tight bags of properties. But we'll wait until it's a bottleneck.

*/
class XOAPI xoStyleSet
{
public:
static const uint32 InitialBitsPerSlot = 2;		// 1 << 2 = 4, is our lowest non-empty size
static const uint32 SlotOffset = 1;				// We need to reserve zero for the "empty" state of a slot

xoStyleSet();		// Simply calls Reset()
~xoStyleSet();		// Destructor does nothing

void			Set( int n, const xoStyleAttrib* attribs, xoPool* pool );
void			Set( const xoStyleAttrib& attrib, xoPool* pool );
xoStyleAttrib	Get( xoStyleCategories cat ) const;
bool			Contains( xoStyleCategories cat ) const;
void			Reset();

protected:
typedef void  (*SetSlotFunc) ( void* lookup, xoStyleCategories cat, int32 slot );
typedef int32 (*GetSlotFunc) ( const void* lookup, xoStyleCategories cat );

void*			Lookup;			// Variable bit-width table that indexes into Attribs. Size is always xoCatEND.
xoStyleAttrib*	Attribs;		// The Category field in here is wasted.
int32			Count;			// Size of Attribs
int32			Capacity;		// Capacity of Attribs
uint32			BitsPerSlot;	// Number of bits in each slot of Lookup. Our possible sizes are 2,4,8.
SetSlotFunc		SetSlotF;
GetSlotFunc		GetSlotF;

void			Grow( xoPool* pool );
int32			GetSlot( xoStyleCategories cat ) const;
void			SetSlot( xoStyleCategories cat, int32 slot );
void			DebugCheckSanity() const;

static void		MigrateLookup( const void* lutsrc, void* lutdst, GetSlotFunc getter, SetSlotFunc setter );

template<uint32 BITS_PER_SLOT>
static void		TSetSlot( void* lookup, xoStyleCategories cat, int32 slot );

template<uint32 BITS_PER_SLOT>
static int32	TGetSlot( const void* lookup, xoStyleCategories cat );

static int32	GetSlot2( const void* lookup, xoStyleCategories cat );
static int32	GetSlot4( const void* lookup, xoStyleCategories cat );
static int32	GetSlot8( const void* lookup, xoStyleCategories cat );
static void		SetSlot2( void* lookup, xoStyleCategories cat, int32 slot );
static void		SetSlot4( void* lookup, xoStyleCategories cat, int32 slot );
static void		SetSlot8( void* lookup, xoStyleCategories cat, int32 slot );

// The -1 here is for SlotOffset
static int32	CapacityAt( uint32 bitsPerSlot )	{ return (1 << bitsPerSlot) - 1; }

};

// The set of style information that is used by the renderer
// This is baked in by the Layout engine.
// This struct is present in every single xoRenderDomNode, so it pays to keep it tight.
class XOAPI xoStyleRender
{
public:
xoBox16 BorderSize;
xoBox16 Padding;			// This is probably not necessary. See log entry from 2014-08-02
xoColor BackgroundColor;
xoColor BorderColor;
int		BackgroundImageID;
float	BorderRadius;

xoStyleRender() { memset(this, 0, sizeof(*this)); }
};

/* Store all style classes in one table, that is owned by one document.
This allows us to reference styles by a 32-bit integer ID instead of by name.
*/
class XOAPI xoStyleTable
{
public:
xoStyleTable();
~xoStyleTable();

void			AddDummyStyleZero();
void			Discard();
xoStyle*		GetOrCreate( const char* name );
const xoStyle*	GetByID( xoStyleID id ) const;
xoStyleID		GetStyleID( const char* name );
void			CloneSlowInto( xoStyleTable& c ) const;					// Does not clone NameToIndex
void			CloneFastInto( xoStyleTable& c, xoPool* pool ) const;	// Does not clone NameToIndex

protected:
podvec<xoString>			Names;		// Names and Styles are parallels
podvec<xoStyle>				Styles;
podvec<int>					UnusedSlots;
fhashmap<xoString, int>		NameToIndex;
};


XOAPI bool xoParseDisplayType( const char* s, intp len, xoDisplayType& t );
XOAPI bool xoParsePositionType( const char* s, intp len, xoPositionType& t );
XOAPI bool xoParseBreakType( const char* s, intp len, xoBreakType& t );
XOAPI bool xoParseFlowAxis( const char* s, intp len, xoFlowAxis& t );
XOAPI bool xoParseFlowDirection( const char* s, intp len, xoFlowDirection& t );
XOAPI bool xoParseBoxSize( const char* s, intp len, xoBoxSizeType& t );
XOAPI bool xoParseTextAlignVertical( const char* s, intp len, xoTextAlignVertical& t );
XOAPI bool xoParseHorizontalBinding( const char* s, intp len, xoHorizontalBindings& t );
XOAPI bool xoParseVerticalBinding( const char* s, intp len, xoVerticalBindings& t );
XOAPI bool xoParseBorder( const char* s, intp len, xoStyle& style );




/* DOM node in the tree.
*/
class XOAPI xoDomEl
{
public:
xoDomEl( xoDoc* doc, xoTag tag );
virtual ~xoDomEl();

virtual void			SetText( const char* txt ) = 0;		// Replace all children with a single xoTagText child, or set internal text if 'this' is xoTagText.
virtual const char*		GetText() const = 0;				// Reverse behaviour of SetText()
virtual void			CloneSlowInto( xoDomEl& c, uint cloneFlags ) const = 0;
virtual void			ForgetChildren() = 0;

xoInternalID					GetInternalID() const		{ return InternalID; }
xoTag							GetTag() const				{ return Tag; }
xoDoc*							GetDoc() const				{ return Doc; }
uint32							GetVersion() const			{ return Version; }

//void			CloneFastInto( xoDomEl& c, xoPool* pool, uint cloneFlags ) const;

void			SetInternalID( xoInternalID id )			{ InternalID = id; }	// Used by xoDoc at element creation time.
void			SetDoc( xoDoc* doc )						{ Doc = doc; }			// Used by xoDoc at element creation and destruction time.
void			SetDocRoot()								{ Tag = xoTagBody; }	// Used by xoDoc at initialization time.

protected:
xoDoc*					Doc;			// Owning document
xoInternalID			InternalID;		// Internal 32-bit ID that is used to keep track of an object (memory address is not sufficient)
xoTag					Tag;			// Tag, such <div>, etc
uint32					Version;		// Monotonic integer used to detect modified nodes

void			IncVersion();
void			CloneSlowIntoBase( xoDomEl& c, uint cloneFlags ) const;
};


/* DOM node that is not text
It is vital that this data structure does not grow much bigger than this.
Right now it's 128 bytes on Windows x64.
*/
class XOAPI xoDomNode : public xoDomEl
{
DISALLOW_COPY_AND_ASSIGN(xoDomNode);
public:
xoDomNode( xoDoc* doc, xoTag tag );
virtual ~xoDomNode();

virtual void			SetText( const char* txt ) override;
virtual const char*		GetText() const override;
virtual void			CloneSlowInto( xoDomEl& c, uint cloneFlags ) const override;
virtual void			ForgetChildren() override;

const pvect<xoDomEl*>&			GetChildren() const			{ return Children; }
podvec<xoStyleID>&				GetClassesMutable()			{ IncVersion(); return Classes; }
const podvec<xoStyleID>&		GetClasses() const			{ return Classes; }
const podvec<xoEventHandler>&	GetHandlers() const			{ return Handlers; }
const xoStyle&					GetStyle() const			{ return Style; }

xoDomEl*		AddChild( xoTag tag );
xoDomNode*		AddNode( xoTag tag );
xoDomText*		AddText( const char* txt = nullptr );
void			RemoveChild( xoDomEl* c );
void			RemoveAllChildren();
intp			ChildCount() const { return Children.size(); }
xoDomEl*		ChildByIndex( intp index );
const xoDomEl*	ChildByIndex( intp index ) const;
void			Discard();

// Replace all child elements with the given xml-like string. Returns empty string on success, or error message.
xoString		Parse( const char* src );
xoString		ParseAppend( const char* src );	// Same as Parse, but append to node
xoString		ParseAppend( const xoStringRaw& src );

bool			StyleParse( const char* t, intp maxLen = INT32MAX );
bool			StyleParsef( const char* t, ... );
// This is here for experiments. Future work needs a better performing method for setting just one attribute of the style.
void			HackSetStyle( const xoStyle& style );

// Classes
void			AddClass( const char* klass );
void			RemoveClass( const char* klass );

// Events
void			AddHandler( xoEvents ev, xoEventHandlerF func, void* context = NULL );
void			AddHandler( xoEvents ev, xoEventHandlerLambda lambda );
bool			HandlesEvent( xoEvents ev ) const { return !!(AllEventMask & ev); }

void			OnTouch( xoEventHandlerF func, void* context )				{ AddHandler( xoEventTouch, func, context ); }
void			OnMouseMove( xoEventHandlerF func, void* context )			{ AddHandler( xoEventMouseMove, func, context ); }
void			OnClick( xoEventHandlerF func, void* context )				{ AddHandler( xoEventClick, func, context ); }
void			OnTimer( xoEventHandlerF func, void* context )				{ AddHandler( xoEventTimer, func, context ); }

void			OnTouch( xoEventHandlerLambda lambda )						{ AddHandler( xoEventTouch, lambda ); }
void			OnMouseMove( xoEventHandlerLambda lambda )					{ AddHandler( xoEventMouseMove, lambda ); }
void			OnClick( xoEventHandlerLambda lambda )						{ AddHandler( xoEventClick, lambda ); }
void			OnTimer( xoEventHandlerLambda lambda )						{ AddHandler( xoEventTimer, lambda ); }

protected:
uint32					AllEventMask;
xoStyle					Style;			// Styles that override those referenced by the Tag and the Classes.
podvec<xoEventHandler>	Handlers;
pvect<xoDomEl*>			Children;
podvec<xoStyleID>		Classes;		// Classes of styles

void			RecalcAllEventMask();
void			AddHandler( xoEvents ev, xoEventHandlerF func, bool isLambda, void* context );
};


class XOAPI xoDomText : public xoDomEl
{
DISALLOW_COPY_AND_ASSIGN(xoDomText);
public:
xoDomText( xoDoc* doc, xoTag tag );
virtual ~xoDomText();

virtual void			SetText( const char* txt ) override;
virtual const char*		GetText() const override;
virtual void			CloneSlowInto( xoDomEl& c, uint cloneFlags ) const override;
virtual void			ForgetChildren() override;

protected:
xoString				Text;			// Applicable only to xoTagText elements
};



class XOAPI xoStringTable
{
public:
xoStringTable();
~xoStringTable();

const char*			GetStr( int id ) const;			// Returns an empty string if the id is invalid or zero.
int					GetId( const char* str );

// This assumes that xoStringTable is "append-only", which it currently is.
// Knowing this allows us to make the clone from Document to Render Document trivially fast.
void				CloneFrom_Incremental( const xoStringTable& src );

protected:
xoPool						Pool;
fhashmap<xoString, int>		NameToId;			// This could be improved dramatically, by avoiding the heap alloc for every item
pvect<const char*>			IdToName;
};



class XOAPI xoImage : public xoTexture
{
public:
xoImage();
~xoImage();

xoImage*		Clone() const;
void			Free();
void			Set( xoTexFormat format, u32 width, u32 height, const void* bytes );
void			Alloc( xoTexFormat format, u32 width, u32 height );
u32				GetWidth() const	{ return TexWidth; }
u32				GetHeight() const	{ return TexHeight; }
const void*		GetData() const		{ return TexData; }
};



class xoImage;

// TODO: Add some kind of locking mechanism, so that an imagestore can be shared by a mutating UI thread
// and a rendering thread.
class XOAPI xoImageStore
{
public:
static const char*	NullImageName;	// You may not use this name "NULL", because it is reserved for the one-and-only null image

xoImageStore();
~xoImageStore();

void			Set( const char* name, xoImage* img );
xoImage*		Get( const char* name ) const;
xoImage*		GetOrNull( const char* name ) const;
const xoImage*	GetNull() const;	// Get the 'null' image, which is a 2x2 checkerboard

// temp hack. shouldn't be here.
void			CloneFrom( const xoImageStore& src );

protected:
static const int	NullImageIndex = 0;

pvect<xoImage*>				ImageList;
fhashmap<xoString, int>		NameToIndex;

};




/* Document.

Version
-------

Every time an event handler runs, we increment the document version number. This is a conservative
way of detecting any change to the document, without requiring that all document updates go via
some kind of accessor function. Our renderer compares its last version to our current version,
and if the two differ, it knows that it needs to update.

*/
class XOAPI xoDoc
{
DISALLOW_COPY_AND_ASSIGN(xoDoc);
public:
xoDomNode					Root;							// Root element of the document tree
xoStyleTable				ClassStyles;					// All style classes defined in this document
xoStyle						TagStyles[xoTagEND];			// Styles of tags. For example, the style of <p>, or the style of <h1>.
xoStringTable				Strings;						// Generic string table.
xoImageStore				Images;							// All images. Some day we may want to be able to share these amongst different documents.

xoDoc();
~xoDoc();
void			Reset();
void			IncVersion();
uint32			GetVersion()		{ return Version; }									// Renderers use purposefully loose MT semantics on this.
void			ResetModifiedBitmap();													// Reset the 'ismodified' bitmap of all DOM elements.
void			MakeFreeIDsUsable();													// All of our dependent renderers have been updated, we can move FreeIDs over to UsableIDs.
void			CloneSlowInto( xoDoc& c, uint cloneFlags, xoRenderStats& stats ) const;	// Used to make a read-only clone for the renderer. Preserves existing.
//void			CloneFastInto( xoDoc& c, uint cloneFlags, xoRenderStats& stats ) const;	// Used to make a read-only clone for the renderer. Starts from scratch.

// Style Classes
bool			ClassParse( const char* klass, const char* style );		// Set the class, overwriting any previously set style

xoDomEl*		AllocChild( xoTag tag );
void			FreeChild( const xoDomEl* el );

xoString		Parse( const char* src ); // Set the entire document from a single xml-like string. Returns empty string on success, or error message.

void			ChildAdded( xoDomEl* el );
void			ChildAddedFromDocumentClone( xoDomEl* el );
void			ChildRemoved( xoDomEl* el );
void			SetChildModified( xoInternalID id );
intp			ChildByInternalIDListSize() const				{ return ChildByInternalID.size(); }
const xoDomEl**	ChildByInternalIDList() const					{ return (const xoDomEl**) ChildByInternalID.data; }
const xoDomEl*	GetChildByInternalID( xoInternalID id ) const	{ return ChildByInternalID[id]; }						// A NULL result means this child has been deleted
xoDomEl*		GetChildByInternalIDMutable( xoInternalID id )	{ return ChildByInternalID[id]; }

protected:
volatile uint32				Version;
xoPool						Pool;					// Used only when making a clone via CloneFast()
bool						IsReadOnly;				// Read-only clone used for rendering
pvect<xoDomEl*>				ChildByInternalID;
BitMap						ChildIsModified;		// Bit is set if child has been modified since we last synced with the renderer
podvec<xoInternalID>		UsableIDs;				// When we do a render sync, then FreeIDs are moved into UsableIDs
podvec<xoInternalID>		FreeIDs;

void	ResetInternalIDs();
void	InitializeDefaultTagStyles();
};


// The umbrella class that houses a DOM tree.
// This processes UI input.
// It schedules rendering.
// It coordinates between DOM and Render threads.
class XOAPI xoDocGroup
{
DISALLOW_COPY_AND_ASSIGN(xoDocGroup);
public:
xoDoc*				Doc;
xoSysWnd*			Wnd;
xoRenderDoc*		RenderDoc;
bool				DestroyDocWithGroup;

xoRenderStats		RenderStats;

xoDocGroup();
~xoDocGroup();

#if XO_PLATFORM_WIN_DESKTOP
static LRESULT CALLBACK StaticWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
LRESULT WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
#endif

// These are the only 3 entry points into our content
xoRenderResult	Render();							// This is always called from the Render thread
xoRenderResult	RenderToImage( xoImage& image );	// This is always called from the Render thread
void			ProcessEvent( xoEvent& ev );		// This is always called from the UI thread

bool			IsDocVersionDifferentToRenderer() const;

protected:
AbcCriticalSection	DocLock;		// Mutation of 'Doc', or cloning of 'Doc' for the renderer

xoRenderResult	RenderInternal( xoImage* targetImage );
//void			FindTarget( const xoVec2f& p, pvect<xoRenderDomEl*>& chain );
bool			BubbleEvent( xoEvent& ev );
};



#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable: 4345 ) // POD initialized with ()
#endif


#ifdef _WIN32
#pragma warning( pop )
#endif



/* A system window, or view.
*/
class XOAPI xoSysWnd
{
public:
enum SetPositionFlags
{
SetPosition_Move = 1,
SetPosition_Size = 2,
};
#if XO_PLATFORM_WIN_DESKTOP
HWND					SysWnd;
#elif XO_PLATFORM_ANDROID
xoBox					RelativeClientRect;		// Set by NuLib_init
#elif XO_PLATFORM_LINUX_DESKTOP
Display*				XDisplay;
Window					XWindowRoot;
//GLint					att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo*			VisualInfo;
Colormap				ColorMap;
Window					XWindow;
GLXContext				GLContext;
XEvent					Event;
#else
XOTODO_STATIC;
#endif
xoDocGroup*			DocGroup;
xoRenderBase*		Renderer;

xoSysWnd();
~xoSysWnd();

static xoSysWnd*	Create();
static xoSysWnd*	CreateWithDoc();
static void			PlatformInitialize();

void	Attach( xoDoc* doc, bool destroyDocWithProcessor );
void	Show();
xoDoc*	Doc();
bool	BeginRender();				// Basically wglMakeCurrent()
void	EndRender();				// SwapBuffers followed by wglMakeCurrent(NULL)
void	SurfaceLost();				// Surface lost, and now regained. Reinitialize GL state (textures, shaders, etc).
void	SetPosition( xoBox box, uint setPosFlags );
xoBox	GetRelativeClientRect();	// Returns the client rectangle (in screen coordinates), relative to the non-client window

protected:
bool	InitializeRenderer();

template<typename TRenderer>
bool	InitializeRenderer_Any( xoRenderBase*& renderer );
};

#ifdef TEMP_ASSERT
	#undef TEMP_ASSERT
	#undef ASSERT
#endif

#ifdef _MSC_VER
#pragma warning(pop) // pop of XO-AMALGAMATION-DISABLED-WARNINGS
#endif
