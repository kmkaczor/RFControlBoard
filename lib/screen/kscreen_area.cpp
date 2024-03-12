#include "kscreen_area.h"
#include "ILI9341_t3n.h"
extern ILI9341_t3n tftdisplay;

K_AREA::K_AREA(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
}

void K_AREA::resize(int width, int height)
{
    this->width = width;
    this->height = height;
}
void K_AREA::move(int x, int y)
{
    this->x = x;
    this->y = y;
}


K_CANVAS *K_AREA::get_canvas()
{
        return this->canvas;
}

K_TEXT::K_TEXT(int x, int y, int width, int height, string *text) : K_AREA(x, y, width, height)
{
    //tftdisplay.println("fuck");
    //K_AREA(x, y, width, height);
    if (text != NULL)
        set_text(text);
    this->canvas = new K_CANVAS(width, height);
}

unsigned int K_TEXT::num_text_rows()
{
    if (this->height <= 0)
        return 0;
        
    return this->height / this->font_size;
}

void K_TEXT::add_text(std::string *str)
{
    text_line.push_back(str);
}

void K_TEXT::set_text(std::string *str)
{
    //tftdisplay.println("set_text");
    //this->text.push_back(str);
    if (num_text_rows() > 0)
    {
        std::vector<string *>::iterator textiter0 = text_line.begin();
        std::vector<string *>::iterator textiter1 = text_line.begin();
        advance(textiter1, text_line.size() - num_text_rows());
        // Here
        text_line.erase(textiter0, textiter1);
        
        this->canvas->fillScreen(this->background_color);
        this->canvas->setTextColor(this->text_color);
        for (string * s : text_line)
            this->canvas->println(s->c_str());
    }
    
}