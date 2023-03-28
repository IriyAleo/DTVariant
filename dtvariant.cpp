//== Project includes ==
#include "dtvariant.h"



static char ** m_temp_to_str;
static uint32_t m_iter_to_str;


DeTypeVar::DeTypeVar ()
{
	m_len = 0;
	m_var = new char[1];
	m_var[0] = '\0';
	m_var_type = DTVAR::UNKNOWN;
	m_var_size = 0;
}

DeTypeVar::~DeTypeVar ()
{
	if (m_var) {
		delete[] m_var;
		m_var = NULL;
	}
}

DeTypeVar::DeTypeVar (DeTypeVar & p_var)
{
	m_len = p_var.m_len;
	m_var = new char[m_len];
	memcpy(m_var, p_var.m_var, m_len);
	m_var_type = p_var.m_var_type;
	m_var_size = p_var.m_var_size;
}

DeTypeVar::DeTypeVar (const DeTypeVar & p_var)
{
	m_len = p_var.m_len;
	m_var = new char[m_len];
	memcpy(m_var, p_var.m_var, m_len);
	m_var_type = p_var.m_var_type;
	m_var_size = p_var.m_var_size;
}

DeTypeVar::DeTypeVar (bool p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%d", p_var);
	m_var_type = DTVAR::BOOL;
	m_var_size = sizeof(bool);
}

DeTypeVar::DeTypeVar (short p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%d", p_var);
	m_var_type = DTVAR::INT;
	m_var_size = sizeof(short);
}

DeTypeVar::DeTypeVar (unsigned short p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%u", p_var);
	m_var_type = DTVAR::UINT;
	m_var_size = sizeof(short);
}

DeTypeVar::DeTypeVar (int p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%d", p_var);
	m_var_type = DTVAR::INT;
	m_var_size = sizeof(int);
}

DeTypeVar::DeTypeVar (unsigned int p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%u", p_var);
	m_var_type = DTVAR::UINT;
	m_var_size = sizeof(int);
}

DeTypeVar::DeTypeVar (long p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%lld", p_var);
	m_var_type = DTVAR::INT;
	m_var_size = sizeof(long);
}

DeTypeVar::DeTypeVar (unsigned long p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%lu", p_var);
	m_var_type = DTVAR::UINT;
	m_var_size = sizeof(long);
}

DeTypeVar::DeTypeVar (long long p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%lld", p_var);
	m_var_type = DTVAR::INT;
	m_var_size = sizeof(long long);
}

DeTypeVar::DeTypeVar (unsigned long long p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%llu", p_var);
	m_var_type = DTVAR::UINT;
	m_var_size = sizeof(long long);
}

DeTypeVar::DeTypeVar (float p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%f", p_var);
	m_var_type = DTVAR::FLOAT;
	m_var_size = sizeof(float);
}

DeTypeVar::DeTypeVar (double p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%f", p_var);
	m_var_type = DTVAR::FLOAT;
	m_var_size = sizeof(double);
}

DeTypeVar::DeTypeVar (long double p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%f", p_var);
	m_var_type = DTVAR::FLOAT;
	m_var_size = sizeof(long double);
}

DeTypeVar::DeTypeVar (char p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%c", p_var);
	m_var_type = DTVAR::CHAR;
	m_var_size = sizeof(char);
}

DeTypeVar::DeTypeVar (signed char p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%d", p_var);
	m_var_type = DTVAR::INT;
	m_var_size = sizeof(signed char);
}

DeTypeVar::DeTypeVar (unsigned char p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	sprintf(m_var, "%u", p_var);
	m_var_type = DTVAR::UINT;
	m_var_size = sizeof(unsigned char);
}

DeTypeVar::DeTypeVar (char * p_var)
{
	m_len = (p_var!=NULL)? strlen(p_var) + 1: 1;
	m_var = new char[m_len];
	if (p_var != NULL) {
		sprintf(m_var, "%s", p_var);
	}
	else {
		sprintf(m_var, "\0");
	}
	m_var_type = DTVAR::STRING;
	m_var_size = sizeof(void*);
}

DeTypeVar::DeTypeVar (void * p_var)
{
	m_len = DTVAR::DEFAULT_LEN;
	m_var = new char[m_len];
	if (p_var != NULL) {
		sprintf(m_var, "%p", p_var);
	}
	else {
		sprintf(m_var, "(nil)");
	}
	m_var_type = DTVAR::POINTER;
	m_var_size = sizeof(void*);
}

DeTypeVar::DeTypeVar (const char * p_var)
{
	m_len = (p_var!=NULL)? strlen(p_var) + 1: 1;
	m_var = new char[m_len];
	if (p_var != NULL) {
		sprintf(m_var, "%s", p_var);
	}
	else {
		sprintf(m_var, "\0");
	}
	m_var_type = DTVAR::STRING;
	m_var_size = sizeof(void*);
}

DeTypeVar::DeTypeVar (std::string p_var)
{
	m_len = p_var.size() + 1;
	m_var = new char[m_len];
	sprintf(m_var, "%s", p_var.c_str());
	m_var_type = DTVAR::STRING;
	m_var_size = sizeof(std::string);
}

int8_t DeTypeVar::toInt8 ()
{
	int8_t t_ret;

	sscanf(m_var, "%hhd", &t_ret);

	return t_ret;
}

int16_t DeTypeVar::toInt16 ()
{
	int16_t t_ret;

	sscanf(m_var, "%hd", &t_ret);

	return t_ret;
}

int32_t DeTypeVar::toInt32 ()
{
	int32_t t_ret;

	sscanf(m_var, "%d", &t_ret);

	return t_ret;
}

int64_t DeTypeVar::toInt64 ()
{
	int64_t t_ret;

	sscanf(m_var, "%lld", &t_ret);

	return t_ret;
}

uint8_t DeTypeVar::toUInt8 ()
{
	uint8_t t_ret;

	sscanf(m_var, "%hhu", &t_ret);

	return t_ret;
}

uint16_t DeTypeVar::toUInt16 ()
{
	uint16_t t_ret;

	sscanf(m_var, "%hu", &t_ret);

	return t_ret;
}

uint32_t DeTypeVar::toUInt32 ()
{
	uint32_t t_ret;

	sscanf(m_var, "%u", &t_ret);

	return t_ret;
}

uint64_t DeTypeVar::toUInt64 ()
{
	uint64_t t_ret;

	sscanf(m_var, "%llu", &t_ret);

	return t_ret;
}

int DeTypeVar::toInt ()
{
	int t_ret;

	sscanf(m_var, "%d", &t_ret);

	return t_ret;
}

unsigned int DeTypeVar::toUInt ()
{
	unsigned int t_ret;

	sscanf(m_var, "%u", &t_ret);

	return t_ret;
}

unsigned int DeTypeVar::toHex ()
{
	unsigned int t_ret;

	sscanf(m_var, "0x%x", &t_ret);

	return t_ret;
}

void * DeTypeVar::toVoid ()
{
	void * t_ret;

	sscanf(m_var, "%p", &t_ret);

	return t_ret;
}

double DeTypeVar::toDouble ()
{
	double t_ret;

	sscanf(m_var, "%lf", &t_ret);

	return t_ret;
}

char * DeTypeVar::toStr ()
{
	char * ret_val;

	if (m_iter_to_str == 0) {
		m_temp_to_str = new char*[DTVAR::TEMP_STRING_COUNT+1];
		for (int iter_temp = 0; iter_temp < DTVAR::TEMP_STRING_COUNT+1; ++iter_temp) {
			m_temp_to_str[iter_temp] = new char[DTVAR::TEMP_STRING_LEN];
		}
	}

	ret_val = m_temp_to_str[m_iter_to_str];
	toStr(ret_val);
	if (++m_iter_to_str == DTVAR::TEMP_STRING_COUNT) {
		m_iter_to_str = 1;
	}

	return ret_val;
}

char * DeTypeVar::toStr (char * p_res)
{
	if (p_res) {
		sprintf(p_res, "%s", m_var);
	}
	return p_res;
}

std::string DeTypeVar::toStdStr ()
{
	return std::string(m_var);
}

DeTypeVar DeTypeVar::toRegExp (std::string p_regex, DeTypeVar p_replace_text)
{
	DeTypeVar res;

	res = std::regex_replace(m_var, std::regex(p_regex), p_replace_text.toStdStr());
	*this = res;

	return res;
}

size_t DeTypeVar::toHash ()
{
	return std::hash<std::string>()(m_var);
}

DeTypeVar	DeTypeVar::fromBytes (void * p_bytes, uint32_t p_len, DTVAR::TYPE p_type)
{
	if (p_bytes == NULL) {
		return "0";
	}

	if (p_type == DTVAR::INT && p_len == sizeof(int8_t)) {
		return DeTypeVar(*(int8_t*)(p_bytes));
	}
	else if (p_type == DTVAR::INT && p_len == sizeof(int16_t)) {
		return DeTypeVar(*(int16_t*)(p_bytes));
	}
	else if (p_type == DTVAR::INT && p_len == sizeof(int32_t)) {
		return DeTypeVar(*(int32_t*)(p_bytes));
	}
	else if (p_type == DTVAR::INT && p_len == sizeof(int64_t)) {
		return DeTypeVar(*(int64_t*)(p_bytes));
	}
	else if (p_type == DTVAR::UINT && p_len == sizeof(uint8_t)) {
		return DeTypeVar(*(uint8_t*)(p_bytes));
	}
	else if (p_type == DTVAR::UINT && p_len == sizeof(uint16_t)) {
		return DeTypeVar(*(uint16_t*)(p_bytes));
	}
	else if (p_type == DTVAR::UINT && p_len == sizeof(uint32_t)) {
		return DeTypeVar(*(uint32_t*)(p_bytes));
	}
	else if (p_type == DTVAR::UINT && p_len == sizeof(uint64_t)) {
		return DeTypeVar(*(uint64_t*)(p_bytes));
	}
	else if (p_type == DTVAR::FLOAT && p_len == sizeof(float)) {
		return DeTypeVar(*(float*)(p_bytes));
	}
	else if (p_type == DTVAR::FLOAT && p_len == sizeof(double)) {
		return DeTypeVar(*(double*)(p_bytes));
	}
	else if (p_type == DTVAR::FLOAT && p_len == sizeof(long double)) {
		return DeTypeVar(*(long double*)(p_bytes));
	}
	else if (p_type == DTVAR::STRING) {
		return DeTypeVar((char*)(p_bytes));
	}
	else {
		return DeTypeVar(p_bytes);
	}
}

void * DeTypeVar::toBytes (void * p_bytes, DTVAR::TYPE p_type, size_t p_type_size)
{
	if (p_bytes == NULL) {
		return NULL;
	}

	if (p_type == DTVAR::UNKNOWN) {
		p_type = m_var_type;
	}
	if (p_type_size == 0) {
		p_type_size = m_var_size;
	}

	if (p_type == DTVAR::INT && p_type_size == sizeof(int8_t)) {
		auto fval = toInt8();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::INT && p_type_size == sizeof(int16_t)) {
		auto fval = toInt16();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::INT && p_type_size == sizeof(int32_t)) {
		auto fval = toInt32();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::INT && p_type_size == sizeof(int64_t)) {
		auto fval = toInt64();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::UINT && p_type_size == sizeof(uint8_t)) {
		auto fval = toUInt8();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::UINT && p_type_size == sizeof(uint16_t)) {
		auto fval = toUInt16();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::UINT && p_type_size == sizeof(uint32_t)) {
		auto fval = toUInt32();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::UINT && p_type_size == sizeof(uint64_t)) {
		auto fval = toUInt64();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::FLOAT && p_type_size == sizeof(float)) {
		auto fval = static_cast<float>(toDouble());
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::FLOAT && p_type_size == sizeof(double)) {
		auto fval = toDouble();
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::FLOAT && p_type_size == sizeof(long double)) {
		auto fval = static_cast<long double>(toDouble());
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else if (p_type == DTVAR::STRING) {
		strcpy((char*)p_bytes, toStr());
	}
	else {
		return NULL;
	}

	return p_bytes;
}

bool DeTypeVar::operator == (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght != right_lenght) {
		return false;
	}

	if (strcmp(m_var, p_var.m_var) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool DeTypeVar::operator != (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght != right_lenght) {
		return true;
	}

	if (strcmp(m_var, p_var.m_var) == 0) {
		return false;
	}
	else {
		return true;
	}
}

bool DeTypeVar::operator > (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght > right_lenght) {
		return true;
	}
	else if (left_lenght < right_lenght) {
		return false;
	}

	if (strcmp(m_var, p_var.m_var) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool DeTypeVar::operator < (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght < right_lenght) {
		return true;
	}
	else if (left_lenght > right_lenght) {
		return false;
	}

	if (strcmp(m_var, p_var.m_var) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool DeTypeVar::operator >= (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght > right_lenght) {
		return true;
	}
	else if (left_lenght < right_lenght) {
		return false;
	}

	if (strcmp(m_var, p_var.m_var) >= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool DeTypeVar::operator <= (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght < right_lenght) {
		return true;
	}
	else if (left_lenght > right_lenght) {
		return false;
	}

	if (strcmp(m_var, p_var.m_var) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

DeTypeVar & DeTypeVar::operator = (const DeTypeVar & p_var)
{
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (right_lenght + 1 > m_len) {
		if (m_var) {
			delete[] m_var;
		}

		m_len = right_lenght + 1;
		m_var = new char[m_len];
	}

	sprintf(m_var, "%s", p_var.m_var);

	m_var_type = p_var.m_var_type;
	m_var_size = p_var.m_var_size;

	return *this;
}

DeTypeVar & DeTypeVar::operator += (const DeTypeVar & p_var)
{
	uint32_t left_lenght = (uint32_t)strlen(m_var);
	uint32_t right_lenght = (uint32_t)strlen(p_var.m_var);

	if (left_lenght + right_lenght + 1 > m_len) {
		char * t_var = new char[left_lenght + right_lenght + 1];
		sprintf(t_var, "%s%s", m_var, p_var.m_var);
		*this = t_var;
		delete[] t_var;
	}
	else {
		sprintf(m_var + left_lenght, "%s", p_var.m_var);
	}

	return *this;
}

DeTypeVar & DeTypeVar::operator + (const DeTypeVar & p_var)
{
	DeTypeVar * ret = new DeTypeVar (m_var);
	*ret += p_var;
	return *ret;
}

DeTypeVar & DeTypeVar::operator () (const DeTypeVar & p_var)
{
	*this = p_var;
	return *this;
}

char & DeTypeVar::operator [] (size_t p_pos)
{
	if (p_pos < m_len) {
		return m_var[p_pos];
	}
	else {
		return m_var[0];
	}
}

std::ostream & operator << (std::ostream & p_stream, DeTypeVar & p_var)
{
	p_stream << p_var.g_var();
	return p_stream;
}

DeTypeVar & operator << (DeTypeVar & p_left, DeTypeVar p_right)
{
	p_left += p_right;
	return p_left;
}


std::istream & operator >> (std::istream & p_stream, DeTypeVar & p_var)
{
	std::string t_str;
	p_stream >> t_str;
	p_var(t_str);
	return p_stream;
}

bool DeTypeVar::isEmpty ()
{
	return (m_var[0] == '\0')? true: false;
}

char & DeTypeVar::getLastSymb ()
{
	return (m_len > 1)? m_var[m_len - 2]: m_var[0];
}
