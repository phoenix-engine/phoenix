#ifndef PHX_RES_MAPPER
#define PHX_RES_MAPPER

#include <memory>
#include <map>

#include "id.hpp"
#include "resource.hpp"

namespace res {
    // Mapper encapsulates implementation details of the mapping of IDs
    // to Resources away from the user.
    //
    // Fetch is used to retrieve a new Resource, which can be used to
    // decompress a static asset.  It does not create a new copy of the
    // asset.
    class Mapper {
    public:
	// Mapper may not be instantiated.
	Mapper() = delete;

	// Fetch creates and retrieves a unique smart-pointer to a
	// Resource.
	static std::unique_ptr<Resource> Fetch(ID) noexcept(false);

    private:
	struct resDefn {
	    size_t               compressed_length;
	    size_t               decompressed_length;
	    const unsigned char* content;
	};

	static std::map<ID, const resDefn> mappings;

	// Here, all names of assets are defined.  Each must have an ID
	// associated with it.

	// triangle.frag.spv
	static const size_t        triangle_frag_spv_len;
	static const unsigned char triangle_frag_spv[];

	// triangle.vert.spv
	static const size_t        triangle_vert_spv_len;
	static const unsigned char triangle_vert_spv[];

	// world2d.frag.spv
	static const size_t        world2d_frag_spv_len;
	static const unsigned char world2d_frag_spv[];

	// world2d.vert.spv
	static const size_t        world2d_vert_spv_len;
	static const unsigned char world2d_vert_spv[];
    };
}; // namespace res

#endif
