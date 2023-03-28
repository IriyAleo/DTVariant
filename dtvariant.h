#ifndef DTVARIANT_H
#define DTVARIANT_H


#if defined(__linux__) || defined(_POSIX_VERSION)
	#define IS_LINUX			(1)
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define IS_WINDOWS			(1)
#endif


 //== C includes ==
#include <stdio.h>
#include <stdint.h>
#include <syslog.h>
 //== C++ includes ==
#include <iostream>
#include <cstring>
#include <regex>
#include <type_traits>



	#if IS_LINUX
class L_DeTypeVar;
typedef L_DeTypeVar	DTVar;
	#elif IS_WINDOWS
class W_DeTypeVar;
typedef W_DeTypeVar	DTVar;
	#else
class DeTypeVar;
typedef DeTypeVar	DTVar;
	#endif

namespace DTVAR {
	enum TYPE {
		INT, UINT, FLOAT, BOOL, CHAR, STRING, ADDRESS, ARRAY, POINTER, UNKNOWN
	};

	const char ARRAY_SPLITTER[] = ",";
	const size_t ARRAY_SPLITTER_LEN = strlen(ARRAY_SPLITTER);
	const size_t DEFAULT_LEN = 255;
	const size_t TEMP_STRING_COUNT = 255;
	const size_t TEMP_STRING_LEN = 4096;
}

/// @brief The DeTypeVar class acts like a union for the most common C/C++ data types
class DeTypeVar
{
public: // public functions
	DeTypeVar ();
	~DeTypeVar ();
	DeTypeVar (DeTypeVar &);
	DeTypeVar (const DeTypeVar &);
	 //== Standard C types ==
	DeTypeVar (bool p_var);
	DeTypeVar (short p_var);
	DeTypeVar (unsigned short p_var);
	DeTypeVar (int p_var);
	DeTypeVar (unsigned int p_var);
	DeTypeVar (long int p_var);
	DeTypeVar (unsigned long int p_var);
	DeTypeVar (long long int p_var);
	DeTypeVar (unsigned long long int p_var);
	DeTypeVar (float p_var);
	DeTypeVar (double p_var);
	DeTypeVar (long double p_var);
	DeTypeVar (char p_var);
	DeTypeVar (signed char p_var);
	DeTypeVar (unsigned char p_var);
	DeTypeVar (char * p_var);
	DeTypeVar (void * p_var);
	 //== Standard C const types ==
	DeTypeVar (const char * p_var);
	 //== Standard C++ types ==
	DeTypeVar (std::string p_var);
		template <typename ... Args>															\
	DeTypeVar (char const * const format, Args const & ... args);
		template <typename ValType>																\
	DeTypeVar (std::vector<ValType> p_var);
	 //== Other types ==
		template <typename CustomType>															\
	DeTypeVar (CustomType & p_var);
		template <typename CustomType>															\
	DeTypeVar (CustomType * p_var);
	 //== Transform to standart types ==
	int8_t		toInt8 ();
	int16_t		toInt16 ();
	int32_t		toInt32 ();
	int64_t		toInt64 ();
	uint8_t		toUInt8 ();
	uint16_t	toUInt16 ();
	uint32_t	toUInt32 ();
	uint64_t	toUInt64 ();
	int			toInt ();
	unsigned int toUInt ();
	unsigned int toHex ();
	void *		toVoid ();
	double		toDouble ();
	char *		toStr();
	char *		toStr (char * p_res);
	 //== Standard C++ types ==
	std::string	toStdStr ();
	DeTypeVar	toRegExp (std::string p_regex, DeTypeVar p_replace_text);
	size_t		toHash ();
		template <typename ValType>																\
	std::vector<ValType>	toVector ();
	 //== Other types ==
	DeTypeVar	fromBytes (void * p_bytes, uint32_t p_len, DTVAR::TYPE p_type = DTVAR::UNKNOWN);
	void*		toBytes (void * p_bytes, DTVAR::TYPE p_type = DTVAR::UNKNOWN,					\
						 size_t p_type_size = 0);
		template <typename ... Args>															\
	int32_t		fromFormat (char const * const format, Args const & ... args);
		template <typename ... Args>															\
	DeTypeVar	toFormat (char const * const format, Args const & ... args);
		template <typename ... Args>															\
	DeTypeVar	copyFormat (char const * const format, Args const & ... args);
	 //== Standard operators ==
	bool		operator == (const DeTypeVar & p_var);
	bool		operator != (const DeTypeVar & p_var);
	bool		operator > (const DeTypeVar & p_var);
	bool		operator < (const DeTypeVar & p_var);
	bool		operator >= (const DeTypeVar & p_var);
	bool		operator <= (const DeTypeVar & p_var);
	DeTypeVar &	operator = (const DeTypeVar & p_var);
	DeTypeVar &	operator += (const DeTypeVar & p_var);
	DeTypeVar &	operator + (const DeTypeVar & p_var);
	DeTypeVar &	operator () (const DeTypeVar & p_var);
	char &		operator [] (size_t p_pos);
	friend std::ostream &	operator << (std::ostream & p_stream, DeTypeVar & p_var);
	friend DeTypeVar &		operator << (DeTypeVar & p_left, DeTypeVar p_right);
	friend std::istream &	operator >> (std::istream & p_stream, DeTypeVar & p_var);

	bool	isEmpty ();
	char &	getLastSymb ();

private: // private functions

public: // public members / encapsulations
	const char *		g_var ()				{ return m_var; }
	const size_t		g_len ()				{ return m_len; }
	const DTVAR::TYPE	g_var_type ()			{ return m_var_type; }
	const size_t		g_var_size ()			{ return m_var_size; }

protected: // protected members
	char * m_var;																				///< Variant pointer
	size_t m_len;																				///< Variant length
	DTVAR::TYPE m_var_type;																		///< Variant type
	size_t m_var_size;																			///< Size of type variant
};


 //== Project includes ==
	#if IS_LINUX
#include "dtvariant_linux.h"
	#elif IS_WINDOWS
#include "dtvariant_windows.h"
	#endif
#include "dtvariant.hpp"


#endif// DTVARIANT_H
