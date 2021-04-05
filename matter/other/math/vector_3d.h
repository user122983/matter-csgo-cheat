#pragma once

#include <cmath>
#include <cfloat>

struct vector_3d {

	vector_3d( ) : x{ }, y{ }, z{ } { }

	vector_3d( const float x, const float y, const float z ) : x{ x }, y{ y }, z{ z } { }

	vector_3d( const float* array ) : x( array[ 0 ] ), y( array[ 1 ] ), z( array[ 2 ] ) { }

	vector_3d& operator+=( const vector_3d& v ) {

		x += v.x;
		y += v.y;
		z += v.z;

		return *this;

	}

	vector_3d& operator-=( const vector_3d& v ) {

		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;

	}

	vector_3d& operator*=( const vector_3d& v ) {

		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;

	}

	vector_3d& operator/=( const vector_3d& v ) {

		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;

	}

	vector_3d& operator+=( const float fl ) {

		x += fl;
		y += fl;
		z += fl;

		return *this;

	}

	vector_3d& operator-=( const float fl ) {

		x -= fl;
		y -= fl;
		z -= fl;

		return *this;

	}


	vector_3d& operator*=( const float fl ) {

		x *= fl;
		y *= fl;
		z *= fl;

		return *this;

	}

	vector_3d& operator/=( const float fl ) {

		x /= fl;
		y /= fl;
		z /= fl;

		return *this;

	}

	vector_3d operator+( const vector_3d& v ) const {

		vector_3d result;

		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;

		return result;

	}

	vector_3d operator-( const vector_3d& v ) const {

		vector_3d delta;

		delta.x = x - v.x;
		delta.y = y - v.y;
		delta.z = z - v.z;

		return delta;

	}

	vector_3d operator*( const vector_3d& v ) const {

		vector_3d result;

		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;

		return result;

	}

	vector_3d operator/( const vector_3d& v ) const {

		vector_3d result;

		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;

		return result;

	}

	vector_3d operator+( const float fl ) const {

		return {

			x + fl,
			y + fl,
			z + fl

		};

	}

	vector_3d operator-( const float fl ) const {

		return {

			x - fl,
			y - fl,
			z - fl

		};

	}

	vector_3d operator*( const float fl ) const {

		return {

			x * fl,
			y * fl,
			z * fl

		};

	}

	vector_3d operator/( const float fl ) const {

		return {

			x / fl,
			y / fl,
			z / fl
		
		};

	}

	float length( ) const {

		return std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );

	}

	float length_sqr( ) const {

		return std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 );

	}

	float vector_normalize( vector_3d& v ) const {

		auto radius = std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );
		radius = 1.f / ( radius + FLT_EPSILON );

		v *= radius;

		return radius;

	}

	vector_3d normalized( ) const {

		auto v = *this;
		vector_normalize( v );
		return v;

	}

	float dot_product( const vector_3d& dot ) const {

		return this->x * dot.x + this->y * dot.y + this->z * dot.z;

	}

	bool is_valid( ) const {
		
		return std::isfinite( this->x ) && std::isfinite( this->y ) && std::isfinite( this->z );
		
	}

	float x, y, z;

};