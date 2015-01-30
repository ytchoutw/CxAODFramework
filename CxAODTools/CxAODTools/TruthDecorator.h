#ifndef CxAODTools_TruthDecorator_H
#define CxAODTools_TruthDecorator_H

#include "ObjectDecorator.h"

enum class TruthIntProps {none };
enum class TruthFloatProps { zPV  };

class TruthDecorator : public ObjectDecorator<TruthIntProps, TruthFloatProps>
{

public:
  TruthDecorator();
  ~TruthDecorator() = default;

};

#endif
