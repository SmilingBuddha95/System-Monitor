#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>


// std::vector<float> prev_stats{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
   std::vector<float> prev_stats{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
};

#endif
