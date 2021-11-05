#include <cassert>
#include <cmath>
#include <iostream>
#include<iomanip>

#include "welford.h"

double EPS = 0.00001;
void assert_near(double a, double b)
{
    assert(fabs(a - b) < EPS);
}

int main(int argc, char const *argv[])
{
    {
        Welford w;
        w.add(0);
        w.add(1);
        w.add(2);
        assert(w.mean() == 1);
        assert(w.variance_sample() == 1);
        assert_near(w.variance_pop(), (double)2/3);

        w.add(3);
        w.add(4);
        assert(w.mean() == 2);
        assert_near(w.variance_sample(), 2.5);
        assert(w.variance_pop() == 2);
    }
    {
        Welford w;
        w.add(100);
        w.add(110);
        w.add(120);
        assert(w.mean() == 110);
        assert(w.variance_sample() == 100);
        assert_near(w.variance_pop(), (double)100*2/3);

        w.add(130);
        w.add(140);
        assert(w.mean() == 120);
        assert(w.variance_sample() == 250);
        assert(w.variance_pop() == 200);
    }

    {
        Welford w1;
        Welford w2;
        
        w1.add(0);
        w1.add(1);
        w1.add(2);
        assert(w1.mean() == 1);
        assert(w1.variance_sample() == 1);
        assert_near(w1.variance_pop(), (double)2/3);

        w2.add(3);
        w2.add(4);
        assert_near(w2.mean(), 3.5);
        assert_near(w2.variance_sample(), .5);
        assert_near(w2.variance_pop(), .25);

        w1.merge(w2);
        assert(w1.mean() == 2);
        assert_near(w1.variance_sample(), 2.5);
        assert(w1.variance_pop() == 2);
    }
    {
        Welford w1;
        Welford w2;
        
        w1.add(100);
        w1.add(110);
        w1.add(120);
        assert(w1.mean() == 110);
        assert(w1.variance_sample() == 100);
        assert_near(w1.variance_pop(), (double)100*2/3);

        w2.add(130);
        w2.add(140);
        assert(w2.mean() == 135);
        assert(w2.variance_sample() == 50);
        assert(w2.variance_pop() == 25);

        w1.merge(w2);
        assert(w1.mean() == 120);
        assert(w1.variance_sample() == 250);
        assert(w1.variance_pop() == 200);
    }

    return 0;
}
