#include <stdio.h>
#include "pub/smoke.h"

  void Creat_smoke_sensor(smoke_sensor *sensor)
  {
        creat_pub(&sensor->base);

        sensor->ismoke = nosmoke;

  }

   void trigger_s(smoke_sensor *sensor, smoke_status Have_smoke)
   {
        sensor->ismoke = Have_smoke;

        if(Have_smoke = havesmoke)
        {
            sensor->base.notify(&sensor->base,"Have Smoke");
        }
        else {
            sensor->base.notify(&sensor->base, "No smoke");
        }

   }