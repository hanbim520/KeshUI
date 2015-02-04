// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KUIInterfaceContainer.h"
#include "KUIMacros.h"
#include "KUIGridContainer.generated.h"


/**
 * General container that has grid layout.
 * Width/heights of the grid can be either < 1.0 (fractional) or >= 1.0 (pixel) - can be mixed.  
 * E.g. [ 5.0, 0.5, 0.5, 5.0 ] would be a 2 column grid of equal size with a 5 pixel border.
 **/
UCLASS(ClassGroup="KeshUI | Container", BlueprintType, Blueprintable)
class KESHUI_API UKUIGridContainer : public UKUIInterfaceContainer
{
	GENERATED_UCLASS_BODY()
	KUI_CLASS_HEADER( UKUIGridContainer )

public:
		
	/* Adds an element at a specific grid location.  Adds to container if necessary. */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void SetGridSlot( uint8 iRow, uint8 iColumn, UKUIInterfaceElement* oChild );

	/* Removes an element from the grid slot.  Does not remove it from the container. */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void RemoveGridSlot( UKUIInterfaceElement* oChild );

	/* Removes a child from this container and from the grid layout. */
	virtual bool RemoveChild( UKUIInterfaceElement* oChild ) override;

	/* Returns true for everything added to a grid location. */
	virtual bool IsChildsLayoutManaged( UKUIInterfaceElement* oChild ) const override;

	/* Adds a column with the given size. Can be either relative (<1.0) or specific (>=1.0) */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void AddColumn( float fWidth );

	/* Adds a row with the given size. Can be either relative (<1.0) or specific (>=1.0) */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void AddRow( float fHeight );

	/* Changes the width of a column. */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void SetColumnWidth( uint8 iColumn, float fWidth );

	/* changes the height of a row. */
	UFUNCTION(Category="KeshUI | Container | Grid", BlueprintCallable)
	virtual void SetRowHeight( uint8 iRow, float fHeight );

	/* Updates the layout of this container. */
	virtual void SetSize( float fWidth, float fHeight ) override;

protected:

	TArray<TArray<TWeakObjectPtr<UKUIInterfaceElement>>> ar2Elements;
	TArray<float> arColumns;
	TArray<float> arRows;

	/* Lays out the grid elements. */
	virtual void DoLayout() override;

};
