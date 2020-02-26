/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrive.h"
#include "commands/AutoDriveDistance.h"
#include "commands/AutoDriveAngle.h"
#include "commands/AutoShoot.h"
#include "commands/AutoDelay.h"
#include "commands/SpinUpShooter.h"
#include "commands/JumbleShooter.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html

/*
From Kyle:
3 independent commands that are in parallel, not series:

(1) Delay a seconds, drive backwards for b seconds
(2) spin up shooter, delay c seconds, turn off shooter
(3) delay d seconds, turn jumbler for e seconds, turn off jumbler

That would allow for shoot then scoot or scoot then shoot by changing delays and durations, as required by our reliable minimum shooting range.
*/

AutoDrive::AutoDrive(DriveTrain *drivetrain, Shooter *shooter) {
#if defined(ENABLE_DRIVETRAIN) && defined(ENABLE_SHOOTER)
  constexpr double a = 0.0; // Drive delay
  constexpr double b = 0.0; // Drive distance (inches)
  constexpr double c = 0.0; // Shooter spin time
  constexpr double d = 0.0; // Jumbler delay
  constexpr double e = 0.0; // Jumbler on time
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands (
    frc2::SequentialCommandGroup{ AutoDelay(a), AutoDriveDistance(drivetrain, b) },
    frc2::ParallelRaceGroup{ SpinUpShooter(shooter), AutoDelay(c) },
    frc2::SequentialCommandGroup{ AutoDelay(d),
                                  frc2::ParallelRaceGroup{ JumbleShooter(shooter, -1), AutoDelay(e) }
                                }
  );
#endif // defined(ENABLE_DRIVETRAIN) && defined(ENABLE_SHOOTER)
}
