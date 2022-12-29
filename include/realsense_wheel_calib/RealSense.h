#ifndef REALSENSE_H_
#define REALSENSE_H_

#include <realsense_wheel_calib/Source.h>

/*
this class encapsulates the realsense sdk calls
*/

class RealSense: public Source {

    protected:
        void init();

    public:
        RealSense();
        ~RealSense();

        void start();
};

#endif