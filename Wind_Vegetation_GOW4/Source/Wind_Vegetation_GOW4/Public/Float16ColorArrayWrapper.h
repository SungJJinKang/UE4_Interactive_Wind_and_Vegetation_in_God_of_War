// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Math/Float16Color.h"
#include "Float16ColorArrayWrapper.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WIND_VEGETATION_GOW4_API UFloat16ColorArrayWrapper : public UObject
{
	GENERATED_BODY()

public:

	TArray<FFloat16Color> Array;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE int32 Num() const
	{
		return Array.Num();
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float R(const int32 index) const
	{
		check(index >= 0 && index < Array.Num());
		return static_cast<float>(Array[index].R);
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float G(const int32 index) const
	{
		check(index >= 0 && index < Array.Num());
		return static_cast<float>(Array[index].G);
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float B(const int32 index) const
	{
		check(index >= 0 && index < Array.Num());
		return static_cast<float>(Array[index].B);
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float A(const int32 index) const
	{
		check(index >= 0 && index < Array.Num());
		return static_cast<float>(Array[index].A);
	}

	FORCEINLINE operator TArray<FFloat16Color>&()
	{
		return Array;
	}

	FORCEINLINE operator const TArray<FFloat16Color>& () const
	{
		return Array;
	}
};
