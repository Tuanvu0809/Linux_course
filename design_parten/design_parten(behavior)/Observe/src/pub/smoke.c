#include <stdio.h>
#include "../../inc/pub/smoke.h"

  void Creat_smoke_sensor(smoke_sensor *sensor)
  {
        creat_pub(&sensor->base);

        sensor->is_moke = no_smoke;

  }

   void trigger_s(smoke_sensor *sensor, smoke_status Have_smoke)
   {
        sensor->is_moke = Have_smoke;

        if(Have_smoke = have_smoke)
        {
            sensor->base.notify(&sensor->base,"Have Smoke");
        }
        else {
            sensor->base.notify(&sensor->base, "No smoke");
        }

   }