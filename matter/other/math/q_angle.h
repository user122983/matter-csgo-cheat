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

		auto result = *this;

		return result += a;

	}

	q_angle operator-( const q_angle& a ) {

		auto result = *this;

		return result -= a;

	}

	q_angle operator*( const q_angle& a ) {

		auto result = *this;

		return result *= a;

	}

	q_angle operator/( const q_angle& a ) {

		auto result = *this;

		return result /= a;

	}

	q_angle operator+( float fl ) {

		auto result = *this;

		return result += fl;

	}

	q_angle operator-( float fl ) {

		auto result = *this;

		return result -= fl;

	}

	q_angle operator*( float fl ) {

		auto result = *this;

		return result *= fl;

	}

	q_angle operator/( float fl ) {

		auto result = *this;

		return result /= fl;

	}
	
	q_angle normalize( ) {

		this->x = std::isfinite( this->x ) ? std::remainderf( this->x, 360.f ) : 0.f;
		this->y = std::isfinite( this->y ) ? std::remainderf( this->y, 360.f ) : 0.f;
		this->z = std::clamp( this->z, -50.f, 50.f );
		
		return *this;
		
	}

	q_angle clamp( ) {
		
		this->x = std::clamp( this->x, -89.f, 89.f );
		this->y = std::clamp( this->y, -180.f, 180.f );
		this->z = std::clamp( this->z, -50.f, 50.f );

		return *this;

	}

	float x, y, z;

};
