#ifndef DTVARIANT_HPP
#define DTVARIANT_HPP

 //== Project includes ==
#include "dtvariant.h"



	template <typename ... Args>
DeTypeVar::DeTypeVar (char const * const format, Args const & ... args)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	toFormat(format, args ...);
	m_var_type = DTVAR::STRING;
}

	template<typename ValType>
DeTypeVar::DeTypeVar (std::vector<ValType> p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];

	DeTypeVar t_var;
	char t_str[DTVAR::TEMP_STRING_LEN];
	size_t t_str_len;

	sprintf(m_var, "[");
	for (auto & iter_var : p_var) {
		t_var(iter_var);
		strcat(m_var, t_var.toStr(t_str));
		strcat(m_var, DTVAR::ARRAY_SPLITTER);
	}
	if ((t_str_len = strlen(m_var)) > 1) {
		m_var[t_str_len - 1] = '\0';
	}
	strcat(m_var, "]");

	m_var_type = DTVAR::ARRAY;
}

	template <typename CustomType>
DeTypeVar::DeTypeVar (CustomType & p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%p", &p_var);
	m_var_type = DTVAR::POINTER;
	m_var_size = sizeof(void*);
}

	template <typename CustomType>
DeTypeVar::DeTypeVar (CustomType * p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%p", p_var);
	m_var_type = DTVAR::POINTER;
	m_var_size = sizeof(void*);
}

	template <typename ValType>
std::vector<ValType> DeTypeVar::toVector ()
{
	DeTypeVar t_dtvar;
	DeTypeVar t_type;
	char t_var[DTVAR::TEMP_STRING_LEN];
	size_t var_len = 0;
	char * iter_val = NULL;
	char * beg_val = NULL;
	ValType type_val;
	std::vector<ValType> ret_vec;

	t_type = type_val;
	strcpy(t_var, m_var);
	var_len = strlen(t_var);
	for (iter_val = beg_val = t_var+1; iter_val < t_var + var_len; ) {
		if (strncmp(iter_val, DTVAR::ARRAY_SPLITTER, DTVAR::ARRAY_SPLITTER_LEN) == 0
			|| *iter_val == ']'
			) {
			memset(iter_val, '\0', DTVAR::ARRAY_SPLITTER_LEN);
			t_dtvar = beg_val;
			t_dtvar.toBytes(&type_val, t_type.g_var_type(), t_type.g_var_size());
			ret_vec.push_back(type_val);
			iter_val = beg_val = iter_val+DTVAR::ARRAY_SPLITTER_LEN;
		}
		else {
			++iter_val;
		}
	}

	return ret_vec;
}

	template <typename ... Args>
int32_t DeTypeVar::fromFormat(char const * const format, Args const & ... args)
{
	int32_t rcode = -1;

	try {
		rcode = sscanf(m_var, format, args ...);
		if (rcode == EOF) {
			sscanf(m_var, "%p", args ...);
		}
	}
	catch (std::exception & exc) {
		printf("DeTypeVar::fromFormat(): exeption №%d [%s], format=[%s]\n", errno, exc.what(), format);
		return rcode;
	}

	return rcode;
}

	template <typename ... Args>
DeTypeVar DeTypeVar::toFormat (char const * const format, Args const & ... args)
{
	char t_var[DTVAR::TEMP_STRING_LEN];

	sprintf(t_var, format, args ...);

	*this = t_var;

	return t_var;
}

	template <typename ... Args>
DeTypeVar DeTypeVar::copyFormat (char const * const format, Args const & ... args)
{
	char t_var[DTVAR::TEMP_STRING_LEN];

	sprintf(t_var, format, args ...);

	*this += t_var;

	return this->m_var;
}


#endif // DTVARIANT_HPP
