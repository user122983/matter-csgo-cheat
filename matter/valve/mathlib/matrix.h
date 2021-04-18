#pragma once

struct matrix3x4 {

	matrix3x4( ) {

		
		
	}
	
	const float* operator[ ]( int index ) const {

		return data[ index ];

	}

	float data[ 3 ][ 4 ];

};

struct view_matrix {

	const float* operator[ ]( int index ) const {

		return data[ index ];

	}

	float data[ 4 ][ 4 ];

};