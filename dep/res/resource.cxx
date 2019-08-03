#include "lz4frame.h"

#include "resource.hpp"

namespace res {
    namespace {
	LZ4F_frameInfo_t _noFrame;

	using bid = LZ4F_blockSizeID_t;
	const size_t lookupBlkSize(bid szid) noexcept(true) {
	    switch (szid) {
	    case LZ4F_default:
		return 2 << 21;
	    case LZ4F_max64KB:
		return 2 << 15;
	    case LZ4F_max256KB:
		return 2 << 17;
	    case LZ4F_max1MB:
		return 2 << 19;
	    case LZ4F_max4MB:
		return 2 << 21;
	    default:
		return 2 << 21;
	    }
	}
    }; // namespace

    const size_t Resource::Len() noexcept(true) {
	return decompressed_content_length;
    }

    Resource::Resource(
      LZ4F_dctx* decoder, const unsigned char* content,
      size_t compressed_content_length,
      size_t decompressed_content_length) noexcept(true)
        : decoder(decoder), consumed(0), next_read_size(0),
          compressed_content_length(compressed_content_length),
          decompressed_content_length(decompressed_content_length),
          content(content) {}

    Resource::~Resource() noexcept(false) {
	auto err = LZ4F_freeDecompressionContext(decoder);
	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}
    }

    const size_t Resource::BlockSize() noexcept(false) {
	LZ4F_frameInfo_t frame = _noFrame;

	// "more" is how much max will be parsed from buf as the header.
	size_t more = LZ4F_HEADER_SIZE_MAX;

	auto errOrNext = LZ4F_getFrameInfo(decoder, &frame,
	                                   content + consumed, &more);
	if (LZ4F_isError(errOrNext)) {
	    throw LZ4F_getErrorName(errOrNext);
	}

	// "more" is now how much was read from buf.
	consumed += more;

	// "errOrNext" is the expected size of the next read.
	next_read_size = errOrNext;

	return lookupBlkSize(frame.blockSizeID);
    }

    const size_t Resource::Read(char*  into,
                                size_t len) noexcept(false) {
	size_t intoSize = len;
	size_t more     = next_read_size;
	size_t written  = 0;
	bool   done     = false;

	// Precalculate the size of the next read.
	BlockSize();

	while (!done && more > 0 && written < len) {
	    // Consume the frame into the destination.
	    auto errOrMore = LZ4F_decompress(
	      decoder, into + written, &intoSize, content + consumed,
	      &more, NULL);
	    if (LZ4F_isError(errOrMore)) {
		throw LZ4F_getErrorName(errOrMore);
	    }
	    if (errOrMore == 0) {
		done = true;
	    }

	    // "intoSize" is now the amount actually decoded into
	    // "into", so add it to the total written.
	    written += intoSize;

	    // Reset "intoSize" to the remaining target buffer for the
	    // next call.
	    intoSize = len - written;

	    // After decoding the block, "more" is the count of bytes
	    // consumed, in that call, from the internal compressed
	    // buffer source.  Add this to the total internal offset.
	    consumed += more;

	    // errOrMore is the ideal next read size.
	    more = next_read_size = errOrMore;
	}

	return written;
    }

    void Resource::Reset() noexcept(true) {
	LZ4F_resetDecompressionContext(decoder);

	consumed = next_read_size = 0;
    }
}; // namespace res
