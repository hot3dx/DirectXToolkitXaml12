//-------------------------------------------------------------------------------------
// SimpleMath.inl -- Simplified C++ Math wrapper for DirectXMath
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//-------------------------------------------------------------------------------------

#pragma once

//#include "SimpleMathXaml12.h"
#include <\DirectXToolKitXaml12\Graphics\SimpleMathXaml12.h>
#include <windef.h>

using namespace DirectX;
using namespace DirectX::DXTKXAML12;


/****************************************************************************
*
* Rectangle
*
****************************************************************************/

//------------------------------------------------------------------------------
// Rectangle operations
//------------------------------------------------------------------------------
inline DirectX::DXTKXAML12::SimpleMath::Vector2 DirectX::DXTKXAML12::SimpleMath::Rectangle::Location() const
{
    return DirectX::DXTKXAML12::SimpleMath::Vector2(float(x), float(y));
}

inline DirectX::DXTKXAML12::SimpleMath::Vector2 DirectX::DXTKXAML12::SimpleMath::Rectangle::Center() const
{
    return DirectX::DXTKXAML12::SimpleMath::Vector2(float(x) + float(width / 2.f), float(y) + float(height / 2.f));
}

inline bool DirectX::DXTKXAML12::SimpleMath::Rectangle::Contains(const SimpleMath::Vector2& point) const
{
    return (float(x) <= point.x) && (point.x < float(x + width)) && (float(y) <= point.y) && (point.y < float(y + height));
}

inline void DirectX::DXTKXAML12::SimpleMath::Rectangle::Inflate(long horizAmount, long vertAmount)
{
    x -= horizAmount;
    y -= vertAmount;
    width += horizAmount;
    height += vertAmount;
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline DirectX::DXTKXAML12::SimpleMath::Rectangle DirectX::DXTKXAML12::SimpleMath::Rectangle::Intersect(const DirectX::DXTKXAML12::SimpleMath::Rectangle& ra, const DirectX::DXTKXAML12::SimpleMath::Rectangle& rb)
{
    long righta = ra.x + ra.width;
    long rightb = rb.x + rb.width;

    long bottoma = ra.y + ra.height;
    long bottomb = rb.y + rb.height;

    long maxX = ra.x > rb.x ? ra.x : rb.x;
    long maxY = ra.y > rb.y ? ra.y : rb.y;

    long minRight = righta < rightb ? righta : rightb;
    long minBottom = bottoma < bottomb ? bottoma : bottomb;

    Rectangle result;

    if ((minRight > maxX) && (minBottom > maxY))
    {
        result.x = maxX;
        result.y = maxY;
        result.width = minRight - maxX;
        result.height = minBottom - maxY;
    }
    else
    {
        result.x = 0;
        result.y = 0;
        result.width = 0;
        result.height = 0;
    }

    return result;
}

inline RECT SimpleMath::Rectangle::Intersect(const RECT& rcta, const RECT& rctb)
{
    long maxX = rcta.left > rctb.left ? rcta.left : rctb.left;
    long maxY = rcta.top > rctb.top ? rcta.top : rctb.top;

    long minRight = rcta.right < rctb.right ? rcta.right : rctb.right;
    long minBottom = rcta.bottom < rctb.bottom ? rcta.bottom : rctb.bottom;

    RECT result;

    if ((minRight > maxX) && (minBottom > maxY))
    {
        result.left = maxX;
        result.top = maxY;
        result.right = minRight;
        result.bottom = minBottom;
    }
    else
    {
        result.left = 0;
        result.top = 0;
        result.right = 0;
        result.bottom = 0;
    }

    return result;
}

inline DirectX::DXTKXAML12::SimpleMath::Rectangle SimpleMath::Rectangle::Union(const DirectX::DXTKXAML12::SimpleMath::Rectangle& ra, const DirectX::DXTKXAML12::SimpleMath::Rectangle& rb)
{
    long righta = ra.x + ra.width;
    long rightb = rb.x + rb.width;

    long bottoma = ra.y + ra.height;
    long bottomb = rb.y + rb.height;

    int minX = ra.x < rb.x ? ra.x : rb.x;
    int minY = ra.y < rb.y ? ra.y : rb.y;

    int maxRight = righta > rightb ? righta : rightb;
    int maxBottom = bottoma > bottomb ? bottoma : bottomb;

    DirectX::DXTKXAML12::SimpleMath::Rectangle result;
    result.x = minX;
    result.y = minY;
    result.width = maxRight - minX;
    result.height = maxBottom - minY;
    return result;
}

inline RECT DirectX::DXTKXAML12::SimpleMath::Rectangle::Union(const RECT& rcta, const RECT& rctb)
{
    RECT result;
    result.left = rcta.left < rctb.left ? rcta.left : rctb.left;
    result.top = rcta.top < rctb.top ? rcta.top : rctb.top;
    result.right = rcta.right > rctb.right ? rcta.right : rctb.right;
    result.bottom = rcta.bottom > rctb.bottom ? rcta.bottom : rctb.bottom;
    return result;
}


/****************************************************************************
 *
 * SimpleMath::Vector2
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector2::operator == (const SimpleMath::Vector2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    return XMVector2Equal(v1, v2);
}

inline bool SimpleMath::Vector2::operator != (const SimpleMath::Vector2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector2& SimpleMath::Vector2::operator+= (const SimpleMath::Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR X = XMVectorAdd(v1, v2);
    XMStoreFloat2(this, X);
    return *this;
}

inline SimpleMath::Vector2& SimpleMath::Vector2::operator-= (const SimpleMath::Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    XMStoreFloat2(this, X);
    return *this;
}

inline SimpleMath::Vector2& SimpleMath::Vector2::operator*= (const SimpleMath::Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    XMStoreFloat2(this, X);
    return *this;
}

inline SimpleMath::Vector2& SimpleMath::Vector2::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVectorScale(v1, S);
    XMStoreFloat2(this, X);
    return *this;
}

inline SimpleMath::Vector2& SimpleMath::Vector2::operator/= (float S)
{
    using namespace DirectX;
    assert(S != 0.0f);
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVectorScale(v1, 1.f / S);
    XMStoreFloat2(this, X);
    return *this;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector2 operator+ (const SimpleMath::Vector2& V1, const SimpleMath::Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V1);
    XMVECTOR v2 = XMLoadFloat2(&V2);
    XMVECTOR X = XMVectorAdd(v1, v2);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

inline SimpleMath::Vector2 operator- (const SimpleMath::Vector2& V1, const SimpleMath::Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V1);
    XMVECTOR v2 = XMLoadFloat2(&V2);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

inline SimpleMath::Vector2 operator* (const SimpleMath::Vector2& V1, const SimpleMath::Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V1);
    XMVECTOR v2 = XMLoadFloat2(&V2);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

inline SimpleMath::Vector2 operator* (const SimpleMath::Vector2& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

inline SimpleMath::Vector2 operator/ (const SimpleMath::Vector2& V1, const SimpleMath::Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V1);
    XMVECTOR v2 = XMLoadFloat2(&V2);
    XMVECTOR X = XMVectorDivide(v1, v2);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

inline SimpleMath::Vector2 operator* (float S, const SimpleMath::Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector2 R;
    XMStoreFloat2(&R, X);
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector2::InBounds(const SimpleMath::Vector2& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&Bounds);
    return XMVector2InBounds(v1, v2);
}

inline float SimpleMath::Vector2::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVector2Length(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector2::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVector2LengthSq(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector2::Dot(const SimpleMath::Vector2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR X = XMVector2Dot(v1, v2);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector2::Cross(const SimpleMath::Vector2& V, SimpleMath::Vector2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR R = XMVector2Cross(v1, v2);
    XMStoreFloat2(&result, R);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Cross(const SimpleMath::Vector2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&V);
    XMVECTOR R = XMVector2Cross(v1, v2);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, R);
    return result;
}

inline void SimpleMath::Vector2::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVector2Normalize(v1);
    XMStoreFloat2(this, X);
}

inline void SimpleMath::Vector2::Normalize(Vector2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR X = XMVector2Normalize(v1);
    XMStoreFloat2(&result, X);
}

inline void SimpleMath::Vector2::Clamp(const SimpleMath::Vector2& vmin, const SimpleMath::Vector2& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&vmin);
    XMVECTOR v3 = XMLoadFloat2(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    XMStoreFloat2(this, X);
}

inline void SimpleMath::Vector2::Clamp(const SimpleMath::Vector2& vmin, const SimpleMath::Vector2& vmax, SimpleMath::Vector2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(this);
    XMVECTOR v2 = XMLoadFloat2(&vmin);
    XMVECTOR v3 = XMLoadFloat2(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    XMStoreFloat2(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float SimpleMath::Vector2::Distance(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector2Length(V);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector2::DistanceSquared(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector2LengthSq(V);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector2::Min(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Min(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Max(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Max(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Lerp(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, float t, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Lerp(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::SmoothStep(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, float t, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::SmoothStep(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Barycentric(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& v3, float f, float g, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR x3 = XMLoadFloat2(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Barycentric(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR x3 = XMLoadFloat2(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::CatmullRom(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& v3, const SimpleMath::Vector2& v4, float t, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR x3 = XMLoadFloat2(&v3);
    XMVECTOR x4 = XMLoadFloat2(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::CatmullRom(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& v3, const SimpleMath::Vector2& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&v2);
    XMVECTOR x3 = XMLoadFloat2(&v3);
    XMVECTOR x4 = XMLoadFloat2(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Hermite(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& t1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& t2, float t, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&t1);
    XMVECTOR x3 = XMLoadFloat2(&v2);
    XMVECTOR x4 = XMLoadFloat2(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Hermite(const SimpleMath::Vector2& v1, const SimpleMath::Vector2& t1, const SimpleMath::Vector2& v2, const SimpleMath::Vector2& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2(&v1);
    XMVECTOR x2 = XMLoadFloat2(&t1);
    XMVECTOR x3 = XMLoadFloat2(&v2);
    XMVECTOR x4 = XMLoadFloat2(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Reflect(const SimpleMath::Vector2& ivec, const SimpleMath::Vector2& nvec, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2(&ivec);
    XMVECTOR n = XMLoadFloat2(&nvec);
    XMVECTOR X = XMVector2Reflect(i, n);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Reflect(const SimpleMath::Vector2& ivec, const SimpleMath::Vector2& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2(&ivec);
    XMVECTOR n = XMLoadFloat2(&nvec);
    XMVECTOR X = XMVector2Reflect(i, n);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Refract(const SimpleMath::Vector2& ivec, const SimpleMath::Vector2& nvec, float refractionIndex, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2(&ivec);
    XMVECTOR n = XMLoadFloat2(&nvec);
    XMVECTOR X = XMVector2Refract(i, n, refractionIndex);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Refract(const SimpleMath::Vector2& ivec, const SimpleMath::Vector2& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2(&ivec);
    XMVECTOR n = XMLoadFloat2(&nvec);
    XMVECTOR X = XMVector2Refract(i, n, refractionIndex);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Transform(const SimpleMath::Vector2& v, const SimpleMath::Quaternion& quat, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Transform(const SimpleMath::Vector2& v, const SimpleMath::Quaternion& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

inline void SimpleMath::Vector2::Transform(const SimpleMath::Vector2& v, const SimpleMath::Matrix& m, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector2TransformCoord(v1, M);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::Transform(const SimpleMath::Vector2& v, const SimpleMath::Matrix& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector2TransformCoord(v1, M);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

_Use_decl_annotations_
inline void SimpleMath::Vector2::Transform(const SimpleMath::Vector2* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector2TransformCoordStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
}

inline void SimpleMath::Vector2::Transform(const SimpleMath::Vector2& v, const SimpleMath::Matrix& m, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector2Transform(v1, M);
    DirectX::XMStoreFloat4(&result, X);
}

_Use_decl_annotations_
inline void SimpleMath::Vector2::Transform(const SimpleMath::Vector2* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector2TransformStream(resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M);
}

inline void SimpleMath::Vector2::TransformNormal(const SimpleMath::Vector2& v, const SimpleMath::Matrix& m, SimpleMath::Vector2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector2TransformNormal(v1, M);
    XMStoreFloat2(&result, X);
}

inline SimpleMath::Vector2 SimpleMath::Vector2::TransformNormal(const SimpleMath::Vector2& v, const SimpleMath::Matrix& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector2TransformNormal(v1, M);

    SimpleMath::Vector2 result;
    XMStoreFloat2(&result, X);
    return result;
}

_Use_decl_annotations_
inline void SimpleMath::Vector2::TransformNormal(const SimpleMath::Vector2* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector2TransformNormalStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
}


/****************************************************************************
 *
 * SimpleMath::Vector3
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector3::operator == (const SimpleMath::Vector3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    return XMVector3Equal(v1, v2);
}

inline bool SimpleMath::Vector3::operator != (const SimpleMath::Vector3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    return XMVector3NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector3& SimpleMath::Vector3::operator+= (const SimpleMath::Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR X = XMVectorAdd(v1, v2);
    XMStoreFloat3(this, X);
    return *this;
}

inline SimpleMath::Vector3& SimpleMath::Vector3::operator-= (const SimpleMath::Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    XMStoreFloat3(this, X);
    return *this;
}

inline SimpleMath::Vector3& SimpleMath::Vector3::operator*= (const SimpleMath::Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    XMStoreFloat3(this, X);
    return *this;
}

inline SimpleMath::Vector3& SimpleMath::Vector3::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVectorScale(v1, S);
    XMStoreFloat3(this, X);
    return *this;
}

inline SimpleMath::Vector3& SimpleMath::Vector3::operator/= (float S)
{
    using namespace DirectX;
    assert(S != 0.0f);
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVectorScale(v1, 1.f / S);
    XMStoreFloat3(this, X);
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector3 SimpleMath::Vector3::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVectorNegate(v1);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector3 operator+ (const SimpleMath::Vector3& V1, const SimpleMath::Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V1);
    XMVECTOR v2 = XMLoadFloat3(&V2);
    XMVECTOR X = XMVectorAdd(v1, v2);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

inline SimpleMath::Vector3 operator- (const SimpleMath::Vector3& V1, const SimpleMath::Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V1);
    XMVECTOR v2 = XMLoadFloat3(&V2);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

inline SimpleMath::Vector3 operator* (const SimpleMath::Vector3& V1, const SimpleMath::Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V1);
    XMVECTOR v2 = XMLoadFloat3(&V2);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

inline SimpleMath::Vector3 operator* (const SimpleMath::Vector3& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

inline SimpleMath::Vector3 operator/ (const SimpleMath::Vector3& V1, const SimpleMath::Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V1);
    XMVECTOR v2 = XMLoadFloat3(&V2);
    XMVECTOR X = XMVectorDivide(v1, v2);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

inline SimpleMath::Vector3 operator* (float S, const SimpleMath::Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector3 R;
    XMStoreFloat3(&R, X);
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector3::InBounds(const SimpleMath::Vector3& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&Bounds);
    return XMVector3InBounds(v1, v2);
}

inline float SimpleMath::Vector3::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVector3Length(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector3::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVector3LengthSq(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector3::Dot(const SimpleMath::Vector3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR X = XMVector3Dot(v1, v2);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector3::Cross(const SimpleMath::Vector3& V, SimpleMath::Vector3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR R = XMVector3Cross(v1, v2);
    XMStoreFloat3(&result, R);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Cross(const SimpleMath::Vector3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&V);
    XMVECTOR R = XMVector3Cross(v1, v2);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, R);
    return result;
}

inline void SimpleMath::Vector3::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVector3Normalize(v1);
    XMStoreFloat3(this, X);
}

inline void SimpleMath::Vector3::Normalize(Vector3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR X = XMVector3Normalize(v1);
    XMStoreFloat3(&result, X);
}

inline void SimpleMath::Vector3::Clamp(const SimpleMath::Vector3& vmin, const SimpleMath::Vector3& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&vmin);
    XMVECTOR v3 = XMLoadFloat3(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    XMStoreFloat3(this, X);
}

inline void SimpleMath::Vector3::Clamp(const SimpleMath::Vector3& vmin, const SimpleMath::Vector3& vmax, SimpleMath::Vector3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(this);
    XMVECTOR v2 = XMLoadFloat3(&vmin);
    XMVECTOR v3 = XMLoadFloat3(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    XMStoreFloat3(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float SimpleMath::Vector3::Distance(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector3Length(V);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector3::DistanceSquared(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector3LengthSq(V);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector3::Min(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Min(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Max(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Max(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Lerp(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, float t, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Lerp(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::SmoothStep(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, float t, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::SmoothStep(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Barycentric(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& v3, float f, float g, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR x3 = XMLoadFloat3(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Barycentric(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR x3 = XMLoadFloat3(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::CatmullRom(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& v3, const SimpleMath::Vector3& v4, float t, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR x3 = XMLoadFloat3(&v3);
    XMVECTOR x4 = XMLoadFloat3(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::CatmullRom(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& v3, const SimpleMath::Vector3& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&v2);
    XMVECTOR x3 = XMLoadFloat3(&v3);
    XMVECTOR x4 = XMLoadFloat3(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Hermite(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& t1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& t2, float t, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&t1);
    XMVECTOR x3 = XMLoadFloat3(&v2);
    XMVECTOR x4 = XMLoadFloat3(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Hermite(const SimpleMath::Vector3& v1, const SimpleMath::Vector3& t1, const SimpleMath::Vector3& v2, const SimpleMath::Vector3& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3(&v1);
    XMVECTOR x2 = XMLoadFloat3(&t1);
    XMVECTOR x3 = XMLoadFloat3(&v2);
    XMVECTOR x4 = XMLoadFloat3(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Reflect(const SimpleMath::Vector3& ivec, const SimpleMath::Vector3& nvec, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3(&ivec);
    XMVECTOR n = XMLoadFloat3(&nvec);
    XMVECTOR X = XMVector3Reflect(i, n);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Reflect(const SimpleMath::Vector3& ivec, const SimpleMath::Vector3& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3(&ivec);
    XMVECTOR n = XMLoadFloat3(&nvec);
    XMVECTOR X = XMVector3Reflect(i, n);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Refract(const SimpleMath::Vector3& ivec, const SimpleMath::Vector3& nvec, float refractionIndex, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3(&ivec);
    XMVECTOR n = XMLoadFloat3(&nvec);
    XMVECTOR X = XMVector3Refract(i, n, refractionIndex);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Refract(const SimpleMath::Vector3& ivec, const SimpleMath::Vector3& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3(&ivec);
    XMVECTOR n = XMLoadFloat3(&nvec);
    XMVECTOR X = XMVector3Refract(i, n, refractionIndex);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Transform(const SimpleMath::Vector3& v, const SimpleMath::Quaternion& quat, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Transform(const SimpleMath::Vector3& v, const SimpleMath::Quaternion& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

inline void SimpleMath::Vector3::Transform(const SimpleMath::Vector3& v, const SimpleMath::Matrix& m, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector3TransformCoord(v1, M);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::Transform(const SimpleMath::Vector3& v, const SimpleMath::Matrix& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector3TransformCoord(v1, M);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

_Use_decl_annotations_
inline void SimpleMath::Vector3::Transform(const SimpleMath::Vector3* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector3TransformCoordStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
}

inline void SimpleMath::Vector3::Transform(const SimpleMath::Vector3& v, const SimpleMath::Matrix& m, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector3Transform(v1, M);
    DirectX::XMStoreFloat4(&result, X);
}

_Use_decl_annotations_
inline void SimpleMath::Vector3::Transform(const SimpleMath::Vector3* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector3TransformStream(resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M);
}

inline void SimpleMath::Vector3::TransformNormal(const SimpleMath::Vector3& v, const SimpleMath::Matrix& m, SimpleMath::Vector3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector3TransformNormal(v1, M);
    XMStoreFloat3(&result, X);
}

inline SimpleMath::Vector3 SimpleMath::Vector3::TransformNormal(const SimpleMath::Vector3& v, const SimpleMath::Matrix& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector3TransformNormal(v1, M);

    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, X);
    return result;
}

_Use_decl_annotations_
inline void SimpleMath::Vector3::TransformNormal(const SimpleMath::Vector3* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector3TransformNormalStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
}


/****************************************************************************
 *
 * SimpleMath::Vector4
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector4::operator == (const SimpleMath::Vector4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    return XMVector4Equal(v1, v2);
}

inline bool SimpleMath::Vector4::operator != (const SimpleMath::Vector4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    return XMVector4NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector4& SimpleMath::Vector4::operator+= (const SimpleMath::Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    XMVECTOR X = XMVectorAdd(v1, v2);
    DirectX::XMStoreFloat4(this, X);
    return *this;
}

inline SimpleMath::Vector4& SimpleMath::Vector4::operator-= (const SimpleMath::Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    DirectX::XMStoreFloat4(this, X);
    return *this;
}

inline SimpleMath::Vector4& SimpleMath::Vector4::operator*= (const SimpleMath::Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    DirectX::XMStoreFloat4(this, X);
    return *this;
}

inline SimpleMath::Vector4& SimpleMath::Vector4::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVectorScale(v1, S);
    DirectX::XMStoreFloat4(this, X);
    return *this;
}

inline SimpleMath::Vector4& SimpleMath::Vector4::operator/= (float S)
{
    using namespace DirectX;
    assert(S != 0.0f);
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVectorScale(v1, 1.f / S);
    DirectX::XMStoreFloat4(this, X);
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector4 SimpleMath::Vector4::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVectorNegate(v1);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Vector4 operator+ (const SimpleMath::Vector4& V1, const SimpleMath::Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V1);
    XMVECTOR v2 = XMLoadFloat4(&V2);
    XMVECTOR X = XMVectorAdd(v1, v2);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

inline SimpleMath::Vector4 operator- (const SimpleMath::Vector4& V1, const SimpleMath::Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V1);
    XMVECTOR v2 = XMLoadFloat4(&V2);
    XMVECTOR X = XMVectorSubtract(v1, v2);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

inline SimpleMath::Vector4 operator* (const SimpleMath::Vector4& V1, const SimpleMath::Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V1);
    XMVECTOR v2 = XMLoadFloat4(&V2);
    XMVECTOR X = XMVectorMultiply(v1, v2);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

inline SimpleMath::Vector4 operator* (const SimpleMath::Vector4& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

inline SimpleMath::Vector4 operator/ (const SimpleMath::Vector4& V1, const SimpleMath::Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V1);
    XMVECTOR v2 = XMLoadFloat4(&V2);
    XMVECTOR X = XMVectorDivide(v1, v2);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

inline SimpleMath::Vector4 operator* (float S, const SimpleMath::Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&V);
    XMVECTOR X = XMVectorScale(v1, S);
    SimpleMath::Vector4 R;
    DirectX::XMStoreFloat4(&R, X);
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool SimpleMath::Vector4::InBounds(const SimpleMath::Vector4& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&Bounds);
    return XMVector4InBounds(v1, v2);
}

inline float SimpleMath::Vector4::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVector4Length(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector4::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVector4LengthSq(v1);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector4::Dot(const SimpleMath::Vector4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&V);
    XMVECTOR X = XMVector4Dot(v1, v2);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector4::Cross(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, SimpleMath::Vector4& result) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(this);
    XMVECTOR x2 = XMLoadFloat4(&v1);
    XMVECTOR x3 = XMLoadFloat4(&v2);
    XMVECTOR R = XMVector4Cross(x1, x2, x3);
    DirectX::XMStoreFloat4(&result, R);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Cross(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(this);
    XMVECTOR x2 = XMLoadFloat4(&v1);
    XMVECTOR x3 = XMLoadFloat4(&v2);
    XMVECTOR R = XMVector4Cross(x1, x2, x3);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, R);
    return result;
}

inline void SimpleMath::Vector4::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVector4Normalize(v1);
    DirectX::XMStoreFloat4(this, X);
}

inline void SimpleMath::Vector4::Normalize(Vector4& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR X = XMVector4Normalize(v1);
    DirectX::XMStoreFloat4(&result, X);
}

inline void SimpleMath::Vector4::Clamp(const SimpleMath::Vector4& vmin, const SimpleMath::Vector4& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&vmin);
    XMVECTOR v3 = XMLoadFloat4(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    DirectX::XMStoreFloat4(this, X);
}

inline void SimpleMath::Vector4::Clamp(const SimpleMath::Vector4& vmin, const SimpleMath::Vector4& vmax, SimpleMath::Vector4& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(this);
    XMVECTOR v2 = XMLoadFloat4(&vmin);
    XMVECTOR v3 = XMLoadFloat4(&vmax);
    XMVECTOR X = XMVectorClamp(v1, v2, v3);
    DirectX::XMStoreFloat4(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float SimpleMath::Vector4::Distance(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector4Length(V);
    return XMVectorGetX(X);
}

inline float SimpleMath::Vector4::DistanceSquared(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR V = XMVectorSubtract(x2, x1);
    XMVECTOR X = XMVector4LengthSq(V);
    return XMVectorGetX(X);
}

inline void SimpleMath::Vector4::Min(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Min(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorMin(x1, x2);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Max(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Max(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorMax(x1, x2);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Lerp(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, float t, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Lerp(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::SmoothStep(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, float t, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::SmoothStep(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t * t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR X = XMVectorLerp(x1, x2, t);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Barycentric(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& v3, float f, float g, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR x3 = XMLoadFloat4(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Barycentric(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR x3 = XMLoadFloat4(&v3);
    XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::CatmullRom(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& v3, const SimpleMath::Vector4& v4, float t, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR x3 = XMLoadFloat4(&v3);
    XMVECTOR x4 = XMLoadFloat4(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::CatmullRom(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& v3, const SimpleMath::Vector4& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&v2);
    XMVECTOR x3 = XMLoadFloat4(&v3);
    XMVECTOR x4 = XMLoadFloat4(&v4);
    XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Hermite(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& t1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& t2, float t, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&t1);
    XMVECTOR x3 = XMLoadFloat4(&v2);
    XMVECTOR x4 = XMLoadFloat4(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Hermite(const SimpleMath::Vector4& v1, const SimpleMath::Vector4& t1, const SimpleMath::Vector4& v2, const SimpleMath::Vector4& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(&v1);
    XMVECTOR x2 = XMLoadFloat4(&t1);
    XMVECTOR x3 = XMLoadFloat4(&v2);
    XMVECTOR x4 = XMLoadFloat4(&t2);
    XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Reflect(const SimpleMath::Vector4& ivec, const SimpleMath::Vector4& nvec, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4(&ivec);
    XMVECTOR n = XMLoadFloat4(&nvec);
    XMVECTOR X = XMVector4Reflect(i, n);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Reflect(const SimpleMath::Vector4& ivec, const SimpleMath::Vector4& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4(&ivec);
    XMVECTOR n = XMLoadFloat4(&nvec);
    XMVECTOR X = XMVector4Reflect(i, n);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Refract(const SimpleMath::Vector4& ivec, const SimpleMath::Vector4& nvec, float refractionIndex, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4(&ivec);
    XMVECTOR n = XMLoadFloat4(&nvec);
    XMVECTOR X = XMVector4Refract(i, n, refractionIndex);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Refract(const SimpleMath::Vector4& ivec, const SimpleMath::Vector4& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4(&ivec);
    XMVECTOR n = XMLoadFloat4(&nvec);
    XMVECTOR X = XMVector4Refract(i, n, refractionIndex);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Transform(const SimpleMath::Vector2& v, const SimpleMath::Quaternion& quat, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Transform(const SimpleMath::Vector2& v, const SimpleMath::Quaternion& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Transform(const SimpleMath::Vector3& v, const SimpleMath::Quaternion& quat, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Transform(const SimpleMath::Vector3& v, const SimpleMath::Quaternion& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Transform(const SimpleMath::Vector4& v, const SimpleMath::Quaternion& quat, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Transform(const SimpleMath::Vector4& v, const SimpleMath::Quaternion& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&v);
    XMVECTOR q = XMLoadFloat4(&quat);
    XMVECTOR X = XMVector3Rotate(v1, q);
    X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

inline void SimpleMath::Vector4::Transform(const SimpleMath::Vector4& v, const SimpleMath::Matrix& m, SimpleMath::Vector4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector4Transform(v1, M);
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Vector4 SimpleMath::Vector4::Transform(const SimpleMath::Vector4& v, const SimpleMath::Matrix& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(&v);
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVECTOR X = XMVector4Transform(v1, M);

    SimpleMath::Vector4 result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}

_Use_decl_annotations_
inline void SimpleMath::Vector4::Transform(const SimpleMath::Vector4* varray, size_t count, const SimpleMath::Matrix& m, SimpleMath::Vector4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(&m);
    XMVector4TransformStream(resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M);
}


/****************************************************************************
 *
 * SimpleMath::Matrix
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Matrix::operator == (const SimpleMath::Matrix& M) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    return (XMVector4Equal(x1, y1)
            && XMVector4Equal(x2, y2)
            && XMVector4Equal(x3, y3)
            && XMVector4Equal(x4, y4)) != 0;
}

inline bool SimpleMath::Matrix::operator != (const SimpleMath::Matrix& M) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    return (XMVector4NotEqual(x1, y1)
            || XMVector4NotEqual(x2, y2)
            || XMVector4NotEqual(x3, y3)
            || XMVector4NotEqual(x4, y4)) != 0;
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Matrix::Matrix(const XMFLOAT3X3& M)
{
    _11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
    _21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
    _31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
    _41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
}

inline SimpleMath::Matrix::Matrix(const XMFLOAT4X3& M)
{
    _11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
    _21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
    _31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
    _41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator= (const XMFLOAT3X3& M)
{
    _11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
    _21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
    _31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
    _41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator= (const XMFLOAT4X3& M)
{
    _11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
    _21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
    _31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
    _41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator+= (const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    x1 = XMVectorAdd(x1, y1);
    x2 = XMVectorAdd(x2, y2);
    x3 = XMVectorAdd(x3, y3);
    x4 = XMVectorAdd(x4, y4);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator-= (const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    x1 = XMVectorSubtract(x1, y1);
    x2 = XMVectorSubtract(x2, y2);
    x3 = XMVectorSubtract(x3, y3);
    x4 = XMVectorSubtract(x4, y4);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator*= (const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMMATRIX M1 = XMLoadFloat4x4(this);
    XMMATRIX M2 = XMLoadFloat4x4(&M);
    XMMATRIX X = XMMatrixMultiply(M1, M2);
    DirectX::XMStoreFloat4x4(this, X);
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    x1 = XMVectorScale(x1, S);
    x2 = XMVectorScale(x2, S);
    x3 = XMVectorScale(x3, S);
    x4 = XMVectorScale(x4, S);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator/= (float S)
{
    using namespace DirectX;
    assert(S != 0.f);
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    float rs = 1.f / S;

    x1 = XMVectorScale(x1, rs);
    x2 = XMVectorScale(x2, rs);
    x3 = XMVectorScale(x3, rs);
    x4 = XMVectorScale(x4, rs);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
    return *this;
}

inline SimpleMath::Matrix& SimpleMath::Matrix::operator/= (const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    x1 = XMVectorDivide(x1, y1);
    x2 = XMVectorDivide(x2, y2);
    x3 = XMVectorDivide(x3, y3);
    x4 = XMVectorDivide(x4, y4);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline SimpleMath::Matrix SimpleMath::Matrix::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
    XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
    XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
    XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

    v1 = XMVectorNegate(v1);
    v2 = XMVectorNegate(v2);
    v3 = XMVectorNegate(v3);
    v4 = XMVectorNegate(v4);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Matrix operator+ (const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

    x1 = XMVectorAdd(x1, y1);
    x2 = XMVectorAdd(x2, y2);
    x3 = XMVectorAdd(x3, y3);
    x4 = XMVectorAdd(x4, y4);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

inline SimpleMath::Matrix operator- (const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

    x1 = XMVectorSubtract(x1, y1);
    x2 = XMVectorSubtract(x2, y2);
    x3 = XMVectorSubtract(x3, y3);
    x4 = XMVectorSubtract(x4, y4);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

inline SimpleMath::Matrix operator* (const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2)
{
    using namespace DirectX;
    XMMATRIX m1 = XMLoadFloat4x4(&M1);
    XMMATRIX m2 = XMLoadFloat4x4(&M2);
    XMMATRIX X = XMMatrixMultiply(m1, m2);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, X);
    return R;
}

inline SimpleMath::Matrix operator* (const SimpleMath::Matrix& M, float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    x1 = XMVectorScale(x1, S);
    x2 = XMVectorScale(x2, S);
    x3 = XMVectorScale(x3, S);
    x4 = XMVectorScale(x4, S);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

inline SimpleMath::Matrix operator/ (const SimpleMath::Matrix& M, float S)
{
    using namespace DirectX;
    assert(S != 0.f);

    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    float rs = 1.f / S;

    x1 = XMVectorScale(x1, rs);
    x2 = XMVectorScale(x2, rs);
    x3 = XMVectorScale(x3, rs);
    x4 = XMVectorScale(x4, rs);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

inline SimpleMath::Matrix operator/ (const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

    x1 = XMVectorDivide(x1, y1);
    x2 = XMVectorDivide(x2, y2);
    x3 = XMVectorDivide(x3, y3);
    x4 = XMVectorDivide(x4, y4);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

inline SimpleMath::Matrix operator* (float S, const SimpleMath::Matrix& M)
{
    using namespace DirectX;

    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

    x1 = XMVectorScale(x1, S);
    x2 = XMVectorScale(x2, S);
    x3 = XMVectorScale(x3, S);
    x4 = XMVectorScale(x4, S);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
    return R;
}

//------------------------------------------------------------------------------
// SimpleMath::Matrix operations
//------------------------------------------------------------------------------

inline bool SimpleMath::Matrix::Decompose(Vector3& scale, SimpleMath::Quaternion& rotation, SimpleMath::Vector3& translation)
{
    using namespace DirectX;

    XMVECTOR s, r, t;

    if (!XMMatrixDecompose(&s, &r, &t, *this))
        return false;

    XMStoreFloat3(&scale, s);
    DirectX::XMStoreFloat4(&rotation, r);
    XMStoreFloat3(&translation, t);

    return true;
}

inline SimpleMath::Matrix SimpleMath::Matrix::Transpose() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(this);
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixTranspose(M));
    return R;
}

inline void SimpleMath::Matrix::Transpose(Matrix& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(this);
    DirectX::XMStoreFloat4x4(&result, XMMatrixTranspose(M));
}

inline SimpleMath::Matrix SimpleMath::Matrix::Invert() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(this);
    SimpleMath::Matrix R;
    XMVECTOR det;
    DirectX::XMStoreFloat4x4(&R, XMMatrixInverse(&det, M));
    return R;
}

inline void SimpleMath::Matrix::Invert(Matrix& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(this);
    XMVECTOR det;
    DirectX::XMStoreFloat4x4(&result, XMMatrixInverse(&det, M));
}

inline float SimpleMath::Matrix::Determinant() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4(this);
    return XMVectorGetX(XMMatrixDeterminant(M));
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

_Use_decl_annotations_
inline SimpleMath::Matrix SimpleMath::Matrix::CreateBillboard(const SimpleMath::Vector3& object, const SimpleMath::Vector3& cameraPosition, const SimpleMath::Vector3& cameraUp, const SimpleMath::Vector3* cameraForward)
{
    using namespace DirectX;
    XMVECTOR O = XMLoadFloat3(&object);
    XMVECTOR C = XMLoadFloat3(&cameraPosition);
    XMVECTOR Z = XMVectorSubtract(O, C);

    XMVECTOR N = XMVector3LengthSq(Z);
    if (XMVector3Less(N, g_XMEpsilon))
    {
        if (cameraForward)
        {
            XMVECTOR F = XMLoadFloat3(cameraForward);
            Z = XMVectorNegate(F);
        }
        else
            Z = g_XMNegIdentityR2;
    }
    else
    {
        Z = XMVector3Normalize(Z);
    }

    XMVECTOR up = XMLoadFloat3(&cameraUp);
    XMVECTOR X = XMVector3Cross(up, Z);
    X = XMVector3Normalize(X);

    XMVECTOR Y = XMVector3Cross(Z, X);

    XMMATRIX M;
    M.r[0] = X;
    M.r[1] = Y;
    M.r[2] = Z;
    M.r[3] = XMVectorSetW(O, 1.f);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, M);
    return R;
}

_Use_decl_annotations_
inline SimpleMath::Matrix SimpleMath::Matrix::CreateConstrainedBillboard(const SimpleMath::Vector3& object, const SimpleMath::Vector3& cameraPosition, const SimpleMath::Vector3& rotateAxis,
                                                 const SimpleMath::Vector3* cameraForward, const SimpleMath::Vector3* objectForward)
{
    using namespace DirectX;

    static const XMVECTORF32 s_minAngle = { { { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f } } }; // 1.0 - XMConvertToRadians( 0.1f );

    XMVECTOR O = XMLoadFloat3(&object);
    XMVECTOR C = XMLoadFloat3(&cameraPosition);
    XMVECTOR faceDir = XMVectorSubtract(O, C);

    XMVECTOR N = XMVector3LengthSq(faceDir);
    if (XMVector3Less(N, g_XMEpsilon))
    {
        if (cameraForward)
        {
            XMVECTOR F = XMLoadFloat3(cameraForward);
            faceDir = XMVectorNegate(F);
        }
        else
            faceDir = g_XMNegIdentityR2;
    }
    else
    {
        faceDir = XMVector3Normalize(faceDir);
    }

    XMVECTOR Y = XMLoadFloat3(&rotateAxis);
    XMVECTOR X, Z;

    XMVECTOR dot = XMVectorAbs(XMVector3Dot(Y, faceDir));
    if (XMVector3Greater(dot, s_minAngle))
    {
        if (objectForward)
        {
            Z = XMLoadFloat3(objectForward);
            dot = XMVectorAbs(XMVector3Dot(Y, Z));
            if (XMVector3Greater(dot, s_minAngle))
            {
                dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
                Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
            }
        }
        else
        {
            dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
            Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
        }

        X = XMVector3Cross(Y, Z);
        X = XMVector3Normalize(X);

        Z = XMVector3Cross(X, Y);
        Z = XMVector3Normalize(Z);
    }
    else
    {
        X = XMVector3Cross(Y, faceDir);
        X = XMVector3Normalize(X);

        Z = XMVector3Cross(X, Y);
        Z = XMVector3Normalize(Z);
    }

    XMMATRIX M;
    M.r[0] = X;
    M.r[1] = Y;
    M.r[2] = Z;
    M.r[3] = XMVectorSetW(O, 1.f);

    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, M);
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateTranslation(const SimpleMath::Vector3& position)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixTranslation(position.x, position.y, position.z));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateTranslation(float x, float y, float z)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixTranslation(x, y, z));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateScale(const SimpleMath::Vector3& scales)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixScaling(scales.x, scales.y, scales.z));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateScale(float xs, float ys, float zs)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixScaling(xs, ys, zs));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateScale(float scale)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixScaling(scale, scale, scale));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateRotationX(float radians)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationX(radians));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateRotationY(float radians)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationY(radians));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateRotationZ(float radians)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationZ(radians));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateFromAxisAngle(const SimpleMath::Vector3& axis, float angle)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    XMVECTOR a = XMLoadFloat3(&axis);
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationAxis(a, angle));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixPerspectiveFovRH(fov, aspectRatio, nearPlane, farPlane));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreatePerspective(float width, float height, float nearPlane, float farPlane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixPerspectiveRH(width, height, nearPlane, farPlane));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixPerspectiveOffCenterRH(left, right, bottom, top, nearPlane, farPlane));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixOrthographicRH(width, height, zNearPlane, zFarPlane));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixOrthographicOffCenterRH(left, right, bottom, top, zNearPlane, zFarPlane));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateLookAt(const SimpleMath::Vector3& eye, const SimpleMath::Vector3& target, const SimpleMath::Vector3& up)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    XMVECTOR eyev = XMLoadFloat3(&eye);
    XMVECTOR targetv = XMLoadFloat3(&target);
    XMVECTOR upv = XMLoadFloat3(&up);
    DirectX::XMStoreFloat4x4(&R, XMMatrixLookAtRH(eyev, targetv, upv));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateWorld(const SimpleMath::Vector3& position, const SimpleMath::Vector3& forward, const SimpleMath::Vector3& up)
{
    using namespace DirectX;
    XMVECTOR zaxis = XMVector3Normalize(XMVectorNegate(XMLoadFloat3(&forward)));
    XMVECTOR yaxis = XMLoadFloat3(&up);
    XMVECTOR xaxis = XMVector3Normalize(XMVector3Cross(yaxis, zaxis));
    yaxis = XMVector3Cross(zaxis, xaxis);

    SimpleMath::Matrix R;
    XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._11), xaxis);
    XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._21), yaxis);
    XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._31), zaxis);
    R._14 = R._24 = R._34 = 0.f;
    R._41 = position.x; R._42 = position.y; R._43 = position.z;
    R._44 = 1.f;
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateFromQuaternion(const SimpleMath::Quaternion& rotation)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    XMVECTOR quatv = XMLoadFloat4(&rotation);
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    DirectX::XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateShadow(const SimpleMath::Vector3& lightDir, const SimpleMath::Plane& plane)
{
    using namespace DirectX::DXTKXAML12;
    SimpleMath::Matrix R;
    XMVECTOR light = XMLoadFloat3(&lightDir);
    XMVECTOR planev = XMLoadFloat4(&plane);
    DirectX::XMStoreFloat4x4(&R, XMMatrixShadow(planev, light));
    return R;
}

inline SimpleMath::Matrix SimpleMath::Matrix::CreateReflection(const SimpleMath::Plane& plane)
{
    using namespace DirectX;
    SimpleMath::Matrix R;
    XMVECTOR planev = XMLoadFloat4(&plane);
    DirectX::XMStoreFloat4x4(&R, XMMatrixReflect(planev));
    return R;
}

inline void SimpleMath::Matrix::Lerp(const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2, float t, SimpleMath::Matrix& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

    x1 = XMVectorLerp(x1, y1, t);
    x2 = XMVectorLerp(x2, y2, t);
    x3 = XMVectorLerp(x3, y3, t);
    x4 = XMVectorLerp(x4, y4, t);

    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
}

inline SimpleMath::Matrix SimpleMath::Matrix::Lerp(const SimpleMath::Matrix& M1, const SimpleMath::Matrix& M2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
    XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
    XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
    XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

    XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
    XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
    XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
    XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

    x1 = XMVectorLerp(x1, y1, t);
    x2 = XMVectorLerp(x2, y2, t);
    x3 = XMVectorLerp(x3, y3, t);
    x4 = XMVectorLerp(x4, y4, t);

    SimpleMath::Matrix result;
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
    DirectX::XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
    return result;
}

inline void SimpleMath::Matrix::Transform(const SimpleMath::Matrix& M, const SimpleMath::Quaternion& rotation, SimpleMath::Matrix& result)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4(&rotation);

    XMMATRIX M0 = XMLoadFloat4x4(&M);
    XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

    DirectX::XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
}

inline SimpleMath::Matrix SimpleMath::Matrix::Transform(const SimpleMath::Matrix& M, const SimpleMath::Quaternion& rotation)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4(&rotation);

    XMMATRIX M0 = XMLoadFloat4x4(&M);
    XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

    SimpleMath::Matrix result;
    DirectX::XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
    return result;
}


/****************************************************************************
 *
 * SimpleMath::Plane
 *
 ****************************************************************************/

inline SimpleMath::Plane::Plane(const SimpleMath::Vector3& point1, const SimpleMath::Vector3& point2, const SimpleMath::Vector3& point3)
{
    using namespace DirectX;
    XMVECTOR P0 = XMLoadFloat3(&point1);
    XMVECTOR P1 = XMLoadFloat3(&point2);
    XMVECTOR P2 = XMLoadFloat3(&point3);
    DirectX::XMStoreFloat4(this, XMPlaneFromPoints(P0, P1, P2));
}

inline SimpleMath::Plane::Plane(const SimpleMath::Vector3& point, const SimpleMath::Vector3& normal)
{
    using namespace DirectX;
    XMVECTOR P = XMLoadFloat3(&point);
    XMVECTOR N = XMLoadFloat3(&normal);
    DirectX::XMStoreFloat4(this, XMPlaneFromPointNormal(P, N));
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Plane::operator == (const SimpleMath::Plane& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4(this);
    XMVECTOR p2 = XMLoadFloat4(&p);
    return XMPlaneEqual(p1, p2);
}

inline bool SimpleMath::Plane::operator != (const SimpleMath::Plane& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4(this);
    XMVECTOR p2 = XMLoadFloat4(&p);
    return XMPlaneNotEqual(p1, p2);
}

//------------------------------------------------------------------------------
// SimpleMath::Plane operations
//------------------------------------------------------------------------------

inline void SimpleMath::Plane::Normalize()
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMPlaneNormalize(p));
}

inline void SimpleMath::Plane::Normalize(Plane& result) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMPlaneNormalize(p));
}

inline float SimpleMath::Plane::Dot(const SimpleMath::Vector4& v) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(this);
    XMVECTOR v0 = XMLoadFloat4(&v);
    return XMVectorGetX(XMPlaneDot(p, v0));
}

inline float SimpleMath::Plane::DotCoordinate(const SimpleMath::Vector3& position) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(this);
    XMVECTOR v0 = XMLoadFloat3(&position);
    return XMVectorGetX(XMPlaneDotCoord(p, v0));
}

inline float SimpleMath::Plane::DotNormal(const SimpleMath::Vector3& normal) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(this);
    XMVECTOR n0 = XMLoadFloat3(&normal);
    return XMVectorGetX(XMPlaneDotNormal(p, n0));
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline void SimpleMath::Plane::Transform(const SimpleMath::Plane& planev, const SimpleMath::Matrix& M, SimpleMath::Plane& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(&planev);
    XMMATRIX m0 = XMLoadFloat4x4(&M);
    DirectX::XMStoreFloat4(&result, XMPlaneTransform(p, m0));
}

inline SimpleMath::Plane SimpleMath::Plane::Transform(const SimpleMath::Plane& plane, const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(&plane);
    XMMATRIX m0 = XMLoadFloat4x4(&M);

    SimpleMath::Plane result;
    DirectX::XMStoreFloat4(&result, XMPlaneTransform(p, m0));
    return result;
}

inline void SimpleMath::Plane::Transform(const SimpleMath::Plane& plane, const SimpleMath::Quaternion& rotation, SimpleMath::Plane& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(&plane);
    XMVECTOR q = XMLoadFloat4(&rotation);
    XMVECTOR X = XMVector3Rotate(p, q);
    X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = SimpleMath::Plane.d
    DirectX::XMStoreFloat4(&result, X);
}

inline SimpleMath::Plane SimpleMath::Plane::Transform(const SimpleMath::Plane& plane, const SimpleMath::Quaternion& rotation)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4(&plane);
    XMVECTOR q = XMLoadFloat4(&rotation);
    XMVECTOR X = XMVector3Rotate(p, q);
    X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = SimpleMath::Plane.d

    SimpleMath::Plane result;
    DirectX::XMStoreFloat4(&result, X);
    return result;
}


/****************************************************************************
 *
 * Quaternion
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Quaternion::operator == (const SimpleMath::Quaternion& q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    return XMQuaternionEqual(q1, q2);
}

inline bool SimpleMath::Quaternion::operator != (const SimpleMath::Quaternion& q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    return XMQuaternionNotEqual(q1, q2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Quaternion& SimpleMath::Quaternion::operator+= (const SimpleMath::Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    DirectX::XMStoreFloat4(this, XMVectorAdd(q1, q2));
    return *this;
}

inline SimpleMath::Quaternion& SimpleMath::Quaternion::operator-= (const SimpleMath::Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    DirectX::XMStoreFloat4(this, XMVectorSubtract(q1, q2));
    return *this;
}

inline SimpleMath::Quaternion& SimpleMath::Quaternion::operator*= (const SimpleMath::Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    DirectX::XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
    return *this;
}

inline SimpleMath::Quaternion& SimpleMath::Quaternion::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMVectorScale(q, S));
    return *this;
}

inline SimpleMath::Quaternion& SimpleMath::Quaternion::operator/= (const SimpleMath::Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    q2 = XMQuaternionInverse(q2);
    DirectX::XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline SimpleMath::Quaternion SimpleMath::Quaternion::operator- () const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMVectorNegate(q));
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Quaternion operator+ (const SimpleMath::Quaternion& Q1, const SimpleMath::Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(&Q1);
    XMVECTOR q2 = XMLoadFloat4(&Q2);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMVectorAdd(q1, q2));
    return R;
}

inline SimpleMath::Quaternion operator- (const SimpleMath::Quaternion& Q1, const SimpleMath::Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(&Q1);
    XMVECTOR q2 = XMLoadFloat4(&Q2);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
    return R;
}

inline SimpleMath::Quaternion operator* (const SimpleMath::Quaternion& Q1, const SimpleMath::Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(&Q1);
    XMVECTOR q2 = XMLoadFloat4(&Q2);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
    return R;
}

inline SimpleMath::Quaternion operator* (const SimpleMath::Quaternion& Q, float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(&Q);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMVectorScale(q, S));
    return R;
}

inline SimpleMath::Quaternion operator/ (const SimpleMath::Quaternion& Q1, const SimpleMath::Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(&Q1);
    XMVECTOR q2 = XMLoadFloat4(&Q2);
    q2 = XMQuaternionInverse(q2);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
    return R;
}

inline SimpleMath::Quaternion operator* (float S, const SimpleMath::Quaternion& Q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(&Q);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMVectorScale(q1, S));
    return R;
}

//------------------------------------------------------------------------------
// Quaternion operations
//------------------------------------------------------------------------------

inline float SimpleMath::Quaternion::Length() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    return XMVectorGetX(XMQuaternionLength(q));
}

inline float SimpleMath::Quaternion::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    return XMVectorGetX(XMQuaternionLengthSq(q));
}

inline void SimpleMath::Quaternion::Normalize()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMQuaternionNormalize(q));
}

inline void SimpleMath::Quaternion::Normalize(Quaternion& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMQuaternionNormalize(q));
}

inline void SimpleMath::Quaternion::Conjugate()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMQuaternionConjugate(q));
}

inline void SimpleMath::Quaternion::Conjugate(Quaternion& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMQuaternionConjugate(q));
}

inline void SimpleMath::Quaternion::Inverse(Quaternion& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMQuaternionInverse(q));
}

inline float SimpleMath::Quaternion::Dot(const SimpleMath::Quaternion& q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4(this);
    XMVECTOR q2 = XMLoadFloat4(&q);
    return XMVectorGetX(XMQuaternionDot(q1, q2));
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline SimpleMath::Quaternion SimpleMath::Quaternion::CreateFromAxisAngle(const SimpleMath::Vector3& axis, float angle)
{
    using namespace DirectX;
    XMVECTOR a = XMLoadFloat3(&axis);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMQuaternionRotationAxis(a, angle));
    return R;
}

inline SimpleMath::Quaternion SimpleMath::Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
    using namespace DirectX;
    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
    return R;
}

inline SimpleMath::Quaternion SimpleMath::Quaternion::CreateFromRotationMatrix(const SimpleMath::Matrix& M)
{
    using namespace DirectX;
    XMMATRIX M0 = XMLoadFloat4x4(&M);

    SimpleMath::Quaternion R;
    DirectX::XMStoreFloat4(&R, XMQuaternionRotationMatrix(M0));
    return R;
}

inline void SimpleMath::Quaternion::Lerp(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2, float t, SimpleMath::Quaternion& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);

    XMVECTOR dot = XMVector4Dot(Q0, Q1);

    XMVECTOR R;
    if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
    {
        R = XMVectorLerp(Q0, Q1, t);
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate(t);
        XMVECTOR t1v = XMVectorReplicate(1.f - t);
        XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
        XMVECTOR X1 = XMVectorMultiply(Q1, tv);
        R = XMVectorSubtract(X0, X1);
    }

    DirectX::XMStoreFloat4(&result, XMQuaternionNormalize(R));
}

inline SimpleMath::Quaternion SimpleMath::Quaternion::Lerp(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2, float t)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);

    XMVECTOR dot = XMVector4Dot(Q0, Q1);

    XMVECTOR R;
    if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
    {
        R = XMVectorLerp(Q0, Q1, t);
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate(t);
        XMVECTOR t1v = XMVectorReplicate(1.f - t);
        XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
        XMVECTOR X1 = XMVectorMultiply(Q1, tv);
        R = XMVectorSubtract(X0, X1);
    }

    SimpleMath::Quaternion result;
    DirectX::XMStoreFloat4(&result, XMQuaternionNormalize(R));
    return result;
}

inline void SimpleMath::Quaternion::Slerp(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2, float t, SimpleMath::Quaternion& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);
    DirectX::XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
}

inline SimpleMath::Quaternion SimpleMath::Quaternion::Slerp(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2, float t)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);

    SimpleMath::Quaternion result;
    DirectX::XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
    return result;
}

inline void SimpleMath::Quaternion::Concatenate(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2, SimpleMath::Quaternion& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);
    DirectX::XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
}

inline SimpleMath::Quaternion SimpleMath::Quaternion::Concatenate(const SimpleMath::Quaternion& q1, const SimpleMath::Quaternion& q2)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4(&q1);
    XMVECTOR Q1 = XMLoadFloat4(&q2);

    SimpleMath::Quaternion result;
    DirectX::XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
    return result;
}


/****************************************************************************
 *
 * Color
 *
 ****************************************************************************/

inline  SimpleMath::Color::Color(const DirectX::PackedVector::XMCOLOR& Packed)
{
    using namespace DirectX;
    DirectX::XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
}

inline  SimpleMath::Color::Color(const DirectX::PackedVector::XMUBYTEN4& Packed)
{
    using namespace DirectX;
    DirectX::XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool  SimpleMath::Color::operator == (const SimpleMath::Color& c) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    return XMColorEqual(c1, c2);
}

inline bool  SimpleMath::Color::operator != (const SimpleMath::Color& c) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    return XMColorNotEqual(c1, c2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline  SimpleMath::Color& SimpleMath::Color::operator= (const DirectX::PackedVector::XMCOLOR& Packed)
{
    using namespace DirectX;
    DirectX::XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
    return *this;
}

inline  SimpleMath::Color& SimpleMath::Color::operator= (const DirectX::PackedVector::XMUBYTEN4& Packed)
{
    using namespace DirectX;
    DirectX::XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
    return *this;
}

inline  SimpleMath::Color& SimpleMath::Color::operator+= (const  SimpleMath::Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    DirectX::XMStoreFloat4(this, XMVectorAdd(c1, c2));
    return *this;
}

inline  SimpleMath::Color& SimpleMath::Color::operator-= (const  SimpleMath::Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    DirectX::XMStoreFloat4(this, XMVectorSubtract(c1, c2));
    return *this;
}

inline SimpleMath::Color& SimpleMath::Color::operator*= (const SimpleMath::Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    DirectX::XMStoreFloat4(this, XMVectorMultiply(c1, c2));
    return *this;
}

inline SimpleMath::Color& SimpleMath::Color::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMVectorScale(c, S));
    return *this;
}

inline SimpleMath::Color& SimpleMath::Color::operator/= (const SimpleMath::Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(this);
    XMVECTOR c2 = XMLoadFloat4(&c);
    DirectX::XMStoreFloat4(this, XMVectorDivide(c1, c2));
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline SimpleMath::Color SimpleMath::Color::operator- () const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
   SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorNegate(c));
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline SimpleMath::Color operator+ (const SimpleMath::Color& C1, const SimpleMath::Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(&C1);
    XMVECTOR c2 = XMLoadFloat4(&C2);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorAdd(c1, c2));
    return R;
}

inline SimpleMath::Color operator- (const SimpleMath::Color& C1, const SimpleMath::Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(&C1);
    XMVECTOR c2 = XMLoadFloat4(&C2);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
    return R;
}

inline SimpleMath::Color operator* (const SimpleMath::Color& C1, const SimpleMath::Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(&C1);
    XMVECTOR c2 = XMLoadFloat4(&C2);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorMultiply(c1, c2));
    return R;
}

inline SimpleMath::Color operator* (const SimpleMath::Color& C, float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(&C);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorScale(c, S));
    return R;
}

inline SimpleMath::Color operator/ (const SimpleMath::Color& C1, const SimpleMath::Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(&C1);
    XMVECTOR c2 = XMLoadFloat4(&C2);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorDivide(c1, c2));
    return R;
}

inline SimpleMath::Color operator* (float S, const SimpleMath::Color& C)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4(&C);
    SimpleMath::Color R;
    DirectX::XMStoreFloat4(&R, XMVectorScale(c1, S));
    return R;
}

//------------------------------------------------------------------------------
// SimpleMath::Color operations
//------------------------------------------------------------------------------

inline DirectX::PackedVector::XMCOLOR SimpleMath::Color::BGRA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4(this);
    PackedVector::XMCOLOR Packed;
    PackedVector::XMStoreColor(&Packed, clr);
    return Packed;
}

inline DirectX::PackedVector::XMUBYTEN4 SimpleMath::Color::RGBA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4(this);
    PackedVector::XMUBYTEN4 Packed;
    PackedVector::XMStoreUByteN4(&Packed, clr);
    return Packed;
}

inline SimpleMath::Vector3 SimpleMath::Color::ToVector3() const
{
    return SimpleMath::Vector3(x, y, z);
}

inline SimpleMath::Vector4 SimpleMath::Color::ToVector4() const
{
    return SimpleMath::Vector4(x, y, z, w);
}

inline void SimpleMath::Color::Negate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMColorNegative(c));
}

inline void SimpleMath::Color::Negate(Color& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMColorNegative(c));
}

inline void SimpleMath::Color::Saturate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMVectorSaturate(c));
}

inline void SimpleMath::Color::Saturate(Color& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMVectorSaturate(c));
}

inline void SimpleMath::Color::Premultiply()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    XMVECTOR a = XMVectorSplatW(c);
    a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
    DirectX::XMStoreFloat4(this, XMVectorMultiply(c, a));
}

inline void SimpleMath::Color::Premultiply(Color& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    XMVECTOR a = XMVectorSplatW(c);
    a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
    DirectX::XMStoreFloat4(&result, XMVectorMultiply(c, a));
}

inline void SimpleMath::Color::AdjustSaturation(float sat)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMColorAdjustSaturation(c, sat));
}

inline void SimpleMath::Color::AdjustSaturation(float sat, SimpleMath::Color& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMColorAdjustSaturation(c, sat));
}

inline void SimpleMath::Color::AdjustContrast(float contrast)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(this, XMColorAdjustContrast(c, contrast));
}

inline void SimpleMath::Color::AdjustContrast(float contrast, SimpleMath::Color& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4(this);
    DirectX::XMStoreFloat4(&result, XMColorAdjustContrast(c, contrast));
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline void SimpleMath::Color::Modulate(const SimpleMath::Color& c1, const SimpleMath::Color& c2, SimpleMath::Color& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4(&c1);
    XMVECTOR C1 = XMLoadFloat4(&c2);
    DirectX::XMStoreFloat4(&result, XMColorModulate(C0, C1));
}

inline SimpleMath::Color SimpleMath::Color::Modulate(const SimpleMath::Color& c1, const SimpleMath::Color& c2)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4(&c1);
    XMVECTOR C1 = XMLoadFloat4(&c2);

    SimpleMath::Color result;
    DirectX::XMStoreFloat4(&result, XMColorModulate(C0, C1));
    return result;
}

inline void SimpleMath::Color::Lerp(const SimpleMath::Color& c1, const SimpleMath::Color& c2, float t, SimpleMath::Color& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4(&c1);
    XMVECTOR C1 = XMLoadFloat4(&c2);
    DirectX::XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
}

inline SimpleMath::Color SimpleMath::Color::Lerp(const SimpleMath::Color& c1, const SimpleMath::Color& c2, float t)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4(&c1);
    XMVECTOR C1 = XMLoadFloat4(&c2);

    SimpleMath::Color result;
    DirectX::XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
    return result;
}


/****************************************************************************
 *
 * Ray
 *
 ****************************************************************************/

//-----------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool SimpleMath::Ray::operator == (const SimpleMath::Ray& r) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3(&position);
    XMVECTOR r2p = XMLoadFloat3(&r.position);
    XMVECTOR r1d = XMLoadFloat3(&direction);
    XMVECTOR r2d = XMLoadFloat3(&r.direction);
    return XMVector3Equal(r1p, r2p) && XMVector3Equal(r1d, r2d);
}

inline bool SimpleMath::Ray::operator != (const SimpleMath::Ray& r) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3(&position);
    XMVECTOR r2p = XMLoadFloat3(&r.position);
    XMVECTOR r1d = XMLoadFloat3(&direction);
    XMVECTOR r2d = XMLoadFloat3(&r.direction);
    return XMVector3NotEqual(r1p, r2p) && XMVector3NotEqual(r1d, r2d);
}

//-----------------------------------------------------------------------------
// SimpleMath::Ray operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Ray::Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const
{
    return sphere.Intersects(position, direction, Dist);
}

inline bool SimpleMath::Ray::Intersects(const BoundingBox& box, _Out_ float& Dist) const
{
    return box.Intersects(position, direction, Dist);
}

inline bool SimpleMath::Ray::Intersects(const SimpleMath::Vector3& tri0, const SimpleMath::Vector3& tri1, const SimpleMath::Vector3& tri2, _Out_ float& Dist) const
{
    return DirectX::TriangleTests::Intersects(position, direction, tri0, tri1, tri2, Dist);
}

inline bool SimpleMath::Ray::Intersects(const SimpleMath::Plane& plane, _Out_ float& Dist) const
{
    using namespace DirectX;

    XMVECTOR p = XMLoadFloat4(&plane);
    XMVECTOR dir = XMLoadFloat3(&direction);

    XMVECTOR nd = XMPlaneDotNormal(p, dir);

    if (XMVector3LessOrEqual(XMVectorAbs(nd), g_RayEpsilon))
    {
        Dist = 0.f;
        return false;
    }
    else
    {
        // t = -(dot(n,origin) + D) / dot(n,dir)
        XMVECTOR pos = XMLoadFloat3(&position);
        XMVECTOR v = XMPlaneDotNormal(p, pos);
        v = XMVectorAdd(v, XMVectorSplatW(p));
        v = XMVectorDivide(v, nd);
        float dist = -XMVectorGetX(v);
        if (dist < 0)
        {
            Dist = 0.f;
            return false;
        }
        else
        {
            Dist = dist;
            return true;
        }
    }
}


/****************************************************************************
 *
 * Viewport
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool SimpleMath::Viewport::operator == (const SimpleMath::Viewport& vp) const
{
    return (x == vp.x && y == vp.y
            && width == vp.width && height == vp.height
            && minDepth == vp.minDepth && maxDepth == vp.maxDepth);
}

inline bool SimpleMath::Viewport::operator != (const SimpleMath::Viewport& vp) const
{
    return (x != vp.x || y != vp.y
            || width != vp.width || height != vp.height
            || minDepth != vp.minDepth || maxDepth != vp.maxDepth);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline SimpleMath::Viewport& SimpleMath::Viewport::operator= (const RECT& rct)
{
    x = float(rct.left); y = float(rct.top);
    width = float(rct.right - rct.left);
    height = float(rct.bottom - rct.top);
    minDepth = 0.f; maxDepth = 1.f;
    return *this;
}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
inline SimpleMath::Viewport& SimpleMath::Viewport::operator= (const D3D11_VIEWPORT& vp)
{
    x = vp.TopLeftX; y = vp.TopLeftY;
    width = vp.Width; height = vp.Height;
    minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
    return *this;
}
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
inline SimpleMath::Viewport& SimpleMath::Viewport::operator= (const D3D12_VIEWPORT& vp)
{
    x = vp.TopLeftX; y = vp.TopLeftY;
    width = vp.Width; height = vp.Height;
    minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
    return *this;
}
#endif

//------------------------------------------------------------------------------
// Viewport operations
//------------------------------------------------------------------------------

inline float SimpleMath::Viewport::AspectRatio() const
{
    if (width == 0.f || height == 0.f)
        return 0.f;

    return (width / height);
}

inline SimpleMath::Vector3 SimpleMath::Viewport::Project(const SimpleMath::Vector3& p, const SimpleMath::Matrix& proj, const SimpleMath::Matrix& view, const SimpleMath::Matrix& world) const
{
    using namespace DirectX;
    XMVECTOR v = XMLoadFloat3(&p);
    XMMATRIX projection = XMLoadFloat4x4(&proj);
    v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection, view, world);
    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, v);
    return result;
}

inline void SimpleMath::Viewport::Project(const SimpleMath::Vector3& p, const SimpleMath::Matrix& proj, const SimpleMath::Matrix& view, const SimpleMath::Matrix& world, SimpleMath::Vector3& result) const
{
    using namespace DirectX;
    XMVECTOR v = XMLoadFloat3(&p);
    XMMATRIX projection = XMLoadFloat4x4(&proj);
    v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection, view, world);
    XMStoreFloat3(&result, v);
}

inline SimpleMath::Vector3 SimpleMath::Viewport::Unproject(const SimpleMath::Vector3& p, const SimpleMath::Matrix& proj, const SimpleMath::Matrix& view, const SimpleMath::Matrix& world) const
{
    using namespace DirectX;
    XMVECTOR v = XMLoadFloat3(&p);
    XMMATRIX projection = XMLoadFloat4x4(&proj);
    v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, view, world);
    SimpleMath::Vector3 result;
    XMStoreFloat3(&result, v);
    return result;
}

inline void SimpleMath::Viewport::Unproject(const SimpleMath::Vector3& p, const SimpleMath::Matrix& proj, const SimpleMath::Matrix& view, const SimpleMath::Matrix& world, SimpleMath::Vector3& result) const
{
    using namespace DirectX;
    XMVECTOR v = XMLoadFloat3(&p);
    XMMATRIX projection = XMLoadFloat4x4(&proj);
    v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, view, world);
    XMStoreFloat3(&result, v);
}
