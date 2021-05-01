#pragma once

#include <corecrt_math.h>

struct mathlib_base {
	
	float anglemod( float a ) {

		a = ( 360.f / 65536 ) * ( static_cast< int >(a * (65536.f / 360.f)) & 65535 );

		return a;

	}

	float angle_normalize( float angle ) {

		angle = std::fmodf( angle, 360.f );

		if ( angle > 180.f )
			angle -= 360.f;

		if ( angle < -180.f )
			angle += 360.f;

		return angle;

	}

	float approach_angle( float target, float value, float speed ) {

		target = anglemod( target );
		value = anglemod( value );

		float delta = target - value;

		if ( speed < 0 )
			speed = -speed;

		if ( delta < -180 )
			delta += 360;
		else if ( delta > 180 )
			delta -= 360;

		if ( delta > speed )
			value += speed;
		else if ( delta < -speed )
			value -= speed;
		else
			value = target;

		return value;
		
	}

	float angle_diff( float dest, float source ) {

		float delta = std::fmodf( dest - source, 360.f );

		if ( dest > source ) {

			if ( delta >= 180 )
				delta -= 360;

		} else {

			if ( delta <= -180 )
				delta += 360;

		}

		return delta;

	}

	float bias( float x, float bias_amt ) {

		static float last_amt = -1.f;
		static float last_exponent = 0.f;

		if ( last_amt != bias_amt ) 
			last_exponent = std::log( bias_amt ) * -1.4427f;

		return std::pow( x, last_exponent );

	}

	float deg_to_rad( float deg ) {

		return ( deg * ( 3.141f / 180.f ) );

	}

	float rad_to_deg( float rad ) {

		return ( rad * ( 180.f / 3.141f ) );

	}

	void angle_vectors( q_angle& angles, vector_3d* forward, vector_3d* right, vector_3d* up ) {

		float cos_y = std::cos( deg_to_rad( angles.y ) ), sin_y = std::sin( deg_to_rad( angles.y ) );
		float cos_x = std::cos( deg_to_rad( angles.x ) ), sin_x = std::sin( deg_to_rad( angles.x ) );
		float cos_z = std::cos( deg_to_rad( angles.z ) ), sin_z = std::sin( deg_to_rad( angles.z ) );

		if ( forward ) {

			forward->x = cos_x * cos_y;
			forward->y = cos_x * sin_y;
			forward->z = -sin_x;

		}

		if ( right ) {

			right->x = -1.f * sin_z * sin_x * cos_y + -1.f * cos_z * -sin_y;
			right->y = -1.f * sin_z * sin_x * sin_y + -1.f * cos_z * cos_y;
			right->z = -1.f * sin_z * cos_x;

		}

		if ( up ) {

			up->x = cos_z * sin_x * cos_y + -sin_z * -sin_y;
			up->y = cos_z * sin_x * sin_y + -sin_z * cos_y;
			up->z = cos_z * cos_x;

		}

	}

	void angle_vectors( const q_angle& angles, vector_3d* forward )	{

		float sin_x = sin( deg_to_rad( angles.x ) );
		float sin_y = sin( deg_to_rad( angles.y ) );
		float cos_x = cos( deg_to_rad( angles.x ) );
		float cos_y = cos( deg_to_rad( angles.y ) );

		forward->x = cos_x * cos_y;
		forward->y = cos_x * sin_y;
		forward->z = -sin_x;
		
	}

	void vector_angles( const vector_3d& forward, q_angle& view ) {

		float pitch, yaw;

		if ( forward.x == 0.f && forward.y == 0.f ) {
			
			pitch = forward.z > 0.f ? 270.f : 90.f;
			yaw = 0.f;
			
		} else {
			
			pitch = std::atan2f(-forward.z, forward.length_2d( ) ) * 180.f / 3.141f;

			if (pitch < 0.f)
				pitch += 360.f;

			yaw = std::atan2f( forward.y, forward.x ) * 180.f / 3.141f;

			if ( yaw < 0.f )
				yaw += 360.f;
		}

		view.x = pitch;
		view.y = yaw;
		view.z = 0.f;
		
	}
	
};

inline mathlib_base m_mathlib_base;