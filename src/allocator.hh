/* src/allocator.hh
   Written by, Sohail Qayum Malik[sqm@hackers.pk] */

#include<stdexcept>
#include<stdlib.h>

/* Include guards */
#ifndef CC_TOKENIZER_ALLOCATOR_HH
#define	CC_TOKENIZER_ALLOCATOR_HH

namespace cc_tokenizer {

template <typename _E>
class allocator {

   public:
      typedef	_E			  value_type;
      typedef	value_type*		  pointer;
      typedef	const value_type* 	  const_pointer;
      typedef	value_type&		  reference;
      typedef	const value_type& 	  const_reference;
      typedef	std::size_t		  size_type;
      typedef	std::ptrdiff_t	  	  difference_type;

      template<typename U> struct rebind {

         typedef	allocator<U>	other;
      };

      size_type max_size(void) const {
    
         return (static_cast<size_type>(0) + static_cast<size_type>(-1)) / sizeof(_E); 
      }
      
      pointer allocate(const size_type n) const throw(std::bad_alloc, std::length_error) {
      
         void* ptr = NULL;
      
         if ( n > 0 ) {
         
            if ( n > max_size() ) {
         
               throw std::length_error("cc_tokenizer::allocator<>::allocate() - Integer overflow.");
            }
         
            ptr = malloc( n * sizeof(_E) );
         
            if ( ptr == NULL ) {
         
               throw std::bad_alloc();
            }
         
         }
        
         return static_cast<pointer>(ptr); 
      }
       
      void deallocate(pointer ptr, size_type n = static_cast<size_type>(0)) {
       
         if ( ptr ) {
          
            free(ptr);
         } 
      }      
};

};

#endif

