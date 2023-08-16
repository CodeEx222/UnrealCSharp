﻿#pragma once

#include "CoreMacro/BindingMacro.h"
#include "Binding/Function/FFunctionPointer.h"
#include "Binding/Function/TFunctionBuilder.inl"
#include "Binding/Function/TConstructorBuilder.inl"
#include "Binding/Function/TDestructorBuilder.inl"
#include "Binding/Template/TClassName.inl"
#include "Binding/Template/TClassFullName.inl"
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Binding/Core/TPropertyValue.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "Binding/Function/TArgument.inl"
#include "Binding/Function/TReturnValue.inl"
#include "Binding/Function/TOverloadBuilder.inl"
#include "Template/TIsNotUEnum.inl"
#include "UEVersion.h"

#define BINDING_STR(Str) #Str

#define BINDING_REMOVE_PREFIX_CLASS_STR(Class) BINDING_REMOVE_PREFIX_CLASS(FString(TEXT(BINDING_STR(Class))))

#define BINDING_REFLECTION_CLASS(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_PREFIX_CLASS_STR(Class); } \
}; \
template <> \
struct TClassFullName<Class> \
{ \
	static FString Get() { return BINDING_STR(Class); } \
};

#define BINDING_CLASS(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_PREFIX_CLASS_STR(Class); } \
}; \
template <> \
struct TClassFullName<Class> \
{ \
static FString Get() { return BINDING_STR(Class); } \
}; \
template <typename T> \
struct TName<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static FString Get() \
	{ \
		return BINDING_STR(Class); \
	} \
}; \
template <typename T> \
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static TArray<FString> Get() \
	{ \
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, FString(FApp::GetProjectName()))}; \
	} \
}; \
template <typename T> \
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TBindingPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TBindingPropertyValue<T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, typename TEnableIf<std::is_same_v<Result, Class>>::Type> : \
	TPropertyInfoBuilder<InClass, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TBindingArgument<T> \
{ \
	using TBindingArgument<T>::TBindingArgument; \
}; \
template <typename T> \
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TBindingReturnValue<T> \
{ \
	using TBindingReturnValue<T>::TBindingReturnValue; \
};

#define BINDING_SCRIPT_STRUCT(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_PREFIX_CLASS_STR(Class); } \
}; \
template <> \
struct TClassFullName<Class> \
{ \
	static FString Get() { return BINDING_STR(Class); } \
}; \
template <typename T> \
struct TName<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static FString Get() { return BINDING_STR(Class); } \
}; \
template <typename T> \
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static TArray<FString> Get() \
	{ \
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TBaseStructure<T>::Get())}; \
	} \
}; \
template <typename T> \
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TScriptStructPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TScriptStructPropertyValue<T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, typename TEnableIf<std::is_same_v<Result, Class>>::Type> : \
	TPropertyInfoBuilder<InClass, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TScriptStructArgument<T> \
{ \
	using TScriptStructArgument<T>::TScriptStructArgument; \
}; \
template <typename T> \
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TScriptStructReturnValue<T> \
{ \
	using TScriptStructReturnValue<T>::TScriptStructReturnValue; \
};

#define BINDING_ENUM(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_PREFIX_CLASS_STR(Class); } \
}; \
template <> \
struct TClassFullName<Class> \
{ \
	static FString Get() { return BINDING_STR(Class); } \
}; \
template <typename T> \
struct TName<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static FString Get() { return BINDING_STR(Class); } \
}; \
template <typename T> \
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> \
{ \
	static TArray<FString> Get() \
	{ \
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, FString(FApp::GetProjectName()))}; \
	} \
}; \
template <typename T> \
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TBindingEnumPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, Class>, T>::Type> : \
	TBindingEnumPropertyValue<T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, typename TEnableIf<std::is_same_v<Result, Class>>::Type> : \
	TPropertyInfoBuilder<InClass, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TBindingEnumArgument<T> \
{ \
	using TBindingEnumArgument<T>::TBindingEnumArgument; \
}; \
template <typename T> \
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, Class>>::Type> : \
	TBindingEnumReturnValue<T> \
{ \
	using TBindingEnumReturnValue<T>::TBindingEnumReturnValue; \
}; \
template <> \
struct TIsNotUEnum<Class> \
{ \
	enum { Value = true }; \
};

#define BINDING_PROPERTY_BUILDER_SET(Property) TPropertyBuilder<decltype(Property), Property>::Set

#define BINDING_PROPERTY_BUILDER_GET(Property) TPropertyBuilder<decltype(Property), Property>::Get

#define BINDING_PROPERTY_BUILDER_INFO(Property) TPropertyBuilder<decltype(Property), Property>::Info()

#if WITH_PROPERTY_INFO
#define BINDING_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), BINDING_PROPERTY_BUILDER_SET(Property), BINDING_PROPERTY_BUILDER_INFO(Property)
#else
#define BINDING_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), BINDING_PROPERTY_BUILDER_SET(Property)
#endif

#if WITH_PROPERTY_INFO
#define BINDING_READONLY_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), nullptr, BINDING_PROPERTY_BUILDER_INFO(Property)
#else
#define BINDING_READONLY_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), nullptr
#endif

#define BINDING_FUNCTION_BUILDER_INVOKE(Function) \
	FFunctionPointer([](BINDING_FUNCTION_SIGNATURE) \
	{ \
		TFunctionBuilder<decltype(Function), Function>::Invoke(BINDING_FUNCTION_PARAM); \
	}).Value.Pointer

#define BINDING_FUNCTION_BUILDER_INFO(Function) TFunctionBuilder<decltype(Function), Function>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_FUNCTION(Function) BINDING_FUNCTION_BUILDER_INVOKE(Function), BINDING_FUNCTION_BUILDER_INFO(Function)
#else
#define BINDING_FUNCTION(Function) BINDING_FUNCTION_BUILDER_INVOKE(Function)
#endif

#define BINDING_OVERLOAD_BUILDER_INVOKE(SIGNATURE, Function) \
	FFunctionPointer([](BINDING_FUNCTION_SIGNATURE) \
	{ \
		TFunctionBuilder<SIGNATURE, Function>::Invoke(BINDING_FUNCTION_PARAM); \
	}).Value.Pointer

#define BINDING_OVERLOAD_BUILDER_INFO(SIGNATURE, Function) TFunctionBuilder<SIGNATURE, Function>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_OVERLOAD(SIGNATURE, Function) BINDING_OVERLOAD_BUILDER_INVOKE(SIGNATURE, Function), BINDING_OVERLOAD_BUILDER_INFO(SIGNATURE, Function)
#else
#define BINDING_OVERLOAD(SIGNATURE, Function) BINDING_OVERLOAD_BUILDER_INVOKE(SIGNATURE, Function)
#endif

#if WITH_FUNCTION_INFO
#define BINDING_OVERLOADS(...) TOverloadBuilder<void*, FFunctionInfo*>::Get(##__VA_ARGS__)
#else
#define BINDING_OVERLOADS(...) TOverloadBuilder<void*>::Get(##__VA_ARGS__)
#endif

#define BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ...) \
	FFunctionPointer([](BINDING_CONSTRUCTOR_SIGNATURE) \
	{ \
		TConstructorBuilder<T, ##__VA_ARGS__>::Invoke(BINDING_CONSTRUCTOR_PARAM); \
	}).Value.Pointer

#define BINDING_CONSTRUCTOR_BUILDER_INFO(T, ...) TConstructorBuilder<T, ##__VA_ARGS__>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_CONSTRUCTOR(T, ...) BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ##__VA_ARGS__), BINDING_CONSTRUCTOR_BUILDER_INFO(T, ##__VA_ARGS__)
#else
#define BINDING_CONSTRUCTOR(T, ...) BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ##__VA_ARGS__)
#endif

#define BINDING_DESTRUCTOR_BUILDER_INVOKE(...) \
	FFunctionPointer([](BINDING_FUNCTION_SIGNATURE) \
	{ \
		TDestructorBuilder<##__VA_ARGS__>::Invoke(BINDING_FUNCTION_PARAM); \
	}).Value.Pointer

#define BINDING_DESTRUCTOR_BUILDER_INFO(...) TDestructorBuilder<##__VA_ARGS__>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_DESTRUCTOR(...) BINDING_DESTRUCTOR_BUILDER_INVOKE(##__VA_ARGS__), BINDING_DESTRUCTOR_BUILDER_INFO(##__VA_ARGS__)
#else
#define BINDING_DESTRUCTOR(...) BINDING_DESTRUCTOR_BUILDER_INVOKE(##__VA_ARGS__)
#endif
