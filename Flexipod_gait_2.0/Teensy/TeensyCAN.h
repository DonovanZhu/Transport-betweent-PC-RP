#ifndef __TeensyCAN_H
#define __TeensyCAN_H

// Defines
#define NB_ESC             4                 // Number of ESCs
#define USB_UART_SPEED     1000000            // Baudrate of the teeensy USB serial link
//
// if speed command higher than 32768, the motor rotates clockwise
// if speed command lower than 32768, the motor rotates counter-clockwise
//
#define DirectionBoundary  32768.0   // 32768(dec) = 0x8000(hex)
#define maxBoundary        65535.0   // 0xffff, command upper limit
#define PID_H              12000.0   // PID controller output upper limit, corresponding to 10A
#define PID_L              -12000.0  // PID controller output lower limit,
#define PID_ANG_H          60.0
#define PID_ANG_L          0.0
#define DRIVE_RATIO        19.20320856  // Drive ratio of motor gear box
#define k_p                65.0       // Proportional parameter
#define k_i                0.15       // Integral parameter
#define k_p_ang            4.5

// -0.0192715 -0.2800474 10.0537329 0.0136186 0.0011329 -0.0076148
#define GRAVITY 9.802 // The gravity acceleration in New York City

// Calibration outcomes
#define GYRO_X_OFFSET        0.0131094
#define GYRO_Y_OFFSET        0.0012340
#define GYRO_Z_OFFSET       -0.0056364

#define ACCEL_X_OFFSET       0.0426984
#define ACCEL_Y_OFFSET      -0.3458546
#define ACCEL_Z_OFFSET       10.0628948

#define CONTACT_ANGLE        120.0
#define CONTACT_TIME_TROT    0.6
#define CONTACT_TIME_CRAWL   0.75
#define CONTACT_TIME_BOUND   0.5

// Teensy->host communication data structure
typedef struct {
  double  angle[NB_ESC];      // Motors rotation angle
  double  rspeed[NB_ESC];     // Motors rpm
  double  torque[NB_ESC];     // Motors torque
  double  motor_command[NB_ESC];    // Motors speed command
  double  acc[3];             // Acceleration in X Y Z direction, m/s^2
  double  gyr[3];             // Gyroscope in X Y Z direction, deg/s
  double  mag[3];
  double  eular[3];
  double  timestamps;
} Teensycomm_struct_t;

// Host->teensy communication data structure
typedef struct {
  double  speedcommand;            // Desired Speed, rpm
  int     gait;
} RPicomm_struct_t;

struct Quaternion {
    double w, x, y, z;
};

struct EulerAngles {
    double roll_e, pitch_e, yaw_e;
};

void Matrix_Vector_Multiply(const double a[3][3], const double b[3], double out[3]);

EulerAngles ToEulerAngles(Quaternion q);
#endif
