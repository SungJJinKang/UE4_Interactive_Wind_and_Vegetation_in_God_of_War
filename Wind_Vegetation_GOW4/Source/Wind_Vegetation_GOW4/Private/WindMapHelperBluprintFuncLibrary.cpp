// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapHelperBluprintFuncLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "WindMap.h"

TArray<UWindMap*> UWindMapHelperBluprintFuncLibrary::GetAllCreatedWindMap()
{
	TArray<UWindMap*> createdWindMaps;

	for(TObjectIterator<UWindMap> iter ; iter ; ++iter)
	{
		createdWindMaps.Add(*iter);
	}

	return createdWindMaps;
}
