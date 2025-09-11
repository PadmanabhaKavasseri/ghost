mkdir build && cd build
   cmake ..
   make


install
sudo make install 
or
export GST_PLUGIN_PATH=$PWD:$GST_PLUGIN_PATH

gst-launch-1.0 videotestsrc ! qtighost ! autovideosink

sudo apt install python3-dev python3-numpy python3-opencv-python

sudo apt install python3-numpy-dev

cp ../opencv_processor.py .
gst-launch-1.0 videotestsrc ! videoconvert ! \
    qtighost script=./opencv_processor.py function=process_frame ! \
    videoconvert ! autovideosink




sudo apt install python3 python3-pip python3-venv python3-dev

cd ~/Projects/gst-template-plugin
python3 -m venv venv
source venv/bin/activate


No venv but segfaulting

LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libpython3.12.so gst-launch-1.0 videotestsrc ! videoconvert ! qtighost script=./opencv_processor.py function=process_frame ! videoconvert ! autovideosink








Working
LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libpython3.12.so gst-launch-1.0 videotestsrc ! videoconvert ! qtighost script=./opencv_processor.py function=process_frame ! videoconvert ! autovideosink


