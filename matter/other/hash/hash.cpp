#include "hash.h"

std::size_t hash::get( const std::string_view string ) const {

    auto ret = m_basis;

	const auto length = std::strlen( string.data( ) );
    for ( std::size_t i = 0; i < length; ++i ) {

        ret ^= string[ i ];
        ret *= m_prime;

    }

    return ret;

}
