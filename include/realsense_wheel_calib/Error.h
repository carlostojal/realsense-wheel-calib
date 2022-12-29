#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>

enum errors_t {
    INVALID_RESOLUTION,
    INVALID_FRAMERATE,
    INVALID_FRAME_TYPE,
    INVALID_CAMERA_TYPE,
    ERROR_STARTING_STREAM,
    CALLBACK_NOT_SET,
    ERROR_CREATING_THREAD,
    ERROR_DETACHING_THREAD,
    ERROR_CANCELLING_THREAD,
    ERROR_GETTING_FRAMES,
    SOURCE_NOT_INITIALIZED
};

class Error {
    public:
        Error(errors_t error);
        errors_t error;
        std::string what();
};

#endif