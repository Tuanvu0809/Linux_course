#ifndef SENSOR_H
#define SENSOR_H

  typedef struct{
    void (*init) (void);
    float (*data)(void);
  }sensor; 
    


#endif