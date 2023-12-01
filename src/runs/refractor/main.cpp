#include <elang/elpch.h>
#include <elang/registry/registry.h>

using namespace el;

struct Test {
	int x, y;
};

constexpr ID xid = "x"_hs;

int main(int argc, char* argv[]) {
	MetaFactory(Test)
		.data<&Test::x>(xid).prop(TagProp, "x");

	constexpr ID hash = TypeHash(Test);
	MetaType meta = Meta(hash);
	MetaData data = meta.data(xid);
	MetaProp prop = data.prop(TagProp);
	Registry reg;
	auto e = reg.create();
	auto view = reg.view<Test>();
	
	
	SparseSet set;
	

	Test t;
	t.x = 20; t.y = -30;
	void* tt = &t;

	auto tvar = meta.from_void(tt);
	cout << TypeName(Test) << endl;
	cout << prop.value().cast<const char*>() << endl;
	cout << data.get(tvar).cast<int>() << endl;
	cout << meta.get(xid, tvar).cast<int>() << endl;
	
	return 0;
}
