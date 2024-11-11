#include <stdio.h>
#include <stdlib.h>

void Optimal(int pages[], int n, int maxFrames) {
    int frames[maxFrames];
    int pageFaults = 0;
    int i, j, k, l;

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
            int farthest = -1;
            int replaceIndex = -1;

            for (j = 0; j < maxFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }

                int nextUse = -1;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if (nextUse == -1) {
                    replaceIndex = j;
                    break;
                } else if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = page;
            pageFaults++;
        }

        printf("Page: %d -> Frames: ", page);
        for (l = 0; l < maxFrames; l++) {
            if (frames[l] == -1) {
                printf(" - ");
            } else {
                printf("%d ", frames[l]);
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

    Optimal(pages, n, maxFrames);

    return 0;
}
