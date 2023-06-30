#pragma once
#include <Vector3.h>

//直線
struct Line {
	//始点
	Vector3 origin;
	//終点への差分ベクトル
	Vector3 diff;

};

//半直線
struct Ray {
	//始点
	Vector3 origin;
	//終点への差分ベクトル
	Vector3 diff;

};

//線分
struct Segment {
	//始点
	Vector3 origin;
	//終点への差分ベクトル
	Vector3 diff;

};

struct Sphere {
	Vector3 center;
	float radius;
};


struct Triangle {
	Vector3 vertices0;
	Vector3 vertices1;
	Vector3 vertices2;

};
