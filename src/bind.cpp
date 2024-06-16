#include "bind.h"

PYBIND11_MODULE(corvus_image, m) {
	bind_image(m);
	bind_cascade_handler(m);
	bind_camera_handler(m);
}