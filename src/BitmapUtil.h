#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H
#include <memory>
class Bitmap;
struct ImageSurface;
/*
 * Define utility helper functions
 * for the Bitmap class.
 *
 * REPLACEMENT IS THE IMAGETEXTURE CLASS
 */

Bitmap& fromImage(const char* name);

#endif
