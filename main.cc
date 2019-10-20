/*
 * main.cc 
*/

#include <iostream>

#include "src/String.hh"

using namespace::cc_tokenizer;

int main(int argc, char* argv[]) {
  
    String<char> ss("Sohail Qayum Malik");
    /* pos, len, n, c */
    ss.replace(10, 5, 0, 'Q');
    std::cout<<ss.c_str()<<std::endl;

    String<char> obj("help");
    String<char> obj1("help");
    std::cout<<obj.compare(obj1)<<std::endl;

    String<char> sqm("Sohail Qiyum MaliQ");
    std::cout<<sqm.size()<<std::endl;
    std::cout<<sqm.rfind('i', 18)<<std::endl;
  
    String<char> s("Sohail");
  
    String<char> q("Qayum");
    String<char> m("Malik");
  
    std::cout<<s.substr(2, 20).c_str()<<std::endl;
  
    std::cout<<"s.size() = "<<s.size()<<", q.size() = "<<q.size()<<", m.size() = "<<m.size()<<std::endl;
  
    std::cout<<s.c_str()<<std::endl;
    s + q + m;
    std::cout<<s.c_str()<<std::endl;
  
    std::cout<<(s + q + m).c_str()<<std::endl;  
    std::cout<<String<char>("Sohail Qayum Malik").c_str()<<std::endl;
  
    String<char> name(s + q + m);
  
    std::cout<<s.c_str()<<" "<<q.c_str()<<" "<<m.c_str()<<std::endl;
  
    String<char> oneMoreTime(s + q + m);
  
    std::cout<<"Name = "<<name.c_str()<<std::endl;
  
    std::cout<<"Name = "<<oneMoreTime.c_str()<<std::endl;
   
#ifdef ALA_DEBUGFLAG
    std::cout<<"Hola!"<<std::endl;
#endif   

   return 0;
}
