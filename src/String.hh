/* src/String.hh
   Written by, Sohail Qayum Malik[sqm@hackers.pk] */

#include "allocator.hh"
#include "input_iterator.hh"   
#include "string_character_traits.hh"

/* Include guards */
#ifndef	CC_TOKENIZER_STRING_HH
#define	CC_TOKENIZER_STRING_HH

namespace cc_tokenizer {

template < typename E, class T = string_character_traits<E>, class A = allocator<E> >
class String {

   public:
 
      typedef	typename A::value_type		value_type; 
      typedef	typename A::size_type		size_type; 
      typedef	typename A::difference_type	difference_type;
      typedef	typename A::reference		reference;
      typedef	typename A::const_reference	const_reference;
      typedef	typename A::pointer 		pointer;
      typedef	typename A::const_pointer 	const_pointer;
      
      typedef	typename std::iterator_traits<input_iterator<E, String<E, T, A> > >::value_type iterator;
      
      enum _NPOS_string { npos = (static_cast<typename A::size_type>(0) + static_cast<typename A::size_type>(-1))/sizeof(E)  };
   
      /* Constructors, default constructible */
      String(void) : str(NULL), size_of_str(size_type(0)), capacity_of_str(size_type(0)) {
      }
     
      /* Constructors, copy constructor */ 
      String(const String<E, T, A>& ref) {
      
         allocator<E> alloc_obj;
         
         try {
         
            str = alloc_obj.allocate(ref.capacity());
            
            if ( str ) {
            
               T::copy(str, ref.str, ref.size());
               size_of_str = ref.size();
               capacity_of_str = ref.capacity();
            }
            else {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
             
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0); 
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
      }
      
      String(const String<E, T, A>& ref, size_type pos, size_type n ) {
      
         if ( ( pos + n ) <= ref.capacity() ) {
         
            allocator<E> alloc_obj;
           
            try {   
               str = alloc_obj.allocate(n);
            
               if ( str ) {
               
                  T::copy(str, ref.str + pos, n);
                  size_of_str = n;
                  capacity_of_str = n;
               }
               else {
            
                  str = NULL;
                  size_of_str = size_type(0);
                  capacity_of_str = size_type(0);
               }
            } 
            catch(std::bad_alloc& e) {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
            catch(std::length_error& e) {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
         }
         else {
      
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
        }       
      }
      
      String(const_pointer ptr, size_type n) {
      
         allocator<E> alloc_obj;
         /* SONI-NOW */
         //std::cout<<"In String(const_pointer, size_type), n = "<<n<<std::endl;
         try {
         
            str = alloc_obj.allocate(n);
            
            if ( str ) {
            
               T::copy(str, ptr, n);
               size_of_str = size_type(n);
               capacity_of_str = size_type(n);   
            }
            else {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
         
      }

      String(const_pointer ptr) {
      
         allocator<E> alloc_obj;
        
         size_of_str = T::length(ptr);
         capacity_of_str = size_of_str + size_type(1);
         
         try {
         
            str = alloc_obj.allocate(capacity_of_str);
            
            if ( str ) {
            
               value_type eos = T::eos();   
            
               T::copy(str, ptr, size());
               T::assign(str[size()], eos);               
            }
            else {
            
               str = NULL;
               size_of_str = 0;
               capacity_of_str = 0;
            }
            
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
      }
      
      String(size_type n, value_type c) {
      
         cc_tokenizer::allocator<E> alloc_obj;
         
         try {
         
            str = alloc_obj.allocate(n);
            
            if ( str && n ) {
               
               for ( size_type i = 0; i < n; i++ ) {
               
                  T::assign(str[i], c);
               }
               
               size_of_str = n;
               capacity_of_str = n;
            }
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
      }

      /* --------------------------------------------------------- */
      /*     Converts a number into an instance of String<...>     */
      /* The following two constructors does as stated previously  */
      /* --------------------------------------------------------- */
      /* n, a signed number */
      String(typename string_character_traits<E>::int_type n) {

         str = NULL;
	 size_of_str = 0;
	 capacity_of_str = 0;
      }

      /* pos, an unsigned number */
      String(size_type pos) {

	 pointer new_str = NULL;
	 cc_tokenizer::allocator<E> alloc_obj;

	 str = NULL;
	 size_of_str = 0;
	 capacity_of_str = 0;

	 try {
	    /* Generate ASCII representation of the number in the reverse order */
	    do {

	       new_str = alloc_obj.allocate(size_of_str + 1); 
	       T::copy(new_str + 1, str, size_of_str);
               value_type rem = value_type(pos % 10 + '0') /* get remainder for the unit place */;
	       T::assign(*new_str, rem);

               if ( str ) {

	          alloc_obj.deallocate(str, size_of_str);
	       }

	       str = new_str;
	       size_of_str = size_of_str + 1;
	       capacity_of_str = size_of_str;

	    } while( (pos = pos / 10) > 0 ) /* Deducts multiple of 10 and stores back the remainder */;

	 }
	 catch (std::bad_alloc &e) {

	    str = NULL;
	    size_of_str = 0;
	    capacity_of_str = 0;
	 }
	 catch (std::length_error &e) {

	    str = NULL;
	    size_of_str = 0;
	    capacity_of_str = 0;
	 }
      }
      
      const_pointer data(void) const {

         return str;
      }
      
      const_pointer c_str(void) {
      
         const_pointer ret = NULL;
         
         //std::cout<<"In c_str()-> capacity() = "<<capacity()<<", size() = "<<size()<<std::endl;
         
         if ( capacity() > size() ) {
         
            //std::cout<<"- 1"<<std::endl;
         
            if ( T::ne(str[size()], T::eos()) ) {
            
               //std::cout<<"- 2"<<std::endl;
              
               value_type eos = T::eos();  
               T::assign(str[size()], eos);               
            }
            
            //std::cout<<"Here ,,,,,,,,,,"<<std::endl;              
            ret = str;
         }
         else { /* resize. Capacity is equal(atleast and atmost) to size, as capacity can never be less than of size, ever */
         
            //std::cout<<"- 3"<<std::endl;
            resize(size() + 1, T::eos());
            size_of_str = size_of_str - 1; /* because, the end of line character is not a part of the actual E array */
            ret = str;
         } 
         
         //std::cout<<"AND HERE......."<<std::endl;
         return ret;
      } 
      
      size_type capacity(void) const {
      
         return capacity_of_str;
      }
      
      size_type size(void) const {
      
         return size_of_str;
      }
      
      size_type max_size(void) const { 
      
         allocator<E> alloc_obj;
      
         return alloc_obj.max_size() - static_cast<size_type>(1);
      }
      
      void resize(size_type n, value_type c) throw (std::length_error) {
      
         if ( n > max_size() ) {
         
            throw std::length_error("cc_tokenizer::String<>::resize() - Integer overflow");
         }
         
         if ( n > size() ) {
         
            if ( n > capacity() ) { /*  */
            
               allocator<E> alloc_obj;
               
               try {
               
                  pointer new_str = alloc_obj.allocate(n);
                  
                  if ( new_str ) {
                  
                     size_type i = 0;
                  
                     for ( ; i < size(); ) {
                     
                        T::assign(new_str[i], str[i]);
                        i++;
                     }
                     for ( ; i < n; ) {
                     
                        T::assign(new_str[i], c); 
                        i++;
                     }
                     
                     alloc_obj.deallocate(str);
                     
                     str = new_str;
                     size_of_str = n;
                     capacity_of_str = n;   
                  }
                  
               }
               catch(std::bad_alloc& e) {
               }
               catch(std::length_error& e) {
               }
            }
            else { /* n is capacity(), atmost */
            
               for ( size_type i = size(); i < n; i++ ) {
               
                  T::assign(str[i], c);
               }
            }
         }
         else { /* n is atmost size(), we'll truncate the string, atmost */
         
            size_of_str = n;
            /* capacity_of_str remains unchanged */
         }
         
      }
                  
      String<E, T, A>& operator+(const String<E, T, A>& ref) throw(std::length_error) {
      
         pointer new_str;
         allocator<E> alloc_obj;
         
         if ( (size() + ref.size()) > max_size() ) {
           
            throw std::length_error("cc_tokenizer::String<>::operator+(const String<>&) - Integer overflow.");   
         }
         
         try {                                                      
            new_str = alloc_obj.allocate(size() + ref.size());
            
            if ( new_str ) {
            
               T::copy(new_str, str, size());
               T::copy(new_str + size(), ref.str, ref.size());
               
               alloc_obj.deallocate( str );
           
               str = new_str;    
               size_of_str = size() + ref.size();
               capacity_of_str = size();
            }
            
         }
         catch(std::bad_alloc& e) {
         }
         catch(std::length_error& e) {
         }
         
         return *this;
      }
      
      String<E, T, A> substr(size_type pos = 0, size_type len = npos) const throw(std::out_of_range){
      
      
         //std::cout<<"pos = "<<pos<<", len = "<<len<<std::endl;
         
         /* If pos is greater than the string length, it throws out_of_range */
         if (pos > size()) {
         
            /* TODO, it is causing segmentation fault */
            throw new std::out_of_range((String<E, T, A>("Index(pos) = ") + String<E, T, A>(pos) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str() );
         }
         
         if (pos == size()) {
         
            return String<E, T, A>();
         }
         
         /* TODO, When len equals npos then, following code block does not get executed */
         if ((pos + len) > size()) {
                     
            len = size() - pos;
         }
        //std::cout<<"pos = "<<pos<<", len = "<<len<<std::endl;                                         
         return String<E, T, A>(this->data() + pos, len);
      }
      
      value_type operator[](size_type pos) const {
      
         return data()[pos];
      }
      
      /* Modifiers begin here */
      /* -------------------- */
      String<E, T, A>& erase(size_type pos = 0, size_type len = npos) throw(std::out_of_range)
      {
          /* pos, originates at zero */
	  /* TODO, consider using capacity() in place of size() */
          if (pos + len > size())
	  {
	      throw std::out_of_range((String<E, T, A>("Index(pos + len) = ") + String<E, T, A>(pos + len) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str());
	  }

	  allocator<E> alloc_obj;
	  pointer new_str = alloc_obj.allocate(size() - len);

	  T::copy(new_str, str, pos);
	  T::copy(new_str + pos, str + pos + len, size() - (pos + len));

	  alloc_obj.deallocate(str);
	  size_of_str = size() - len;
	  capacity_of_str = size_of_str;
	  str = new_str;

          return *this;
      }

      /* 
       * pos, position of the first character of type T to be replaced. If it is greater than the size/length of the string then out_of_range exception is thrown
       * len, number of characters to be replaced with the "T c". If string is shorter, as many characters as possible are replaced. A value of String<...>::npos indicates all characters untill the end of string(The sub-string of the whole string relative to "pos" that will be replaced by the "n" copies of the "c")
       * n, size of "T c"(number of characters to copy)
       * c, character value repeated n times
       */ 
      String<E, T, A>& replace(size_type pos, size_type len, size_type n, E c) throw(std::out_of_range) {

         /* pos, originates at zero */
	 /* TODO, consider using capacity() in place of size() */
         if ( pos >= size() ) {

	    throw std::out_of_range((String<E, T, A>("Index(pos) = ") + String<E, T, A>(pos) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str() );
	 }

         /* If string is shorter than the number of replacements relative to pos  then, adust the len. len can be equal to String<...>::npos as well */
         if ( len == npos ) {

	    len = size() - pos;  

	 } else if ( ( pos + len ) > size() ) {

	    len = len - ( ( pos + len ) - size() );
	 }

         /* Note:- "len" and "n" are mutually exclusive */ 
	 /* Note:- len, length of the portion/part of the string that will be replaced by the n copies of "c" */

	 if ( len == n ) {

	    for ( size_type i = pos; i < pos + n; i++ ) {

	       T::assign(str[i], c);  
	    }

	    return *this;
	 }

         /* len and n can now be not equal */  
	 if ( size() > ( size() - len + n ) ) { /* happens when len > n */

	    for ( size_type i = pos; i < (pos + n); i++ ) {

	       T::assign(str[i], c);
	    }
            for ( size_type i = pos + len; i < size(); i++ ) {
	      
	       T::assign(str[i - (len - n)], str[i]);
	    }

	    size_of_str = size() - len + n;
	    /* capacity_of_str, it remains unchanged. It atleast is equal to the previous size of the now changed string */

	 }
	 else if ( capacity() > ( size() - len + n ) ) { /* happens if len < n */
            for ( size_type i = pos + len; i < size() + (n - len); i++ ) {

	       T::assign(str[i + (n - len)], str[i]);
            }

	    for ( size_type i = pos; i < pos + n; i++ ) {

               T::assign(str[i], c); 
	    }

	    size_of_str = size_of_str + (n - len);
            /* capacity_of_str, it remains unchanged. All changes were in the outer bounds of the capacity */
	 } 
	 else { /* Reallocate, n > len and size of new string is capacity() + (n - len)  */
	    allocator<E> alloc_obj;
	    pointer new_str = alloc_obj.allocate(capacity() + ( n - len ));
            
            T::copy(new_str, str, pos);

	    for ( size_type i = pos; i < pos + n; i++ ) {

               T::assign(new_str[i], c);
	    }

	    for ( size_type i = pos + len; i < size() ; i++ ) {

               /* pos + n + ( i - ( pos + len ) ) */ 
               T::assign(new_str[n + i - len], str[i] );     
	    }

	    if ( str ) {

	       alloc_obj.deallocate(str, capacity());
	    }

            str = new_str; 
	    size_of_str = capacity() + ( n - len );
	    capacity_of_str = size_of_str;
	 }

         return *this;
      }
      /* Modifiers end here */
      
      size_type find(const_pointer s, size_type pos, size_type n) const {
      
         String<E, T, A> str(s, n);
         
         return find(str, pos);
      } 
      
      size_type find(value_type c, size_type pos = 0) const {
     
         /*
	  * TODO, sizeof of value_type should be a function
	  */
         String<E, T, A> str(1, c);
      
         return find(str, pos);
      }  
      
      size_type find(const String<E, T, A>& str, size_type pos = 0) const {
      
         size_type ret = String<E, T, A>::npos;
         
         if ( pos < size() && str.size() <= (size() - pos) ) {
         
            size_type i = pos, idx = pos, j = 0;
            
            for (; i < size(); ) {
            
               if ( T::eq(this->str[i], str[i - idx]) ) {
               
                  if ( j == (str.size() - 1) ) {
                  
                     ret = idx;
                     break;
                  }
                  
                  j++;
               }
               else {
               
                  i = idx;
                  idx = idx + 1;
                  j = 0;
               }
               
               i++;
            } 
         }
         
         return ret;    
      }

      size_type rfind(const String<E, T, A>& str, size_type pos = String<E, T, A>::npos) const {

         size_type ret = String<E, T, A>::npos, idx = 0;
         
         if (pos >= size()) {
            pos = size() - 1;
         }
         
         if (str.size() > 0 && pos >= (str.size() - 1)) {
            
            while ((idx=find(str, idx)) < pos) {
            
               ret = idx;
               idx = idx + str.size();
            }                                    
         }
                  
	     return ret;
      }

      size_type rfind(value_type c, size_type pos = String<E, T, A>::npos) const {

         /*
	  * TODO, sizeof value_type should be the function
	  */ 
         String<E, T, A> str(1, c); 


	 return rfind(str, pos);
      }

      typename T::int_type compare(const String<E, T, A>& ref) const {

         typename T::int_type ret = size() - ref.size();

         if ( !ret ) 
	 {
            ret = T::compare(data(), ref.data(), size());    
         }

         return ret;
      }

      /*
       *  @brief Compare substring to a string
       *  @pos Index of first character of substring
       *  @n Number of characters in substring
       *  @str String to compare against
       *  @return <0, 0, >0
      */
      typename T::int_type compare(size_type pos, size_type n, const String<E, T, A>& ref) const {

         String<E, T, A> str(*this, pos, n);

         return str.compare(ref);
      }
   
   private:      
      pointer str;
      size_type size_of_str;
      size_type capacity_of_str;    
};
};

#endif
