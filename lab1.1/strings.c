#include <stdbool.h>
#include <string.h>

bool string_cmp(const char* lhs, const char* rhs){
	return ((strlen(lhs) == strlen(rhs)) && (strncmp(lhs,rhs,strlen(rhs))==0));
}
