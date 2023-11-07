# Kernel-Based Keylogger

A basic kernel-level keylogger module made using C. The module captures and logs keyboard events in the kernel log.

## Prerequisites

- A Linux system.
- Kernel development headers installed.
- Root access.

## Building the Module

1. Clone the repository to your local system.

2. Open a terminal and navigate to the project directory.

3. Build the module by running the following command:

```shell
make
```

On success, This will generate a kernel module file called keylogger.ko

## Loading the module

```shell
sudo insmod keylogger.ko
```

This will load the keylogger module into the kernel.

```shell
dmesg
```

You can see a log message that says module is loaded.

Now you can try typing anything and just run ``dmesg`` to see the keylogs.

## Unloading the module

```shell
sudo rmmod keylogger
```

This will remove the module from the kernel

## Important notes

- The use of keyloggers for unauthorized or malicious purposes is illegal and unethical. This project is intended for educational and debugging purposes only.
- Always be careful when you are in kernel level, small mistakes can brick the kernel.
- Developer of this code is not responsible for any damage/actions caused by anyone.

## Contributing

You're welcome to contribute to this project

- If you find any bugs, please [open an issue](https://github.com/47hxl-53r/kernel-level-keylogger/issues).
- Want to contribute to the project? Feel free to open a pull request.

## LICENSE

This project is licensed under the MIT license. 

