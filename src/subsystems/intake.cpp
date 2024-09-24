#include "main.h"
#include "../src/init/initRobot.cpp"
#include "intake.hpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

// Global variable for intake state
int intakeB = 0;

void Intake::run(void* param) {
    while (true) {
        // Handle R1 and R2 for intake forward and backward control
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intakeB = 1;  // Run intake forward
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeB = -1;  // Run intake backward
        } else {
            intakeB = 0;  // Stop intake if neither R1 nor R2 is pressed
        }

        // Toggle the intake state with A button press
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            intakeB = (intakeB != 1) ? 1 : 0;
        }

        // Apply the state to the intake motor
        if (intakeB == 1) {
            IntakeMotor.move(127);  // Run intake forward
        } else if (intakeB == -1) {
            IntakeMotor.move(-127); // Run intake backward
        } else {
            IntakeMotor.move(0);  // Stop intake
        }

        pros::delay(20);  // Delay to avoid overwhelming the system
    }
}
