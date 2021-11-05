#include <cstdint>

class Welford
{
private:
    /* data */
    uint64_t _count;
    double _m;
    double _s;

    double _get_variance(int ddof)
    {
        if (_count <= 0)
            return 0;

        int min_count = ddof;
        if (_count <= min_count)
            return 0;
        else
            return _s / (_count - ddof);
    }

public:
    Welford()
    {
        _count = 0;
        _m = 0;
        _s = 0;
    };

    double mean() { return _m; }
    uint64_t count() { return _count; }
    double variance_sample() { return _get_variance(1); }
    double variance_pop() { return _get_variance(0); }

    void add(double element)
    {
        _count += 1;
        double delta = element - _m;
        _m += delta / _count;
        _s += delta * (element - _m);
    }

    void merge(Welford other)
    {
        uint64_t count = _count + other._count;
        double delta = _m - other._m;
        double delta2 = delta * delta;
        double m = (_count * _m + other._count * other._m) / count;
        double s = _s + other._s + delta2 * (_count * other._count) / count;
        
        _count = count;
        _m = m;
        _s = s;
    }
};
