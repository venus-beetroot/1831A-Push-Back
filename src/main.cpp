#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <sys/wait.h>

#include "lemlib/selector.hpp" // For auton selector
#include "robot-config.hpp"
#include "controls.hpp"
#include "autons.hpp"
#include "colorsort.hpp"

// ----------------------------------------------------
// IMPORTANT - Autonomous Selector Routine Declaration
// ----------------------------------------------------

LV_IMG_DECLARE(image); //TKSRC Logo

// TODO - Temporary
void debug_watcher() {

    double varDouble = 0;
    int varInt = 0;
    char varChar = 'a';
    std::string varString = "My String";

    while (true) {
        printf("[Variable]: %f / %d / %c / %s \n", varDouble, varInt, varChar, varString.c_str());
        pros::delay(10);
    }
}


void initialize() {
    // ------------------------------------------
    // Displaying TKSRC Logo (During calibration)
    // ------------------------------------------
    lv_obj_t *img = lv_img_create(lv_scr_act()); // Add to screen
    lv_img_set_src(img, &image); // Link to source image
    lv_obj_align(img, LV_ALIGN_CENTER, 0, -20);

    // -----------------------
    // Initialise Chassis
    // -----------------------
    // @removed - LLEMU CANNOT BE USED WITH LVGL | pros::lcd::initialize(); // initialize brain screen

    chassis.calibrate(); // calibrate sensors

    // -----------------------
    // Initialise Sensors
    // -----------------------
    colorSort.set_led_pwm(100);

    // -----------------------
    // Initialise Subsystems
    // -----------------------
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    doinker.set_value(false);

    lv_obj_del(img); // stop displaying TKSRC Logo as Calibration has ended

    // -----------------------
    // TODO - LVGL INIT
    // -----------------------


    static const char* redBtnmMap[] = {
        "R-Auton1", "R-Auton2", "R-Auton3", "\n",
        "R-Auton4", "R-Auton5", "R-Auton6", nullptr
    };
    static const char* redBtnmDesc[] = {
        "R-Auton1", "R-Auton2", "R-Auton3",
        "R-Auton4", "R-Auton5", "R-Auton6", nullptr
    };

    static const char* blueBtnmMap[] = {
        "B-Auton1", "B-Auton2", "B-Auton3", "\n",
        "B-Auton4", "B-Auton5", "B-Auton6", nullptr
    };
    static const char* blueBtnmDesc[] = {
        "R-Auton1", "R-Auton2", "R-Auton3",
        "R-Auton4", "R-Auton5", "R-Auton6", nullptr
    };

    static const char* skillsBtnmMap[] = {
        "Auton", "Preload", "Skills 1", "\n",  
        "Skills 2", "Skills 3", "Skills 4", nullptr
    };
    static const char* skillsBtnmDesc[] = {
        "Auton", "Preload", "Skills 1",  
        "Skills 2", "Skills 3", "Skills 4", nullptr
    };

    lemlib::selector::init(999, redBtnmMap, blueBtnmMap, skillsBtnmMap, redBtnmDesc, blueBtnmDesc, skillsBtnmDesc); // declaring default auton

    // TODO - temporary 
    pros::Task watcher(debug_watcher);

}


void disabled() {}


void competition_initialize() {}


void autonomous() {  

    // chassis.setPose(0, 0, 180); 

    int auton = lemlib::selector::auton;

    lemlib::selector::autonStarted = true;
    
    if (auton >= 1 && auton <= 100) {
        switch (auton) {
            case 1: red1(); break;
            case 2: red2(); break;
            case 3: red3(); break;
            case 4: red4(); break;
            case 5: red5(); break;
            case 6: red6(); break;
            // add more red cases as needed up to 100
        }
    }
    else if (auton >= -100 && auton <= -1) {
        switch (auton) {
            case -1: blue1(); break;
            case -2: blue2(); break;
            case -3: blue3(); break;
            case -4: blue4(); break;
            case -5: blue5(); break;
            case -6: blue6(); break;
            // add more blue cases as needed up to -100
        }
    }
    else if (auton >= 101 && auton <= 201) {
        switch (auton) {
            case 101: skills1(); break;
            case 102: skills2(); break;
            case 103: skills3(); break;
            case 104: skills4(); break;
            case 105: skills5(); break;
            case 106: skills6(); break;
            // add more skills cases as needed up to 106
        }
    }
    else {
        // Default auton
        auton1obj();
    }

    


}

void opcontrol() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    // DON'T CHANGE!: Multi-treading for robot controls (To prevent color sort interruption)
    pros::Task intakeTask(intake_control); // Interrupted by color sort
    pros::Task driveTask(drivetrain_control);
    pros::Task doinkerTask(doinker_control);
}
