#include <stdlib.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main() {
	const char caster[] = "cccaster.v3.1.exe";
	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(screenWidth, screenHeight, "caster-gui");

	Vector2 mousePosition = { 0 };
	Vector2 windowPosition = { 500, 200 };
	Vector2 panOffset = mousePosition;
	bool dragWindow = false;

	SetWindowPosition(windowPosition.x, windowPosition.y);

	bool exitWindow = false;

	SetTargetFPS(60);
	char host[1024] = "";
	char spectate[1024] = "";
	int host_state = STATE_NORMAL;
	int spectate_state = STATE_NORMAL;

	Rectangle host_bounds = {200, 200, 300, 30};
	Rectangle spectate_bounds = {200, 300, 300, 30};

	while (!exitWindow && !WindowShouldClose()) {

		mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !dragWindow) {
			if (CheckCollisionPointRec(mousePosition, (Rectangle){ 0, 0, screenWidth, 20 })) {
				dragWindow = true;
				panOffset = mousePosition;
			}
		}

		if (dragWindow) {
			windowPosition.x += (mousePosition.x - panOffset.x);
			windowPosition.y += (mousePosition.y - panOffset.y);

			SetWindowPosition((int)windowPosition.x, (int)windowPosition.y);

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);

		exitWindow = GuiWindowBox((Rectangle){ 0, 0, screenWidth, screenHeight }, "#198# CASTER-GUI");

		DrawText(TextFormat("IP:Port"), 10, 200, 30, DARKGRAY);
		GuiTextBox(host_bounds, host, 1024, host_state);
		if (GuiButton((Rectangle) {500, 200, 80, 30}, "Connect/Host")) {
			system(TextFormat("START /B %s -n %s", caster, host));
			memset(host, '\0', strlen(host));
		}
		if (GuiButton((Rectangle) {580, 200, 60, 30}, "Paste")) {
			strcpy(host, GetClipboardText());
			system(TextFormat("START /B %s -n %s", caster, host));
			memset(host, '\0', strlen(host));
		}
		if (CheckCollisionPointRec(mousePosition, host_bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			host_state = STATE_FOCUSED;
			spectate_state = STATE_NORMAL;
		}

		DrawText(TextFormat("Spectate"), 10, 300, 30, DARKGRAY);
		GuiTextBox(spectate_bounds, spectate, 1024, spectate_state);
		if (GuiButton((Rectangle) {500, 300, 80, 30}, "Connect")) {
			system(TextFormat("START /B %s -ns %s", caster, spectate));
			memset(spectate, '\0', strlen(spectate));
		}
		if (GuiButton((Rectangle) {580, 300, 60, 30}, "Paste")) {
			strcpy(spectate, GetClipboardText());
			system(TextFormat("START /B %s -ns %s", caster, spectate));
			memset(spectate, '\0', strlen(spectate));
		}
		if (CheckCollisionPointRec(mousePosition, spectate_bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			spectate_state = STATE_FOCUSED;
			host_state = STATE_NORMAL;
		}

		DrawText(TextFormat("Offline"), 10, 400, 30, DARKGRAY);
		if (GuiButton((Rectangle) {200, 400, 80, 30}, "Training")) {
			system(TextFormat("START /B %s -not", caster));
		}

		if (!CheckCollisionPointRec(mousePosition, host_bounds) &&
				!CheckCollisionPointRec(mousePosition, spectate_bounds) &&
				IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			host_state = STATE_NORMAL;
			spectate_state = STATE_NORMAL;
		}
		EndDrawing();

	}

	CloseWindow();
	return 0;
}
