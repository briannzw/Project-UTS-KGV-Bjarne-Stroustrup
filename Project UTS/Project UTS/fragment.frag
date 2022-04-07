#version 330

uniform vec4 colors[8];

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main(){
	color = vec4(1.0, 1.0, 1.0, 1.0);

	const float pi = 2 * acos(0.0);
	float degToRad = pi/180;

	float angle = atan (vPos.y, vPos.x);
	if((angle >= 0 * degToRad) && (angle < 45 * degToRad)){
		color = colors[0];
	}
	else if((angle >= 45 * degToRad) && (angle < 90 * degToRad)){
		color = colors[1];
	}
	else if((angle >= 90 * degToRad) && (angle < 135 * degToRad)){
		color = colors[2];
	}
	else if((angle >= 135 * degToRad) && (angle < 180 * degToRad)){
		color = colors[3];
	}
	else if((angle >= -180 * degToRad) && (angle < -135 * degToRad)){
		color = colors[4];
	}
	else if((angle >= -135 * degToRad) && (angle < -90 * degToRad)){
		color = colors[5];
	}
	else if((angle >= -90 * degToRad) && (angle < -45 * degToRad)){
		color = colors[6];
	}
	else if((angle >= -45 * degToRad) && (angle < -0 * degToRad)){
		color = colors[7];
	}
	
}