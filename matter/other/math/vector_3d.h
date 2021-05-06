#pragma once

#include <cmath>

struct vector_3d {

	vector_3d( ) : x{ }, y{ }, z{ } { }

	vector_3d( float x, float y, float z ) : x{ x }, y{ y }, z{ z } { }

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

	vector_3d& operator+=( float fl ) {

		x += fl;
		y += fl;
		z += fl;

		return *this;

	}

	vector_3d& operator-=( float fl ) {

		x -= fl;
		y -= fl;
		z -= fl;

		return *this;

	}

	vector_3d& operator*=( float fl ) {

		x *= fl;
		y *= fl;
		z *= fl;

		return *this;

	}

	vector_3d& operator/=( float fl ) {

		x /= fl;
		y /= fl;
		z /= fl;

		return *this;

	}

	vector_3d operator+( const vector_3d& v ) {

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

	vector_3d operator*( const vector_3d& v ) {

		vector_3d result;

		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;

		return result;

	}

	vector_3d operator/( vector_3d& v ) {

		vector_3d result;

		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;

		return result;

	}

	vector_3d operator+( float fl ) {

		return {

			x + fl,
			y + fl,
			z + fl

		};

	}

	vector_3d operator-( float fl ) {

		return {

			x - fl,
			y - fl,
			z - fl

		};

	}

	vector_3d operator*( float fl ) {

		return {

			x * fl,
			y * fl,
			z * fl

		};

	}

	vector_3d operator/( float fl ) {

		return {

			x / fl,
			y / fl,
			z / fl
		
		};

	}
	
	float length( ) {

		return std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );

	}

	float length_2d( ) const {

		return std::sqrtf( x * x + y * y );

	}
	
	float length_sqr( ) {

		return std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 );

	}

	float vector_normalize( vector_3d& v ) {

		float radius = std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );
		radius = 1.f / ( radius + 1.192092896e-07F );

		v *= radius;

		return radius;

	}

	vector_3d normalized( ) {

		vector_3d v = *this;
		vector_normalize( v );
		return v;

	}

	float dot_product( const vector_3d& dot ) const {

		return x * dot.x + y * dot.y + z * dot.z;

	}

	bool is_zero( ) {

		return std::fpclassify( x ) == FP_ZERO && std::fpclassify( y ) == FP_ZERO && std::fpclassify( z ) == FP_ZERO;
		
	}
	
	float x, y, z;

};