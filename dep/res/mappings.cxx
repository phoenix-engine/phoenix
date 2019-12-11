#include "id.hpp"
#include "mapper.hpp"

namespace res {
    std::map<ID, const Mapper::resDefn> Mapper::mappings{

	// pushconstants.frag.spv
	{
		ID::pushconstants_frag_spv,
		{ 1127, pushconstants_frag_spv_len, pushconstants_frag_spv },
	},

	// pushconstants.vert.spv
	{
		ID::pushconstants_vert_spv,
		{ 1096, pushconstants_vert_spv_len, pushconstants_vert_spv },
	},

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
    };
}; // namespace res
