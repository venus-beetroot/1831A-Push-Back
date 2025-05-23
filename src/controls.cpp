#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <sys/wait.h>

#include "robot-config.hpp"
#include "colorsort.hpp"
#include "lemlib/selector.hpp"

char alliance = 'N';
bool allianceConfirmed = false;


void intake_control() {
    // const double stuck_lim_low = 0.0;
    // const double stuck_lim_high = 0.0;
    // const int reverse_time = 200;
    // const int forward_delay = 100;

    // intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    // bool intake_spinning = true;

    

    // while (true) {
    //     // Determine alliance based on selected auton
    //     char alliance = 'N';
    //     if (lemlib::selector::auton >= 1 && lemlib::selector::auton <= 100) {
    //         alliance = 'R';
    //     } else if (lemlib::selector::auton >= -100 && lemlib::selector::auton <= -1) {
    //         alliance = 'B';
    //     } else if (lemlib::selector::auton >= 101 && lemlib::selector::auton <= 200) {
    //         alliance = 'S';
    //     }

    //     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {

    //     }

    //     // Outtake
    //     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    //         intake.move(127);
    //         intake_spinning = false;
    //     }
    //     // Intake with color sorting
    //     else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    //         if (alliance == 'R' || alliance == 'B') {
    //             // Continuously update hue and check ring color
    //             bool passed = ringInspect(alliance); // ringInspect() reads hue and checks alliance
    //             if (passed) {
    //                 intake.move(-127); // Accept ring
    //             } else {
    //                 intake.move(-127);   // Reject ring (stop intake)
    //                 pros::delay(1100);
    //                 intake.brake();
    //                 pros::delay(200);
    //                 intake.move(-127);
    //             }
    //         } else {
    //             // Skills: no sorting
    //             intake.move(-127);
    //         }
    //         intake_spinning = false;
    //     }
    //     // Stop intake if not spinning
    //     else if (intake_spinning == false) {
    //         intake.move(0);
    //         intake_spinning = true;
    //     }
    //     pros::delay(10);
    // }
}



void doinker_control() {

    // doinker.set_value(false);

    // bool toggle = false;
    // bool latch = false;

    // while (true) {
    //     bool b_button = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);

    //     if (b_button && !latch) {
    //         toggle = !toggle;             // Flip the toggle state
    //         doinker.set_value(toggle);  // Update mogo_mech based on the new toggle state
    //         latch = true;                 // Engage latch to prevent repeated toggles
    //     } else if (!b_button) {
    //         latch = false;                // Reset latch when button is released
    //     }
    //     pros::delay(10);
    // }
}

void drivetrain_control() {
    while (true) {
        chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        
          // ------------------------------- //
         //  EXPERIMENTAL - Variable Ctl   //
        // ----------------------------- //

        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
            leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            chassis.tank(leftY, rightY);                     // Regular tank

        pros::delay(10);
    }
}
