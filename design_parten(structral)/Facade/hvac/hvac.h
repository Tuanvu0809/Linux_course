#ifndef HVAC_H
#define HVAC_H
    /*struct */
    typedef struct {
        void (*temp) (int temperator);
        void (*mode) (char *mode); 

    }Hvac_mode;

    Hvac_mode *Creat_hvac();

    

#endif