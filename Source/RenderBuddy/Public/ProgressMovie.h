// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoviePipelineExecutor.h"  // This is the correct header for UMoviePipelineExecutorBase

/**
 * 
 */
class RENDERBUDDY_API ProgressMovie : public UMoviePipelineExecutorBase
{
public:
	ProgressMovie();
	virtual float GetStatusProgress_Implementation() const override;

	~ProgressMovie();
};
