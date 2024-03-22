#ifndef WRITEREQUEST_H
#define WRITEREQUEST_H

#include "Request.h"
#include <vector>

class WriteRequest : public Request {
public:
    int offset;
    std::string bytesToWrite;
    WriteRequest(int uniqueID, int opcode, const std::string& pathName, int offset, std::string bytesToWrite);
    // declaration for the destructor of the WriteRequest class.
    virtual ~WriteRequest() = default;
    // This declares a member function named process that takes no arguments and returns void. The virtual keyword indicates that this function is a virtual function. Virtual functions are used in polymorphism, allowing derived classes to provide their own implementation of the function.
    Response process();
};

#endif // WRITEREQUEST_H
