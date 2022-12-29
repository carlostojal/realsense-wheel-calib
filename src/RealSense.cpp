#include <librealsense2/rs.hpp>
#include <realsense_wheel_calib/RealSense.h>

RealSense::RealSense() : Source(RGBD) { // initialize the RealSense as a RGBD source

    // TODO: confirm the resolution on the data sheet
    this->setFrameResolution(COLOR, std::make_pair(640, 480));
    this->setFrameResolution(DEPTH, std::make_pair(640, 480));
    this->setFramerate(30);

    this->init();
}

RealSense::~RealSense() {
    
    // TODO: close the stream
}

// initialize the configuration of the RealSense
void RealSense::init() {

    std::cout << "Initializing RealSense..." << std::endl;

    rs2::pipeline pipe;
    rs2::config cfg;

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

    std::cout << "Initialization done." << std::endl;
}

// start streaming
void RealSense::start() {
    // can't handle streaming if the callback functions are not set
    if(this->depthCallback == NULL || this->imageCallback == NULL)
        throw Error(CALLBACK_NOT_SET);

    // TODO: create a thread to handle the streaming and dettach it
}