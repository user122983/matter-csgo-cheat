#pragma once

struct matrix3x4 {

	matrix3x4 (

		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23) {

		data[ 0 ][ 0 ] = m00; data[ 0 ][ 1 ] = m01; data[ 0 ][ 2 ] = m02; data[ 0 ][ 3 ] = m03;
		data[ 1 ][ 0 ] = m10; data[ 1 ][ 1 ] = m11; data[ 1 ][ 2 ] = m12; data[ 1 ][ 3 ] = m13;
		data[ 2 ][ 0 ] = m20; data[ 2 ][ 1 ] = m21; data[ 2 ][ 2 ] = m22; data[ 2 ][ 3 ] = m23;

	}

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