// #ifdef HAVE_CONFIG_H
// #include "config.h"
// #endif

#include "qtighost.hpp"
#include <gst/video/video.h>

GST_DEBUG_CATEGORY_STATIC(gst_qtighost_debug);
#define GST_CAT_DEFAULT gst_qtighost_debug

// Pad capabilities - supports common video formats
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS("video/x-raw, "
        "format=(string){I420,YV12,YUY2,UYVY,AYUV,RGBx,BGRx,xRGB,xBGR,RGBA,BGRA,ARGB,ABGR,RGB,BGR}, "
        "width=(int)[1,MAX], "
        "height=(int)[1,MAX], "
        "framerate=(fraction)[0/1,MAX]"));

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS("video/x-raw, "
        "format=(string){I420,YV12,YUY2,UYVY,AYUV,RGBx,BGRx,xRGB,xBGR,RGBA,BGRA,ARGB,ABGR,RGB,BGR}, "
        "width=(int)[1,MAX], "
        "height=(int)[1,MAX], "
        "framerate=(fraction)[0/1,MAX]"));

// Function declarations
static void gst_qtighost_class_init(GstQtiGhostClass * klass);
static void gst_qtighost_init(GstQtiGhost * filter);
static GstFlowReturn gst_qtighost_transform_ip(GstBaseTransform * trans, GstBuffer * buf);

// Define the type
#define gst_qtighost_parent_class parent_class
G_DEFINE_TYPE(GstQtiGhost, gst_qtighost, GST_TYPE_BASE_TRANSFORM);

// Class initialization
static void gst_qtighost_class_init(GstQtiGhostClass * klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    GstElementClass *gstelement_class = GST_ELEMENT_CLASS(klass);
    GstBaseTransformClass *transform_class = GST_BASE_TRANSFORM_CLASS(klass);

    // Set element metadata
    gst_element_class_set_static_metadata(gstelement_class,
        "QTI Ghost Filter",
        "Filter/Effect/Video",
        "Pass-through video filter that logs frame receipt",
        "Your Name <your.email@example.com>");

    // Add pad templates
    gst_element_class_add_static_pad_template(gstelement_class, &src_factory);
    gst_element_class_add_static_pad_template(gstelement_class, &sink_factory);

    // Set transform function - we use transform_ip for in-place transformation
    transform_class->transform_ip = GST_DEBUG_FUNCPTR(gst_qtighost_transform_ip);
}

// Instance initialization
static void gst_qtighost_init(GstQtiGhost * filter)
{
    // Initialize frame counter
    filter->frame_count = 0;
    
    // Set that we want in-place transformation (no copying needed)
    gst_base_transform_set_in_place(GST_BASE_TRANSFORM(filter), TRUE);
    
    // Set that we can work with any caps (passthrough)
    gst_base_transform_set_passthrough(GST_BASE_TRANSFORM(filter), TRUE);
}

// The main transform function - called for each buffer
static GstFlowReturn gst_qtighost_transform_ip(GstBaseTransform * trans, GstBuffer * buf)
{
    GstQtiGhost *filter = GST_QTIGHOST(trans);
    
    // Increment frame counter
    filter->frame_count++;
    
    // Print frame information to console
    g_print("QTI Ghost: Received frame #%u, timestamp: %" GST_TIME_FORMAT ", size: %zu bytes\n",
        filter->frame_count,
        GST_TIME_ARGS(GST_BUFFER_TIMESTAMP(buf)),
        gst_buffer_get_size(buf));
    
    // Return the buffer unchanged
    return GST_FLOW_OK;
}

// Plugin initialization function
static gboolean plugin_init(GstPlugin * plugin)
{
    // Initialize debug category
    GST_DEBUG_CATEGORY_INIT(gst_qtighost_debug, "qtighost", 0, "QTI Ghost filter");
    
    // Register the element
    return gst_element_register(plugin, "qtighost", GST_RANK_NONE, GST_TYPE_QTIGHOST);
}

// Plugin definition macro
GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    qtighost,
    "QTI Ghost pass-through video filter",
    plugin_init,
    PACKAGE_VERSION,
    GST_LICENSE,
    GST_PACKAGE_NAME,
    GST_PACKAGE_ORIGIN)