#include "hwlib.hpp"
#include "MPU.h"
#include "Flex.h"
#include "test_code.cpp"


// converts the negative values to positive values
int minus(int value) {
    if (value < 0) {
        value *= -1;
        return value;
    } else {
        return value;
    }
}

// reads all values and prints them in the console
void read() {
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    hwlib::i2c_bus_bit_banged_scl_sda bus(scl, sda);

    Mpu6050 Mpu6050(bus);
    Mpu6050.startup();

///// TEMP VALUES ////////////////////////////////////

    int check = 0;

///// ACCELORAMOTOR VALUES ////////////////////////////////////
    float acc_x = 0;
    int acckommaX = 0;
    float acc_y = 0;
    int acckommaY = 0;
    float acc_z = 0;
    int acckommaZ = 0;

///// GYROSCOPE VALUES ////////////////////////////////////
    float gyro_x = 0;
    int gyrkommaX = 0;
    float gyro_y = 0;
    int gyrkommaY = 0;
    float gyro_z = 0;
    int gyrkommaZ = 0;



///// FLEXSENSOR VALUES ////////////////////////////////////
//    due::pin_adc pink1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0); // pink
//    due::pin_adc ring1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1); // ring
//    due::pin_adc middle1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2); // middle
//    due::pin_adc index1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3); // index
//    due::pin_adc thumb1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4); // thumb

    for (;;) {
        ///// FLEXSENSOR READ/WRITE //////////////////////////////////
//        float pinkF1 = Flex::getFingerAngle(pink1);         //call function from Flex to calculate the angular position of the finger
//        hwlib::cout << "pink angle 1 = " << (int) pinkF1;
//        float ringF1 = Flex::getFingerAngle(ring1);
//        hwlib::cout << "ring angle 1 = " << (int) ringF1;
//        float middleF1 = Flex::getFingerAngle(middle1);
//        hwlib::cout << "middle angle 1 = " << (int) middleF1;
//        float indexF1 = Flex::getFingerAngle(index1);
//        hwlib::cout << "index angle 1 = " << (int) indexF1;
//        float thumbF1 = Flex::getFingerAngle(thumb1);
//        hwlib::cout << "thumb angle 1 = " << (int) thumbF1 << "\n";


        ///// ACCELEROMTER READ AND PRINT //////////////////////////////////
        int16_t accX_result = Mpu6050.getAccX();            // calls function from Mpu6050 to get the data from Accelerometer X axis
        int16_t accY_result = Mpu6050.getAccY();
        int16_t accZ_result = Mpu6050.getAccZ();
        acc_x = accX_result / 1000.0; // max = 16348.0;     // divide by 1000 to get the first digits
        acckommaX = accX_result - ((int) acc_x *
                                   1000.0);    // subtract the acc_x from the accX_result to get the numbers after the comma's
        acc_y = accY_result / 1000.0;
        acckommaY = accY_result - ((int) acc_y * 1000.0);
        acc_z = accZ_result / 1000.0;
        acckommaZ = accZ_result - ((int) acc_z * 1000.0);

        /// print acc x //////////////////////////////////
        hwlib::cout << "acc_x" << hwlib::setw(8) << (int) acc_x << "."; // print everything before the comma
        check = minus(acckommaX);                               // set negative to positive behind the comma
        hwlib::cout << check << "\n";                                   // print after the comma
        ///// print acc y //////////////////////////////////
        hwlib::cout << "acc_y" << hwlib::setw(8) << (int) acc_y << ".";
        check = minus(acckommaY);
        hwlib::cout << check << "\n";
        /// print acc z //////////////////////////////////
        hwlib::cout << "acc_z" << hwlib::setw(8) << (int) acc_z << ".";
        check = minus(acckommaZ);
        hwlib::cout << check << "\n";


        ///// GYROSCOPE READ AND PRINT //////////////////////////////////
        int16_t raw_gyro_x = Mpu6050.getGyroX();        //calls function from the Mpu6050 library to get the data of gyroscope X axis.
        int16_t raw_gyro_y = Mpu6050.getGyroY();
        int16_t raw_gyro_z = Mpu6050.getGyroZ();

        gyro_x = (float) ((raw_gyro_x) / 10);            // divide by 10 to get the first digits
        gyrkommaX = raw_gyro_x - ((int) gyro_x * 10);  // subtract the acc_x from the accX_result to get the numbers after the comma's
        gyro_y = (float) ((raw_gyro_y) / 10);
        gyrkommaX = raw_gyro_y - ((int) gyro_y * 10);
        gyro_z = (float) ((raw_gyro_z) / 10);
        gyrkommaX = raw_gyro_z - ((int) gyro_z * 10);

        /// print Gyro z //////////////////////////////////
        hwlib::cout << "\n" << "\n";
        hwlib::cout << "gyro_x" << hwlib::setw(8) << (int) gyro_x << "."; // print values before the comma
        check = minus(gyrkommaX);
        hwlib::cout << check << "\n";                                   // print the values after the comma
        /// print Gyro y //////////////////////////////////
        hwlib::cout << "gyro_y" << hwlib::setw(8) << (int) gyro_y << ".";
        check = minus(gyrkommaY);
        hwlib::cout << check << "\n";
        /// print Gyro z //////////////////////////////////
        hwlib::cout << "gyro_z" << hwlib::setw(8) << (int) gyro_z << ".";
        check = minus(gyrkommaZ);
        hwlib::cout << check << "\n";


        hwlib::wait_ms(1000);
    }
}
//    for (;;){
//
//        hwlib::wait_ms(1000);
//        testcase = 0;
//        hwlib::cout << "\n";
//        hwlib::cout << "\n";
//        if (gyro_X_as > 20 || gyro_X_as < (-20)){
//            hwlib::cout << "x-axis word gedraait." << "\n";
//        }
//        if (gyro_Y_as > 20 || gyro_Y_as < (-20)){
//            hwlib::cout << "y-axis word gedraait." << "\n";
//        }
//        if (gyro_Z_as > 20 || gyro_Z_as < (-20)){
//            hwlib::cout << "z-axis word gedraait." << "\n";
//        }
//        hwlib::wait_ms(1000);
//        hwlib::cout << "\n";
//        hwlib::cout << "\n";
//        temp = Mpu6050.getTemp():
//        hwlib::cout << "temperatuur is " << (int)temp << "\n";
//        hwlib::wait_ms(1000);
//        hwlib::cout << "\n";
//        hwlib::cout << "\n";
//        if (pinkF1 > 1){
//            hwlib::cout << "pink" << "\n";
//        }
//        if (ringF1 > 1){
//            hwlib::cout << "Ring Finger" << "\n";
//        }
//        if (middleF1 > 1){
//            hwlib::cout << "middle Finger" << "\n";
//        }
//        if (indexF1 > 1){
//            hwlib::cout << "index Finger" << "\n";
//        }
//        if (thumbF1 > 1){
//            hwlib::cout << "thumb" << "\n";
//        }
//        hwlib::wait_ms(10000);
//        hwlib::cout << "\n";
//        hwlib::cout << "\n";
//
//    }
//}
//
//int test(){
//    // Values
//    due::pin_adc pink1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0); // pink
//    due::pin_adc ring1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1); // ring
//    due::pin_adc middle1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2); // middle
//    due::pin_adc index1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3); // index
//    due::pin_adc thumb1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4); // thumb
//
//    int16_t temp;
//    int testcase = 0;
//
//    float pinkF1 = Flex::getFingerAngle(pink1);
//    float ringF1 = Flex::getFingerAngle(ring1);
//    float middleF1 = Flex::getFingerAngle(middle1);
//    float indexF1 = Flex::getFingerAngle(index1);
//    float thumbF1 = Flex::getFingerAngle(thumb1);
//    int16_t acc_X_as = Mpu6050.getAccX();
//    int16_t acc_Y_as = Mpu6050.getAccY();
//    int16_t acc_Z_as = Mpu6050.getAccZ();
//    int16_t gyro_X_as = Mpu6050.getGyroX();
//    int16_t gyro_Y_as = Mpu6050.getGyroY();
//    int16_t gyro_Z_as = Mpu6050.getGyroZ();
//
//
//
//
//}

int main( void ){
//    read();
//    checkFinger();
    checkAcc();
}