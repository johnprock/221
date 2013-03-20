/** 
 * Comparator.h:
 * A comparator class which is used to compare two integers.
 * It is used in priority queue class to compare two keys.
 * To compare two objects of a certain type, you need to always 
 * specify the actual data type for the parameters of your comparator, 
 * so Comp is a normal class, not a template which uses generic data types.
 * If you are using another data type rather than integer as 
 * the keys of priority queue, you have to rewrite a comparator
 * class for that data type.
 *
 * This code is written by refering to the code fragment 7.3 in
 * "Data Structures and Algorithms in C++" by M. T. Goodrich et al.
 */
#ifndef COMPARATOR_H_
#define COMPARATOR_H_
class Comp {
public:
  // Call (Comp Object).(i1,i2) to compare the two intergers i1 and i2
  int operator()(const int i1, const int i2) const {
    if (i1 < i2)
      return -1;
    if (i2 < i1)
      return 1;
    else
      return 0;
  }
};
#endif
