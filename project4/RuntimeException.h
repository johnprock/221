/** 
 * RuntimeException.h:
 * A base class which defines run-time exception class.
 * All other exceptions defined in Interface.h are derived from this class.
 * This code is excerpted from the code fragment 2.7 in
 * "Data Structures and Algorithms in C++" by M. T. Goodrich et al.
 */
#ifndef RUNTIMEEXCEPTION_H_
#define RUNTIMEEXCEPTION_H_
#include <string>
class RuntimeException {// generic run-time exception
 private:
  std::string errorMsg;
 public:
  RuntimeException(const std::string& err) { errorMsg = err; }
  std::string getMessage() const { return errorMsg; }
  friend std::ostream& operator<<(std::ostream& out, const RuntimeException& e)
  { return out << e.getMessage(); }
};
// exception thrown when the container is empty
class EmptyContainerException : public RuntimeException {  
public:
  EmptyContainerException(const std::string& err) : RuntimeException(err) {}
};
// exception thrown when passing the boundary of the container
class BoundaryViolationException : public RuntimeException {  
public:
  BoundaryViolationException(const std::string& err) : RuntimeException(err) {}
};
// exception thrown when user uses a invalid position
class InvalidPositionException : public RuntimeException {  
public:
  InvalidPositionException(const std::string& err) : RuntimeException(err) {}
};
#endif
