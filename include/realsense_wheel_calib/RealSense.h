#ifndef REALSENSE_H_
#define REALSENSE_H_

#include <librealsense2/rs.hpp>
#include <cstring>
#include <cerrno>
#include <realsense_wheel_calib/Source.h>

/*
this class encapsulates the realsense sdk calls
*/

// thread routine to handle new frames
void *realsense_acquire(void *arg);

class RealSense: public Source {

    protected:
        // override the init routine
        void init();

        // the ID of the thread handling new images
        pthread_t stream_tid = 0;


    public:
        RealSense();
        ~RealSense();

        // realsense sdk stuff
        rs2::pipeline *pipe = nullptr; // need to store the pipe pointer to use on callbacks

        void start();
        void stop();
};

#endif