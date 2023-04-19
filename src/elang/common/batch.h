/*****************************************************************//**
 * @file   batch.h
 * @brief  Batch unit for graphic renderers.
 *		   Batches are flexible enough to be used by all sorts of graphic libraries.
 *		   Able to accomodate all kinds of vertex and material types.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/

#ifndef  EL_BATCH_H
#define  EL_BATCH_H

#include "define.h"

namespace el
{
	/**
	 * @brief A single batch unit for graphic renderers.
	 * 
	 * Has all the fields that suffices most use cases, including a void* type vertices, sizet* type indices.
	 * Batch does not have any methods that guarantee the safety of its pointers or the prevention memory leaks.
	 * This must be done manually.
	 */
	struct Batch
	{
		void* vertices;
		sizet* indices;
		uint32 vertex_count, index_count, material, flag;
		float depth;

#pragma warning ( push )
#pragma warning ( disable: 26495 )
		// Necessary for entt
		Batch() {};
#pragma warning ( pop )

		/**
		 * Construct a batch out of the following parameters.
		 *
		 * @param vertices_ Array of verticies.
		 * @param indices_ Array of indicies.
		 * @param vertex_count_ Amount of vertex count.
		 * @param index_count_ Amount of index count.
		 * @param material_ Entity index of material.
		 * @param flag_ Batch flags which usage may vary between graphic engines.
		 * @param depth_ General sort depth of batch.
		 */
		Batch(void* vertices_, sizet* indices_, uint32 vertex_count_, uint32 index_count_, uint32 material_, uint32 flag_, float depth_)
			: vertices(vertices_), vertex_count(vertex_count_), indices(indices_),
			index_count(index_count_), material(material_), depth(depth_), flag(flag_) {
		}
	};
}

#endif //  EL_DEFINE_H
