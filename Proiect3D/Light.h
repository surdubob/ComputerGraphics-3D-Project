#pragma once

#include<gl/freeglut.h>

struct float2
{
    float2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    float x;
    float y;
};

struct float3
{
    float3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}

    float x;
    float y;
    float z;
};
struct float4
{
    float4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _a = 0.0f) : x(_x), y(_y), z(_z), a(_a) {}

    float x;
    float y;
    float z;
    float a;
};

struct color4
{
    color4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _a = 0.0f) : r(_x), g(_y), b(_z), a(_a) {}

    float r;
    float g;
    float b;
    float a;
};

struct Light
{

    Light(GLenum lightID = GL_LIGHT0
        , color4 ambient = color4(0.0, 0.0, 0.0, 1.0)
        , color4 diffuse = color4(1.0, 1.0, 1.0, 1.0)
        , color4 specular = color4(1.0, 1.0, 1.0, 1.0)
        , float4 position = float4(0.0, 0.0, 1.0, 0.0)
        , float3 spotDirection = float3(1.0, 0.0, 0.0)
        , float  spotExponent = 0.0
        , float  spotCutoff = 180.0f
        , float  constantAttenuation = 0.5
        , float  linearAttenuation = 0.0
        , float  quadraticAttenuation = 0.0)


        : m_LightID(lightID)
        , m_Ambient(ambient)
        , m_Diffuse(diffuse)
        , m_Specular(specular)
        , m_Position(position)
        , m_SpotDirection(spotDirection)
		, m_SpotExponent(spotExponent)
        , m_SpotCutoff(spotCutoff)
        , m_ConstantAttenuation(constantAttenuation)
        , m_LinearAttenuation(linearAttenuation)
        , m_QuadraticAttenuation(quadraticAttenuation)
    {}


    void Activate()
    {
    	glEnable(m_LightID);
        glLightfv(m_LightID, GL_AMBIENT, &(m_Ambient.r));
        glLightfv(m_LightID, GL_DIFFUSE, &(m_Diffuse.r));
        glLightfv(m_LightID, GL_SPECULAR, &(m_Specular.r));
        glLightfv(m_LightID, GL_POSITION, &(m_Position.x));
        glLightfv(m_LightID, GL_SPOT_DIRECTION, &(m_SpotDirection.x));
        glLightf(m_LightID, GL_SPOT_EXPONENT, m_SpotExponent);
        glLightf(m_LightID, GL_SPOT_CUTOFF, m_SpotCutoff);
        glLightf(m_LightID, GL_CONSTANT_ATTENUATION, m_ConstantAttenuation);
        glLightf(m_LightID, GL_LINEAR_ATTENUATION, m_LinearAttenuation);
        glLightf(m_LightID, GL_QUADRATIC_ATTENUATION, m_QuadraticAttenuation);
    }


    void Deactivate()
    {
        glDisable(m_LightID);
    }

    GLenum m_LightID;
    color4 m_Ambient;
    color4 m_Diffuse;
    color4 m_Specular;
    float4 m_Position;
    float3 m_SpotDirection;
    float  m_SpotExponent;
    float  m_SpotCutoff;
    float  m_ConstantAttenuation;
    float  m_LinearAttenuation;
    float  m_QuadraticAttenuation;

};

struct Material
{
    Material(color4 ambient = color4(0.2, 0.2, 0.2, 1.0)
        , color4 diffuse = color4(0.8, 0.8, 0.8, 1.0)
        , color4 specular = color4(0.0, 0.0, 0.0, 1.0)
        , color4 emission = color4(0.0, 0.0, 0.0, 1.0)
        , float shininess = 0)
        : m_Ambient(ambient)
        , m_Diffuse(diffuse)
        , m_Specular(specular)
        , m_Emission(emission)
        , m_Shininess(shininess)
    {}

    void Apply()
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_Ambient.r));
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_Diffuse.r));
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_Specular.r));
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &(m_Emission.r));
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess);
    }

    color4 m_Ambient;
    color4 m_Diffuse;
    color4 m_Specular;
    color4 m_Emission;
    float  m_Shininess;
};

Material g_SunMaterial(color4(0, 0, 0, 1), color4(1, 1, 1, 1), color4(1, 1, 1, 1));
Material g_EarthMaterial(color4(0.2, 0.2, 0.2, 1.0), color4(1, 1, 1, 1), color4(1, 1, 1, 1), color4(0, 0, 0, 1), 50);
Material g_MoonMaterial(color4(0.1, 0.1, 0.1, 1.0), color4(1, 1, 1, 1), color4(0.2, 0.2, 0.2, 1), color4(0, 0, 0, 1), 10);