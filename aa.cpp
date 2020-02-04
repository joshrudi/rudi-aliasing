#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
using namespace boost::gil;

// very early in development.  Unstable, not ready for prime time :(
int main()
{
    rgb8_image_t input;
    png_read_and_convert_image("src_img/600p.png", input);
    rgb8_image_t img(512, 512);
    rgb8_pixel_t red(255, 0, 0);
    fill_pixels(view(img), red);
    png_write_view("processed_img/redsquare.png", const_view(img));
    png_write_view("processed_img/copy.png", const_view(input));
}