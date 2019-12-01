/*
 * startprogram.c
 *
 *  Created on: 20 ����. 2019 �.
 *      Author: Shironeko
 */

#include <stdbool.h>
#include "stm32f10x.h"
#include "commandsRoutine.h"

extern volatile bool ct;

void processStopProgramCommand(__attribute__((unused)) uint8_t* buffer,__attribute__((unused)) uint8_t count)
{
	ct = true;
	send_answer(stopProgramPacketType, NOEEROR);
}


