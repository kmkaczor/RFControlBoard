#ifndef LVGL_COMP_DISPLAY
#define LVGL_COMP_DISPLAY

#include <lvgl.h>
#include <type_traits>
#include <array>
#include <functional>
#include <memory>
//#include "Arduino.h"
//#include "config.h"
//#include "theme_based.h"

template<typename Numeric>
Numeric matrix_determinate3x3(const std::array<std::array<Numeric, 3>, 3> m)
{
    static_assert(std::is_arithmetic<Numeric>::value, "Not a numeric type!");
    return (
            m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]) -
            m[1][2] * (m[0][0] * m[2][1] - m[2][0] * m[0][1]) +
            m[2][2] * (m[0][0] * m[1][1] - m[1][0] * m[0][1]));
}
// template <typename N, typename = typename std::enable_if<std::is_arithmetic<N>::value, N>::type> // Force arithmetic only

typedef lv_theme_t* (*theme_cb_t)(lv_display_t*);
//typedef void (*lv_display_flush_cb_t)(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);
class DisplayTouchController {

public:
    template<typename Numeric> // TODO: Perhaps allow for n-point calibration
    struct ts_precalibration_data_t {
        static_assert(std::is_arithmetic<Numeric>::value, "Not a numeric type!");
        const std::array<std::pair<Numeric, Numeric>, 3> lcd_coords;
        const std::array<std::pair<Numeric, Numeric>, 3> ts_coords; // Coordinates of touch screen reading.
    };

    struct ts_cal_t {
        bool is_calibrated = {false};
        float x_alpha;
        float x_beta;
        float x_delta;

        float y_alpha;
        float y_beta;
        float y_delta;
    };

    template<typename Numeric>
    DisplayTouchController(
            uint32_t width,
            uint32_t height,
            theme_cb_t theme_cb,
            lv_display_flush_cb_t disp_cb,
            lv_indev_read_cb_t ts_cb,
            DisplayTouchController::ts_precalibration_data_t<Numeric>* cal,
            void* disp_buf1 = nullptr, void* disp_buf2 = nullptr, uint32_t disp_buf_size = 0
    )
            : width(width), height(height), theme_cb(theme_cb), disp_cb(disp_cb), ts_cb(ts_cb), disp_buf1(disp_buf1), disp_buf2(disp_buf2),
              disp_buf_size(disp_buf_size)
    {
        static_assert(std::is_arithmetic<Numeric>::value, "Not a numeric type!");
        this->calibrate_ts(cal);
    };
    theme_cb_t theme_cb;
    lv_theme_t* theme;
    const uint32_t width;
    const uint32_t height;
    lv_display_flush_cb_t disp_cb;
    ts_cal_t ts_cal{0};


    lv_display_t* display{};
protected:
    lv_indev_t* ts{};
    lv_indev_read_cb_t ts_cb;
    void* disp_buf1;
    void* disp_buf2;
    uint32_t disp_buf_size;

    //  https://www.ti.com/lit/an/slyt277/slyt277.pdf, see definitions for Equation 8
    template<typename Numeric>
    void calibrate_ts(const ts_precalibration_data_t<Numeric>* tsc)
    {
        static_assert(std::is_arithmetic<Numeric>::value, "Not a numeric type!");

        std::array<Numeric, 3> x;
        std::array<Numeric, 3> y;
        std::array<std::array<Numeric, 3>, /*5*/ 3> m;

        for ( std::size_t i = 0; i < tsc->lcd_coords.size(); i++ )
        {
            x[i] = tsc->lcd_coords[i].first;
            y[i] = tsc->lcd_coords[i].second;
        }

        for ( size_t i = 0; i < tsc->ts_coords.size(); i++ ) // Should always be 3
        {
            m[i][0] = tsc->ts_coords.at(i).first;
            m[i][1] = tsc->ts_coords.at(i).second;
            m[i][2] = 1;
        }

        int determinate = matrix_determinate3x3(m);

        std::array<std::array<Numeric, 3>, 3> m2 = m;
        m2[0][0] = x[0];
        m2[1][0] = x[1];
        m2[2][0] = x[2];
        this->ts_cal.x_alpha = (float) matrix_determinate3x3(m2) / determinate;

        m2 = m;
        m2[0][1] = x[0];
        m2[1][1] = x[1];
        m2[2][1] = x[2];
        this->ts_cal.x_beta = (float) matrix_determinate3x3(m2) / determinate;

        m2 = m;
        m2[0][2] = x[0];
        m2[1][2] = x[1];
        m2[2][2] = x[2];
        this->ts_cal.x_delta = (float) matrix_determinate3x3(m2) / determinate;

        m2 = m;
        m2[0][0] = y[0];
        m2[1][0] = y[1];
        m2[2][0] = y[2];
        this->ts_cal.y_alpha = (float) matrix_determinate3x3(m2) / determinate;

        m2 = m;
        m2[0][1] = y[0];
        m2[1][1] = y[1];
        m2[2][1] = y[2];
        this->ts_cal.y_beta = (float) matrix_determinate3x3(m2) / determinate;

        m2 = m;
        m2[0][2] = y[0];
        m2[1][2] = y[1];
        m2[2][2] = y[2];
        this->ts_cal.y_delta = (float) matrix_determinate3x3(m2) / determinate;

        this->ts_cal.is_calibrated = true;
    };

    friend class LVGL_Controller;
};

#endif