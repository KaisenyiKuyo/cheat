#pragma once

#define ARGB(a, r, g, b) 0 | a << 24 | r << 16 | g << 8 | b
#define M_PI 3.14159265358979323846
const float ESP_BOX_WIDTH = 100.0f; // Chiều rộng cố định
const float ESP_BOX_HEIGHT = 200.0f;

float Rainbow() {
	static float x = 0, y = 0;
	static float r = 0, g = 0, b = 0;
	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	} else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	} else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	} else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	} else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	} else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}
	x+= 0.25f; 
	if (x >= 255.0f)
		x = 0.0f;
	y+= 0.25f;
	if (y > 1530.0f)
		y = 0.0f;
	return ARGB(255, (int)r, (int)g, (int)b);
}

class ESP {
	public:
	
	void drawText(const char *text, float X, float Y, float size, long color) {
		ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(X, Y), color, text);
	}
	
	void drawLine(float startX, float startY, float stopX, float stopY, float thicc, long color) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(startX, startY), ImVec2(stopX, stopY), color, thicc);
	}
	
	void drawBorder(float X, float Y, float width, float height, float thicc, long color) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + width, Y + height), color, thicc);
	}
	
	void drawBox(float X, float Y, float width, float height, float thicc, long color) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + width, Y + height), color, thicc);
	}
	
	void drawCornerBox(int x, int y, int w, int h, float thickness, long color) {
		int iw = w / 4;
		int ih = h / 4;
		
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + iw, y), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + ih), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - 1, y), ImVec2(x + w - 1, y + ih), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + iw, y + h), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - iw, y + h), ImVec2(x + w, y + h), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thickness);
	}
};

void drawFixedESPBox(ImDrawList *draw, ImVec2 centerPos) {
    ImVec2 min = ImVec2(centerPos.x - ESP_BOX_WIDTH / 2, centerPos.y - ESP_BOX_HEIGHT / 2);
    ImVec2 max = ImVec2(centerPos.x + ESP_BOX_WIDTH / 2, centerPos.y + ESP_BOX_HEIGHT / 2);
    draw->AddRect(min, max, IM_COL32(255, 255, 255, 255), 0.0f, 0, 1.0f); // Vẽ hộp với màu trắng và độ dày 1.0f
}


bool isOutsideScreen(ImVec2 pos, ImVec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

void DrawCd(ImDrawList *draw, ImVec2 position, float size, ImU32 color, int cd){
	ImVec2 points[4] = {
        	ImVec2(position.x - size, position.y),
        	ImVec2(position.x, position.y - size),
        	ImVec2(position.x + size, position.y),
        	ImVec2(position.x, position.y + size)
    };
    if(cd == 0){
		draw->AddConvexPolyFilled(points, 4, color);
	
	}else{
		
		//draw->AddConvexPolyFilled(points, 4, IM_COL32(255, 255, 255, 255));
		auto textSize = ImGui::CalcTextSize(std::to_string(cd).c_str(), 0, ((float) kHeight / 30.0f));
		draw->AddText(ImGui::GetFont(), ((float) kHeight / 30.0f), {position.x - (textSize.x / 2 ) , position.y - (textSize.y / 2) }, ImColor(0, 255, 0, 255), std::to_string(cd).c_str());
	}
}

ImVec2 pushToScreenBorder(ImVec2 Pos, ImVec2 screen, int offset) {
    int x = (int) Pos.x;
    int y = (int) Pos.y;
	
    if (Pos.y < 0) {
        y = -offset;
    }
	
    if (Pos.x > screen.x) {
        x = (int) screen.x + offset;
    }
	
    if (Pos.y > screen.y) {
        y = (int) screen.y + offset;
    }
	
    if (Pos.x < 0) {
        x = -offset;
    }
    return ImVec2(x, y);
}

void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}

void DrawCircleHealth2(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 1.7);
}

Color colorByDistance(int distance, float alpha){
    Color _colorByDistance;
    if (distance < 450)
        _colorByDistance = Color(255,0,0, alpha);
    if (distance < 200)
        _colorByDistance = Color(255,0,0, alpha);
    if (distance < 121)
        _colorByDistance = Color(0,10,51, alpha);
    if (distance < 51)
        _colorByDistance = Color(0,67,0, alpha);
    return _colorByDistance;
}
Vector2 pushToScreenBorder(Vector2 Pos, Vector2 screen, int offset) {
    int X = (int)Pos.x;
    int Y = (int)Pos.y;
    if (Pos.y < 50) {
        // top
        Y = 42 - offset;
    }
     if (Pos.x > screen.x) {
        // right
        X =  (int)screen.x + offset;
    }
    if (Pos.y > screen.y) {
        // bottom
        Y = (int)screen.y +  offset;
    }
    if (Pos.x < 60) {
        // left
        X = 20 - offset;
    }
    return Vector2(X, Y);
}
bool isOutsideSafeZone(Vector2 pos, Vector2 screen) {
    if (pos.y < 60) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 50;
    
}
int countEnemiesInRange(float range) {
    if (espManager->MyPlayer == NULL) {
        return 0; // Không có người chơi chính
    }

    // Vector3 myPosition = ActorLinker_getPosition(espManager->MyPlayer);
    int enemyCount = 0;

    for (int i = 0; i < espManager->enemies->size(); i++) {

      void *Enemy = (*espManager->enemies)[i]->object;

		void *actorLinker = espManager->MyPlayer;
		
        if (Enemy != nullptr) {
                                            Vector3 EnemyPos = Vector3::zero();

                                    VInt3* locationPtr = (VInt3*)((uint64_t)Enemy + 0xC0); // Giả sử location ở offset 0xC0
                        VInt3* forwardPtr = (VInt3*)((uint64_t)Enemy + 0xCC); // Giả sử forward ở offset 0xCC (thay đổi offset nếu cần)

                                Vector3 myPos = ActorLinker_getPosition(actorLinker);
                        EnemyPos = VInt2Vector(*locationPtr,*forwardPtr);

            // Vector3 enemyPosition = ActorLinker_getPosition(enemy);
            // EnemyPos = VInt2Vector(LActorRoot_get_location(Enemy), LActorRoot_get_forward(Enemy));
            // Tính khoảng cách giữa người chơi và kẻ địch
                        float distanceToMe = Vector3::Distance(myPos, EnemyPos);            // float distance = Vector3::Distance(myPosition, EnemyPos);
            if (distanceToMe <= range) {
                enemyCount++;
            }
        }
    }
    return enemyCount;
}
