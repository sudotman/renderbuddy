#include "MyEditorSubsystem.h"

//Alternative to store indices - not being used

void UMyEditorSubsystem::SetStoredIndex(int32 NewIndex)
{
    StoredIndex = NewIndex;
}

int32 UMyEditorSubsystem::GetStoredIndex() const
{
    return StoredIndex;
}