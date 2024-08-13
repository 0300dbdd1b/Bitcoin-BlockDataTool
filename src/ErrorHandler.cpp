#include "ErrorHandler.hpp"

using namespace std;

ErrorCode Error(string message, ErrorCode error)
{
	fprintf(stderr, "%s\n", message.c_str());
	return error;
}
