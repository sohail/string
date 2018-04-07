/* src/string_character_traits.hh
   Written by, Sohail Qayum Malik[sqm@hackers.pk] */

/*
Character traits?
-------------------
---------------------
-----------------------
C++ strings can be based on different types of characters. And each type of character can also have different properties, which are known as character traits.
The character traits for a given type define properties of this character type such as how they compare to each other, how they are moved or copied or how they type-cast to/from other types.
Each set of character traits is specified as a template specialization of this class template that has to define the public members listed below, which shall behave as explained, although the internals on how this is achieved can be freely implemented in the class template specialization for the type
*/

#include "allocator.hh"

/* Include guards */
#ifndef CC_TOKENIZER_STRING_CHARACTER_TRAITS_HH
#define	CC_TOKENIZER_STRING_CHARACTER_TRAITS_HH

namespace cc_tokenizer {

/* The template specialization for char type */
template <typename _E>
struct string_character_traits;

template<>
struct string_character_traits<char> {	

   typedef	char					   _E;
   typedef	_E					   char_type;
   
   /* Where INT_T is a type that can represent all the valid characters representable by a char_type plus an end-of-file value (eof) which is compatible with iostream class member functions */
   typedef  	int 					   int_type;
   
   typedef	allocator<char_type>::size_type		   size_type;
   typedef	allocator<char_type>::pointer		   pointer;
   typedef	allocator<char_type>::const_pointer        const_pointer;
   typedef	allocator<char_type>::reference		   reference;
   typedef	allocator<char_type>::const_reference      const_reference;

   static void assign(char_type& c1, char_type& c2) {

      c1 = c2;   	
   }
      
   static bool eq(const_reference x, const_reference y) {
    	
      return x == y;
   }

   static bool ne(const_reference x, const_reference y) {
 
	  return ! eq(x, y);   
   }
   
   static bool lt(const_reference x, const_reference y) {
   
     return x < y ; 
   }
   
   /* ! lt() does not automatically mean gt(), that is why the definition seems incomplete. Just don't forget to use the ne() method as well */
   static bool gt(const_reference x, const_reference y) {
   
      return x > y;
   }

   static char_type eos(void) {

      return '\0';
   }
   
   /* Returns the value used as end-of-file indicator. This value is a value of type int_type such that it does not compare equal to the int_type equivalents of any valid character value */
   static int_type eof(void) {
   
      return 0;
   }

   static int compare(const_pointer compared, const_pointer comparing, size_type n) {
   
      int ret = 0; 
   
      for ( size_type i = 0; i < n; i++ ) {
	  	    
         if ( gt(compared[i], comparing[i]) ) {
		 
            ret = 1;			
	    break;
         }		 
		 
         if ( lt(compared[i], comparing[i]) ) {
		 
	    ret = -1;			
	    break;
	 }	  
      }
          
      return ret;
   }
   
   static size_type length(const_pointer s) {

      size_type i = 0;

      for (; s[i] != eos();)
          i++; 
	 
	  return i;
   }

   static pointer copy(pointer dst, const_pointer src, size_type n) {

      size_type i = 0;

	  for (;i < n;) {

             dst[i] = src[i]; 
             i++;
	  }

	  return dst;       
   }

};

/* The template specialization for wide-character type */
template<>
struct string_character_traits<wchar_t> {
   
   typedef	wchar_t					   _E;
   typedef	_E					   char_type;
   
   /* Where INT_T is a type that can represent all the valid characters representable by a char_type plus an end-of-file value (eof) which is compatible with iostream class member functions */
   typedef	wint_t					   int_type;	
   
   typedef	allocator<char_type>::size_type		   size_type;
   typedef	allocator<char_type>::pointer		   pointer;
   typedef	allocator<char_type>::const_pointer    	   const_pointer;
   typedef	allocator<char_type>::reference		   reference;
   typedef	allocator<char_type>::const_reference  	   const_reference;
   
   static void assign(char_type& c1, char_type& c2) {

      c1 = c2;   	
   }
   
   static bool eq(const_reference x, const_reference y) {
    	
      return x == y;
   }

   static bool ne(const_reference x, const_reference y) {
 
	  return ! eq(x, y);   
   }
      
   static bool lt(const_reference x, const_reference y) {
   
      return x < y ; 
   }
   
   /* ! lt() does not automatically mean gt(), that is why the definition seems incomplete. Just don't forget to use the ne() method as well */
   static bool gt(const_reference x, const_reference y) {
   
      return x > y;
   }
   
   static char_type eos(void) {

      return L'\0';
   }
   
   /* Returns the value used as end-of-file indicator. This value is a value of type int_type such that it does not compare equal to the int_type equivalents of any valid character value */
   static int_type eof(void) {
   
      return 0;
   }
   
   static int compare(const_pointer compared, const_pointer comparing, size_type n) {
   
      int ret = 0; 
   
      for ( size_type i = 0; i < n; i++ ) {
	  	    
         if ( gt(compared[i], comparing[i]) ) {
		 
            ret = 1;			
	        break;
         }		 
		 
         if ( lt(compared[i], comparing[i]) ) {
		 
	        ret = -1;			
	        break;
	     }	  
      }
      
      return ret;
   }
   
   static size_type length(const_pointer s) {

      size_type i = 0;

      for (; s[i] != eos();)
          i++; 
	 
	  return i;
   }
   
   static pointer copy(pointer dst, const_pointer src, size_type n) {

      size_type i = 0;

	  for (;i < n;) {

         dst[i] = src[i]; 
         i++;
	  }

	  return dst;       
   }   
      
};

};

#endif
