mkdir build && cd build
   cmake ..
   make


install
sudo make install 
or
export GST_PLUGIN_PATH=$PWD:$GST_PLUGIN_PATH

gst-launch-1.0 videotestsrc ! qtighost ! autovideosink