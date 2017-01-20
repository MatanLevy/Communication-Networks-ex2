#include "Email.h"




string Email :: printMail() const {
		return  std :: to_string(id) + " " + from + " " + "\"" + subject + "\"" ;
	}

Email::~Email() {}
