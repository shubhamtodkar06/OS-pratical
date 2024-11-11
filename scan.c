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

void SCAN(int requests[], int n, int head, int disk_size, int direction) {
    int totalMovement = 0;
    int sequence[n + 2];
    int count = 0;

    requests[n] = head;
    requests[n + 1] = (direction == 1) ? disk_size - 1 : 0;
    n += 2;

    sort(requests, n);

    int headIndex;
    for (int i = 0; i < n; i++) {
        if (requests[i] == head) {
            headIndex = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = headIndex; i < n; i++) {
            sequence[count++] = requests[i];
        }
        for (int i = headIndex - 1; i >= 0; i--) {
            sequence[count++] = requests[i];
        }
    } else {
        for (int i = headIndex; i >= 0; i--) {
            sequence[count++] = requests[i];
        }
        for (int i = headIndex + 1; i < n; i++) {
            sequence[count++] = requests[i];
        }
    }

    printf("SCAN Disk Scheduling Sequence:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", sequence[i]);
        if (i > 0) {
            totalMovement += abs(sequence[i] - sequence[i - 1]);
        }
    }
    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int n, head, disk_size, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n + 2];
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the direction (1 for up, 0 for down): ");
    scanf("%d", &direction);

    SCAN(requests, n, head, disk_size, direction);

    return 0;
}
