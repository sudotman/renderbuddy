// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressMovie.h"

ProgressMovie::ProgressMovie()
{
}

ProgressMovie::~ProgressMovie()
{
}

// Override the GetStatusProgress_Implementation
float ProgressMovie::GetStatusProgress_Implementation() const
{
    // Return the progress value (you can implement any logic here)
    float CurrentProgress = 0.5f; // Example: 50% progress
    return CurrentProgress;
}

