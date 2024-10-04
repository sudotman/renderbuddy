// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MyEditorSubsystem.generated.h"

//Alternative to store indices - not being used

/**
 * 
 */
UCLASS()
class RENDERBUDDY_API UMyEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	// Example of a stored index variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subsystem")
	int32 StoredIndex;

	// Function to set the index
	UFUNCTION(BlueprintCallable, Category = "Subsystem")
	void SetStoredIndex(int32 NewIndex);

	// Function to get the index
	UFUNCTION(BlueprintCallable, Category = "Subsystem")
	int32 GetStoredIndex() const;
};

