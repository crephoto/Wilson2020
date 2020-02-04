/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Button.h>


RobotContainer::RobotContainer() : m_autoDriveDistance(&m_driveTrain) {
  // ANOTHER WAY OF CONSTRUCTING: m_autoDriveDistance = AutoDriveDistance(&m_driveTrain);
  // Initialize all of your commands and subsystems here
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here


  frc2::Button([this] {return codriver_controller.GetRawButton(ConXBOXController::LEFT_BUMPER); }).WhileHeld(new SpinUpShooter(&m_shooter));

  frc2::Button([this] {return codriver_controller.GetRawButton(ConXBOXController::RIGHT_BUMPER); }).WhileHeld(new ActivateShooter(&m_shooter));

  frc2::Button([this] {return codriver_controller.GetRawButton(ConXBOXController::X);}).WhileHeld(new ExtendClimber(&m_climber));
  
  frc2::Button([this] {return codriver_controller.GetRawButton(ConXBOXController::Y);}).WhileHeld(new RetractClimber(&m_climber));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autoDriveDistance;
}
