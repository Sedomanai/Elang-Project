/*****************************************************************//**
 * @file   registry.h
 * @brief  The heart of Elang Engine
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include <entt/entt.hpp>
#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

namespace el
{
	using Registry = entt::registry;
	using Entity = entt::entity;
	using ID = entt::id_type;
	using Any = entt::any;
	using MetaType = entt::meta_type;
	using MetaData = entt::meta_data;
	using MetaFunc = entt::meta_func;
	using MetaProp = entt::meta_prop;
	using HashString = entt::hashed_string;
	using MetaHandle = entt::handle;
	using SparseSet = entt::sparse_set;

	constexpr HashString TagProp = "tag"_hs;

	#define MetaFactory(T) entt::meta<T>()
	#define AllTypes entt::resolve()
	#define Meta(lit) entt::resolve(lit)
	#define Typeof(T) entt::type_id<T>()
	#define TypeName(T) entt::type_name<T>::value()
	#define TypeHash(T) entt::type_hash<T>::value()
	#define NullEntity entt::null
}