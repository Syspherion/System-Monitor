#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

 unsigned long long int prevTotal = 0;
 unsigned long long int prevIdleAll = 0;

};

#endif