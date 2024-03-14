//
// Created by korey on 3/11/24.
//

#include "lvgl.h" // For widgets

#if LV_USE_THEME_BASED

#include "theme_based.h"
#include "src/core/lv_global.h"
#include "src/misc/lv_color.h"
//#include "src/core/lv_obj_style.h"
#include "src/font/lv_font.h"
struct _lv_based_theme_t;
typedef struct _lv_based_theme_t lv_based_theme_t;
#define theme_def (*(lv_based_theme_t *(void *))

#if LV_USED_DIV
const lv_obj_class_t lv_division_main_class = {
        .base_class = &lv_obj_class,
        .width_def = LV_PCT(100),
        .height_def = LV_PCT(80),
        .name = "division_main"
};

const lv_obj_class_t lv_division_btnm_class = {
        .base_class = &lv_obj_class,
        .width_def = LV_PCT(100),
        .height_def = LV_PCT(20),
        .name = "division_btnm"
};

lv_obj_t * lv_division_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_division_main_class, parent);
    lv_obj_class_init_obj(obj);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
    return obj;
}
#endif

#define BT_COLOR_BLACK lv_color_black()
#define BT_COLOR_WHITE lv_color_white()
#define BT_COLOR_DARK  lv_palette_darken(LV_PALETTE_GREY, 5)
#define BT_COLOR_DIM  lv_palette_darken(LV_PALETTE_GREY, 2)
#define BT_COLOR_LIGHT lv_palette_lighten(LV_PALETTE_GREY, 1)
#define BT_SCROLLBAR_WIDTH 3
#define BT_LOGBOX_BG COLOR_BLACK
#define BT_LOGBOX_TEXT COLOR_WHITE
#define BT_LOGBOX_FONT &lv_font_montserrat_10i
#define BT_WINDOW_PADDING 3
#define BT_LOGBOX_PADDING 0
#define BT_BUTTONMENU_PADDING 2 // Space from border to icon
//#define BT_BUTTONMENU_BUTTON_MARGIN  // Space between buttons

typedef struct {
    // Widgets
    lv_style_t screen;
    lv_style_t scrollbar;
    lv_style_t list;
    lv_style_t button_matrix;
    lv_style_t button;
    lv_style_t arc_line;
    lv_style_t arc_knob;
    lv_style_t ta_cursor;

    // Specialized widgets instances
    lv_style_t logbox;
    lv_style_t division_main;
    lv_style_t division_btnm;
    lv_style_t division_main_flex;
    lv_style_t division_btnm_flex;

    lv_style_t transp;
    lv_style_t white;
    lv_style_t dim;
    lv_style_t light;
    lv_style_t dark;

} lv_theme_based_styles_t;

struct _lv_based_theme_t{

    lv_theme_t base;
    lv_theme_based_styles_t styles;
    bool init;
} ;


/*
struct lv_based_theme_t {
        .base {
                .apply_cb = apply_theme,
                .parent = NULL,
                .user_data = NULL,
                .disp = NULL,
                .color_primary = lv_color_black(),
                .color_secondary = lv_color_white(),
                .font_small = &lv_font_montserrat_8,
                .font_normal = &lv_font_montserrat_12,
                .font_large = &lv_font_montserrat_14,
                .flags = 0
        },
        .init = false
};
*/

//#define TYPE(n) lv_obj_check_type(obj, n)

void apply_theme(lv_theme_t* th, lv_obj_t* obj)
{
    lv_based_theme_t* theme = (lv_based_theme_t*) th;
    if ( lv_obj_get_parent(obj) == NULL )
    {
        lv_obj_add_style(obj, &theme->styles.screen, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        return;
    }

    if ( lv_obj_check_type(obj, &lv_obj_class))
    {
#if LV_USE_TABVIEW
        lv_obj_t* parent = lv_obj_get_parent(obj);
        /*Tabview content area*/
        if ( lv_obj_check_type(parent, &lv_tabview_class))
        {
            lv_obj_add_style(obj, &theme->styles.screen, 0);
            return;
        }
            /*Tabview pages*/
        else if ( lv_obj_check_type(lv_obj_get_parent(parent), &lv_tabview_class))
        {
            lv_obj_add_style(obj, &theme->styles.screen, 0);
            lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif

#if LV_USE_WIN
        /*Header*/
        if ( lv_obj_get_index(obj) == 0 && lv_obj_check_type(lv_obj_get_parent(obj), &lv_win_class))
        {
            lv_obj_add_style(obj, &theme->styles.light, 0);
            return;
        }
            /*Content*/
        else if ( lv_obj_get_index(obj) == 1 && lv_obj_check_type(lv_obj_get_parent(obj), &lv_win_class))
        {
            lv_obj_add_style(obj, &theme->styles.light, 0);
            lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif
        lv_obj_add_style(obj, &theme->styles.white, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
    }
#if LV_USE_BUTTON
    else if ( lv_obj_check_type(obj, &lv_button_class))
    {
        lv_obj_add_style(obj, &theme->styles.dark, 0);
    }
#endif

#if LV_USE_BUTTONMATRIX
    else if ( lv_obj_check_type(obj, &lv_buttonmatrix_class))
    {
#if LV_USE_MSGBOX
        if ( lv_obj_check_type(lv_obj_get_parent(obj), &lv_msgbox_class))
        {
            lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS);
            return;
        }
#endif
#if LV_USE_TABVIEW
        if ( lv_obj_check_type(lv_obj_get_parent(obj), &lv_tabview_class))
        {
            lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS);
            return;
        }
#endif
        lv_obj_add_style(obj, &theme->styles.white, 0);
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS);
    }
#endif

#if LV_USE_BAR
    else if ( lv_obj_check_type(obj, &lv_bar_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_INDICATOR);
    }
#endif

#if LV_USE_SLIDER
    else if ( lv_obj_check_type(obj, &lv_slider_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &theme->styles.dim, LV_PART_KNOB);
    }
#endif

#if LV_USE_TABLE
    else if ( lv_obj_check_type(obj, &lv_table_class))
    {
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS);
    }
#endif

#if LV_USE_CHECKBOX
    else if ( lv_obj_check_type(obj, &lv_checkbox_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_INDICATOR | LV_STATE_CHECKED);
    }
#endif

#if LV_USE_SWITCH
    else if ( lv_obj_check_type(obj, &lv_switch_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.dim, LV_PART_KNOB);
    }
#endif

#if LV_USE_CHART
    else if ( lv_obj_check_type(obj, &lv_chart_class))
    {
        lv_obj_add_style(obj, &theme->styles.white, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_CURSOR);
    }
#endif

#if LV_USE_ROLLER
    else if ( lv_obj_check_type(obj, &lv_roller_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_SELECTED);
    }
#endif

#if LV_USE_DROPDOWN
    else if ( lv_obj_check_type(obj, &lv_dropdown_class))
    {
        lv_obj_add_style(obj, &theme->styles.white, 0);
    }
    else if ( lv_obj_check_type(obj, &lv_dropdownlist_class))
    {
        lv_obj_add_style(obj, &theme->styles.white, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_SELECTED);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_SELECTED | LV_STATE_CHECKED);
    }
#endif
    else if (lv_obj_check_type(obj, &lv_division_main_class))
    {
        lv_obj_add_style(obj, &theme->styles.division_main, 0);
        lv_obj_add_style(obj, &theme->styles.division_main_flex, 0);
    }
    else if (lv_obj_check_type(obj, &lv_division_btnm_class))
    {
        lv_obj_add_style(obj, &theme->styles.division_btnm, 0);
        lv_obj_add_style(obj, &theme->styles.division_btnm_flex, 0);
    }
#if LV_USE_ARC
    else if ( lv_obj_check_type(obj, &lv_arc_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.transp, 0);
        lv_obj_add_style(obj, &theme->styles.arc_line, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &theme->styles.arc_line, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &theme->styles.dim, LV_PART_KNOB);
        lv_obj_add_style(obj, &theme->styles.arc_knob, LV_PART_KNOB);
    }
#endif

#if LV_USE_SPINNER
    else if ( lv_obj_check_type(obj, &lv_spinner_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.transp, 0);
        lv_obj_add_style(obj, &theme->styles.arc_line, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &theme->styles.arc_line, LV_PART_INDICATOR);
    }
#endif

#if LV_USE_TEXTAREA
    else if ( lv_obj_check_type(obj, &lv_textarea_class))
    {
        lv_obj_add_style(obj, &theme->styles.white, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &theme->styles.ta_cursor, LV_PART_CURSOR | LV_STATE_FOCUSED);
    }
#endif

#if LV_USE_CALENDAR
    else if ( lv_obj_check_type(obj, &lv_calendar_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
    }
#endif

#if LV_USE_KEYBOARD
    else if ( lv_obj_check_type(obj, &lv_keyboard_class))
    {
        lv_obj_add_style(obj, &theme->styles.screen, 0);
        lv_obj_add_style(obj, &theme->styles.white, LV_PART_ITEMS);
        lv_obj_add_style(obj, &theme->styles.light, LV_PART_ITEMS | LV_STATE_CHECKED);
    }
#endif
#if LV_USE_LIST
    else if ( lv_obj_check_type(obj, &lv_list_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
        return;
    }
    else if ( lv_obj_check_type(obj, &lv_list_text_class))
    {

    }
    else if ( lv_obj_check_type(obj, &lv_list_button_class))
    {
        lv_obj_add_style(obj, &theme->styles.dark, 0);

    }
#endif
#if LV_USE_MSGBOX
    else if ( lv_obj_check_type(obj, &lv_msgbox_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        return;
    }
#endif
#if LV_USE_SPINBOX
    else if ( lv_obj_check_type(obj, &lv_spinbox_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
        lv_obj_add_style(obj, &theme->styles.dark, LV_PART_CURSOR);
    }
#endif
#if LV_USE_TILEVIEW
    else if ( lv_obj_check_type(obj, &lv_tileview_class))
    {
        lv_obj_add_style(obj, &theme->styles.screen, 0);
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
    }
    else if ( lv_obj_check_type(obj, &lv_tileview_tile_class))
    {
        lv_obj_add_style(obj, &theme->styles.scrollbar, LV_PART_SCROLLBAR);
    }
#endif

#if LV_USE_LED
    else if ( lv_obj_check_type(obj, &lv_led_class))
    {
        lv_obj_add_style(obj, &theme->styles.light, 0);
    }
#endif
    // Non-widget styles

}


void style_init_reset(lv_style_t* style)
{
    lv_style_init(style);
}


void style_init(lv_based_theme_t* theme)
{
    //if (theme == NULL)
    //    return NULL;

    style_init_reset(&theme->styles.scrollbar);
    lv_style_set_bg_opa(&theme->styles.scrollbar, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.scrollbar, BT_COLOR_DARK);
    lv_style_set_width(&theme->styles.scrollbar, BT_SCROLLBAR_WIDTH);

    style_init_reset(&theme->styles.screen);
    lv_style_set_bg_opa(&theme->styles.screen, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.screen, BT_COLOR_DARK);
    lv_style_set_text_color(&theme->styles.screen, BT_COLOR_LIGHT);

    style_init_reset(&theme->styles.transp);
    lv_style_set_bg_opa(&theme->styles.transp, LV_OPA_TRANSP);

    style_init_reset(&theme->styles.white);
    lv_style_set_bg_opa(&theme->styles.white, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.white, BT_COLOR_WHITE);
    lv_style_set_line_width(&theme->styles.white, 1);
    lv_style_set_line_color(&theme->styles.white, BT_COLOR_WHITE);
    lv_style_set_arc_width(&theme->styles.white, 2);
    lv_style_set_arc_color(&theme->styles.white, BT_COLOR_WHITE);

    style_init_reset(&theme->styles.light);
    lv_style_set_bg_opa(&theme->styles.light, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.light, BT_COLOR_LIGHT);
    lv_style_set_line_width(&theme->styles.light, 1);
    lv_style_set_line_color(&theme->styles.light, BT_COLOR_LIGHT);
    lv_style_set_arc_width(&theme->styles.light, 2);
    lv_style_set_arc_color(&theme->styles.light, BT_COLOR_LIGHT);

    style_init_reset(&theme->styles.dark);
    lv_style_set_bg_opa(&theme->styles.dark, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.dark, BT_COLOR_DARK);
    lv_style_set_line_width(&theme->styles.dark, 1);
    lv_style_set_line_color(&theme->styles.dark, BT_COLOR_DARK);
    lv_style_set_arc_width(&theme->styles.dark, 2);
    lv_style_set_arc_color(&theme->styles.dark, BT_COLOR_DARK);

    style_init_reset(&theme->styles.dim);
    lv_style_set_bg_opa(&theme->styles.dim, LV_OPA_COVER);
    lv_style_set_bg_color(&theme->styles.dim, BT_COLOR_DIM);
    lv_style_set_line_width(&theme->styles.dim, 1);
    lv_style_set_line_color(&theme->styles.dim, BT_COLOR_DIM);
    lv_style_set_arc_width(&theme->styles.dim, 2);
    lv_style_set_arc_color(&theme->styles.dim, BT_COLOR_DIM);
#if LV_USE_DIV
#endif
#if LV_USE_LIST
    style_init_reset(&theme->styles.list);
    style_init_reset(&theme->styles.logbox);
#endif
//#if LV_USE_ARC
//    style_init_reset(&theme->styles.arc_line);
//    lv_style_set_arc_width(&theme->styles.arc_line, 6);
//    style_init_reset(&theme->styles.arc_knob);
//    lv_style_set_pad_all(&theme->styles.arc_knob, 5);
//#endif
//
//#if LV_USE_TEXTAREA
//    style_init_reset(&theme->styles.ta_cursor);
//    lv_style_set_border_side(&theme->styles.ta_cursor, LV_BORDER_SIDE_LEFT);
//    lv_style_set_border_color(&theme->styles.ta_cursor, COLOR_DIM);
//    lv_style_set_border_width(&theme->styles.ta_cursor, 2);
//    lv_style_set_bg_opa(&theme->styles.ta_cursor, LV_OPA_TRANSP);
//    lv_style_set_anim_duration(&theme->styles.ta_cursor, 500);
//#endif

//    return theme;
}

lv_theme_t* lv_theme_based_init(lv_display_t* disp)
{

    static lv_based_theme_t theme = {
            .base =
                    {
                            .apply_cb = apply_theme,
                            .parent = NULL,
                            .user_data = NULL,
                            //.disp = disp,
                            .disp = NULL,
                            .color_primary = { LV_RB_COLOR_BLACK },
                            .color_secondary = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
                            .font_small = &lv_font_montserrat_8,
                            .font_normal = &lv_font_montserrat_10,
                            .font_large = &lv_font_montserrat_12,
                            .flags = 0
                    },
            .init = 1
    };

    theme.base.disp = disp;
    style_init(&theme);

    if ( disp == NULL || lv_display_get_theme(disp) == (lv_theme_t*) &theme )
        lv_obj_report_style_change((lv_style_t* )&theme.styles);

    return (lv_theme_t *) &theme;
}

#endif
