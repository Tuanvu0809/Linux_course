#ifndef SERCURITY_H
#define SERCURITY_H
    typedef struct{
        void (*mode_ser) (char *mode);
        void (*active_arlam) (void);
        void (*deactive_arlam) (void);

    }Sercurity_mode;

    Sercurity_mode *Creat_sercuirty();
#endif