#ifndef CxAODTools_EnumHasher_H
#define CxAODTools_EnumHasher_H

#ifndef __MAKECINT__ // CINT, you're definitely too stupid for this

#include <type_traits>
#include <functional>

// All hail stackoverflow
// Generic hash function for strongly typed enums

// Why do we need it:
// we can't use simple enums for decorators because different enums with same name for value
// inside are ambiguous in C
// we can't use simple map instead of unordered_map because of gcc 4.7, and Accessors and
// Decorators don't have empty constructors. So we can't use map::emplace (4.7),
// neither map::operator[] (empty ctors required)
// Yay !


template<typename enum_type>
struct EnumHash
{
  typedef typename std::underlying_type< enum_type >::type underlying_type;
  typedef typename std::hash< underlying_type >::result_type result_type;
  result_type operator()( const enum_type& arg ) const
  {
    std::hash< underlying_type > hasher;
    return hasher( static_cast< underlying_type >( arg ) );
  }
};

#endif // not __MAKECINT__

#endif
