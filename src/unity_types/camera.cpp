#include "camera.hpp"

matrix44 camera::get_world_to_camera_matrix() const { 
	return memory::read<matrix44>(m_address + O_CAMERA_STATE + 0x9C);//O_CAMERA_STATE_WORLDTOCAMERA_MATRIX);
}

vector2& camera::world_to_screen(const vector3& pos) {

	vector2 ret{ 0,0 };

	if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
		return ret;
	}

	auto temp = get_world_to_camera_matrix();

	auto const view_matrix = matrix44::transpose(temp);

	const vector3 up = { view_matrix._21, view_matrix._22, view_matrix._23 };
	const vector3 right = { view_matrix._11, view_matrix._12, view_matrix._13 };

	const float w =
	{
		view_matrix._41 * pos.x +
		view_matrix._42 * pos.y +
		view_matrix._43 * pos.z +
		view_matrix._44
	};

	if (w < 0.1f) {
		return ret;
	}

	ret.x =
	{
		view_matrix._11 * pos.x +
		view_matrix._12 * pos.y +
		view_matrix._13 * pos.z +
		view_matrix._14
	};

	ret.y =
	{
		view_matrix._21 * pos.x +
		view_matrix._22 * pos.y +
		view_matrix._23 * pos.z +
		view_matrix._24
	};

	ret.x = (1920.f / 2.f) * (1.f + ret.x / w); // TODO - refactor hardcoded monitor dimensions
	ret.y = (1080.f / 2.f) * (1.f - ret.y / w);

	return ret;
}

float camera::get_fov() const {
	return memory::read<float>(m_address + O_CAMERA_STATE + O_CAMERA_STATE_FOV);
}