#ifndef ENVIRON_H_
#define ENVIRON_H_

/* 
this header defines the calibration environment:
- dimensions of the charuco boards
- signatures of the boards (the first Aruco tags IDs as ASCII chars)
*/ 

#define CHARUCO_N_COLS	13
#define CHARUCO_N_ROWS	9

#define SIGNATURE_LEN	5 // each signature is 5 chars long
#define REFERENCE_SIGNATURE	"ATTEN" // for example: 'A'->65 (10)
#define WHEEL_SIGNATURE		"WHEEL"

#endif
