#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

const int DEFAULT_SIZE = (int) 1e5;
const int STEP = (int) 1;

int main() {
    int x = 0, y = 0;

    for (char c; c = getchar(); ) {
        switch(c) {
            case 'N':
                y += STEP;
                break;
            case 'W':
                x -= STEP;
                break;
            case 'E':
                x += STEP;
                break;
            case 'S':
                y -= STEP;
                break;
            default:
                printf("%lf", sqrt(x * x + y * y));
                return 0;
        }
    }

    assert(false);        
}
