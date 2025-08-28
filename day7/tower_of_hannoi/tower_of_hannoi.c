#include <stdio.h>

void towerOfHanoi(int n, char source_rod, char destination_rod, char middle_rod) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source_rod, destination_rod);
        return;
    }

    towerOfHanoi(n - 1, source_rod, middle_rod, destination_rod);
    printf("Move disk %d from %c to %c\n", n, source_rod, destination_rod);
    towerOfHanoi(n - 1, middle_rod, destination_rod, source_rod);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
