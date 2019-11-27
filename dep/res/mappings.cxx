#include "id.hpp"
#include "mapper.hpp"

namespace res {
    std::map<ID, const Mapper::resDefn> Mapper::mappings{

	// triangle.frag.spv
	{
		ID::triangle_frag_spv,
		{ 415, triangle_frag_spv_len, triangle_frag_spv },
	},

	// triangle.vert.spv
	{
		ID::triangle_vert_spv,
		{ 992, triangle_vert_spv_len, triangle_vert_spv },
	},

	// world2d.frag.spv
	{
		ID::world2d_frag_spv,
		{ 415, world2d_frag_spv_len, world2d_frag_spv },
	},

	// world2d.vert.spv
	{
		ID::world2d_vert_spv,
		{ 979, world2d_vert_spv_len, world2d_vert_spv },
	},
    };
}; // namespace res
