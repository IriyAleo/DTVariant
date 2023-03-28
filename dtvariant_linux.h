#ifndef DTVARIANT_LINUX_H
#define DTVARIANT_LINUX_H

 //== Project includes ==
#include "dtvariant.h"
 //== Linux includes ==
#include <netinet/in.h>
#include <arpa/inet.h>



class L_DeTypeVar : public DeTypeVar
{
public: // public functions
	using DeTypeVar::DeTypeVar;

	L_DeTypeVar (DeTypeVar &);
	L_DeTypeVar (const DeTypeVar &);
	 //== Linux types ==
	L_DeTypeVar (in_addr p_var);
	 //== Transform to linux types ==
	in_addr		toInAddr ();
	 //== Other types ==
	L_DeTypeVar	fromBytes (void * p_bytes, uint32_t p_len, DTVAR::TYPE p_type = DTVAR::UNKNOWN);
	void*		toBytes (void * p_bytes, DTVAR::TYPE p_type = DTVAR::UNKNOWN,					\
						 size_t p_type_size = 0);
	 //== Standard operators ==
	friend L_DeTypeVar &	operator << (L_DeTypeVar & p_left, L_DeTypeVar p_right);

private: // private functions

public: // public members / encapsulations

private: // private members

};



#endif// DTVARIANT_LINUX_H
