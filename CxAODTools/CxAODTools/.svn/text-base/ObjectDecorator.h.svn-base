#ifndef CxAODTools_ObjectDecorator_H
#define CxAODTools_ObjectDecorator_H

#ifndef __MAKECINT__

#include <unordered_map>
#include <map>
#include <cstdlib>

#include "EnumHasher.h"

#include "AthContainers/AuxElement.h"

template < typename IntProps, typename FloatProps >
class ObjectDecorator {
  public:
    typedef typename
      std::unordered_map<IntProps, SG::AuxElement::Decorator<int>, EnumHash<IntProps>>
      MapIntDec;
    typedef typename
      std::unordered_map<IntProps, SG::AuxElement::Accessor<int>, EnumHash<IntProps>>
      MapIntAcc;
    typedef typename
      std::unordered_map<FloatProps, SG::AuxElement::Decorator<float>, EnumHash<FloatProps>>
      MapFloatDec;
    typedef typename
      std::unordered_map<FloatProps, SG::AuxElement::Accessor<float>, EnumHash<FloatProps>>
      MapFloatAcc;

  protected:

    static MapIntDec m_intDecs;
    static MapIntAcc m_intAccs;
    static MapFloatDec m_floatDecs;
    static MapFloatAcc m_floatAccs;

    std::map<IntProps, std::string> m_intPropNames;
    std::map<FloatProps, std::string> m_floatPropNames;


    template <class T>
      void setAuxValue(
          T value,
          const SG::AuxElement* object,
          SG::AuxElement::Decorator<T>& deco,
          SG::AuxElement::Accessor<T>& acce,
          std::string &name);
    template <class T>
      T getAuxValue(
          const SG::AuxElement* object,
          SG::AuxElement::Accessor<T>& acce,
          std::string &name);
    template <class T>
      bool getAuxValue(
          const SG::AuxElement* object,
          SG::AuxElement::Accessor<T>& acce,
          T &value,
          std::string& );
    template <class T>
      bool existsAuxValue(
          const SG::AuxElement* object,
          SG::AuxElement::Accessor<T>& acce);

  public:
    ObjectDecorator() = default;
    ~ObjectDecorator()= default;

    SG::AuxElement::Decorator<int>& dec(IntProps p);
    SG::AuxElement::Decorator<float>& dec(FloatProps p);

    SG::AuxElement::Accessor<int>& acc(IntProps p);
    SG::AuxElement::Accessor<float>& acc(FloatProps p);

    int get(const SG::AuxElement* particle, IntProps p);
    float get(const SG::AuxElement* particle, FloatProps p);

    bool get(const SG::AuxElement* particle, IntProps p, int& value);
    bool get(const SG::AuxElement* particle, FloatProps p, float& value);

    bool exists(const SG::AuxElement* particle, IntProps p);
    bool exists(const SG::AuxElement* particle, FloatProps p);

    void set(const SG::AuxElement* particle, IntProps p, int value);
    void set(const SG::AuxElement* particle, FloatProps p, float value);

    void copy(const SG::AuxElement* pIn, SG::AuxElement* pOut, IntProps p);
    void copy(const SG::AuxElement* pIn, SG::AuxElement* pOut, FloatProps p);
};

//=============================================================================
// Define the implementation of the methods here in the header file.
// This is done since we are dealing with a templated functions!
//=============================================================================

#include "CxAODTools/ObjectDecorator.icc"

#endif // __MAKECINT__

#endif //CxAODMaker_ObjectDecorator_H
