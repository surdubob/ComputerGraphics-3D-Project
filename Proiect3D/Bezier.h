#pragma once

class vec3
{
public:

	// Constructors
	vec3() : x(0), y(0), z(0)
	{}

	vec3(float vx, float vy, float vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}

	vec3(const vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	// Destructor
	~vec3() {}

	// A minimal set of vector operations
	vec3 operator * (float mult) const // result = this * arg
	{
		return vec3(x * mult, y * mult, z * mult);
	}

	vec3 operator + (const vec3& v) const // result = this + arg
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 operator - (const vec3& v) const // result = this - arg
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	float x, y, z;
};

class CRSpline
{
public:

    // Constructors and destructor
    CRSpline();
    CRSpline(const CRSpline&);
    ~CRSpline();

    // Operations
    void AddSplinePoint(const vec3& v);
    vec3 GetInterpolatedSplinePoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
    int GetNumPoints();
    vec3& GetNthPoint(int n);

    // Static method for computing the Catmull-Rom parametric equation
    // given a time (t) and a vector quadruple (p1,p2,p3,p4).
    static vec3 Eq(float t, const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4);

private:
    std::vector<vec3> vp;
    float delta_t;
};

CRSpline::CRSpline()
    : vp(), delta_t(0)
{
}

CRSpline::CRSpline(const CRSpline& s)
{
    for (int i = 0; i < (int)s.vp.size(); i++)
        vp.push_back(s.vp[i]);
    delta_t = s.delta_t;
}

CRSpline::~CRSpline()
{}

// Solve the Catmull-Rom parametric equation for a given time(t) and vector quadruple (p1,p2,p3,p4)
vec3 CRSpline::Eq(float t, const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4)
{
    float t2 = t * t;
    float t3 = t2 * t;

    float b1 = .5 * (-t3 + 2 * t2 - t);
    float b2 = .5 * (3 * t3 - 5 * t2 + 2);
    float b3 = .5 * (-3 * t3 + 4 * t2 + t);
    float b4 = .5 * (t3 - t2);

    return (p1 * b1 + p2 * b2 + p3 * b3 + p4 * b4);
}

void CRSpline::AddSplinePoint(const vec3& v)
{
    vp.push_back(v);
    delta_t = (float)1 / (float)vp.size();
}

vec3 CRSpline::GetInterpolatedSplinePoint(float t)
{
    // Find out in which interval we are on the spline
    int p = (int)(t / delta_t);
    // Compute local control point indices
#define BOUNDS(pp) { if (pp < 0) pp = 0; else if (pp >= (int)vp.size()-1) pp = vp.size() - 1; }
    int p0 = p - 1;     BOUNDS(p0);
    int p1 = p;         BOUNDS(p1);
    int p2 = p + 1;     BOUNDS(p2);
    int p3 = p + 2;     BOUNDS(p3);
    // Relative (local) time 
    float lt = (t - delta_t * (float)p) / delta_t;
    // Interpolate
    return CRSpline::Eq(lt, vp[p0], vp[p1], vp[p2], vp[p3]);
}

int CRSpline::GetNumPoints()
{
    return vp.size();
}

vec3& CRSpline::GetNthPoint(int n)
{
    return vp[n];
}