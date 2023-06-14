#pragma once

#include "FNameSpace.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T, typename Enable = void>
struct TNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};
