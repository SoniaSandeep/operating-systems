#include <stdio.h>

#define MAX 50

/* FIFO Page Replacement */
void fifo(int pages[], int n, int frames)
{
    int frame[MAX];
    int i, j, front = 0;
    int hit, faults = 0;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            faults++;

            printf("PF No. %d: ", faults);
            for(j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame[j]);
            }
            printf("\n");
        }
    }

    printf("FIFO Page Faults: %d\n", faults);
}

/* LRU Page Replacement */
void lru(int pages[], int n, int frames)
{
    int frame[MAX], recent[MAX];
    int i, j, pos, min;
    int hit, faults = 0, count = 0;

    for(i = 0; i < frames; i++)
    {
        frame[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                count++;
                recent[j] = count;
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            pos = -1;

            /* Find empty frame first */
            for(j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            /* If no empty frame, find LRU page */
            if(pos == -1)
            {
                pos = 0;
                min = recent[0];

                for(j = 1; j < frames; j++)
                {
                    if(recent[j] < min)
                    {
                        min = recent[j];
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            count++;
            recent[pos] = count;
            faults++;

            printf("PF No. %d: ", faults);
            for(j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame[j]);
            }
            printf("\n");
        }
    }

    printf("LRU Page Faults: %d\n", faults);
}

/* Optimal Page Replacement */
void optimal(int pages[], int n, int frames)
{
    int frame[MAX];
    int i, j, k;
    int hit, faults = 0;
    int pos, farthest, index;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            /* Empty frame available */
            pos = -1;

            for(j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            /* No empty frame */
            if(pos == -1)
            {
                farthest = -1;

                for(j = 0; j < frames; j++)
                {
                    index = n;

                    for(k = i + 1; k < n; k++)
                    {
                        if(frame[j] == pages[k])
                        {
                            index = k;
                            break;
                        }
                    }

                    if(index > farthest)
                    {
                        farthest = index;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;

            printf("PF No. %d: ", faults);
            for(j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame[j]);
            }
            printf("\n");
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
}

int main()
{
    int pages[MAX];
    int n, frames, i;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
