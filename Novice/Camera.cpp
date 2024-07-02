#include "Camera.h"
#include "Grid.h"
#include "imgui.h"

void Camera::DebugText(){
	ImGui::DragFloat3("rotate", &rotate_.x, 0.1f);
	ImGui::DragFloat3("position", &position_.x, 0.1f);
}
