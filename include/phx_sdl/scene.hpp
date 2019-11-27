#ifndef PHX_SDL_SCENE_HPP
#define PHX_SDL_SCENE_HPP

#include <vector>

#include <glm/vec2.hpp>
#include <id.hpp>

namespace phx_sdl {

    class Scene {

    public:
	struct Surface {
	    std::vector<glm::vec2> verts;
	};

	struct Shader {
	    res::ID frag;
	    res::ID vert;
	};

	// Defaults has some predefined Scenes.
	struct Defaults {
	    static const Scene triangle;
	    static const Scene world2d;
	};

	Surface surface;
	Shader  shader;
    };

} // namespace phx_sdl

#endif // PHX_SDL_SCENE_HPP