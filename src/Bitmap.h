// Header guard
#ifndef BITMAP_H
#define BITMAP_H
#define UNKNOWN_FORMAT 0x01A // Arbituary value to set an unknown format.
/*
unscoped enum for simple PixelFormats
*/
typedef enum{
	RGB,
	RGBA,
	BGR
}PixelFormat;

/*
	A simple class that defines a Bitmap.
	It can be imagined as a struct.
	Contains pixel data width and height
	as well as an enum that states the pixel format
*/
struct SDL_Surface;
class Bitmap{
	public:
		Bitmap( SDL_Surface* , PixelFormat fmt);
		Bitmap( void*, int, int, PixelFormat fmt);
		Bitmap ( int , int , PixelFormat fmt);
		Bitmap();
		Bitmap( const Bitmap& other ) = default;
		~Bitmap();
		// return the pixel format as an integer
		const int get_format() const;
		// set the data taking in a void pointer.
		void set_data( void* );
		// set width
		void set_width(int);
		// set height
		void set_height(int);
		// return the data as a void*
		void* get_data();
		const int get_width() const;
		const int get_height() const;
	private:
		PixelFormat fmt;
		void* data;
		int width;
		int height;
};

#endif
