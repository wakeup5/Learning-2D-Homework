#include "stdafx.h"
#include "util.h"

namespace myUtil
{
	/**	getAngleByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 엇각?을 반환
	*/
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0) angle = M_PI * 2 - angle;
		return angle;
	}

	/**	getDistanceByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 두 점사이의 거리를 반환
	*/
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float dx = endX - startX;
		float dy = endY - startY;

		return sqrt(dx * dx + dy * dy);
	}

	/**	getGradeRadianByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 그 기울기의 라디안 각도를 반환
	*/
	float getGradeRadian(float x1, float y1, float x2, float y2)
	{
		//atan2는 시계방향 기준이므로 y축 반전이 필요하다.
		//return atan2(y1 - y2, x2 - x1);
		
		if (y1 > y2)
		{
			return atan2(y1 - y2, x2 - x1);
		}
		else
		{
			return 2 * M_PI - atan2(y2 - y1, x2 - x1);
		}
		
	}
	/**	getGradeDegreeByTwoPoint
	@date	2015/06/13
	@brief	두개의 좌표를 받아 그 기울기의 디그리 각도를 반환
	*/
	float getGradeDegree(float x1, float y1, float x2, float y2)
	{
		return degFromRad(getGradeRadian(x1, y1, x2, y2));
	}

	//라디안 각도를 디그리 각도로 변환
	float degFromRad(float radian)
	{
		return (radian / (2 * M_PI)) * 360;
	}
	//디그리 각도를 라디안 각도로 변환
	float radFromDeg(float degree)
	{
		return (degree / 360) * (2 * M_PI);
	}
}