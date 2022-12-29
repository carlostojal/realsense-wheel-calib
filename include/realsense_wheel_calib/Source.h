#ifndef SOURCE_H_
#define SOURCE_H_

#include <cstdint>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <realsense_wheel_calib/Error.h>

/*
this class represents any generic video capture device used for calibration
*/

enum camera_type_t {
	RGB,
	RGBD
};

enum frame_type_t {
	DEPTH,
	COLOR
};

class Source {

	protected:
		bool hasDepthCapability;
		std::pair<uint16_t,uint16_t> colorFrameResolution;
		std::pair<uint16_t,uint16_t> depthFrameResolution;
		uint8_t framerate;
		Eigen::Matrix3d intrinsic; // intrinsic 3x3 matrix of double
		camera_type_t type;

		bool initialized = false;
		bool started = false;

		virtual void init();

	public:
		Source(enum camera_type_t type);
		virtual ~Source() = 0;

		void onImageCallback(void (*callback)(cv::Mat frame), frame_type_t type);

		uint8_t getFramerate();
		void setFramerate(uint8_t fps);

		std::pair<uint16_t,uint16_t> getFrameResolution(frame_type_t type);
		void setFrameResolution(frame_type_t type, std::pair<uint16_t,uint16_t> res);

		camera_type_t getCameraType();
		void setCameraType(camera_type_t type);

		void (*imageCallback)(cv::Mat frame) = nullptr; // callback function for image processing
		void (*depthCallback)(cv::Mat frame) = nullptr; // callback function for depth processing

		virtual void start();
		virtual void stop();


};

#endif
