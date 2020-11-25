// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TransformTypes.h"

class UMaterialInterface;
class UInteractiveToolManager;
class IToolsContextAssetAPI;
struct FMeshDescription;
class FDynamicMesh3;
class AActor;
class UPrimitiveComponent;
class UTexture2D;

/**
 * Utility functions for generating Assets in InteractiveTool implementations
 */
namespace AssetGenerationUtil
{
	/**
	 * Creates a new StaticMesh actor/component, with a new mesh asset stored at the given PackagePath created via the AssetAPI
	 * @param AssetAPI pointer to context asset API that will be used to create new asset
	 * @param TargetWorld world that Actor will be created in
	 * @param Mesh geometry for the mesh
	 * @param Transform transformation for the new actor
	 * @param ObjectName name of the new asset
	 * @param PackagePath path of the new asset
	 * @param Material optional single material to set on actor
	 * @return new mesh actor
	 */
	MODELINGCOMPONENTS_API AActor* GenerateStaticMeshActor(
		IToolsContextAssetAPI* AssetAPI,
		UWorld* TargetWorld,
		const FDynamicMesh3* Mesh,
		const FTransform3d& Transform,
		FString ObjectName,
		UMaterialInterface* Material = nullptr
	);

	/**
	* Creates a new StaticMesh actor/component, with a new mesh asset stored at the given PackagePath created via the AssetAPI
	* @param AssetAPI pointer to context asset API that will be used to create new asset
	* @param TargetWorld world that Actor will be created in
	* @param Mesh geometry for the mesh
	* @param Transform transformation for the new actor
	* @param ObjectName name of the new asset
	* @param PackagePath path of the new asset
	* @param Materials materials to set on generated actor
	* @return new mesh actor
	*/
	MODELINGCOMPONENTS_API AActor* GenerateStaticMeshActor(
		IToolsContextAssetAPI* AssetAPI,
		UWorld* TargetWorld,
		const FDynamicMesh3* Mesh,
		const FTransform3d& Transform,
		FString ObjectName,
		const TArrayView<UMaterialInterface*>& Materials
	);


	/**
	 * Save generated UTexture2D that is currently in the Transient package (ie generated in code) as an Asset with a given name 
	 * @param AssetAPI pointer to context asset API that will be used to create new asset
	 * @param TransientTexture texture to save
	 * @param ObjectName name of the new asset
	 * @param RelativeToAsset New texture will be saved at the same path as the UPackage for this UObject, which we assume to be an Asset (eg like a UStaticMesh)
	 */
	MODELINGCOMPONENTS_API bool SaveGeneratedTexture2D(
		IToolsContextAssetAPI* AssetAPI,
		UTexture2D* TransientTexture,
		FString ObjectName,
		const UObject* RelativeToAsset);

	/**
	 * Strip the appended auto-generated _UUID suffix on the given string, if we can detect one
	 * @param InputName input string that may have _UUID suffix
	 * @return InputName without _UUID suffix
	 */
	MODELINGCOMPONENTS_API FString StripGeneratedAssetSuffixFromName(
		FString InputName);

	/**
	 * Look up the name for the Asset underlying the given Component, if there is one.
	 * Optionally Strip off the appended auto-generated UUID string if we can detect one.
	 * If there is not a known underlying asset, returns the Component's name
	 * @param Component the Component we want the Asset Base Name for
	 * @param bRemoveAutoGeneratedSuffixes strip off generated UUID suffix if one is detected (default true)
	 * @return the Name for the Component
	 */
	MODELINGCOMPONENTS_API FString GetComponentAssetBaseName(
		UPrimitiveComponent* Component, 
		bool bRemoveAutoGeneratedSuffixes = true);


}