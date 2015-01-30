#ifndef CxAODTools_IndexDecorator_H
#define CxAODTools_IndexDecorator_H

#include "ObjectDecorator.h"

enum class IndexIntProps { partIndex };
enum class IndexFloatProps { None };

class IndexDecorator : public ObjectDecorator<IndexIntProps, IndexFloatProps>
{

public:
  IndexDecorator();
  ~IndexDecorator() = default;

};

#endif
