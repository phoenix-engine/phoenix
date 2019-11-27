#include <id.hpp>

#include "phx_sdl/scene.hpp"

namespace phx_sdl {

    const Scene Scene::Defaults::triangle{
	Surface{},
	Shader{ res::ID::triangle_frag_spv, res::ID::triangle_vert_spv }
    };

    const Scene Scene::Defaults::world2d{
	Surface{},
	Shader{ res::ID::world2d_frag_spv, res::ID::world2d_vert_spv }
    };

} // namespace phx_sdl