// Copyright 2014-2015 Matt Chapman. All Rights Reserved.

#include "KeshUI/KeshUI.h"
#include "KeshUI/Component/KUITriangleListInterfaceComponent.h"


UKUITriangleListInterfaceComponent::UKUITriangleListInterfaceComponent( const class FObjectInitializer& oObjectInitializer )
	: Super(oObjectInitializer)
{
	arTriangles.SetNum( 0 );
	tTexture = NULL;
	v4Bounds.X = 0.f;
	v4Bounds.Y = 0.f;
	v4Bounds.Z = 0.f;
	v4Bounds.W = 0.f;
	v2Size = FVector2D::ZeroVector;
	iTriangleCount = 0;
}


int16 UKUITriangleListInterfaceComponent::GetTriangleCount() const
{
	return iTriangleCount;
}


int16 UKUITriangleListInterfaceComponent::GetArrayCapacity() const
{
	return arTriangles.Num();
}


void UKUITriangleListInterfaceComponent::SetArrayCapacity( int16 iCapacity )
{
	arTriangles.SetNum( iCapacity );
}


void UKUITriangleListInterfaceComponent::AddTriangleStruct( const FCanvasUVTri& stTriangle )
{
	arTriangles.Add( stTriangle );

	v4Bounds.X = min( ( iTriangleCount == 0 ? v4Bounds.X : stTriangle.V0_Pos.X ), min( stTriangle.V0_Pos.X, min( stTriangle.V1_Pos.X, stTriangle.V2_Pos.X ) ) );
	v4Bounds.Y = min( ( iTriangleCount == 0 ? v4Bounds.Y : stTriangle.V0_Pos.Y ), min( stTriangle.V0_Pos.Y, min( stTriangle.V1_Pos.Y, stTriangle.V2_Pos.Y ) ) );
	v4Bounds.Z = max( ( iTriangleCount == 0 ? v4Bounds.Z : stTriangle.V0_Pos.X ), max( stTriangle.V0_Pos.X, max( stTriangle.V1_Pos.X, stTriangle.V2_Pos.X ) ) );
	v4Bounds.W = max( ( iTriangleCount == 0 ? v4Bounds.W : stTriangle.V0_Pos.Y ), max( stTriangle.V0_Pos.Y, max( stTriangle.V1_Pos.Y, stTriangle.V2_Pos.Y ) ) );

	++iTriangleCount;

	InvalidateRenderCache();
}


void UKUITriangleListInterfaceComponent::AddTriangle( FVector2D v2ScreenPointA, FVector2D v2ScreenPointB, FVector2D v2ScreenPointC, 
	FVector2D v2TexturePointA, FVector2D v2TexturePointB, FVector2D v2TexturePointC,
	FLinearColor lcPointA, FLinearColor lcPointB, FLinearColor lcPointC )
{
	FCanvasUVTri stTriangle;

	stTriangle.V0_Pos = v2ScreenPointA;
	stTriangle.V0_UV = v2TexturePointA;
	stTriangle.V0_Color = lcPointA;

	stTriangle.V1_Pos = v2ScreenPointB;
	stTriangle.V1_UV = v2TexturePointB;
	stTriangle.V1_Color = lcPointB;

	stTriangle.V2_Pos = v2ScreenPointC;
	stTriangle.V2_UV = v2TexturePointC;
	stTriangle.V2_Color = lcPointC;

	AddTriangleStruct( stTriangle );
}


UTexture* UKUITriangleListInterfaceComponent::GetTexture() const
{
	return tTexture;
}


void UKUITriangleListInterfaceComponent::SetTexture( UTexture* tTexture )
{
	if ( this->tTexture == tTexture )
		return;

	this->tTexture = tTexture;

	Invalidate();
}


const FVector2D& UKUITriangleListInterfaceComponent::GetSize() const
{
	if ( iTriangleCount == 0 )
		return FVector2D::ZeroVector;
	
	return v2Size;
}


bool UKUITriangleListInterfaceComponent::IsPositionable() const
{
	return false;
}


bool UKUITriangleListInterfaceComponent::HasValidComponents() const
{
	if ( arTriangles.Max() == 0 )
		return false;

	if ( tTexture == NULL )
		return false;

	return true;
}


void UKUITriangleListInterfaceComponent::ConstructNewItem()
{
	if ( !HasValidComponents() )
		return;

	if ( tTexture == NULL )
		return;
	
	if ( tTexture->Resource == NULL )
		return;

	stItem.Reset();

	stItem = TSharedPtr<FCanvasTriangleItem>( new FCanvasTriangleItem(
		arTriangles,
		tTexture->Resource
	) );

	v2Size.X = v4Bounds.X - v4Bounds.Z;
	v2Size.Y = v4Bounds.Y - v4Bounds.W;

	Super::ConstructNewItem();
}