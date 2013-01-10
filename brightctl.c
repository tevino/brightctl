#include <stdio.h>
#include <string.h>

const char *CTL_FILE = "/sys/class/backlight/acpi_video0/brightness";
const char *MAX_FILE = "/sys/class/backlight/acpi_video0/max_brightness";

void show_help()
{
    printf("Usage: brightctl up/down\n");
}

int cat(const char *file_path)
{
    FILE *fl = fopen(file_path, "r");
    int num;
    fscanf(fl, "%d", &num);
    fclose(fl);
    return num;
}

void set_brightness(int num)
{
    FILE *fl = fopen(CTL_FILE, "w");
    fprintf(fl, "%d", num);
    fclose(fl);
}

int main(int argc, char *argv[])
{
    int bright = -1;
    
    switch(argc)
    {
        case 2:
        {
            int max = cat(MAX_FILE);
            int current = cat(CTL_FILE);

            printf("brightness: max %d, current %d", max, current);
            const char *method = argv[1];

            if (strcmp(method, "up") == 0 && current < max)
            {
                bright = current + 1;
            }
            else if(strcmp(method, "down") == 0 && current > 0)
            {
                bright = current - 1;
            }
            break;
        }
        default:
        {
            show_help();
            return -1;
        }
    }
    if(bright > -1)
    {
        printf(", set %d", bright);
        set_brightness(bright);
    }
    printf("\n");
    return 0;
}
