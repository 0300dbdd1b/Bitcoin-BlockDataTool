#ifndef ERROR_HANDLER_HPP
 #define ERROR_HANDLER_HPP
 #include <iostream>
 #include <string>

enum ErrorCode
{
	SUCCESS,
	ERROR
};

ErrorCode Error(std::string message, ErrorCode error);

#endif
