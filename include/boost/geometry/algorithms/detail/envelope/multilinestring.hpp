// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTILINESTRING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTILINESTRING_HPP

#include <cstddef>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/linestring.hpp>
#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/expand/box.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_range_expand_policy
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& mbr, Geometry const& geometry)
    {
        Box helper_mbr;
        envelope_range
            <
                Geometry, Dimension, DimensionCount
            >::apply(geometry, helper_mbr);

        dispatch::expand
            <
                Box, Box, Dimension, DimensionCount
            >::apply(mbr, helper_mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename MultiLinestring,
    std::size_t Dimension,
    std::size_t DimensionCount,
    typename CS_Tag
>
struct envelope
    <
        MultiLinestring,
        Dimension, DimensionCount,
        multi_linestring_tag, CS_Tag
    > : detail::envelope::envelope_range
        <
            MultiLinestring,
            Dimension,
            DimensionCount,
            detail::envelope::envelope_range_expand_policy
                <
                    Dimension, DimensionCount
                >
        >
{};

template
<
    typename MultiLinestring,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct envelope
    <
        MultiLinestring,
        Dimension, DimensionCount,
        multi_linestring_tag, spherical_equatorial_tag
    > : detail::envelope::envelope_linear_on_spheroid
        <
            MultiLinestring,
            Dimension,
            DimensionCount,
            detail::envelope::envelope_range_expand_policy
                <
                    Dimension, DimensionCount
                >
        >
{};


} // namespace dispatch
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTILINESTRING_HPP
