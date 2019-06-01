#pragma once

enum errorcode
{
	NOERROR = 0x0,						// ��� ������
	CRYSTAL =  0x1,						// �� ������� ��������� ��������� ���������
	PLL =  0x2,							// �� ������� ��������� PLL
	SW_PLL =  0x3,						// �� ������� ������������� �� PLL
	LSI =  0x4,							// �� ������� ��������� LSI
	HardFault =  0x5,					// ����������� ������
	MemManageFault =  0x6,				// ������ ������� ���������� �������
	BusFault =  0x7,					// ������ ����
	UsageFault =  0x8,					// ������ ���������
	WDTRESET =  0x9,					// ������������ �� watchdog
	//�����
	BAD_PUMP_RELAY =  0x10, 			// ��������� ���� ������
	BAD_PUMP =  0x11,					// ��� ������� ������
	BAD_PUMP_TRIAK =  0x12,				// ���� ������ ��� ���������� ������
	BAD_PUMP_TRIAK2 =  0x13,			// ��� ������� ��� ����������� ������
	//����������
	WATERLEVEL_UP_ON =  0x20,			// ����� ������� ������ ��������
	WATERLEVEL_DOWN_ON =  0x21,			// ����� ������ ������ ��������
	WATERLEVEL_UP_OFF =  0x22,			// �� ����������� ������� ������ ��������
	WATERLEVEL_DOWN_OFF =  0x23,		// �� �����������  ������ ������ ��������
	OVERFLOW =  0x24,					// ������������
	//���
	OVERHEAT =  0x30,					// ����������� ���� 95
	NTC_NOT_PRESENT =  0x31,			// ��� ������� � ������� �����������
	NO_HEATER =  0x32,					// ��� ������� ����
	BAD_HEATER_RELAY =  0x33,			// ��� ������� ����
	HEATER_RELAY_STICKING =  0x34,		// ���� ���� �������
	TRY_SET_HEAT_WITHOUT_WATER =  0x35, // ��������� ������� ��� ����
	SET_HEAT_OVER90 =  0x36, 			// ������� ��������� ����������� ���� 90
	//���������
	NO_ENGINE =  0x40,					// ��� ������� ���������
	ENGINE_RELAYCW_STICKING =  0x41,	// ��������� ���� ��������� 1
	ENGINE_RELAYCCW_STICKING =  0x42,	// ��������� ���� ��������� 2
	NO_TACHO =  0x43,					// ��� ������� � ��������� ��� ��������� �� ��������������
	PID_ERROR =  0x44,					//
	//������
	NO_LOCKER = 0x50,					// ��� ������� �� �������
	BAD_DOOR_TRIAK = 0x51,				// ��� ������� �� �������
	BAD_DOOR_TRIAK2 = 0x52,				// ���� ������ �� ������� ��� ����������� ���������
	TRY_OPEN_DOOR_WITH_WATER =  0x53,   // ������� �������������� ������ ��� ��������� ����
	//�������
	TRY_OPEN_WATER_WITH_OPEN_DOOR =  0x60,	// ������� ������� ���� ��� �������� ������
	TRY_OPEN_WATER_WITH_WATER =  0x61,	// ������� ������� ���� ��� ��������� ����
	//eeprom
	EEPROM_EMPTY =  0x70,				// ��� ������� ������
	EEPROM_BADCRC =  0x71,				// ������������ crc
	EEPROM_LOCK =  0x72,				// ���������� ������ �� ��������� � �������������
	EEPROM_WRITEERROR =  0x73,			// �� ������� �������� �����y
};

void set_error(enum errorcode code);
void set_warning(enum errorcode code);

