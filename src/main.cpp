#include <iostream>
#include <realsense_wheel_calib/RealSense.h>

int main() {

	RealSense *rs;

	try {
		rs = new RealSense();
	} catch(Error e) {
		std::cerr << e.what() << std::endl;
		return e.error;
	}

	// TODO: define callback functions

	try {
		rs->start();
	} catch(Error e) {
		std::cerr << e.what() << std::endl;
		return e.error;
	}

	/* TODO:
	 * - do charuco boards detection
	 * - do wheel and reference board identification (based on the board IDs)
	 * - reconstruct board corners to 3D space (CUDA or OpenCL accelerated)
	 * - compute the transformation between the reference and the wheel with ICP
	 * - publish the transformation via UDP to the client (possibly an Android app in the future)
	*/

	delete rs;

	return 0;
}
