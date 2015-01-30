#ifndef CxAODTools_ConfigFieldBase_H
#define CxAODTools_ConfigFieldBase_H


class ConfigFieldBase {

 public:
  
  // constructor
  ConfigFieldBase() {};

  // destructor
  virtual ~ConfigFieldBase() {};
  
  // clone 
  virtual ConfigFieldBase* clone() const = 0;

};

#endif
