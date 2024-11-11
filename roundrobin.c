#include <stdio.h>
#include <stdlib.h>


struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};


struct Node {
    int data;
    struct Node* next;
};


struct Queue {
    struct Node *front, *rear;
};


struct Node* newNode(int k) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = k;
    temp->next = NULL;
    return temp;
}


struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


void enqueue(struct Queue* q, int k) {
    struct Node* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}


int dequeue(struct Queue* q) {
    if (q->front == NULL)
        return -1;
    struct Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    int data = temp->data;
    free(temp);
    return data;
}


void roundRobin(struct Process processes[], int n, int quantum) {
    int total_time = 0;
    int completed = 0;

    struct Queue* queue = createQueue();

    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    enqueue(queue, 0);
    visited[0] = 1;

    while (completed < n) {
        int i = dequeue(queue);

        if (i == -1) {
            continue;
        }

        if (processes[i].remaining_time > 0) {
            if (processes[i].remaining_time <= quantum) {

                total_time += processes[i].remaining_time;
                processes[i].remaining_time = 0;
                processes[i].completion_time = total_time;
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                completed++;
            } else {
                total_time += quantum;
                processes[i].remaining_time -= quantum;
            }

            for (int j = 0; j < n; j++) {
                if (processes[j].arrival_time <= total_time && processes[j].remaining_time > 0 && !visited[j]) {
                    enqueue(queue, j);
                    visited[j] = 1;
                }
            }

            if (processes[i].remaining_time > 0) {
                enqueue(queue, i);
            }
        }
    }
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    roundRobin(processes, n, quantum);

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    return 0;
}
