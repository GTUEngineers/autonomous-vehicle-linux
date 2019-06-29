/**
 * \file        SteerController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "autonomousVehicle_conf.h"
#include "dwt_delay.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

SteerController::SteerController()
{
	steer_mutex = xSemaphoreCreateMutex();
}

SteerController::~SteerController()
{
	vSemaphoreDelete(steer_mutex);
}

void SteerController::set_value (int val)
{
	if(val > STEERING_MAX_RIGHT_VALUE || val < STEERING_MAX_LEFT_VALUE)
		return;

	xSemaphoreTake( steer_mutex, portMAX_DELAY );
    int dir_val = 0;
    if(get_encoder_value() > val)
        dir_val = 1;
    //sets STEER_DIRECTION_PIN_CONF according to dir_val
    switch(dir_val){
        case 1:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
            break;
        case 0:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
    last_position = val;
    xSemaphoreGive( steer_mutex);
}

int SteerController::get_value ( )
{
    return last_position;
}

float SteerController::get_encoder_value ( )
{
    return 0.0;
}

void SteerController::steer_task ( )
{
	DWT_Init();
	int count = get_encoder_value();
    while (1)
    {
    	xSemaphoreTake( steer_mutex, portMAX_DELAY );
		while(get_value() != get_encoder_value()){
			pulse();
			xSemaphoreGive( steer_mutex);
			xSemaphoreTake( steer_mutex, portMAX_DELAY );
		}
		xSemaphoreGive( steer_mutex);
    };
}

void SteerController::test ( )
{
	//RELOCATE this function call
	DWT_Init();
	// to most right by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		DWT_Delay(150);
	}
			
	// wait 1 second
    HAL_Delay(1000);
	
    // to zero point by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		DWT_Delay(150);
	}
			
	// wait 1 second
    HAL_Delay(1000);
	
    // to most left by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		DWT_Delay(150);
	}

	// wait 1 second
	HAL_Delay(1000);

    // to zero point by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		DWT_Delay(150);
	}
	
	// wait 1 second
	HAL_Delay(1000);
}

void SteerController::pulse()
{
	HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
	DWT_Delay(150);
	HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
	sDWT_Delay(150);
}
