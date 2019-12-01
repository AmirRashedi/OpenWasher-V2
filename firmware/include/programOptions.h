/*
 * washprograms.h
 *
 *  Created on: 3 ���. 2019 �.
 *      Author: Shironeko
 */

#pragma once

#include <stdint.h>
#include "programs.h"
#include "limits.h"

#pragma pack(push, 1)

typedef struct {
	uint8_t temperature;
	uint8_t delay;
	uint8_t washingSpeed;
	uint8_t spinningSpeed;
	uint8_t waterLevel;
	uint8_t rinsingCycles;
} programOptions;

#pragma pack(pop)


