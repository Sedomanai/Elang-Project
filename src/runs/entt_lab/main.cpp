
#include "basic.h"
#include "reflection.h"

int main() {
	construct();
	resolve();
	
	auto st = reg.storage(lit::pos);
	auto pos = entt::resolve(lit::pos);
	if (pos) {
		cout << pos.info().name() << " is resolved" << endl;
		
		auto x = pos.data("x"_hs);
		cout << x.type().info().name() << " ";
		if (auto prop = x.prop(lit::tag))
			cout << prop.value().cast<const char*>() << endl;

		cout << "size of meta data " << sizeof(x) << endl;

		for (sizet i = 0; i < 4; i++) {
			if (st->contains(e[i])) {
				auto pv = st->value(e[i]);
				if (pv) {
					cout << "reinterpret: " << reinterpret_cast<position*>(pv)->x << endl;
					auto handle = pos.from_void(pv);

					// both ways work
					auto any = x.get(handle); // but this is probably faster
					cout << *(float*)any.data() << endl;
					auto any2 = handle.get("x"_hs);
					cout << *(float*)any2.data() << endl;
				}
			}
		}
	}

}

