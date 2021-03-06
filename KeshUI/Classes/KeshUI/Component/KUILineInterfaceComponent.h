// Copyright 2014-2015 Matt Chapman. All Rights Reserved.

#pragma once

#include "KeshUI/Component/KUICanvasItemInterfaceComponent.h"
#include "KeshUI/KUIMacros.h"
#include "KUILineInterfaceComponent.generated.h"

/**
 * KeshUI UI Framework (KUI) Line render component.
 */
UCLASS(ClassGroup="KeshUI|Component", Blueprintable, BlueprintType)
class KESHUI_API UKUILineInterfaceComponent : public UKUICanvasItemInterfaceComponent
{
	GENERATED_BODY()
	KUI_CLASS_HEADER( UKUILineInterfaceComponent )

	UKUILineInterfaceComponent( const class FObjectInitializer& oObjectInitializer );

public:

	/* Gets the origin of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual const FVector& GetOrigin() const;

	/* Sets the origin of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual void SetOriginStruct( const FVector& vOrigin );

	/* Sets the origin of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual void SetOrigin( float fX, float fY, float fZ = 0.f );

	/* Gets the end of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual const FVector& GetEnd() const;

	/* Sets the end of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual void SetEndStruct( const FVector& vEnd );

	/* Sets the end of the component. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual void SetEnd( float fX, float fY, float fZ = 0.f );

	/* Gets the thickness of the texture from the screen. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual float GetThickness() const;

	/* Sets the texture location. */
	UFUNCTION(Category="KeshUI|Component|Line", BlueprintCallable)
	virtual void SetThickness( float fThickness );

	/* Gets the size of this component. */
	virtual const FVector2D& GetSize() const override;

	/* Returns true if this can have its location changed. */
	virtual bool IsPositionable() const override;

	/* Returns true if there's enough information to render. */
	virtual bool HasValidComponents() const override;

	/* Updates size and thickness. */
	virtual void Render( AKUIInterface* aHud, UCanvas* oCanvas, const FVector2D& v2Origin, UKUIInterfaceElement* oRenderCacheObject = NULL ) override;

protected:

	FVector vOrigin;
	FVector vEnd;
	FVector2D v2Size;
	float fThickness;

	/* Tries to construct a new FCanvasLineItem! */
	virtual void ConstructNewItem() override;

};
