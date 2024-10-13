#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    Pt() {}
    Pt(long long _x, long long _y) : x(_x), y(_y) {}
    Pt operator+(const Pt &p) const { return Pt(x + p.x, y + p.y); }
    Pt operator-(const Pt &p) const { return Pt(x - p.x, y - p.y); }
    long long cross(const Pt &p) const { return x * p.y - y * p.x; }
    long long dot(const Pt &p) const { return x * p.x + y * p.y; }
    long long cross(const Pt &a, const Pt &b) const {
        return (a - *this).cross(b - *this);
    }
    long long dot(const Pt &a, const Pt &b) const {
        return (a - *this).dot(b - *this);
    }
    long long sqrLen() const { return this->dot(*this); }
};

bool lexComp(const Pt &l, const Pt &r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

// https://codeforces.com/topic/58970/en1
Pt rf;

bool A(const Pt &p) {
    return rf.cross(p) > 0 || (rf.cross(p) == 0 && rf.dot(p) > 0);
}

bool ccwcomp(const Pt &a, const Pt &b) {
    return (A(a) == A(b) && a.cross(b) > 0) || (A(a) && !A(b));
}

int sgn(long long val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

vector<Pt> seq;
Pt translation;
bool prepCalled = false;
int sz;

bool pointInTriangle(Pt a, Pt b, Pt c, Pt point) {
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) +
                   abs(point.cross(c, a));
    return s1 == s2;
}

void prepare(vector<Pt> &points) {
    prepCalled = true;
    sz = points.size();
    int pos = 0;

    // ccw sorting, if input is not ccw sorted
    // rf = {0, 0};
    // sort(points.begin(), points.end(), [](const Pt& a, const Pt& b){
    //     return ccwcomp(a, b);
    // });
    for (int i = 1; i < sz; i++) {
        if (lexComp(points[i], points[pos])) pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    sz--;
    seq.resize(sz);
    for (int i = 0; i < sz; i++) seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

vector<Pt> points;

bool pointInConvexPolygon(Pt point) {
    if (!prepCalled) prepare(points);
    point = point - translation;
    // because of the translation, p0 is essentially (0, 0) now
    // so no need to subtract it from every point then

    // sz means n though, or vice versa
    // replaced n with sz
    // first check if p lies in between p1 and pn
    if (seq[0].cross(point) != 0  // (p1 - p0) x (p - p0) = 0 means p is on the
                                  // line connecting p0 and p1
        &&
        sgn(seq[0].cross(point)) !=
            sgn(seq[0].cross(seq[sz - 1])))  // if (p1 - p0) x (p - p0) and (p1
                                             // - p0) x (pn - p0) have same sign
        return false;
    if (seq[sz - 1].cross(point) != 0  // (pn - p0) x (p - p0) = 0 means p is on
                                       // the line connecting p0 and pn
        &&
        sgn(seq[sz - 1].cross(point)) !=
            sgn(seq[sz - 1].cross(seq[0])))  // if (pn - p0) x (p - p0) and (pn
                                             // - p0) x (p1 - p0) have same sign
        return false;

    if (seq[0].cross(point) ==
        0)  // if p is on the line connecting p0 and p1, then pp0 should have
            // less or equal length than p1p0
        return seq[0].sqrLen() >= point.sqrLen();

    // we want to binary search the last point from p1,...,pn which is not
    // counter-clockwise from p with respect to p0 remember p1,...,pn are
    // seq[0],...,seq[n - 1] translated wrt p0 now

    int l = 0, r = sz - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        // this means points[mid + 1] or seq[mid] (translated wrt p0) is to the
        // right or in a clockwise position wrt point we want to find the last
        // such point
        int pos = mid;
        if (seq[pos].cross(point) >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], Pt(0, 0), point);
}