/*****************************************************************//**
 * @file   poly2d.h
 * @brief  2D polygons (convex only)
 *          Currently not in use. (Explains the poor docs.)
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_POLY2D_H
#define  EL_POLY2D_H
#include "define.h"
#include "vec2.h"

namespace el
{

#define EL_MAX_POLYGON_VERTS 8
     /** @brief Polygon bounds with @ref poly2d::count of corners, each with its vertex position and its normal vector. */
    struct poly2d
    {
        /** @var count @brief Amount of corners in this polygon in size_t. */
        sizet count;
        /** @var verts @brief The vertices of the corners in this polygon. */
        vec2 verts[EL_MAX_POLYGON_VERTS];
        /** @var norms @brief The normals of the corners in this polygon. */
        vec2 norms[EL_MAX_POLYGON_VERTS];
    };
}
#endif