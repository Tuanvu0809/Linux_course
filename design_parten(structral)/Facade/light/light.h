#ifndef LIGHT_T
#define LIGHT_T

    /*struct Light*/
    typedef struct{
        void (*Turn_on) (void);
        void (*Turn_off) (void);
        void (*Set_bright_ness) (int level);
    }Light_mode;

    Light_mode *Creat_light();
    
    

#endif