#ifndef Algorithm_DataTypes_CheckStdContainer
#define Algorithm_DataTypes_CheckStdContainer

#include <type_traits>
#include <vector>
#include <map>

namespace hepfw{
  
  template<typename>
  struct is_std_vector : std::false_type {};
  
  template<typename T, typename A>
  struct is_std_vector< std::vector<T,A> > : std::true_type {};
  
  template<typename>
  struct is_std_map : std::false_type {};
  
  template<typename T, typename A>
  struct is_std_map< std::map<T,A> > : std::true_type {};
  
}

#endif  
