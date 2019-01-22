#pragma once

//Log acceleration and angular velocity of the car
//Support timestamped data so it can be correlated with GPS, power data, pedal, steering, etc.
//Locate the sensor as close to the center of gravity of the car as possible

#include <stdbool.h> //stdbool: Part of the C Standard Library. Defines bool, true and false.
#include "gpio.h" //gpio: Used to initialize and read/write GPIO. The read/write functions in this module are digital (i.e. true/false).
#include "interrupt.h" //interrupt: Used to initialize interrupts across supported platforms. In this case, we need it for our soft timers.
#include "log.h" //log: Defines useful log macros that are retargeted to UART and stdout on STM32 and x86 respectively.
#include "soft_timer.h" //soft_timer: Software-based timers backed by a single hardware timer. Used to create arbitrary timeouts without consuming all of our hardware timers.
#include "wait.h" //wait: Attempts to put the CPU to sleep until an interrupt. No-op on x86
#include "delay.h" // For real-time delays
#include "mbed.h"

//set up spi
//MOSI is__
//MISO is__
//SCLK is__
//gyro chip select is__

SPI spi(PTC6, PTC7, PTC5); //MOSI, MISO, SCLK
DigitalOut gyroCSPin(PTC0);

int main(){

//SPI Mode is__(0?)
	spi.format(8,0);
	spi.frequency(8000000);


//Code Steps:
//A) Test if connected with the gyroscope
// 	i) Read "who am i" register (Adress code:__) and check if the gyroscope responds
//		the id registed value should be __
	gyroCSPin = 0;
	spi.write(143);
	int who_am_i_value = spi.write(0);
	wait_us(3);
	gyroCSPin = 1;

	if(who_am_i_value == 212){
		printf("Gyroscope is working!\n")
	}else{
		printf("gyroscope is not working!\n");
	}

//B) 1)Write the 1st Gyroscope Control Register (address code:__) to :
//		sets the stampling rate to 95 stamples per second
//		enables all aces to be read
//		turns on gyroscope
	
	guroCSPin = 0;
	wait_us(3);
	spi.write(32);
	spi.write(15);
	wait_us(3);
	gyroCSPin = 1;

//	2) Write the 4th Gyroscope Control Register (address code:__) to 16:
//		sts the sensitivity range to +/- 500 degrees per second
	
	guroCSPin = 0;
	wait_us(3);
	spi.write(35);
	spi.write(16);
	wait_us(3);
	gyroCSPin = 1;

	while(true){
//C) Read data from the gyroscope
//	3) Read 2 bytes of angular velocity data around the X axis (address code:__)
	gyroCSPin = 0;
	wait_us(3);
	spi.write(232);
	short gyroXAxisLowB = spi.write(0);
	short gyroXAxisHighB = spi.write(0);
	short gyroXAxis = gyroXAxisHighB << | gyroXAsxisLowB;
	wait_us(3);
	gyroCSPin = 1;

//	4) Read 2 bytes of angular velocity data around the Y axis (address code:__)

	gyroCSPin = 0;
	wait_us(3);
	spi.write(234);
	short gyroYAxisLowB = spi.write(0);
	short gyroYAxisHighB = spi.write(0);
	short gyroYAxis = gyroYAxisHighB << | gyroYAxisLowB;
	wait_us(3);
	gyroCSPin = 1;

//	5) Read 2 bytes of angular velocity data around the Z axis (address code:__)

	gyroCSPin = 0;
	wait_us(3);
	spi.write(236);
	short gyroZAxisLowB = spi.write(0);
	short gyroZAxisHighB = spi.write(0);
	short gyroZAxis = gyroZAxisHighB << | gyroZAxisLowB;
	wait_us(3);
	gyroCSPin = 1;

	printf("Gyro: X: %d, Y: %d, Z: %d \n", gyroXAxis, gyroYAxis, gyroZAxis);
	wait(0.5);
	}
}
//Units
//Linear acceleration measurement range (g)
//Angular rate measurement range (dps)
//Linear acceleration sensitivity(mg/LSB)
//Angular rate sensitivity(mdps/LSB)

//Linear acceleration output data rate (Hz)
//Angular rate output data rate (Hz)
//(linear acceleration)*(change in time)= linear velocity
//Anglular velocity = linear velocity/radius
