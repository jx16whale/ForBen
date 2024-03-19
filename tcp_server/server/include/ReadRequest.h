#ifndef READREQUEST_H
#define READREQUEST_H

#include "Request.h"
#include "HashMap.h"

class ReadRequest : public Request {
private:
    int offset;
    int numBytesToRead;

public:
    ReadRequest(int uniqueID, int opcode, const std::string& pathName, int offset, int numBytesToRead);
    // declaration for the destructor of the ReadRequest class.
    virtual ~ReadRequest() = default;
    // This declares a member function named process that takes no arguments and returns void. The virtual keyword indicates that this function is a virtual function. Virtual functions are used in polymorphism, allowing derived classes to provide their own implementation of the function.
    void process();
    void setPathName();
    bool checkMonitor(HashMap& hashMap);
};

#endif // READREQUEST_H
