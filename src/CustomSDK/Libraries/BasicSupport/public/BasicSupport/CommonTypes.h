#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#ifdef _MSC_VER

#	define _COMPILER_NAME	"vc"

#	if _MSC_VER<1400 ||_MSC_VER>1930
#		error	"Compiler Version Not Supported!"
#	elif _MSC_VER==1400
#		define _CRT_VER_NAME	"80"	//Visual Studio 2005
#	elif _MSC_VER==1500
#		define _CRT_VER_NAME	"90"	//Visual Studio 2008
#	elif _MSC_VER==1600
#		define _CRT_VER_NAME	"100"	//Visual Studio 2010
#	elif _MSC_VER==1700
#		define _CRT_VER_NAME	"110"	//Visual Studio 2012
#	elif _MSC_VER==1800
#		define _CRT_VER_NAME	"120"	//Visual Studio 2013
#	elif _MSC_VER>=1900 && _MSC_VER<1910
#		define _CRT_VER_NAME	"140"	//Visual Studio 2015
#	elif _MSC_VER>=1910 && _MSC_VER<1920
#		define _CRT_VER_NAME	"140"	//Visual Studio 2017
#	elif _MSC_VER>=1920 && _MSC_VER<1930
#		define _CRT_VER_NAME	"140"	//Visual Studio 2019
#	endif

#	if SIZE_MAX==0xffffffffffffffffui64
#		define _PLATFORM	"x64"
#	elif SIZE_MAX == 0xffffffffui32
#		define _PLATFORM	"x32"
#	endif

# define SYMBOL_EXPORT _declspec(dllexport)
# define SYMBOL_IMPORT _declspec(dllimport)

#else

#	define _CRT_VER_NAME
#	define _COMPILER_NAME
#	define _PLATFORM

# define SYMBOL_EXPORT
# define SYMBOL_IMPORT

#endif //_MSC_VER

#ifdef _DEBUG
#	define _DEBUG_FLAG	"_d"
#else
#	define _DEBUG_FLAG
#endif // _DEBUG

#define CLASS_PTR_DECLARE(CLASS_NAME)                                                              \
	typedef boost::shared_ptr<class CLASS_NAME> CLASS_NAME##Ptr;                                     \
	typedef boost::weak_ptr<class CLASS_NAME> CLASS_NAME##WPtr;                                      \
	typedef boost::shared_ptr<const class CLASS_NAME> CLASS_NAME##ConstPtr;

#define STRUCT_PTR_DECLARE(STRUCT_NAME)																														 \
	typedef boost::shared_ptr<struct STRUCT_NAME> STRUCT_NAME##Ptr;																   \
	typedef boost::weak_ptr<struct STRUCT_NAME> STRUCT_NAME##WPtr;																	 \
	typedef boost::shared_ptr<const struct STRUCT_NAME> STRUCT_NAME##ConstPtr;	

#define NOCOPYABLE_DECLARE(TYPE_NAME)																															 \
public:																																														 \
	typedef TYPE_NAME NoCopyableType;																																 \
private: 																																													 \
	TYPE_NAME( const TYPE_NAME& );																																	 \
	const TYPE_NAME& operator=( const TYPE_NAME&);

#define PRIVATE_STRUCT_COPY_DECLARE(CLASS_NAME) 																									 \
protected:																																												 \
	friend struct CLASS_NAME##Private;																															 \
	inline CLASS_NAME##Private* GetPP() const																												 \
	{																																																 \
		return reinterpret_cast<CLASS_NAME##Private *>(_Private_Ptr);																	 \
	} 																																															 \
public:																																														 \
	typedef CLASS_NAME CopyableType;																																 \
protected:																																												 \
	typedef CLASS_NAME##Private PrivateType;																												 \

#define PRIVATE_STRUCT_DECLARE(CLASS_NAME) 																												 \
	NOCOPYABLE_DECLARE(CLASS_NAME)																																	 \
protected:																																												 \
	friend struct CLASS_NAME##Private;																															 \
	inline CLASS_NAME##Private* GetPP() const																												 \
	{																																																 \
		return reinterpret_cast<CLASS_NAME##Private *>(_Private_Ptr);																	 \
	} 																																															 \
protected:																																												 \
	typedef CLASS_NAME##Private PrivateType;																												 \

#define T_D() PrivateType * const d = GetPP()
