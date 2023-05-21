#include <entt/entt.hpp>
#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

entt::registry reg;
entt::entity e[4];

struct position { float x, y; };
struct velocity { float dx, dy; };

namespace lit {
	constexpr auto tag = "tag"_hs;
	constexpr auto pos = entt::type_hash<position>::value();
	constexpr auto vel = entt::type_hash<velocity>::value();
}

void construct() {
	for (sizet i = 0; i < 4; i++)
		e[i] = reg.create();

	reg.emplace<position>(e[0], 4.0f, 5.0f);
	reg.emplace<position>(e[1], 7.0f, 3.0f);
	reg.emplace<velocity>(e[1], 1.0f, 2.0f);
	reg.emplace<velocity>(e[2], 2.0f, 3.0f);
	entt::meta<position>()
		.data<&position::x>("x"_hs).prop("tag"_hs, "x");
}