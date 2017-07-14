#ifndef BITMAP_H
#define BITMAP_H
#define UNKNOWN_FORMAT 0x01A

typedef enum{
	RGB,
	RGBA,
	BGR
}PixelFormat;

class Bitmap{
	public:
		Bitmap( void*, int, int, PixelFormat fmt);
		Bitmap ( int , int , PixelFormat fmt);
		Bitmap();
		Bitmap( const Bitmap& other ) = default;
		~Bitmap();
		int get_format() const;
		void set_data( void* );
		void set_width(int);
		void set_height(int);
		void* get_data();
		int get_width() const;
		int get_height() const;
	private:
		PixelFormat fmt;
		void* data;
		int width;
		int height;
};

#endif
