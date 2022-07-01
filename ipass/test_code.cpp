#include "MPU.h"
#include "hwlib.hpp"
#include "Flex.h"



void checkFinger(){
    due::pin_adc pink1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0); // pink
    due::pin_adc ring1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1); // ring
    due::pin_adc middle1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2); // middle
    due::pin_adc index1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3); // index
    due::pin_adc thumb1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4); // thumb

    for (;;) {
        float pinkF1 = Flex::getFingerAngle(pink1);         //call function from Flex to calculate the angular position of the finger
        if (pinkF1 > 5){
            hwlib::cout << "pink bend" << "\n";
        }
        float ringF1 = Flex::getFingerAngle(ring1);
        if (ringF1 > 5){
            hwlib::cout << "ring finger bend" << "\n";
        }float middleF1 = Flex::getFingerAngle(middle1);
        if (middleF1 > 5){
            hwlib::cout << "middle finger bend" << "\n";
        }
        float indexF1 = Flex::getFingerAngle(index1);
        if (indexF1 > 5){
            hwlib::cout << "index finger bend" << "\n";
        }
        float thumbF1 = Flex::getFingerAngle(thumb1);
        if (thumbF1 > 5){
            hwlib::cout << "thumb bend" << "\n";
        }

        hwlib::wait_ms(1000);
    }
}

void checkAcc(){
    int16_t accX_result = Mpu6050.getAccX();
    int16_t accY_result = Mpu6050.getAccY();
    int16_t accZ_result = Mpu6050.getAccZ();

    for (;;){
        if ((float)accX_result < 0){
            hwlib::cout << " x= right";
        }
        else if ((float)accX_result > 0){
            hwlib::cout << "x= left";
        }
        if ((float)accY_result < 0){
            hwlib::cout << "y= right";
        }
        else if ((float)accY_result > 0){
            hwlib::cout << "y= left";
        }
        if ((float)accZ_result < 0){
            hwlib::cout << "z= right";
        }
        else if ((float)accZ_result > 0){
            hwlib::cout << "z= left";
        }
    }
};