/* src/input_iterator.hh
   Written by, Sohail Qayum Malik[sqm@hackers.pk] */

#include <iterator>

#ifndef CC_TOKENIZER_INPUT_ITERATOR_HH
#define	CC_TOKENIZER_INPUT_ITERATOR_HH

namespace cc_tokenizer {

template <typename _E, class _Tp>
class input_iterator : public std::iterator< std::input_iterator_tag, input_iterator<_E, _Tp> > {

   /* It is essential that to instanciate this type the constructor which accepts pointer to _Tp gets used
      It is essential that while instanciating this type, the _Tp::begin() or _Tp::end() gets used */
   _Tp& container;  

   public:
     /* Return by value. It is essential that object to iterate upon, remains encapsulated here. The outside world can only access it by value and not by reference */ 
     _Tp base(void) {

        return container;
     }
     
     /* A type is DefaultConstructible if it has a default constructor, that is, if it is possible to construct an object of that type without initializing the object to any particular value */
     input_iterator(void) : container(*(new _Tp())) {
     }
      
     input_iterator(_Tp *ptr) : container(*ptr) {
     }

     ~input_iterator(void) {

        delete &container; 
     }
};

};

#endif
