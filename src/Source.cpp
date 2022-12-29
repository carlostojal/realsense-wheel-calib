#include <iostream>
#include <realsense_wheel_calib/Source.h>

Source::Source(enum camera_type_t type) {
	this->setCameraType(type);
}

Source::~Source() {
	this->initialized = false;
	this->started = false;
}

void Source::init() {
	this->initialized = true;
}

void Source::start() {
	if(!this->initialized)
		throw Error(SOURCE_NOT_INITIALIZED);
	this->started = true;
}

void Source::stop() {
	this->started = false;
}

void Source::onImageCallback(void (*callback)(cv::Mat frame), frame_type_t type) {
	switch(type) {
		case DEPTH:
			this->depthCallback = callback;
			break;
		case COLOR:
			this->imageCallback = callback;
			break;
		default:
			throw Error(INVALID_FRAME_TYPE);
			break;
	}
}

uint8_t Source::getFramerate() {
	return this->framerate;
}

void Source::setFramerate(uint8_t fps) {
	if(fps < 0)
		throw Error(INVALID_FRAMERATE);
	this->framerate = fps;
}

std::pair<uint16_t,uint16_t> Source::getFrameResolution(frame_type_t type) {
	switch(type) {
		case DEPTH:
			return this->depthFrameResolution;
		case COLOR:
			return this->colorFrameResolution;
		default:
			throw Error(INVALID_FRAME_TYPE);
			break;
	}
}

void Source::setFrameResolution(frame_type_t type, std::pair<uint16_t,uint16_t> res) {

	if(res.first < 0 || res.second < 0)
		throw Error(INVALID_RESOLUTION);

	switch(type) {
		case DEPTH:
			this->depthFrameResolution = res;
			this->hasDepthCapability = true;
			break;
		case COLOR:
			this->colorFrameResolution = res;
			this->hasDepthCapability = false;
			break;
	}
}

camera_type_t Source::getCameraType() {
	return type;
}

void Source::setCameraType(camera_type_t t) {
	switch(t) {
		case RGB:
			this->hasDepthCapability = false;
		case RGBD:
			this->hasDepthCapability = true;
			break;
		default:
			throw Error(INVALID_CAMERA_TYPE);
			return;
	}
	type = t;
}
