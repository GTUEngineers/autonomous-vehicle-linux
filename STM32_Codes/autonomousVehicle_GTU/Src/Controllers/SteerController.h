/**
 * \file        SteerController.h
 * \brief       A brief description one line.
 *
 * \author      tolga
 * \date        6 Tem 2019
 */

#ifndef CONTROLLERS_STEERCONTROLLER_H_
#define CONTROLLERS_STEERCONTROLLER_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/
pinSettings STEER_DIRECTION_PIN_CONF = { GPIOF, GPIO_PIN_6 };
pinSettings STEER_PULSE_PIN_CONF = { GPIOF, GPIO_PIN_7 };
/*------------------------------< Prototypes >--------------------------------*/

//initialization function of steering
void steer_construct ( );
//deletes mutex MIGHT BE RENAMED
void steer_destruct ( );
void steer_set_value (int val);
int steer_get_value ( );
float steer_get_encoder_value ( );
void steer_test ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
