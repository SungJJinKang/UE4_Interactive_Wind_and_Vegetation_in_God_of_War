// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Wind_Vegetation_GOW4EditorTarget : TargetRules
{
	public Wind_Vegetation_GOW4EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Wind_Vegetation_GOW4" } );
	}
}
