#include <iostream>
#include <cstdint>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <boost/math/statistics/linear_regression.hpp>

#define FRAMERATE 30
#define CHESSBOARD_N_COLS 13
#define CHESSBOARD_N_ROWS 9

int main() {

	// frame dimensions
	uint16_t dimensions[2] = {1280, 720};

	// encapsulates device and sensors
	rs2::pipeline pipe;
	rs2::config cfg;

	cfg.enable_stream(RS2_STREAM_COLOR, dimensions[0], dimensions[1], RS2_FORMAT_BGR8, FRAMERATE);
	cfg.enable_stream(RS2_STREAM_DEPTH, dimensions[0], dimensions[1], RS2_FORMAT_BGR8, FRAMERATE);
	
	// start streaming with default the specified configuration
	rs2::pipeline_profile profile;
	
	try {
		profile = pipe.start(cfg);
	} catch(rs2::error e) {
		std::cout << "Error starting stream: " << e.what() << std::endl;
		return -1;
	}

	// frame align objects
	rs2::align align_to_depth(RS2_STREAM_DEPTH);
	rs2::align align_to_color(RS2_STREAM_COLOR);

	rs2::colorizer c; // used to colorize depth images

	while(true) {

		rs2::frameset frameset;
		try {
			frameset = pipe.wait_for_frames();
		} catch(rs2::error e) {
			std::cout << "Error getting frames: " << e.what() << std::endl;
			return -2;
		}

		// align the frameset to depth
		frameset = align_to_depth.process(frameset);

		// get color frame
		rs2::video_frame color = frameset.get_color_frame();
		// get depth frame
		rs2::depth_frame depth = frameset.get_depth_frame();
		// colorize depth frame
		rs2::video_frame colorized_depth = c.colorize(depth);

		// convert the color frame to opencv Mat
		cv::Mat colorFrame(cv::Size(dimensions[0], dimensions[1]), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);

		int detectionFlags = cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS;

		// detect the chessboard corners
		std::vector<cv::Point2f> corners; // these are the 2D chessboard corners
		cv::findChessboardCorners(colorFrame, cv::Size(CHESSBOARD_N_ROWS-1, CHESSBOARD_N_COLS-1), corners, detectionFlags);

		// deproject the image corners to 3D space
		// rs2_deproject_pixel_to_point(...)

		// do the plane equation estimation
		// https://www.boost.org/doc/libs/1_81_0/libs/math/doc/html/math_toolkit/linear_regression.html maybe???
		// linear regression done on each axis individually would provide a plane equation estimation

	}

	return 0;
}
