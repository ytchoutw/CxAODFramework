#ifndef CxAODTools_ConfigStore_H
#define CxAODTools_ConfigStore_H

// STL includes
#include <map>
#include <string>
#include <vector>

// Forward declarations
class ConfigFieldBase;


class ConfigStore {

 public:

  // constructor
  ConfigStore();

  // copy constructor
  ConfigStore(const ConfigStore& other);

  // assignment operator
  ConfigStore& operator=(const ConfigStore& other);

  // destructor
  virtual ~ConfigStore();
  
  // get data field from store
  template <class T> 
  const T& get(const std::string& key) const;

  // get data field from store (if it is there)
  template <class T> 
  void getif(const std::string& key, T& value) const;

  // put data field in store
  template <class T> 
  void put(const std::string& key, const T& value, const bool& overwrite = false);

  // remove data field in store
  void remove(const std::string& key);
  
  // flush store (remove all entries)
  void flush();

  
  // create store from steering file
  static ConfigStore* createStore(const char* filename);
  static ConfigStore* createStore(const std::string& filename) { return createStore( filename.c_str() ) ; }


 private:

  // map of data fields
  std::map<std::string,ConfigFieldBase*> m_data;
  
  // convert string field to other type, used by createStore()
  template <class T>
  static T convertField(const std::string& value);

  // convert vector of strings field to vector of other type, used by createStore()
  template <class T, class O>
  static T convertVector(const std::vector<std::string>& value);

};

#include "CxAODTools/ConfigStore.icc"

#endif
