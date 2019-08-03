#include "id.hpp"
#include "mapper.hpp"

namespace res {
    std::map<ID, const Mapper::resDefn> Mapper::mappings{

	// frag.spv
	{
		ID::frag_spv,
		{ 415, frag_spv_len, frag_spv },
	},

	// vert.spv
	{
		ID::vert_spv,
		{ 992, vert_spv_len, vert_spv },
	},

	// vk_renderer.frag
	{
		ID::vk_renderer_frag,
		{ 187, vk_renderer_frag_len, vk_renderer_frag },
	},

	// vk_renderer.vert
	{
		ID::vk_renderer_vert,
		{ 336, vk_renderer_vert_len, vk_renderer_vert },
	},
    };
}; // namespace res
