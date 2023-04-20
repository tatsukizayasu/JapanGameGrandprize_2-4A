#include "PolyLine.h"
#include "DxLib.h"

//-------------------------------------
// コンストラクタ 
//-------------------------------------
PolyLine::PolyLine()
{
	collider_type = (int)COLLIDER::POLY_LINE;
}

//-------------------------------------
// コンストラクタ 引数：点の座標と数
//-------------------------------------
PolyLine::PolyLine(Location bend_points[], unsigned int size)
{
	collider_type = (int)COLLIDER::POLY_LINE;
	for (int i = 0; i < size; i++)
	{
		this->bend_points.push_back(new SphereCollider(bend_points[i]));
	}
	for (int i = 0; i < size - 1; i++)
	{
		lines.push_back(new LineCollider(bend_points[i], bend_points[i + 1]));
	}

	location = (bend_points[0] + bend_points[size - 1]) / 2;


#ifdef _STAGE_BUILDER
	Location vector;

	for (auto line : lines)
	{
		vector = line->ColliderBase::GetLocation() - location;
		vector_to_line.push_back(vector);
	}

	for (auto bend_point : this->bend_points)
	{
		vector = bend_point->GetLocation() - location;
		vector_to_bend_point.push_back(vector);
	}

	pivot.SetLocation(location);
	old_location = location;
#endif
}

//-------------------------------------
// コンストラクタ 引数：円のベクター配列
//-------------------------------------
PolyLine::PolyLine(const vector<SphereCollider*> spheres)
{
	collider_type = (int)COLLIDER::POLY_LINE;
	for (int i = 0; i < spheres.size(); i++)
	{
		bend_points.push_back(new SphereCollider(*spheres[i]));
	}

	for (int i = 0; i < spheres.size() - 1; i++)
	{
		lines.push_back(new LineCollider(
			spheres[i]->GetLocation(), spheres[i + 1]->GetLocation()
		));
	}

	location = (bend_points[0]->GetLocation() +
		bend_points[bend_points.size() - 1]->GetLocation()) / 2;

	MakeLocation();

#ifdef _STAGE_BUILDER
	Location vector;

	for (auto line : lines)
	{
		vector = line->ColliderBase::GetLocation() - location;
		vector_to_line.push_back(vector);
	}

	for (auto bend_point : this->bend_points)
	{
		vector = bend_point->GetLocation() - location;
		vector_to_bend_point.push_back(vector);
	}


	pivot.SetLocation(location);
	old_location = location;
#endif
}

//-------------------------------------
// コピーコンストラクタ 
//-------------------------------------
PolyLine::PolyLine(const PolyLine& poly_line)
{
	collider_type = (int)COLLIDER::POLY_LINE;
	for (auto it : poly_line.bend_points)
	{
		this->bend_points.push_back(new SphereCollider(*it));
	}

	for (auto it : poly_line.lines)
	{
		this->lines.push_back(new LineCollider(*it));
	}

	location = poly_line.GetLocation();

#ifdef _STAGE_BUILDER

	pivot = poly_line.pivot;
	for (auto vector : poly_line.vector_to_line)
	{
		vector_to_line.push_back(vector);
	}
	for (auto vector : poly_line.vector_to_bend_point)
	{
		vector_to_bend_point.push_back(vector);
	}

	old_location = location;
#endif
}

//---------------------------------
// デストラクタ
//---------------------------------
PolyLine::~PolyLine()
{
	for (int i = 0; i < bend_points.size(); i++)
	{
		delete bend_points[i];
	}
	bend_points.clear();

	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	lines.clear();

	vector_to_line.clear();
	vector_to_bend_point.clear();
}

//---------------------------------
// 更新
//---------------------------------
void PolyLine::Update()
{
#ifdef _STAGE_BUILDER
	bool did_bend_points_move = false;

	if (location != old_location)
	{
		for (int i = 0; i < bend_points.size(); i++)
		{
			bend_points[i]->SetLocation(location + vector_to_bend_point[i]);
		}
	}

	if (pivot.GetLocation() != old_location)
	{
		for (int i = 0; i < bend_points.size(); i++)
		{
			bend_points[i]->SetLocation(pivot.GetLocation() + vector_to_bend_point[i]);
		}
	}

	MakeLocation();
	
	for (int i = 0; i < bend_points.size(); i++)
	{
		vector_to_bend_point[i]
			= bend_points[i]->GetLocation() - pivot.GetLocation();
	}

	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->SetLocation(bend_points[i]->GetLocation(), LINE_START);
		lines[i]->SetLocation(bend_points[i + 1]->GetLocation(), LINE_END);
	}
	
	old_location = location;

#endif
}

//-------------------------------------
// 描画
//-------------------------------------
void PolyLine::Draw()const
{
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->Draw();
	}

	for (auto it : bend_points)
	{
		it->Draw();
	}

#ifdef _STAGE_BUILDER

	pivot.Draw();

#endif
}

//---------------------------------
// SphereColliderとの当たり判定
//---------------------------------
bool PolyLine::HitSphere(const class SphereCollider* sphere_collider)const
{
	bool is_hit = false;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitSphere(sphere_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//---------------------------------
// BoxColliderとの当たり判定
//---------------------------------
bool PolyLine::HitBox(const class BoxCollider* box_collider)const
{
	bool is_hit = false;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitBox(box_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//---------------------------------
// LineColliderとの当たり判定
//---------------------------------
bool PolyLine::HitLine(const class LineCollider* line_collider)const
{
	bool is_hit = false;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i]->HitLine(line_collider))
		{
			return true;
		}
	}

	return is_hit;
}

//----------------------------------
// PolyLineとの当たり判定
//----------------------------------
bool PolyLine::HitPolyLine(const PolyLine* poly_line)const
{
	bool is_hit = false;
	const vector<LineCollider*>* arg_lines = poly_line->GetLines();

	for (auto line : lines)
	{
		for (auto arg_line : *arg_lines)
		{
			if (line->HitLine(arg_line))
			{
				is_hit = true;
				break;
			}
		}		
	}

	return is_hit;
}

//-------------------------------
// 当たり判定チェック
//------------------------------
bool PolyLine::HitCheck(ColliderBase* collider)const
{
	bool is_hit = false;

	int class_type = collider->GetName();
	switch (class_type)
	{
	case (int)COLLIDER::DEFAULT:
		is_hit = HitBox(static_cast<BoxCollider*>(collider));
		break;

	case (int)COLLIDER::SPHERE:
		is_hit = HitSphere(static_cast<SphereCollider*>(collider));
		break;

	case (int)COLLIDER::BOX:
		is_hit = HitBox(static_cast<BoxCollider*>(collider));
		break;

	case (int)COLLIDER::LINE:
		is_hit = HitLine(static_cast<LineCollider*>(collider));
		break;

	case (int)COLLIDER::POLY_LINE:
		collider = static_cast<PolyLine*>(collider);
		is_hit = HitPolyLine(static_cast<PolyLine*>(collider));
		break;

	default:
		break;
	}

	return is_hit;
}

//---------------------------------
// 点の削除
//---------------------------------
void PolyLine::DeleteBendPoint(int index)
{
	delete bend_points[index];
	bend_points.erase(bend_points.begin() + index);

	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	lines.clear();

	if (2 <= bend_points.size())
	{
		for (int i = 0; i < bend_points.size() - 1; i++)
		{
			lines.push_back(new LineCollider(bend_points[i]->GetLocation(),
				bend_points[i + 1]->GetLocation()));
		}
	}
}

//---------------------------------------
// 中心座標の計算、再計算
//---------------------------------------
void PolyLine::MakeLocation()
{
	Location points[2] =
	{
		bend_points[0]->GetLocation(),
		bend_points[bend_points.size() - 1]->GetLocation()
	};
	Location middle = (points[0] + points[1]) / 2;

	location = middle;

#ifdef _STAGE_BUILDER
	/*for (int i = 0; i < bend_points.size(); i++)
	{
		vector_to_bend_point[i] = bend_points[i]->GetLocation() - location;
	}*/
	pivot.SetLocation(middle);
#endif
}