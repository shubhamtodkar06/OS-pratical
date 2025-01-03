#include <stdio.h>
#include <stdlib.h>

void FCFS(int pages[], int n, int maxFrames) {
    int frames[maxFrames];
    int pageFaults = 0;
    int i, j, k;

    for (i = 0; i < maxFrames; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        for (j = 0; j < maxFrames; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            frames[pageFaults % maxFrames] = page;
            pageFaults++;
        }

        printf("Page: %d -> Frames: ", page);
        for (k = 0; k < maxFrames; k++) {
            if (frames[k] == -1) {
                printf(" - ");
            } else {
                printf("%d ", frames[k]);
            }
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int n, maxFrames;

    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &maxFrames);

    if (maxFrames < 3) {
        printf("Frame size must be at least 3.\n");
        return 1;
    }

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the page reference string (space-separated values): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    FCFS(pages, n, maxFrames);

    return 0;
}
