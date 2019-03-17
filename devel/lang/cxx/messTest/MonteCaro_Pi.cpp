/* Monte Carlo simulation to calculate Pi */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

int main(int argc, char **argv){
#if 1  /* user define value */
    const int NUMBER_OF_TRIALS = 99999999; /* trial times */
    const float Radius = 1.0;               /* give the radius of a circle */
#endif
    const float AreaSquare = Radius * Radius * 4; /* the area of square of the circle */
    int numberOfHits = 0; /* to record the times of hits */

    float Pi;   /* to record the result */

    srand((unsigned)time(NULL));

    for(int i = 0; i < NUMBER_OF_TRIALS; i++) {
        float x = (2 * Radius) * 1.0 * rand() / RAND_MAX - Radius;
        float y = (2 * Radius) * 1.0 * rand() / RAND_MAX - Radius;

        if(sqrt((x * x) + (y * y)) <= 1.0)
            numberOfHits++;
    }

    Pi = 4.0 * numberOfHits / NUMBER_OF_TRIALS;
    cout << "Pi is " << Pi << endl;

    return 0;
}
