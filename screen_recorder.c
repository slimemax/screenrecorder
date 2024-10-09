#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define FFMPEG_RECORD_COMMAND "ffmpeg.exe -f gdigrab -framerate %d -i desktop -t %d %s"
#define FFMPEG_GIF_COMMAND "ffmpeg.exe -i %s -vf \"fps=%d,scale=%d:-1:flags=lanczos\" -loop 0 %s"

volatile int stop_recording = 0;
volatile int start_recording = 0;
int recording_time = 3;
int framerate = 25;
int gif_fps = 10;
int gif_scale = 800;
WORD hotkey = VK_F2;
UINT modifier = 0;

void handle_signal(int signal) {
    stop_recording = 1;
}

void display_menu() {
    printf("Screen Recorder Configuration Menu:\n");
    printf("1. Set Hotkey (current: Shift + %c)\n", hotkey);
    printf("2. Set Recording Time (current: %d seconds)\n", recording_time);
    printf("3. Set Framerate (current: %d fps)\n", framerate);
    printf("4. Set GIF FPS (current: %d fps)\n", gif_fps);
    printf("5. Set GIF Scale Width (current: %d pixels)\n", gif_scale);
    printf("6. Start Recording\n");
    printf("7. Exit\n");
}

void configure_settings() {
    int choice;
    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1: {
                char new_hotkey;
                printf("Enter new hotkey character: ");
                scanf(" %c", &new_hotkey);
                hotkey = new_hotkey;
                break;
            }
            case 2:
                printf("Enter new recording time in seconds: ");
                scanf("%d", &recording_time);
                break;
            case 3:
                printf("Enter new framerate: ");
                scanf("%d", &framerate);
                break;
            case 4:
                printf("Enter new GIF FPS: ");
                scanf("%d", &gif_fps);
                break;
            case 5:
                printf("Enter new GIF scale width: ");
                scanf("%d", &gif_scale);
                break;
            case 6:
                start_recording = 1;
                return;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    // Register signal handler to stop recording on CTRL+C
    signal(SIGINT, handle_signal);

    // Configure settings through menu
    configure_settings();

    // Generate unique filenames using timestamp
    char video_filename[64];
    char gif_filename[64];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(video_filename, sizeof(video_filename), "temp_%04d%02d%02d%02d%02d%02d.mp4", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    snprintf(gif_filename, sizeof(gif_filename), "output_%04d%02d%02d%02d%02d%02d.gif", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Create command to capture screen using ffmpeg
    char ffmpeg_record_command[256];
    snprintf(ffmpeg_record_command, sizeof(ffmpeg_record_command), FFMPEG_RECORD_COMMAND, framerate, recording_time, video_filename);

    printf("Starting screen recording for %d seconds.\n", recording_time);
    if (system(ffmpeg_record_command) == -1) {
        printf("Press Enter to continue..."); getchar();
        perror("Failed to execute ffmpeg");
        return 1;
    }

    // Create command to convert video to GIF using ffmpeg
    char ffmpeg_gif_command[256];
    snprintf(ffmpeg_gif_command, sizeof(ffmpeg_gif_command), FFMPEG_GIF_COMMAND, video_filename, gif_fps, gif_scale, gif_filename);

    printf("Converting video to GIF using FFmpeg...\n");
    if (system(ffmpeg_gif_command) == -1) {
        printf("Press Enter to continue..."); getchar();
        perror("Failed to execute FFmpeg for GIF conversion");
        return 1;
    }

    printf("Recording saved as %s\n", gif_filename);
    return 0;
}
