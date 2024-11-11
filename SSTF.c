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

int findClosestRequest(int requests[], int visited[], int n, int head) {
    int minDistance = __INT_MAX__;
    int closestIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int distance = abs(head - requests[i]);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = i;
            }
        }
    }
    return closestIndex;
}

void SSTF(int requests[], int n, int head) {
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    int totalMovement = 0;
    int currentPosition = head;
    int sequence[n];

    for (int i = 0; i < n; i++) {
        int closest = findClosestRequest(requests, visited, n, currentPosition);
        if (closest == -1) break;

        visited[closest] = 1;
        sequence[i] = requests[closest];

        totalMovement += abs(currentPosition - requests[closest]);
        currentPosition = requests[closest];
    }

    printf("SSTF Disk Scheduling Sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int n, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    SSTF(requests, n, head);

    return 0;
}
