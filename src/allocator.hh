/* src/allocator.hh
   Written by, Sohail Qayum Malik */

#include<stdexcept>
#include<stdlib.h>

/* Include guards */
#ifndef CC_TOKENIZER_ALLOCATOR_HH
#define	CC_TOKENIZER_ALLOCATOR_HH

namespace cc_tokenizer {

template <typename E>
class allocator;

template <>
class allocator<char> {

   public:
      typedef	char			  value_type;
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
    
         return (static_cast<size_type>(0) + static_cast<size_type>(-1)) / sizeof(value_type); 
      }
      
      pointer allocate(const size_type n) const throw(std::bad_alloc, std::length_error) {
      
         void* ptr = NULL;
      
         if ( n > 0 ) {
         
            if ( n > max_size() ) {
         
               throw std::length_error("cc_tokenizer::allocator<>::allocate() - Integer overflow.");
            }
         
            ptr = malloc( n * sizeof(value_type) );
         
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

template <>
class allocator<unsigned char> {

   public:
      typedef	unsigned char			  value_type;
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
    
         return (static_cast<size_type>(0) + static_cast<size_type>(-1)) / sizeof(value_type); 
      }
      
      pointer allocate(const size_type n) const throw(std::bad_alloc, std::length_error) {
      
         void* ptr = NULL;
      
         if ( n > 0 ) {
         
            if ( n > max_size() ) {
         
               throw std::length_error("cc_tokenizer::allocator<>::allocate() - Integer overflow.");
            }
         
            ptr = malloc( n * sizeof(value_type) );
         
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

template <>
class allocator<wchar_t> {

   public:
      typedef	wchar_t			  value_type;
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
    
         return (static_cast<size_type>(0) + static_cast<size_type>(-1)) / sizeof(value_type); 
      }
      
      pointer allocate(const size_type n) const throw(std::bad_alloc, std::length_error) {
      
         void* ptr = NULL;
      
         if ( n > 0 ) {
         
            if ( n > max_size() ) {
         
               throw std::length_error("cc_tokenizer::allocator<>::allocate() - Integer overflow.");
            }
         
            ptr = malloc( n * sizeof(value_type) );
         
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

