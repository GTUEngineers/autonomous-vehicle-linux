/**
 * \file        SteerController.h
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

#ifndef CONTROLLERS_STEERCONTROLLER_H_
#define CONTROLLERS_STEERCONTROLLER_H_

/*------------------------------< Includes >----------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "semphr.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class SteerController
{
public:
    SteerController ( );
   ~SteerController ( );
    void set_value (int val);
    int get_value ( );
    float get_encoder_value ( );
	void test();
	void pulse();

private:
    void steer_task ( );
    //last position of the steering
    int last_position;
    SemaphoreHandle_t steer_mutex;
};

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
