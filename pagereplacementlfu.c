`#include <stdio.h>
 
int main()
{
    int pages;
    printf("Enter the number of Pages: ");
    scanf("%d", &pages);
    int refString[pages];
    printf("\nEnter the reference string values:\n");
    for (int i=0; i<pages; i++)
        scanf("%d", &refString[i]);
    int frames;
    printf("Enter the total number of frames: ");
    scanf("%d", &frames);
    int frame_set[frames];
    for (int i = 0; i < frames; i++)
        frame_set[i] = -1;
    int page_faults = 0;
    int frequency_table[frames];
    for (int i = 0; i < frames; i++)
        frequency_table[i] = 0;
    int replaced_index[frames];
    printf("\n LFU Page Replacement Algorithm \n");
    printf("   Reference string \t Page Frames\n\n");
    for (int i=0; i<pages; i++)
    {
        int flag = 0;
        for (int j=0; j<frames; j++)
        {
            if (frame_set[j] == refString[i])
            {
                flag = 1;
                frequency_table[j]++;
                break;
            }
        }
        if (!flag)
        {
            if (page_faults <= frames - 1){
                frame_set[page_faults] = refString[i];
                frequency_table[page_faults]++;
                replaced_index[page_faults]=i;
            }
            else
            {
                int min_freq = pages;
                for (int j=0; j<frames; j++)
                {
                    if(frequency_table[j] < min_freq)
                        min_freq = frequency_table[j];
                }
                int min_index = -1;
                int min_replaced = pages;
                for (int j=0; j<frames; j++)
                {
                    if (frequency_table[j] == min_freq)
                    {
                        if (min_replaced > replaced_index[j])
                        {
                            min_replaced = replaced_index[j];
                            min_index = j;
                        }
                    }
                }
                frame_set[min_index] = refString[i];
                replaced_index[min_index] = i;
                frequency_table[min_index] = 1;
            }
            page_faults++;
        }
       
        printf("\t%d\t\t", refString[i]);
        for (int j=0; j<frames; j++)
            printf("%d\t", frame_set[j]);
        printf("\n");
    }
    printf("\nTotal Page Faults: %d \n", page_faults);
 
    float pageHits = pages - page_faults;
    float hitRatio = pageHits/pages;
    float missRatio = (float)page_faults/pages;
 
    printf("\nHit ratio: %f", hitRatio);
    printf("\nMiss ratio: %f\n", missRatio);
    return 0;
}`