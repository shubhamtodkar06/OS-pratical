#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void C_LOOK(int requests[], int n, int head, int direction) {
    int totalMovement = 0;
    int sequence[n];
    int count = 0;

    sort(requests, n);

    int headIndex;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            headIndex = i;
            break;
        }
    }

    if (direction == 1) {  // Moving towards higher end
        for (int i = headIndex; i < n; i++) {
            sequence[count++] = requests[i];
        }
        for (int i = 0; i < headIndex; i++) {
            sequence[count++] = requests[i];
        }
    } else {  // Moving towards lower end
        for (int i = headIndex - 1; i >= 0; i--) {
            sequence[count++] = requests[i];
        }
        for (int i = n - 1; i >= headIndex; i--) {
            sequence[count++] = requests[i];
        }
    }

    printf("C-LOOK Disk Scheduling Sequence:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", sequence[i]);
        if (i > 0) {
            totalMovement += abs(sequence[i] - sequence[i - 1]);
        }
    }
    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int n, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (1 for up, 0 for down): ");
    scanf("%d", &direction);

    C_LOOK(requests, n, head, direction);

    return 0;
}

