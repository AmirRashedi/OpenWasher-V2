#include "stm32f10x.h"
#include "commandsHandler.h"
#include "uart_driver.h"

volatile uint8_t txbuffer[TXBUFFERSIZE];
volatile uint8_t* txreadhandler = (uint8_t*)txbuffer;
volatile uint8_t* txwritehandler = (uint8_t*)txbuffer;

volatile uint8_t rxbuffer[RXBUFFERSIZE];
volatile uint8_t rxnum;
volatile uint8_t rxlength;
volatile uint8_t crc = 0;

volatile enum e_rxstate
{
	STARTTOKEN,
	LENGTH,
	PACKET,
	CRCTOKEN
} rxstate = STARTTOKEN;

void USART1_IRQHandler()
{
	if (USART1->SR & USART_SR_TXE)
	{
		if (txreadhandler == txwritehandler)
			USART1->CR1 &= ~USART_CR1_TXEIE;
		else
		{
			USART1->DR = *txreadhandler++;
			if (txreadhandler == txbuffer + TXBUFFERSIZE)
				txreadhandler = (uint8_t*)txbuffer;
		}
	}
	if (USART1->SR & USART_SR_IDLE)
	{
		USART1->DR;
		rxstate = STARTTOKEN;
	}
	if (USART1->SR & USART_SR_RXNE)
	{
		uint8_t data = USART1->DR;
		switch(rxstate)
		{
			case STARTTOKEN:
				if(data == 0xAB)
					rxstate = LENGTH;
				break;
			case LENGTH:
				crc = addcrc(0x8F, data);
				rxlength = data;
				if(rxlength)
					rxstate = PACKET;
				else
					rxstate = CRCTOKEN;
				rxnum = 0;
				break;
			case PACKET:
				crc = addcrc(crc, data);
				rxbuffer[rxnum++] = data;
				if(rxnum == rxlength)
					rxstate = CRCTOKEN;
				break;
			case CRCTOKEN:
				if(data == crc)
				{
					processCommand((uint8_t*)rxbuffer, rxlength);
				}
				rxstate = STARTTOKEN;
				break;
		}
	}
}

void send(uint8_t data)
{
	//while(!(USART1->SR & USART_SR_TXE));
	//USART1->DR = data;

	uint8_t* nexttx =
			(txwritehandler == txbuffer + TXBUFFERSIZE - 1) ?
					txbuffer : txwritehandler + 1;

	if (!(USART1->CR1 & USART_CR1_TXEIE))
	{
		//�������� �� ���� - ����� ���� ������
		USART1->DR = data;
		USART1->CR1 |= USART_CR1_TXEIE;
	} else
	{
		//���� ������� rx � �������� �������, ����
		while (nexttx == txreadhandler);

		*txwritehandler = data;
		txwritehandler = nexttx;
	}
}

void send16(uint16_t data)
{
	send(data >> 8);
	send(data);
}

//���������� stdio
int _write(__attribute__((unused)) int file, char *ptr, int len)
{
	if(len>253)
		len = 253;

	send(0xAB);
	//
	uint8_t crc = addcrc(0x8F, len+1);
	send(len+1);
	//
	crc = addcrc(crc, 0x58);
	send(0x58);
	for(uint8_t i = 0; i < len; i++)
	{
		crc = addcrc(crc, ptr[i]);
		send(ptr[i]);
	}
	//
	send(crc);
	//
	return len;
}

void send_event(enum eventcode code)
{
	send(0xAB);
	send(2);
	send(0x5E);
	//
	uint8_t crc = addcrc(0x62, code);
	send(code);
	send(crc);
}

void send_event1args(enum eventcode code, uint8_t arg)
{
	send(0xAB);
	send(3);
	send(0x5E);
	//
	uint8_t crc = addcrc(0xA6, code);
	send(code);
	crc = addcrc(crc, arg);
	send(arg);
	send(crc);
}


void send_error(enum errorcode code)
{
	send(0xAB);
	send(2);
	send(0x5B);
	//
	uint8_t crc = addcrc(0x5D, code);
	send(code);
	send(crc);
}

void waittransmissionend()
{
	while(USART1->CR1 & USART_CR1_TXEIE);
	while(!(USART1->SR & USART_SR_TC));
}

uint8_t addcrc(uint8_t crc, uint8_t data)
{
	for (uint8_t p = 0; p < 8; p++)
	{
		if ((crc ^ data) & 0x01)
		{
			crc = ((crc >> 1) ^ 0x8C);
		} else
		{
			crc >>= 1;
		}
		data >>= 1;
	}

	return crc;
}
