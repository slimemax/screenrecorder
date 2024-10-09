# ScreenRecorder

ScreenRecorder is a simple screen recording tool for Windows. It allows you to record your screen using a hotkey (Shift + Q) and convert the recording into a GIF. This project uses FFmpeg for recording and conversion.

## Features
- Screen recording with hotkey (Shift + Q)
- Converts screen recordings to GIF
- Customizable framerate, recording duration, and GIF quality

## Requirements
- Windows operating system
- FFmpeg executable in the same directory as the compiled `screen_recorder.exe` -DOWNLOAD FFMPEG HERE: https://github.com/BtbN/FFmpeg-Builds/releases 

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/slimemax/screenrecorder.git
   ```

2. Move into the project directory:
   ```sh
   cd screenrecorder
   ```

3. Ensure `ffmpeg.exe` is in the same directory as the compiled executable.

4. If you want to Compile the code using MinGW:
   ```sh
   x86_64-w64-mingw32-gcc screen_recorder.c -o screen_recorder.exe -luser32 -lgdi32
   ```

## Usage
1. Run the executable:
   ```sh
   screen_recorder.exe
   ```

2. Press `Shift + Q` to start the screen recording.
3. The program will create a screen recording (`.mp4`) and convert it into a GIF.

## Building and Running on Linux (with Wine)
1. Make sure Wine is installed.
2. Run the executable using Wine:
   ```sh
   wine screen_recorder.exe
   ```

## License
This project is open source and available under the MIT License.

## Contributing
Feel free to submit issues and pull requests for new features or bug fixes.

## Author
- [slimemax](https://github.com/slimemax)

## Troubleshooting
If you encounter issues:
- Make sure `ffmpeg.exe` has executable permissions.
- Run the program in a Windows environment or through Wine on Linux for proper execution.

## Notes
- FFmpeg is used for both screen capturing and converting the recordings to GIFs. Ensure it is accessible to avoid errors.


