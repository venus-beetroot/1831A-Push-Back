#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/device.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <sys/wait.h>

#include "controls.hpp"
#include "robot-config.hpp"


void autonColorSort();
void driverColorSort();
void ColorSortAlg();



void setColorSort() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::clear_line(3);
        pros::lcd::set_text(3, "[CLS] Alliance: RED");
        alliance = 'R';
    } else {
        pros::lcd::clear_line(3);
        pros::lcd::set_text(3, "[CLS] Alliance: BLUE");
        alliance = 'B';
    }
}
bool objInspect(char alliance) {
    const float blue_lim_low = 150, blue_lim_high = 250;
    const float red_lim_low = 0, red_lim_high = 80;
    double hue = colorSort.get_hue();

    printf("Current hue: %f\n", hue);

    if (alliance == 'B') {
        return !(red_lim_low < hue && hue < red_lim_high);
    } else if (alliance == 'R') {
        return !(blue_lim_low < hue && hue < blue_lim_high);
    }
    return true;
}

void Intake_SortedMove(int voltage, float msDelay, int penaltyFactor, bool async) {
    // Get the start time
    if (async) {
        pros::Task task([&]() { Intake_SortedMove(voltage, msDelay, penaltyFactor, false); });
        pros::delay(10); // delay to give the task time to start
        return;
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = startTime + std::chrono::milliseconds(static_cast<int>(msDelay));

    // While the elapsed time is less than msDelay
    while (std::chrono::high_resolution_clock::now() < endTime) {
        if (voltage > 0) {
            // Intaking
            bool passed = objInspect(alliance);
            if (passed) {
                intake.move(voltage);
            } else {
                intake.move(voltage * penaltyFactor);
            }
        } else {
            // Outtaking or stopping
            intake.move(voltage);
        }
        pros::delay(10);
    }

    // Stop intake after delay
    intake.move(0);
}

void autonColorSort(int voltage, int sort_time, bool infinite, bool async) {
    if (async) {
        pros::Task task([=]() { autonColorSort(voltage, sort_time, infinite, false); });
        pros::delay(10); // Give the task time to start
        return;
    }

    if (infinite) {
        sort_time = 99999; // Override sort_time if infinite is true
    }

    int elapsed = 0;
    while (elapsed < sort_time) {
        double hue = colorSort.get_hue();
        if (alliance == 'R' || alliance == 'B') {
            // Continuously update hue and check ring color
            bool passed = objInspect(alliance); // ringInspect() reads hue and checks alliance
            if (passed) {
                intake.move(voltage); // Accept ring
            } else {
                intake.move(voltage);   // Reject ring (stop intake)
                pros::delay(1100);
                intake.brake();
                pros::delay(200);
                if(infinite) {
                    intake.move(voltage); // Resume intake
                } else {
                    intake.brake(); // Stop intake
                }
            }
        } else {
            // Skills: no sorting
            intake.move(voltage);
        }
        pros::delay(20);
        elapsed += 20;
    }
}


void driverColorSort() {}
    
void ColorSortAlg() {}
    
