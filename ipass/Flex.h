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

#ifndef HWLIB_I2C_HPP_FLEX_H
#define HWLIB_I2C_HPP_FLEX_H

#include "hwlib.hpp"

/**
 * \brief This is the main class for the Flex Sensors
 */
class Flex{
public:
    /// The getFingerAngle measures the resistance of the Flex Sensor and calculates the angular position.
    static float getFingerAngle(due::pin_adc &finger){
        float degree = 4095.0 / 90;
        int fingerRead = finger.read();
        float FingerAngle = (float)fingerRead / degree;
        return FingerAngle;
    }
};

#endif //HWLIB_I2C_HPP_FLEX_H