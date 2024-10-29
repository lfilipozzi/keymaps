// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "lib/oled.h"

void render_numlock_section(void) {
    static const char PROGMEM num_on[] = {0x80, 0x81, 0x82, 0x83, 0};
    static const char PROGMEM num_off[] = {0xa0, 0xa1, 0xa2, 0xa3, 0};
    static const char PROGMEM cap_on[] = {0x84, 0x85, 0x86, 0x87, 0};
    static const char PROGMEM cap_off[] = {0xa4, 0xa5, 0xa6, 0xa7, 0};
    static const char PROGMEM scr_on[] = {0xba, 0xbb, 0xbc, 0xbd, 0};
    static const char PROGMEM scr_off[] = {0xda, 0xdb, 0xdc, 0xdd, 0};

    led_t led_state = host_keyboard_led_state();

    oled_set_cursor(oled_max_chars()-12, 3);
    // num lock
    oled_write_P(led_state.num_lock ? num_on : num_off, false);
    oled_write_P(led_state.caps_lock ? cap_on : cap_off, false);
    oled_write_P(led_state.scroll_lock ? scr_on : scr_off, false);
}

#ifdef OLED_ENABLE
// oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
//     if (!is_keyboard_master()) {
//         return OLED_ROTATION_180;
//     }
//     return rotation;
// }
//
// bool oled_task_kb(void) {
//     if (!oled_task_user()) {
//         return false;
//     }
//     if (is_keyboard_master()) {
//         render_layer_state();
//     } else {
//         oled_write_raw_P(bs_logo_img, sizeof(bs_logo_img));
//     }
//     return false;
// }

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return rotation;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_layer_state();
    return false;
}
#endif
