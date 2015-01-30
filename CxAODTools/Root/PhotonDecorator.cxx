
#include "CxAODTools/PhotonDecorator.h"

template <>
PhotonDecorator::MapIntDec ObjectDecorator<PhotIntProps, PhotFloatProps>::m_intDecs = {};

template <>
PhotonDecorator::MapIntAcc ObjectDecorator<PhotIntProps, PhotFloatProps>::m_intAccs = {};

template <>
PhotonDecorator::MapFloatDec ObjectDecorator<PhotIntProps, PhotFloatProps>::m_floatDecs = {};

template <>
PhotonDecorator::MapFloatAcc ObjectDecorator<PhotIntProps, PhotFloatProps>::m_floatAccs = {};

PhotonDecorator::PhotonDecorator(){
  m_intPropNames = {
    {PhotIntProps::partIndex, "partIndex"},
    {PhotIntProps::passOR, "passOR"},
    {PhotIntProps::passORGlob, "passORGlob"},
    //TODO: Check these two
    //{PhotIntProps::isVeryLooseLH, "isVeryLooseLH"}, {PhotIntProps::isVeryTightLH, "isVeryTightLH"},
    //{PhotIntProps::isTightPP, "isTightPP"},
    {PhotIntProps::isTightIso, "isTightIso"},
    {PhotIntProps::isVBFALoosePhoton, "isVBFALoosePhoton"}, {PhotIntProps::isVBFASignalPhoton, "isVBFASignalPhoton"}
  };

  m_floatPropNames = {
    {PhotFloatProps::IDEff, "IDEff"}, {PhotFloatProps::IDEffSys, "IDEffSys"}
  };
}
