/***********************************************************************
*    mathutilites.cpp:                                                 *
*    Namespace MathUtilities, for general math functions               *
*    Copyright (c) 2016 Tyler Lewis                                    *
************************************************************************
*    This is a header file for tjlutils:                               *
*    https://github.com/tlewiscpp/tjlutils                            *
*    This file may be distributed with the entire tjlutils library,    *
*    but may also be distributed as a standalone file                  *
*    The source code is released under the GNU LGPL                    *
*    This file holds the implementation of a MathUtilities namespace   *
*    It is used to do general mathematical operations such as getting  *
*    a random value between two numbers or rounding up/down            *
*                                                                      *
*    You should have received a copy of the GNU Lesser General         *
*    Public license along with tjlutils                                *
*    If not, see <http://www.gnu.org/licenses/>                        *
***********************************************************************/

#include <exception>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>

#include "mathutilities.h"

namespace MathUtilities
{
    static std::unique_ptr<MathUtilities::Random> randomDevice;
    Random::Random(std::mt19937::result_type seed) :
        m_randomEngine{seed}
    {

    }
        
    int Random::drawNumber(int min, int max)
    {
        return std::uniform_int_distribution<int>{min, max}(this->m_randomEngine);
    }

    int randomBetween(int lowLimit, int highLimit)
    {
        if (!MathUtilities::randomDevice) {
            randomDevice = std::unique_ptr<MathUtilities::Random>{new MathUtilities::Random()};
        }
        return randomDevice->drawNumber(lowLimit, highLimit);
    }

    std::mt19937 randomlySeededMersenneTwister()
    {
        std::mt19937 rng(std::random_device{}());
        rng.discard(MathUtilities::MERSENNE_TWISTER_DISCARD_THRESHOLD);
        return rng;
    }

    bool approximatelyEquals(double lhs, double rhs, double threshold)
    {
        return (tAbs(lhs, rhs) <= threshold);
    }

    bool approximatelyEquals(float lhs, float rhs, double threshold)
    {
        return approximatelyEquals(static_cast<double>(lhs), static_cast<double>(rhs), threshold);
    }

    bool approximatelyEquals(float lhs, double rhs, double threshold)
    {
        return approximatelyEquals(static_cast<double>(lhs), rhs, threshold);
    }

    bool approximatelyEquals(double lhs, float rhs, double threshold)
    {
        return approximatelyEquals(lhs, static_cast<double>(rhs), threshold);
    }

    bool isEvenlyDivisibleBy(int numberToCheck, int divisor)
    {
        if ((numberToCheck == 0) || (divisor == 0)) {
            return false;
        }
        return ((numberToCheck % divisor) == 0);
    }

    bool isEven(int numberToCheck)
    {
        return isEvenlyDivisibleBy(numberToCheck, 2);
    }

    bool isOdd(int numberToCheck) 
    {
        return !isEven(numberToCheck);
    }

    char randomAsciiByte()
    {
        return static_cast<char>(randomBetween(ASCII_LOW_LIMIT, ASCII_HIGH_LIMIT));
    }

    int roundIntuitively(double numberToRound)
    {
        if (numberToRound > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Error, numeric argument " + toStdString(numberToRound) + " passed to round will exceed maximum value for int");
        } else {
            double tempContainer{numberToRound - static_cast<int>(numberToRound)};
            if (tempContainer >= 0.5) {
                return (static_cast<int>(numberToRound) + 1);
            } else {
                return static_cast<int>(numberToRound);
            }
        }
    }

    int roundUp(double numberToRound, double threshold)
    {
        if (threshold > 1) {
            throw std::invalid_argument("Error, threshold  " + toStdString(threshold) + " is larger than 1");
        } else if (threshold < 0) {
            throw std::invalid_argument("Error, threshold  " + toStdString(threshold) + " is less than 0");
        } else if (numberToRound > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Error, numeric argument " + toStdString(numberToRound) + " passed to round will exceed maximum value for int");
        } else {
            double tempContainer{numberToRound - static_cast<int>(numberToRound)};
            if (tempContainer >= threshold) {
                return (static_cast<int>(numberToRound) + 1);
            } else {
                return static_cast<int>(numberToRound);
            }
        }
    }

    int roundDown(double numberToRound, double threshold)
    {
        if (threshold > 1) {
            throw std::invalid_argument("Error, threshold " + toStdString(threshold) + " is larger than 1");
        } else if (threshold < 0) {
            throw std::invalid_argument("Error, threshold " + toStdString(threshold) + " is less than 0");
        } else if (numberToRound > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Error, numeric argument " + toStdString(numberToRound) + " passed to round will exceed maximum value for int");
        } else {
            float tempContainer = numberToRound - static_cast<int>(numberToRound);
            if (tempContainer <= threshold) {
                return static_cast<int>(numberToRound);
            } else {
                return (static_cast<int>(numberToRound) + 1);
            }
        }
    }

    int roundIntuitively(float numberToRound)
    {
        return roundIntuitively(static_cast<double>(numberToRound));
    }

    int roundUp(float numberToRound, double threshold)
    {
        return roundUp(static_cast<double>(numberToRound), threshold);
    }

    int roundDown(float numberToRound, double threshold)
    {
        return roundDown(static_cast<double>(numberToRound), threshold);
    }
}
