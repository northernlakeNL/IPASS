/**
 * \file
 * \author      Tom Noordermeer
 * \copyright   Copyright (c) 2022, Tom Noordermeer
 *
 * \page License
 *
 * This is a free software library for anyone to use.
 * it is under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPU6050_H
#define MPU6050_H
#include "hwlib.hpp"

/**
 * \brief The main class, it is used to read the MPU6050 Accelerometer, Gyroscope and thermometer.
 */

class Mpu6050 {
private:
    hwlib::i2c_bus &bus;
    uint8_t address = 0x68;
    uint8_t PWR_mgmt1 = 0x6B;
    uint8_t PWR_mgmt2 = 0x6C;
    uint8_t AccXoutH = 0x3B;
    uint8_t AccYoutH = 0x3D;
    uint8_t AccZoutH = 0x3F;
    uint8_t TempH = 0x41;
    uint8_t GyrXoutH = 0x43;
    uint8_t GyrYoutH = 0x45;
    uint8_t GyrZoutH = 0x47;
    uint8_t AccConf = 0x1C;
    uint8_t GyroConf = 0x1B;

public:
    Mpu6050(hwlib::i2c_bus &bus) :
            bus(bus) {}
    /**
     *  The startup Function is used to set the correct values to the power registers, without this the chip will remain in sleep
     *  mode and not give any values.
     */
    void startup() {

        ///// STARTUP VALUES///////////////////////////
        uint8_t nosleep2 = 128;
        uint8_t nosleep1 = 0b00000000;
        uint8_t AccConfig = 0b000000;
        uint8_t GyroConfig = 0b0001000;
        ///// POWER1 CONFIG///////////////////////////
        {hwlib::i2c_write_transaction power_wtrans = bus.write(address);
            power_wtrans.write(PWR_mgmt1);
            power_wtrans.write(nosleep1);
        }
        ///// POWER2 CONFIG///////////////////////////
        {hwlib::i2c_write_transaction power_wtrans = bus.write(address);
            power_wtrans.write(PWR_mgmt2);
            power_wtrans.write(nosleep2);
        }
        ///// ACCEL CONFIG///////////////////////////
        {hwlib::i2c_write_transaction power_wtrans = bus.write(address);
            power_wtrans.write(AccConf);
            power_wtrans.write(AccConfig);
        }
        ///// GYRO CONFIG///////////////////////////
        {hwlib::i2c_write_transaction power_wtrans = bus.write(address);
            power_wtrans.write(GyroConf);
            power_wtrans.write(GyroConfig);
        }
    }
    /// The get Temp Function reads the temperature read by the MPU6050 and returns the value.

    int16_t getTemp(){
        uint8_t Temp_Result[2];
        int16_t raw_temp = 0;
        {hwlib::i2c_write_transaction accx_wtrans = bus.write(address);
            accx_wtrans.write(TempH);
        }
        {hwlib::i2c_read_transaction accx_rtrans = bus.read(address);
            accx_rtrans.read(Temp_Result, 2);
        }
        raw_temp = (int16_t)((Temp_Result[0] << 8) | Temp_Result[1]);
        return raw_temp;
    }
    /// The GetAccX reads the X value of the Accelerometer and returns the value.
    int16_t getAccX() {
        uint8_t accX_result[2];
        int16_t raw_acc_x = 0;
        {hwlib::i2c_write_transaction accx_wtrans = bus.write(address);
            accx_wtrans.write(AccXoutH);
        }
        {hwlib::i2c_read_transaction accx_rtrans = bus.read(address);
            accx_rtrans.read(accX_result, 2);
        }
        raw_acc_x = (int16_t)((accX_result[0] << 8) | accX_result[1]);
        return raw_acc_x;
    };

    /// The GetAccY reads the Y value of the Accelerometer and returns the value.
    int16_t getAccY() {
        uint8_t accY_result[2];
        int16_t raw_acc_y = 0;
        {hwlib::i2c_write_transaction accy_wtrans = bus.write(address);
            accy_wtrans.write(AccYoutH);
        }
        {hwlib::i2c_read_transaction accy_rtrans = bus.read(address);
            accy_rtrans.read(accY_result, 2);
        }
        raw_acc_y = (int16_t)((accY_result[0] << 8) | accY_result[1]);
        return raw_acc_y;
    };

    /// The GetAccZ reads the Z value of the Accelerometer and returns the value.
    int16_t getAccZ() {
        uint8_t accZ_result[2];
        int16_t raw_acc_z = 0;
        {hwlib::i2c_write_transaction accz_wtrans = bus.write(address);
            accz_wtrans.write(AccZoutH);
        }
        {hwlib::i2c_read_transaction accz_rtrans = bus.read(address);
            accz_rtrans.read(accZ_result, 2);
        }
        raw_acc_z = (int16_t)((accZ_result[0] << 8) | accZ_result[1]);
        return raw_acc_z;
    };

    ////////// GYROSCOPE ///////////////////////////////
    /// The GetGyroX reads the X value of the Accelerometer and returns the value.
    int16_t getGyroX() {
        uint8_t gyroX_result[2];
        int16_t raw_gyro_x = 0;
        {hwlib::i2c_write_transaction gyrox_wtrans = bus.write(address);
            gyrox_wtrans.write(GyrXoutH);
        }
        {hwlib::i2c_read_transaction gyrox_rtrans = bus.read(address);
            gyrox_rtrans.read(gyroX_result, 2);
        }
        raw_gyro_x = (int16_t)((gyroX_result[0] << 8) | gyroX_result[1]);
        return raw_gyro_x;
    };

    /// The GetGyroY reads the Y value of the Accelerometer and returns the value.
    int16_t getGyroY() {
        uint8_t gyroY_result[2];
        int16_t raw_gyro_y = 0;
        {hwlib::i2c_write_transaction gyroy_wtrans = bus.write(address);
            gyroy_wtrans.write(GyrYoutH);
        }
        {hwlib::i2c_read_transaction gyroy_rtrans = bus.read(address);
            gyroy_rtrans.read(gyroY_result, 2);
        }
        raw_gyro_y = (int16_t)((gyroY_result[0] << 8) | gyroY_result[1]);
        return raw_gyro_y;
    };

    /// The GetGyroZ reads the Z value of the Accelerometer and returns the value.
    int16_t getGyroZ() {
        uint8_t gyroZ_result[2];
        int16_t raw_gyro_z = 0;
        {hwlib::i2c_write_transaction gyroz_wtrans = bus.write(address);
            gyroz_wtrans.write(GyrZoutH);
        }
        {hwlib::i2c_read_transaction gyroz_rtrans = bus.read(address);
            gyroz_rtrans.read(gyroZ_result, 2);
        }
        raw_gyro_z = (int16_t)((gyroZ_result[0] << 8) | gyroZ_result[1]);
        return raw_gyro_z;
    };
};
#endif //MPU6050_H