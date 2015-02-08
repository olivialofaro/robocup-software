#include "mbed.h"
#include "console.hpp"
#include "commands.hpp"
#include <iostream>

Ticker lifeLight;
DigitalOut ledOne(LED1);
DigitalOut ledTwo(LED2);

//testBallSense additions
DigitalOut testLED(LED4);
DigitalOut BallSenseLED(p21);
AnalogIn BallSenseIn(p16);
//testBallSense end

/**
 * timer interrupt based light flicker
 */
void imAlive()
{
    ledOne = !ledOne;
}

void testBallSense()
{
    while(1)
    {
        BallSenseLED = !BallSenseLED;
        testLED = !testLED;
        printf("%f\r\n" , BallSenseIn.read());
        wait(500);
    }
}

/**
 * system entry point
 */
int main() 
{

    lifeLight.attach(&imAlive, 0.25);
    initConsole();

    testBallSense();

    while (true)
    {
        /*
         * check console communications, currently does nothing
         * then execute any active iterative command
         */
        conComCheck();
        //execute any active iterative command
        executeIterativeCommand();

        /*
         * check if a system stop is requested
         */
        if (isSysStopReq() == true)
        {
            break;
        }

        //main loop heartbeat
        wait(0.1);
        ledTwo = !ledTwo;
    }

    //clear light for main loop (shows its complete)
    ledTwo = false;
}

