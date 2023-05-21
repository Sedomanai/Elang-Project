#include <entt/entt.hpp>
#include <entt/core/hashed_string.hpp>

struct test {
	int i;
	float f;
	std::string s;
	void print() { cout << "    print: " << i << " " << f << " " << s << endl; }
	void add(int i_, float f_) { i += i_; f += f_; }
};

struct foo {
	float v;
	test t;
};

struct bar {
	int i;
	test t;
	foo f;
};

constexpr unsigned long long strhash = entt::type_hash<std::string>::value();

void iterate_meta(entt::meta_type& meta, const char* tab = "") {
	cout << tab << "data" << endl;
	for (auto&& [id, dat] : meta.data()) {
		auto tag = dat.prop("tag"_hs);
		cout << tab << "  " << dat.type().info().name() << " " << ((tag) ? tag.value().cast<const char*>() : "err_data_name") << endl;
	}
	cout << tab << "func" << endl;
	for (auto&& [id, func] : meta.func()) {
		auto tag = func.prop("tag"_hs);
		cout << tab << "  " << func.ret().info().name() << " "
			<< ((tag) ? tag.value().cast<const char*>() : "err_func_name") << "(";
		for (auto i = 0; i < func.arity(); i++) {
			cout << func.arg(i).info().name();
			if (i < func.arity() - 1)
				cout << ", ";
		} cout << ")\n";
	}
}

void resolve() {
	entt::meta<test>().prop("tag"_hs, "test")
		.data<&test::i>("i"_hs).prop("tag"_hs, "i")
		.data<&test::f>("f"_hs).prop("tag"_hs, "f")
		.data<&test::s>("s"_hs).prop("tag"_hs, "s")
		.func<&test::print>("print"_hs).prop("tag"_hs, "print")
		.func<&test::add>("add"_hs).prop("tag"_hs, "add");

	entt::meta<foo>().prop("tag"_hs, "foo")
		.data<&foo::t>("t"_hs).prop("tag"_hs, "t")
		.data<&foo::v>("v"_hs).prop("tag"_hs, "v");

	entt::meta<bar>().prop("tag"_hs, "bar")
		.data<&bar::f>("v"_hs).prop("tag"_hs, "f")
		.data<&bar::i>("i"_hs).prop("tag"_hs, "i")
		.data<&bar::t>("t"_hs).prop("tag"_hs, "t");

	cout << "all reflected types: " << endl;
	for (auto&& [id, type] : entt::resolve()) {
		cout << "  " << type.info().name() << ": " << type.id() << ", " << type.info().hash() << endl;
		iterate_meta(type, "    ");
	} cout << endl;
}

void print_meta_for_void(void*, entt::meta_type&, const char*);
void print_meta_value(entt::meta_data& data, entt::meta_any& handle, const char* tab) {
	auto value = data.get(handle);
	switch (data.type().id()) {
	case "int"_hs: cout << value.cast<int>();
		return;
	case "float"_hs: cout << value.cast<float>();
		return;
	case strhash: cout << value.cast<std::string>();
		return;
	}

	auto meta = entt::resolve(data.type().id());
	if (meta) {
		print_meta_for_void(value.data(), meta, (std::string(tab) + std::string(" ")).c_str());
	}
}

void print_data_of_handle(entt::meta_any& handle, entt::meta_data& dat, const char* tab = "") {
	auto tag = dat.prop("tag"_hs);
	cout << tab << "  " << ((tag) ? tag.value().cast<const char*>() : "err_data_name") << ": ";
	print_meta_value(dat, handle, tab);
	cout << endl;
}

void print_meta_for_void(void* vt, entt::meta_type& meta, const char* tab = "") {
	auto handle = meta.from_void(vt);
	cout << tab << meta.info().name() << endl;
	for (auto&& [id, dat] : meta.data()) {
		print_data_of_handle(handle, dat, tab);
	}
}

template<typename ...Args>
void invoke(void* vt, entt::meta_type& meta, entt::id_type func, Args ...args) {
	auto handle = meta.from_void(vt);
	handle.invoke(func, args...);
}

void ttest() {
	test t;
	t.i = 100;
	t.f = 200.0f;
	t.s = "destiny";

	test tt;
	tt.i = 300;
	tt.f = 500.0f;
	tt.s = "essential";

	auto struct_meta = entt::resolve("struct test"_hs);
	print_meta_for_void(&t, struct_meta);
	print_meta_for_void(&tt, struct_meta);

	invoke(&t, struct_meta, "print"_hs);
	invoke(&tt, struct_meta, "add"_hs, 4, 10.0f);
	print_meta_for_void(&tt, struct_meta);

	foo f;
	f.v = 150.53f;
	f.t.i = 500;
	f.t.f = 780.0f;
	f.t.s = "accelerate";

	auto foo_meta = entt::resolve("struct foo"_hs);
	print_meta_for_void(&f, foo_meta);

	bar b;
	b.i = 10;
	auto& bt = b.t;
	bt.i = 20;
	bt.f = 56.23f;
	bt.s = "hwllo word";
	auto& bf = b.f;
	bf.v = 523.5f;
	bf.t = { 60, 23.1f, "bbuy" };

	auto bar_meta = entt::resolve("struct bar"_hs);
	print_meta_for_void(&b, bar_meta);
}
