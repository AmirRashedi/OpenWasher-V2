#include "stm32f10x.h"
#include "door_hardware.h"

//TODO: �� ��������� � ������������� ��������� - ��� ����
inline void lock_door()
{
	GPIOA->BSRR = 0x00008000;
}

inline void unlock_door()
{
	GPIOA->BSRR = 0x80000000;
}

