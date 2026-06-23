#include "raylib.h"

enum GameState {
    MENU,
    GAME,
    GAMEOVER
};

int main() {
    const int W = 800;
    const int H = 600;

    InitWindow(W, H, "C For Cpeed");
    SetTargetFPS(60);

    GameState state = MENU;

    Rectangle player = { 375, 500, 50, 80 };
    Rectangle enemy = { 375, -100, 50, 80 };

    float playerSpeed = 6.0f;
    float enemySpeed = 5.0f;

    int score = 0;

    while (!WindowShouldClose()) {

        switch (state) {

        case MENU:

            if (IsKeyPressed(KEY_ENTER)) {
                player.x = 375;
                enemy.y = -100;
                score = 0;
                state = GAME;
            }

            break;

        case GAME:

            if (IsKeyDown(KEY_LEFT))
                player.x -= playerSpeed;

            if (IsKeyDown(KEY_RIGHT))
                player.x += playerSpeed;

            // Keep player on road
            if (player.x < 200)
                player.x = 200;

            if (player.x > 550)
                player.x = 550;

            enemy.y += enemySpeed;

            if (enemy.y > H) {
                enemy.y = -100;
                enemy.x = (float)(220 + GetRandomValue(0, 300));
                score++;
            }

            if (CheckCollisionRecs(player, enemy)) {
                state = GAMEOVER;
            }

            break;

        case GAMEOVER:

            if (IsKeyPressed(KEY_R)) {
                player.x = 375;
                enemy.x = 375;
                enemy.y = -100;
                score = 0;
                state = GAME;
            }

            break;
        }

        BeginDrawing();
        ClearBackground(BROWN);

        switch (state) {

        case MENU:

            DrawText("2D RACING GAME", 250, 200, 40, BLACK);
            DrawText("Press ENTER to Start", 260, 300, 25, BLACK);
            DrawText("ESC to Quit", 310, 350, 20, BLACK);

            break;

        case GAME:

            // Road
            DrawRectangle(200, 0, 400, H, GRAY);

            // Lane markers
            for (int y = 0; y < H; y += 80) {
                DrawRectangle(395, y, 10, 40, WHITE);
            }

            // Player car
            DrawRectangleRec(player, BLUE);

            // Enemy car
            DrawRectangleRec(enemy, RED);

            DrawText(TextFormat("Score: %i", score), 20, 20, 30, WHITE);

            break;

        case GAMEOVER:

            DrawText("GAME OVER", 250, 200, 50, RED);
            DrawText(TextFormat("Score: %i", score), 320, 280, 30, BLACK);
            DrawText("Press R to Restart", 260, 350, 30, BLACK);

            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
