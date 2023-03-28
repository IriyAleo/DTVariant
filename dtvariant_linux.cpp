//== Project includes ==
#include "dtvariant_linux.h"



L_DeTypeVar::L_DeTypeVar (DeTypeVar & p_var)
{
	*this = DeTypeVar(p_var);
}

L_DeTypeVar::L_DeTypeVar (const DeTypeVar & p_var)
{
	*this = DeTypeVar(p_var);
}

L_DeTypeVar::L_DeTypeVar (in_addr p_var)
{
	m_len = 17;
	m_var = new char[m_len];
	sprintf(m_var, "%s", inet_ntoa(p_var));
	m_var_type = DTVAR::ADDRESS;
	m_var_size = sizeof(in_addr);
}

in_addr L_DeTypeVar::toInAddr ()
{
	in_addr addr;
	inet_aton(m_var, &addr);

	return addr;
}

L_DeTypeVar	L_DeTypeVar::fromBytes (void * p_bytes, uint32_t p_len, DTVAR::TYPE p_type)
{
	if (p_bytes == NULL) {
		return DeTypeVar::fromBytes(p_bytes, p_len, p_type);
	}

	if (p_type == DTVAR::ADDRESS) {
		return L_DeTypeVar(*(in_addr*)(p_bytes));
	}
	else {
		return DeTypeVar::fromBytes(p_bytes, p_len, p_type);
	}
}

void * L_DeTypeVar::toBytes (void * p_bytes, DTVAR::TYPE p_type, size_t p_type_size)
{
	if (p_bytes == NULL) {
		return NULL;
	}

	if (p_type == DTVAR::UNKNOWN) {
		p_type = m_var_type;
	}
	if (p_type_size == 0) {
		p_type_size = m_var_type;
	}

	if (p_type == DTVAR::ADDRESS) {
		in_addr fval;
		fval.s_addr = inet_addr(m_var);
		memcpy(p_bytes, &fval, sizeof(fval));
	}
	else {
		return DeTypeVar::toBytes(p_bytes, p_type, p_type_size);
	}

	return p_bytes;
}

L_DeTypeVar & operator << (L_DeTypeVar & p_left, L_DeTypeVar p_right)
{
	p_left += p_right;
	return p_left;
}
