#include <realsense_wheel_calib/RealSense.h>

RealSense::RealSense() : Source(RGBD) { // initialize the RealSense as a RGBD source

    // TODO: confirm the resolution on the data sheet
    this->setFrameResolution(COLOR, std::make_pair(640, 480));
    this->setFrameResolution(DEPTH, std::make_pair(640, 480));
    this->setFramerate(30);

    this->init();
}

RealSense::~RealSense() {

    this->stop();    
}

// initialize the configuration of the RealSense
void RealSense::init() {

    std::cout << "Initializing RealSense..." << std::endl;

    rs2::pipeline pipe;
    rs2::config cfg;

    // save the pipe pointer
    this->pipe = &pipe;

    cfg.enable_stream(RS2_STREAM_COLOR, this->getFrameResolution(COLOR).first, this->getFrameResolution(COLOR).second, 
        RS2_FORMAT_BGR8, this->getFramerate());
    
    cfg.enable_stream(RS2_STREAM_DEPTH, this->getFrameResolution(DEPTH).first, this->getFrameResolution(DEPTH).second,
        RS2_FORMAT_BGR8, this->getFramerate());

    // start streaming with specified configuration
    rs2::pipeline_profile profile;
    try {
        std::cout << "Starting stream..." << std::endl;
        profile = pipe.start(cfg);
    } catch(rs2::error e) {
        std::cerr << "Error starting stream: " << e.what() << std::endl;
        throw Error(ERROR_STARTING_STREAM);
        return;
    }

    // frame align objects
    rs2::align align_to_depth(RS2_STREAM_DEPTH);
    rs2::align align_to_color(RS2_STREAM_COLOR);

    // TODO: set the instrinsics matrix of the instance

    std::cout << "Initialization done." << std::endl;
}


void *realsense_acquire(void *arg) {
    RealSense *rs = (RealSense *) arg;

    // frame align objects
	rs2::align align_to_depth(RS2_STREAM_DEPTH);
	rs2::align align_to_color(RS2_STREAM_COLOR);

	rs2::colorizer c; // used to colorize depth images

    while(true) {

		rs2::frameset frameset;
		try {
			frameset = (rs->pipe)->wait_for_frames();
		} catch(rs2::error e) {
			std::cout << "Error getting frames: " << e.what() << std::endl;
			throw new Error(ERROR_GETTING_FRAMES);
		}

		// align the frameset to depth
		frameset = align_to_depth.process(frameset);

		// get color frame
		rs2::video_frame color = frameset.get_color_frame();
		// get depth frame
		rs2::depth_frame depth = frameset.get_depth_frame();
		// colorize depth frame
		rs2::video_frame colorized_depth = c.colorize(depth);

        std::pair<uint16_t, uint16_t> colorResolution = rs->getFrameResolution(COLOR);
        std::pair<uint16_t, uint16_t> depthResolution = rs->getFrameResolution(DEPTH);

		// convert the color frame to opencv Mat
		cv::Mat colorFrame(cv::Size(colorResolution.first, colorResolution.second), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
        rs->imageCallback(colorFrame);

        // convert the depth frame to opencv Mat
        cv::Mat depthFrame(cv::Size(depthResolution.first, colorResolution.second), CV_8UC3, (void*)colorized_depth.get_data(), cv::Mat::AUTO_STEP);
        rs->depthCallback(depthFrame);

	}
}

// start streaming
void RealSense::start() {
    // can't handle streaming if the callback functions are not set
    if(this->depthCallback == NULL || this->imageCallback == NULL)
        throw Error(CALLBACK_NOT_SET);

    // create a thread to handle the streaming
    if(pthread_create(&(this->stream_tid), NULL, realsense_acquire, this) != 0) {
        std::cerr << "Error creating thread: " << strerror(errno) << std::endl;
        throw Error(ERROR_CREATING_THREAD);
    }

    // no syncronization needed here, just detach the thread and let it run
    if(pthread_detach(this->stream_tid) != 0) {
        std::cerr << "Error detaching thread: " << strerror(errno) << std::endl;
        throw Error(ERROR_DETACHING_THREAD);
    }
}

void RealSense::stop() {

    // destroy the acquire thread
    if(pthread_cancel(this->stream_tid) != 0) {
        std::cerr << "Error destroying the acquire thread: " << strerror(errno) << std::endl;
    }
    
    // stop the pipeline
    if(this->pipe != nullptr) {
        this->pipe->stop();
        delete pipe;
    }
}