/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Constants.h"
#include <frc2/command/SubsystemBase.h>
#include <rev/CANPIDController.h>
#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <TimeOfFlight.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

#ifdef ENABLE_SHOOTER
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SetBottomMotorSpeed(double velocity);

  void SetTopMotorSpeed(double velocity);

  double GetBottomMotorSpeed();
  
  double GetTopMotorSpeed();

  void SpinUp();

  void SpinTop();

  void SpinBottom();
  
  void StopSpinUp();

  void StopTop();

  void StopBottom();

  void Activate();

  void Deactivate();

  void SetFeedSpeed(double speed);

  void SetHopperSpeed(double speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  rev::CANSparkMax m_topMotor{ConShooter::Top::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_bottomMotor{ConShooter::Bottom::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};

  // Built-in encoders on the NEO Motors above
  rev::CANEncoder m_topEncoder = m_topMotor.GetEncoder();
  rev::CANEncoder m_bottomEncoder = m_bottomMotor.GetEncoder();

  //PID controller
  rev::CANPIDController m_topVelocityPID = m_topMotor.GetPIDController();
  rev::CANPIDController m_bottomVelocityPID = m_bottomMotor.GetPIDController();

  TalonSRX m_feedMotor{ConShooter::Feeder::MOTOR_ID};
  TalonSRX m_hopperMotor{ConShooter::Hopper::MOTOR_ID};

  frc::TimeOfFlight m_powerCellDetector{0};
#endif // ENABLE_SHOOTER
};
