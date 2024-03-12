#ifndef K_SCREEN_AREA_GUARD
#define K_SCREEN_AREA_GUARD
#include <stdlib.h>
#include <string>
#include <vector>
#include <type_traits>
#include <Adafruit_GFX.h>
using namespace std;

#define k_color_t uint16_t

typedef GFXcanvas16 K_CANVAS;

class K_AREA
{
    protected:
        static const unsigned int type {0x0};
        K_CANVAS *canvas;
    public:
        int x = 0;
        int y = 0;
        unsigned int width = 0;
        unsigned int height = 0;
        k_color_t background_color;
        bool update {0};
        K_CANVAS * get_canvas();
   
        K_AREA() {};
        K_AREA(int x, int y, int width, int height);

        virtual unsigned int get_type() {return this->type;}
        void move(int, int);
        void set_bgcolor(k_color_t color) {this->background_color = color;}
        void resize(int, int);

};

#define K_TEXT_TYPE 0x01;
class K_TEXT : public K_AREA
{
    protected:
        static const unsigned int type = K_TEXT_TYPE;
    public:
        virtual unsigned int get_type() {return this->type;}
        K_TEXT();
        K_TEXT(int, int, int, int, std::string *);
        unsigned int text_color;
        unsigned int font_size;
        vector<string *> text_line;
        void add_text(string *);
        bool wrap_text = true;
        bool clear_on_wrap = true;
        void set_textcolor(k_color_t color) {this->text_color = color;}
        
        void set_wrap(bool x) { this->wrap_text = x; }
        void set_text(std::string *);        
        unsigned int num_text_rows();
};

#endif