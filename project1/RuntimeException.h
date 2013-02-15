#ifndef RUNTIMEEXCEPTION_H_
#define RUNTIMEEXCEPTION_H_

#include <string>

using namespace std;

class RuntimeException {
  public:
    RuntimeException(const string& err) : errorMsg(err) {}
    string getMessage() const {return errorMsg;}
  
  private:
    string errorMsg;
};

inline std::ostream& operator<<(std::ostream& out, const RuntimeException& e){ 
  return out << e.getMessage();
}

#endif
