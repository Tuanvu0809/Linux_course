#ifndef CONFIG_H
#define CONFIG_H

/* Mode */
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL,
    EXIT_CHOICE,
} MODE;

/*Status*/
typedef enum
{
    PUMP_OFF,
    PUMP_ON,
} STATUS;

/* Led Status*/
typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LED_STATUS;

typedef struct
{
    int Temperature;
    int Moisture;
} data;

typedef struct
{
    int moisture_min;
    int moisture_max;
    int times;
    int check;
    MODE Mode_sys;
} SETTING;

#endif
