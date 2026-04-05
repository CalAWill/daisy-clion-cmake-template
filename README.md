# 🌼 Daisy Seed CLion & CMake Template

A plug-and-play template for building bare-metal C++ audio applications for the Electro-Smith Daisy Seed using CMake and CLion.

This template includes pre-configured run configurations for **USB Flashing (DFU)** and **Hardware Debugging (ST-Link)**.

---

## 1. Prerequisites (The Toolchain)
Before opening this project, you must have the embedded ARM toolchain installed on your computer.

* **ARM GNU Toolchain:** Required to compile C++ for the STM32 chip.
    * *Ubuntu/Debian:* `sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib`
    * *Mac:* `brew install arm-none-eabi-gcc`
* **dfu-util:** Required to flash the board via a standard USB cable.
    * *Ubuntu/Debian:* `sudo apt install dfu-util`
    * *Mac:* `brew install dfu-util`
* **OpenOCD (Optional):** Required only if you are using an ST-Link hardware debugger.
    * *Ubuntu/Debian:* `sudo apt install openocd`
    * *Mac:* `brew install openocd`

*(Note for Linux users: Ensure you have set up your `udev` rules for both the Daisy Seed in DFU mode and your ST-Link, or Linux will block the USB connection!)*

---

## 2. How to Clone This Template
Because this project relies on STMicroelectronics drivers nested inside `libDaisy`, you **must** use the `--recursive` flag when cloning.

Run this in your terminal:
```bash
git clone --recursive https://github.com/CalAWill/daisy-clion-cmake-template <your-project-name>
```
*(If you forgot the flag and your `lib` folders are empty, run `git submodule update --init --recursive` inside the project folder to fix it).*

---

## 3. CLion Setup
1. Open CLion, select **Open**, and choose the `CMakeLists.txt` file in the root folder. Click **Open as Project**.
2. Go to **Settings/Preferences > Build, Execution, Deployment > CMake**.
3. In the **CMake options** box, paste this exact line to tell CLion we are cross-compiling for the Daisy:
   `-DCMAKE_TOOLCHAIN_FILE=lib/libDaisy/cmake/toolchains/stm32h750xx.cmake`
4. Click **Apply** and wait for the CMake tab at the bottom to say `[Finished]`.

---

## 4. Flashing Your Code

Thanks to the included `.run` configurations, your dropdown menu in the top right of CLion is already set up.

### Method A: USB Flashing (No extra hardware)
1. Select the **Flash Daisy (USB)** configuration from the top right dropdown.
2. Put your Daisy Seed into Bootloader mode:
    * Hold the **BOOT** button.
    * Press the **RESET** button.
    * Release the **BOOT** button.
3. Click the Green **Build (Hammer)** icon. The code will compile and automatically push to the board.

### Method B: Hardware Debugging (ST-Link)
1. Wire your ST-Link to the Daisy Seed debug header (GND, SWCLK, SWDIO).
2. Select the **Debug Daisy (ST-Link)** configuration from the top right dropdown.
3. Set a breakpoint in `src/main.cpp`.
4. Click the Green **Debug (Bug)** icon. OpenOCD will automatically flash the board and pause execution at your breakpoint.

---

## 5. Starting a New Project
To use this template as a starting point for a new repository:

1. **Clone the template into a new folder:**
   ```bash
   git clone --recursive https://github.com/CalAWill/daisy-clion-cmake-template my-new-project
   cd my-new-project
   ```

2. **Reset the Git history:**
   ```bash
   rm -rf .git
   git init
   git add .
   git commit -m "Initial commit from Daisy template"
   ```

3. **Re-initialize the Daisy submodules:**
   *Because the `.git` folder was deleted, you need to re-link the submodules to your new repository:*
   ```bash
   git submodule add https://github.com/electro-smith/libDaisy lib/libDaisy
   git submodule add https://github.com/electro-smith/DaisySP lib/DaisySP
   git submodule update --init --recursive
   ```

4. **Rename your project:**
   Open `CMakeLists.txt` and update the `project()` name on **line 4**:
   ```cmake
   project(MyNewProjectName C CXX ASM)
   ```

5. **Open in CLion:**
   Follow the setup instructions in **Section 3** to configure your toolchain.
