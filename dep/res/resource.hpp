#ifndef PHX_RES
#define PHX_RES

#include "lz4frame.h"

namespace res {
    class Resource {
    public:
	// The default constructor is meaningless.  Every Resource must
	// be created with a reference to a static array with an
	// uncompressed length.
	Resource() = delete;

	// To construct a Resource, pass it an initialized LZ4F decoder
	// context, an array containing LZ4 compressed bytes, and the
	// size (in bytes) of the uncompressed resource.
	//
	// Most users should simply use Mapper::Fetch.
	Resource(LZ4F_dctx*, const unsigned char*,
	         size_t compressed_length,
	         size_t decompressed_length) noexcept(true);
	~Resource() noexcept(false);

	// Len returns the full decompressed size of the asset.
	const size_t Len() noexcept(true);

	// BlockSize returns the maximum required size of a block which
	// may be written to by a single partial Read.
	const size_t BlockSize() noexcept(false);

	// Read ingests up to len bytes into the target buffer.  For the
	// best performance, the user should pass a buffer sized to the
	// full size of the resource, given by Len(), or to the block
	// size, given by BlockSize().  A smaller buffer may also be
	// used.
	//
	// Reset() may be called to begin from the beginning.
	const size_t Read(char* into, size_t len) noexcept(false);

	// Reset returns the state of the Res to its initial state,
	// ready to begin filling a new target buffer.
	void Reset() noexcept(true);

    private:
	LZ4F_dctx* decoder;
	size_t     consumed;
	size_t     next_read_size;

	const size_t         compressed_content_length;
	const size_t         decompressed_content_length;
	const unsigned char* content;
    };
}; // namespace res

#endif
