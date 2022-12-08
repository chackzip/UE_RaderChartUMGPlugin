#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RADERCHARTUMGPLUGIN_API SRaderChart : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRaderChart)
	{}
	SLATE_ARGUMENT(FSlateBrush*, Brush)
	SLATE_ARGUMENT(TArray<float>, ValueArray)
	SLATE_ARGUMENT(FSlateBrush*, OutlineBrush)
	SLATE_ARGUMENT(float, OutlineWidth)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const override;

	void DrawChart(FColor& InColor, FSlateBrush* InBrush, TArray<FSlateVertex>& Vertices, FVector2f InCenter, float InRadius, float InDeg, FSlateWindowElementList& InOutDrawElements, int32 InLayerId);
	void DrawOutline(FColor& InColor, FSlateBrush* InBrush, TArray<FSlateVertex>& InVertices, FSlateWindowElementList& InOutDrawElements, int32 InLayerId);

	void SetValueArray(TArray<float>& InValueArray);
	void SetOutlineWidth(float InOutlineWidth);
	void SetBrush(FSlateBrush* InBrush);
	void SetOutlineBrush(FSlateBrush* InBrush);

protected:
	FInvalidatableBrushAttribute Brush;
	TArray<float> ValueArray;
	FInvalidatableBrushAttribute OutlineBrush;
	float OutlineWidth;
};