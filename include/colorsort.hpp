#ifndef COLORSORT_HPP
#define COLORSORT_HPP


/**
 * @file controls.hpp
 * @brief Header file for robot control mechanisms.
 *
 * This file declares the functions used to manage various colorsort mechanisms
 * of the robot, such as autonomous, intake, driver, normal colorsort algorithm, 
 * setting colorsort and recognising the colours of rings.
 *
 */
#include "main.h"

/**
 * @brief Toggles between Red and Blue alliance and updates the LLEMU LCD display.
 */
 void setColorSort();

 /**
  * @brief Inspects rings to determine if they match the alliance color.
  * 
  * @return `true` if the ring passes the inspection, `false` otherwise.
  */
 bool objInspect(char alliance);
 /**
 * @brief Moves the intake system with sorting functionality.
 * 
 * @param voltage Voltage to apply to the intake motor.
 * @param msDelay Duration of the movement in milliseconds.
 * @param penaltyFactor Multiplier for voltage if an invalid ring is detected.
 * @param async If `true`, runs the movement asynchronously.
 */
 void Intake_SortedMove(int voltage, float msDelay, int penaltyFactor, bool async);

 /**
 * @brief Moves the the color sort algorithm for autonomous (relates to Intake_SortedMove).
 */
 void autonColorSort(int voltage, int sort_time, bool infinite, bool async);

 /**
 * @brief Moves the the color sort algorithm for driver control (relates to Intake_SortedMove).
 */
 void driverColorSort();

 /**
 * @brief Regular color sort algorithm.
 */
 void ColorSortAlg();


#endif