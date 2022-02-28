// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"

#include "Engine/TextureRenderTarget2D.h"

void UWindMap::SlowUpdateWindMap(const FVector& localLocation, const FVector& windVector)
{
	check(IsValid(WindMap));
	if (IsValid(WindMap))
	{
		//WindMap->UpdateTexture2D()
	}
}
