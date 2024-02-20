#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#define SAMPLE_FREQ 44100.0

void die(char *);

double make_freq(char *);
int make_note(char *, int);

void write_wav(FILE *, int, int, int, int, double, int);

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stdout, "usage: ./compose [tempo] [filename (read)] [filename (write)]\n");
        return EXIT_FAILURE;
    }

    int tempo = atoi(argv[1]);
    if (tempo == 0)
    {
        fprintf(stdout, "tempo must be number\n");
        return EXIT_FAILURE;
    }
    else if (tempo < 0)
    {
        fprintf(stdout, "tempo must be positive number\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        fprintf(stdout, "cannot open file: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    int Amp;
    if (fscanf(fp, "Amp %d\n", &Amp) != 1)
    {
        fprintf(stdout, "1st row: Amp [integer]\n");
        return EXIT_FAILURE;
    }

    int sin_ratio;
    if (fscanf(fp, "sin %d\n", &sin_ratio) != 1)
    {
        fprintf(stdout, "2nd row: sin [integer]\n");
        return EXIT_FAILURE;
    }

    int saw_ratio;
    if (fscanf(fp, "saw %d\n", &saw_ratio) != 1)
    {
        fprintf(stdout, "3rd row: saw [integer]\n");
        return EXIT_FAILURE;
    }

    int tri_ratio;
    if (fscanf(fp, "tri %d\n", &tri_ratio) != 1)
    {
        fprintf(stdout, "4th row: tri [integer]\n");
        return EXIT_FAILURE;
    }

    int squ_ratio;
    if (fscanf(fp, "squ %d\n", &squ_ratio) != 1)
    {
        fprintf(stdout, "5th row: squ [integer]\n");
        return EXIT_FAILURE;
    }

    FILE *fpw = fopen(argv[3], "w");

    int ratio_sum = sin_ratio + saw_ratio + tri_ratio + squ_ratio;

    int Amp_sin = Amp * (double)sin_ratio / ratio_sum;
    int Amp_saw = Amp * (double)saw_ratio / ratio_sum;
    int Amp_tri = Amp * (double)tri_ratio / ratio_sum;
    int Amp_squ = Amp * (double)squ_ratio / ratio_sum;

    char scale[4]; // Cs4
    char note[3];  // 4d
    while (fscanf(fp, "%[^ ] %[^\n]\n", scale, note) == 2)
    {
        double freq = make_freq(scale);
        int num = make_note(note, tempo);
        write_wav(fpw, Amp_sin, Amp_saw, Amp_tri, Amp_squ, freq, num);
    }
    fclose(fp);
    fclose(fpw);

    return EXIT_SUCCESS;
}

double make_freq(char *scale)
{
    double freq;
    if (strlen(scale) == 1)
    {
        if (scale[0] == 'R')
        {
            freq = 0.0;
        }
        else
        {
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: R 1\n");
            exit(1);
        }
    }
    else if (strlen(scale) == 2)
    {
        double freq_std;
        switch (scale[0])
        {
        case 'A':
            freq_std = 440.0;
            break;
        case 'B':
            freq_std = 440.0 * pow(2.0, 2.0 / 12.0);
            break;
        case 'C':
            freq_std = 440.0 * pow(2.0, -9.0 / 12.0);
            break;
        case 'D':
            freq_std = 440.0 * pow(2.0, -7.0 / 12.0);
            break;
        case 'E':
            freq_std = 440.0 * pow(2.0, -5.0 / 12.0);
            break;
        case 'F':
            freq_std = 440.0 * pow(2.0, -4.0 / 12.0);
            break;
        case 'G':
            freq_std = 440.0 * pow(2.0, -2.0 / 12.0);
            break;
        default:
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: C4 2\n");
            exit(1);
            break;
        }

        int d_oct;
        switch (scale[1])
        {
        case '0':
            d_oct = -4;
            break;
        case '1':
            d_oct = -3;
            break;
        case '2':
            d_oct = -2;
            break;
        case '3':
            d_oct = -1;
            break;
        case '4':
            d_oct = 0;
            break;
        case '5':
            d_oct = 1;
            break;
        case '6':
            d_oct = 2;
            break;
        case '7':
            d_oct = 3;
            break;
        case '8':
            d_oct = 4;
            break;
        default:
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: C4 3\n");
            exit(1);
            break;
        }
        freq = freq_std * pow(2.0, d_oct);
    }
    else if (strlen(scale) == 3)
    {
        if (scale[1] != 'S')
        {
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: CS4 4\n");
            exit(1);
        }
        double freq_std;
        switch (scale[0])
        {
        case 'A':
            freq_std = 440.0 * pow(2.0, 1.0 / 12.0);
            break;
        case 'C':
            freq_std = 440.0 * pow(2.0, -8.0 / 12.0);
            break;
        case 'D':
            freq_std = 440.0 * pow(2.0, -6.0 / 12.0);
            break;
        case 'F':
            freq_std = 440.0 * pow(2.0, -3.0 / 12.0);
            break;
        case 'G':
            freq_std = 440.0 * pow(2.0, -1.0 / 12.0);
            break;
        default:
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: CS4 5\n");
            exit(1);
            break;
        }

        int d_oct;
        switch (scale[2])
        {
        case '0':
            d_oct = -4;
            break;
        case '1':
            d_oct = -3;
            break;
        case '2':
            d_oct = -2;
            break;
        case '3':
            d_oct = -1;
            break;
        case '4':
            d_oct = 0;
            break;
        case '5':
            d_oct = 1;
            break;
        case '6':
            d_oct = 2;
            break;
        case '7':
            d_oct = 3;
            break;
        case '8':
            d_oct = 4;
            break;
        default:
            fprintf(stdout, "%s\n", scale);
            fprintf(stdout, "scale like: CS4 6\n");
            exit(1);
            break;
        }
        freq = freq_std * pow(2.0, d_oct);
    }
    else
    {
        fprintf(stdout, "%s\n", scale);
        fprintf(stdout, "scale like: CS4 7\n");
        exit(1);
    }

    return freq;
}

int make_note(char *note, int tempo)
{
    int sample_num;
    double delta = 60.0 * SAMPLE_FREQ / tempo;
    if (strlen(note) == 1)
    {
        double length;
        switch (note[0])
        {
        case '1':
            length = 4.0;
            break;
        case '2':
            length = 2.0;
            break;
        case '4':
            length = 1.0;
            break;
        case '8':
            length = 1.0 / 2.0;
            break;
        default:
            fprintf(stdout, "%s\n", note);
            fprintf(stdout, "note like: 4d 1\n");
            exit(1);
            break;
        }
        sample_num = delta * length;
    }
    else if (strlen(note) == 2)
    {
        double length;
        if (note[0] == '1' && note[1] == '6')
        {
            length = 1.0 / 4.0;
        }
        else
        {
            if (note[1] != 'd')
            {
                fprintf(stdout, "%s\n", note);
                fprintf(stdout, "note like: 4d 2\n");
                exit(1);
            }
            switch (note[0])
            {
            case '2':
                length = 1.5 * 2.0;
                break;
            case '4':
                length = 1.5 * 1.0;
                break;
            case '8':
                length = 1.5 * 1.0 / 2.0;
                break;
            default:
                fprintf(stdout, "%s\n", note);
                fprintf(stdout, "note like: 4d 3\n");
                exit(1);
                break;
            }
        }
        sample_num = delta * length;
    }
    else
    {
        fprintf(stdout, "%s\n", note);
        fprintf(stdout, "note like: 4d 4\n");
        exit(1);
    }
    return sample_num;
}

void write_wav(FILE *fpw, int Amp_sin, int Amp_saw, int Amp_tri, int Amp_squ, double freq, int num)
{
    short data[num];
    // init
    for (int i = 0; i < num; i++)
    {
        data[i] = 0;
    }
    //
    for (int i = 0; i < num; i++)
    {
        data[i] += (short)(Amp_sin * sin(2 * M_PI * freq * (i / SAMPLE_FREQ)));
    }

    for (int i = 0; i < num; i++)
    {
        data[i] += (short)(2 * Amp_saw * (freq * (i / SAMPLE_FREQ) - floor(freq * (i / SAMPLE_FREQ) + 1.0 / 2.0)));
    }

    for (int i = 0; i < num; i++)
    {
        data[i] += (short)(Amp_tri * (2 * fabs(2 * (freq * (i / SAMPLE_FREQ) - floor(freq * (i / SAMPLE_FREQ) + 1.0 / 2.0))) - 1));
    }

    for (int i = 0; i < num; i++)
    {
        data[i] += (short)(Amp_squ * (((sin(2 * M_PI * freq * (i / SAMPLE_FREQ))) > 0) - ((sin(2 * M_PI * freq * (i / SAMPLE_FREQ))) < 0)));
    }

    if (fwrite(data, sizeof(short), num, fpw) != num)
    {
        die("write");
    }
}

void die(char *s)
{
    perror(s);
    exit(1);
}
