#ifndef AUTONS_HPP
#define AUTONS_HPP

#pragma once


// Autonomous routines declarations
int auton1obj();
int blue1();
int blue2();
int blue3();
int blue4();
int blue5();
int blue6();
int red1();
int red2();
int red3();
int red4();
int red5();
int red6();
int skills1();
int skills2();
int skills3();
int skills4();
int skills5();
int skills6();

void default_constants();

// red neg
void red_solowp();
void red_7neg();
void red_7greed();

// red pos
void red_goalrush();
void red_5pos();

// blue neg
void blue_solowp();
void blue_7neg();
void blue_7greed();

// blue pos
void blue_goalrush();
void blue_5pos();

// default/test autons
void move_forward();
void tuning();
void red_testauto();
void blue_testauto();

#endif // AUTONS_HPP
