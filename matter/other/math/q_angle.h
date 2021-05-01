#pragma once

#include <algorithm>
#include <cmath>

struct q_angle {
	
	q_angle() : x{ }, y{ }, z{ } { }

	q_angle( float x, float y, float z ) : x{ x }, y{ y }, z{ z } { }

	q_angle& operator+=( const q_angle& a ) {

		x += a.x;
		y += a.y;
		z += a.z;

		return *this;

	}

	q_angle& operator-=( const q_angle& a ) {

		x -= a.x;
		y -= a.y;
		z -= a.z;

		return *this;

	}

	q_angle& operator*=( const q_angle& a ) {

		x *= a.x;
		y *= a.y;
		z *= a.z;

		return *this;

	}

	q_angle& operator/=( const q_angle& a ) {

		x /= a.x;
		y /= a.y;
		z /= a.z;

		return *this;

	}

	q_angle& operator+=( float fl ) {

		x += fl;
		y += fl;
		z += fl;

		return *this;

	}

	q_angle& operator-=( float fl ) {

		x -= fl;
		y -= fl;
		z -= fl;

		return *this;

	}


	q_angle& operator*=( float fl ) {

		x *= fl;
		y *= fl;
		z *= fl;

		return *this;

	}

	q_angle& operator/=( float fl ) {

		x /= fl;
		y /= fl;
		z /= fl;

		return *this;

	}

	q_angle operator+( const q_angle& a ) {

		q_angle result = *this;

		return result += a;

	}

	q_angle operator-( const q_angle& a ) {

		q_angle result = *this;

		return result -= a;

	}

	q_angle operator*( const q_angle& a ) {

		q_angle result = *this;

		return result *= a;

	}

	q_angle operator/( const q_angle& a ) {

		q_angle result = *this;

		return result /= a;

	}

	q_angle operator+( float fl ) {

		q_angle result = *this;

		return result += fl;

	}

	q_angle operator-( float fl ) {

		q_angle result = *this;

		return result -= fl;

	}

	q_angle operator*( float fl ) {

		q_angle result = *this;

		return result *= fl;

	}

	q_angle operator/( float fl ) {

		q_angle result = *this;

		return result /= fl;

	}
	
	q_angle normalize( ) {

		x = std::isfinite( x ) ? std::remainderf( x, 360.f ) : 0.f;
		y = std::isfinite( y ) ? std::remainderf( y, 360.f ) : 0.f;
		z = std::clamp( z, -50.f, 50.f );
		
		return *this;
		
	}

	q_angle clamp( ) {
		
		x = std::clamp( x, -89.f, 89.f );
		y = std::clamp( y, -180.f, 180.f );
		z = std::clamp( z, -50.f, 50.f );

		return *this;

	}

	bool is_zero( ) {

		return std::fpclassify( x ) == FP_ZERO && std::fpclassify( y ) == FP_ZERO && std::fpclassify( z ) == FP_ZERO;

	}

	float x, y, z;

};
