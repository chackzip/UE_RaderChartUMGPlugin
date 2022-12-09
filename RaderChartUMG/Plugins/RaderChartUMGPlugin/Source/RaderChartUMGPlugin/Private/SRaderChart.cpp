#include "SRaderChart.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRaderChart::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	ValueArray = InArgs._ValueArray;
	OutlineBrush = FInvalidatableBrushAttribute(InArgs._OutlineBrush);
	OutlineWidth = InArgs._OutlineWidth;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SRaderChart::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	if (ValueArray.Num() < 3)
	{
		return LayerId;
	}

	const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
	const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
	const FVector2f Center = FVector2f(Pos.X, Pos.Y) + (0.5f * FVector2f(Size.X,Size.Y));
	const float Radius = FMath::Min(Size.X, Size.Y) * 0.5f;
	const float Deg = 360 / ValueArray.Num();

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	FLinearColor LinearColor = /*ColorAndOpacity.Get() * */InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	TArray<FSlateVertex> Vertices;
	Vertices.Reserve(ValueArray.Num() + 1);

	// Add center vertex
	Vertices.AddZeroed();
	FSlateVertex& CenterVertex = Vertices.Last();

	CenterVertex.Position = FVector2f(Center.X, Center.Y);
	CenterVertex.Color = FinalColorAndOpacity;
	CenterVertex.SetTexCoords(FVector4f(0.5f, 0.5f, 1.0f, 1.0f));

	// Add vertices
	for (int i = 0; i < ValueArray.Num(); i++)
	{
		const float CurrentRad = FMath::DegreesToRadians(Deg * i + 90);
		FVector2f VertPos(FMath::Cos(CurrentRad), -FMath::Sin(CurrentRad));

		Vertices.AddZeroed();
		FSlateVertex& OuterVert = Vertices.Last();

		OuterVert.Position = Center + VertPos * Radius * ValueArray[i];
		OuterVert.Color = FinalColorAndOpacity;
		FVector2f UV = FVector2f( (OuterVert.Position.X - Pos.X) / Size.X, (OuterVert.Position.Y - Pos.Y) / Size.Y);
		OuterVert.SetTexCoords(FVector4f(UV.X, UV.Y, 1.0f, 1.0f));
	}

	TArray<SlateIndex> Indices;
	for (int i = 1; i <= ValueArray.Num(); i++)
	{
		Indices.Add(0);
		Indices.Add(i);

		if (ValueArray.Num() < i + 1)
		{
			Indices.Add(1);
		}
		else
		{
			Indices.Add(i + 1);
		}
	}

	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*SlateBrush);
	FSlateDrawElement::MakeCustomVerts(
		OutDrawElements,
		LayerId,
		Handle,
		Vertices,
		Indices,
		nullptr,
		0,
		0
	);

	const FSlateBrush* OutlineSlateBrush = OutlineBrush.GetImage().Get();
	FLinearColor OutlineLinearColor = /*ColorAndOpacity.Get() * */InWidgetStyle.GetColorAndOpacityTint() * OutlineSlateBrush->GetTint(InWidgetStyle);
	FColor FinalOutlineColorAndOpacity = OutlineLinearColor.ToFColor(true);
	TArray<FSlateVertex> OutlineVertices;
	for (int i = 1; i < Vertices.Num(); i++)
	{
		FVector2f StartPosition = Vertices[i].Position;
		FVector2f EndPosition;
		if((i+1) < Vertices.Num())
		{
			EndPosition = Vertices[i + 1].Position;
		}
		else
		{
			EndPosition = Vertices[1].Position;
		}

		FVector2f StartToEndVec = EndPosition - StartPosition;
		FVector2f NormalVec1 = FVector2f(-StartToEndVec.Y, StartToEndVec.X);
		FVector2f NormalVec2 = FVector2f(StartToEndVec.Y, -StartToEndVec.X);
		NormalVec1.Normalize();
		NormalVec2.Normalize();

		OutlineVertices.AddZeroed();
		FSlateVertex& OuterVert1 = OutlineVertices.Last();
		OuterVert1.Position = (StartPosition + (NormalVec1 * OutlineWidth));
		OuterVert1.Color = FinalOutlineColorAndOpacity;

		OutlineVertices.AddZeroed();
		FSlateVertex& OuterVert2 = OutlineVertices.Last();
		OuterVert2.Position = (StartPosition + (NormalVec2 * OutlineWidth));
		OuterVert2.Color = FinalOutlineColorAndOpacity;

		OutlineVertices.AddZeroed();
		FSlateVertex& OuterVert3 = OutlineVertices.Last();
		OuterVert3.Position = (EndPosition + (NormalVec1 * OutlineWidth));
		OuterVert3.Color = FinalOutlineColorAndOpacity;

		OutlineVertices.AddZeroed();
		FSlateVertex& OuterVert4 = OutlineVertices.Last();
		OuterVert4.Position = (EndPosition + (NormalVec2 * OutlineWidth));
		OuterVert4.Color = FinalOutlineColorAndOpacity;
	}

	TArray<SlateIndex> OutlineIndices;
	for (int i = 1; i < Vertices.Num(); i++)
	{
		int startIndex = (i - 1) * 4;
		OutlineIndices.Add(startIndex);
		OutlineIndices.Add(startIndex + 3);
		OutlineIndices.Add(startIndex + 1);

		OutlineIndices.Add(startIndex);
		OutlineIndices.Add(startIndex + 2);
		OutlineIndices.Add(startIndex + 3);
	}

	const FSlateResourceHandle OutlineHandle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*OutlineSlateBrush);
	FSlateDrawElement::MakeCustomVerts(
		OutDrawElements,
		LayerId,
		OutlineHandle,
		OutlineVertices,
		OutlineIndices,
		nullptr,
		0,
		0
	);

	return LayerId;
}

void SRaderChart::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SRaderChart::SetValueArray(TArray<float>& InValueArray)
{
	ValueArray = InValueArray;
}

void SRaderChart::SetOutlineBrush(FSlateBrush* InBrush)
{
	OutlineBrush.SetImage(*this, InBrush);
}


void SRaderChart::SetOutlineWidth(float InOutlineWidth)
{
	OutlineWidth = InOutlineWidth;
}
