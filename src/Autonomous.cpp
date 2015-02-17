#include <cstdint>
#include <cmath>
#include "WPILib.h"
#include "DevBot.h"

void DevBot::AutonomousInit() {
	robotDrive.SetSafetyEnabled( false );
	Backward( 0.25, 2.5 );
}

void DevBot::AutonomousPeriodic() {
	Wait( 0.005 );
}

void DevBot::Turn( float absSpeed, float targetAngle ) {
	float offset;
	float absOffset;
	float speed;

	// Reset the gyro to 0 degrees
	gyro.Reset();
	
	do {
		// Find the offsets for the rest of the math
		offset = gyro.GetAngle() - targetAngle;
		absOffset = std::abs( offset );
		
		// Calculate output speed
		if( offset > 0 )
			speed = absSpeed;
		else
			speed = -1*absSpeed;

		// Turn
		robotDrive.MecanumDrive_Cartesian( 0, 0, speed );

		// Keep CPU from catching fire and network from exploding in a fireball of packets.
		Wait( 0.005 );
	} while( absOffset > 1 ); // Repeat until target is reached.

	// Leave everything as we found it
	robotDrive.MecanumDrive_Cartesian( 0, 0, 0 );
}

void DevBot::Backward( float Speed, float Time ) {
	// Reset the gyro to 0 degrees
	gyro.Reset();

	// Initialize Timer
	Timer timer;
	timer.Reset();
	timer.Start();

	// Move straight, changing angle to adjust for drift
	while ( timer.Get() <= Time ) {
		robotDrive.MecanumDrive_Cartesian( 0, -Speed, gyro.GetAngle() * 0.1 );
		Wait( 0.005 );
	}
	
	// Leave everything as we found it
	robotDrive.MecanumDrive_Cartesian( 0, 0, 0 );
	timer.Stop();
}

void DevBot::Forward( float Speed, float Time ) {
	// Reset the gyro to 0 degrees
	gyro.Reset();

	// Initialize Timer
	Timer timer;
	timer.Reset();
	timer.Start();

	// Move straight, changing angle to adjust for drift
	while ( timer.Get() <= Time ) {
		robotDrive.MecanumDrive_Cartesian( 0, Speed, -gyro.GetAngle() * 0.1 );
		Wait( 0.005 );
	}
	
	// Leave everything as we found it
	robotDrive.MecanumDrive_Cartesian( 0, 0, 0 );
	timer.Stop();
}
