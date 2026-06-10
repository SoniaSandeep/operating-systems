#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 5;
int x = 0;

// Semaphore wait operation
void wait()
{
    mutex--;
}

// Semaphore signal operation
void signal()
{
    mutex++;
}

// Producer function
void producer()
{
    wait();

    full++;
    empty--;
    x++;

    printf("Producer has produced: Item %d\n", x);

    signal();
}

// Consumer function
void consumer()
{
    wait();

    full--;
    empty++;

    printf("Consumer has consumed: Item %d\n", x);

    x--;

    signal();
}

int main()
{
    int choice;

    printf("\n1. Produce");
    printf("\n2. Consume");
    printf("\n3. Exit\n");

    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if ((mutex == 1) && (empty != 0))
                {
                    producer();
                }
                else
                {
                    printf("Buffer is full!\n");
                }
                break;

            case 2:
                if ((mutex == 1) && (full != 0))
                {
                    consumer();
                }
                else
                {
                    printf("Buffer is empty!\n");
                }
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    }
    while (choice != 3);

    return 0;
}
