#include <map>

#include "lz4frame.h"

#include "id.hpp"
#include "mapper.hpp"
#include "resource.hpp"

namespace res {
    std::unique_ptr<Resource> Mapper::Fetch(ID id) noexcept(false) {
	// This will never fail as long as every ID has a mapping.
	auto from = mappings[id];

	LZ4F_dctx* dec;
	auto       lz4v = LZ4F_getVersion();
	auto       err  = LZ4F_createDecompressionContext(&dec, lz4v);

	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}

	return std::unique_ptr<Resource>(
	  new Resource(dec, from.content, from.compressed_length,
	               from.decompressed_length));
    };
}; // namespace res
