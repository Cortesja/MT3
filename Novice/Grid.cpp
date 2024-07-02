#include "Grid.h"
#include "imgui.h"
#include "Novice.h"
#include <cassert>

void Grid::Initialize(){
}

void Grid::Update(){
	Render();
}

void Grid::Draw(const Matrix4x4& viewWorldProjectionMatrix, const Matrix4x4& viewportMatrix){
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

    for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
        localStart_[xIndex].x = (-kGridHalfWidth + xIndex * kGridEvery);
        localStart_[xIndex].y = -kGridHalfWidth;
        localStart_[xIndex].z = 0.0f;

        localEnd_[xIndex].x = (-kGridHalfWidth + xIndex * kGridEvery);
        localEnd_[xIndex].y = kGridHalfWidth;
        localEnd_[xIndex].z = 0.0f;

        ndcVertexStart_[xIndex] = func.Transform(localStart_[xIndex], viewWorldProjectionMatrix);
        ndcVertexEnd_[xIndex] = func.Transform(localEnd_[xIndex], viewWorldProjectionMatrix);

        screenStart_[xIndex] = func.Transform(ndcVertexStart_[xIndex], viewportMatrix);
        screenEnd_[xIndex] = func.Transform(ndcVertexEnd_[xIndex], viewportMatrix);

        Novice::DrawLine(
            static_cast<uint32_t>(screenStart_[xIndex].x), static_cast<uint32_t>(screenStart_[xIndex].y),
            static_cast<uint32_t>(screenEnd_[xIndex].x), static_cast<uint32_t>(screenEnd_[xIndex].y),
            color
        );

        if (xIndex == kSubdivision / 2 - 1) {
            color = 0x00000088;
        }
        else {
            color = 0xFFFFFF88;
        }
    }

    // Reset color for horizontal lines
    color = 0xFFFFFF88;

    // Draw horizontal lines
    for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
        localStart_[zIndex].x = -kGridHalfWidth;
        localStart_[zIndex].y = (-kGridHalfWidth + zIndex * kGridEvery);
        localStart_[zIndex].z = 0.0f;

        localEnd_[zIndex].x = kGridHalfWidth;
        localEnd_[zIndex].y = (-kGridHalfWidth + zIndex * kGridEvery);
        localEnd_[zIndex].z = 0.0f;

        ndcVertexStart_[zIndex] = func.Transform(localStart_[zIndex], viewWorldProjectionMatrix);
        ndcVertexEnd_[zIndex] = func.Transform(localEnd_[zIndex], viewWorldProjectionMatrix);

        screenStart_[zIndex] = func.Transform(ndcVertexStart_[zIndex], viewportMatrix);
        screenEnd_[zIndex] = func.Transform(ndcVertexEnd_[zIndex], viewportMatrix);

        Novice::DrawLine(
            static_cast<int>(screenStart_[zIndex].x), static_cast<int>(screenStart_[zIndex].y),
            static_cast<int>(screenEnd_[zIndex].x), static_cast<int>(screenEnd_[zIndex].y),
            color
        );

        if (zIndex == kSubdivision / 2 - 1) {
            color = 0x00000088;
        }
        else {
            color = 0xFFFFFF88;
        }
    }


	//for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
	//	localStart_[xIndex].x = (-float(kSubdivision / 2.0f) + float(xIndex * kGridEvery));
	//	localStart_[xIndex].y = -kGridHalfWidth;

	//	localEnd_[xIndex].x = (-float(kSubdivision / 2.0f) + float(xIndex * kGridEvery));
	//	localEnd_[xIndex].y = kGridHalfWidth;

	//	ndcVertexStart_[xIndex] = func.Transform(localStart_[xIndex], viewWorldProjectionMatrix);
	//	ndcVertexEnd_[xIndex] = func.Transform(localEnd_[xIndex], viewWorldProjectionMatrix);

	//	screenStart_[xIndex] = func.Transform(localStart_[xIndex], viewportMatrix);
	//	screenEnd_[xIndex] = func.Transform(localEnd_[xIndex], viewportMatrix);

	//	Novice::DrawLine(
	//		(int)screenStart_[xIndex].x, (int)screenStart_[xIndex].y,
	//		(int)screenEnd_[xIndex].x, (int)screenEnd_[xIndex].y,
	//		color
	//	);
	//	if (xIndex == kSubdivision / 2 - 1) {
	//		color = 0x00000088;
	//	}
	//	else {
	//		color = 0xFFFFFF88;
	//	}
	//}
}

void Grid::Render(){
	worldMatrix_ = func.MakeAffineMatrix({ 1,1,1 }, rotate_, position_);
}

void Grid::DebugWindow(){
}
