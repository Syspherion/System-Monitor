#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp

 private:
 unsigned long long int prevTotal = 0;
 unsigned long long int prevIdleAll = 0;

};

#endif