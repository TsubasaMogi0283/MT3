#pragma once


struct Sphere {
	Vector3 center;
	float radius;
};

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

struct Plane {
	Vector3 normal; //法線
	float distance; //距離
};

//三角形
struct Triangle {
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;

};



