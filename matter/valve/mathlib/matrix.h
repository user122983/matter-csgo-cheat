#pragma once

struct matrix3x4 {

	const float* operator[ ]( const int index ) const {

		return data[ index ];

	}

	float data[ 3 ][ 4 ];

};

struct view_matrix {

	const float* operator[ ]( const int index ) const {

		return data[ index ];

	}

	float data[ 4 ][ 4 ];

};