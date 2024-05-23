#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover YOUR IMAGE FILE \n");
        return 1;
    }
    if (argv[1] == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *file = NULL;
    uint8_t buffer[512];
    int counter = 0;
    while (fread(buffer, 1, 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (file != NULL)
            {
                fclose(file);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            file = fopen(filename, "w");
        }
        if (file != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, file);
        }
    }
    fclose(input);
    fclose(file);
    return 0;
}
