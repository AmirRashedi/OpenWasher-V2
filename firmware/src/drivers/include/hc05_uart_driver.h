/*
 * hc05_uart_driver.h
 *
 *  Created on: 3 ���. 2019 �.
 *      Author: Shironeko
 */

#pragma once

void hc05_enter_setting_mode();
void hc05_leave_setting_mode();
char* hc05_sendcommand(char* data);
