#include "Game.h"
#include <iostream>

// 생성자
Game::Game(WINDOW* win, int stage) : game_win(win), stage(stage), score(0), isGameOver(false), direction(LEFT), keyPressed(false) {
    initializeStage();
}

// 초기화 메서드
void Game::initializeStage() {
    score = 0;
    switch(stage) {
        case 1:
            snake = Snake(Position(10, 10), 3, LEFT);
            break;
        case 2:
            snake = Snake(Position(5, 5), 3, LEFT);
            break;
        case 3:
            snake = Snake(Position(10, 10), 3, LEFT);
            break;
        case 4:
            snake = Snake(Position(16, 18), 3, LEFT);
            break;
        default:
            snake = Snake(Position(10, 10), 3, LEFT); // 기본값
            break;
    }

    map.setMap(stage); // stageNum에 따른 맵 설정
    setSnake();

    item1 = ItemSetting(map).makeItem(1);
    item2 = ItemSetting(map).makeItem(2);
    item3 = ItemSetting(map).makeItem(3);
    setItem();

    gateSpawned = false; // 초기 상태로 설정
    setGate();
}


// 설정자
void Game::setSnake() {
    // head 설정
    map.setPositionInfo(snake.getHeadPosition().getPositionX(), snake.getHeadPosition().getPositionY(), HEAD);

    // tail 설정
    for (const Position &part : snake.getSnakeBody()) {
        if (part.getPositionX() == snake.getHeadPosition().getPositionX() &&
            part.getPositionY() == snake.getHeadPosition().getPositionY()) {
            continue; // 머리와 같은 위치인 경우 생략
        }
        map.setPositionInfo(part.getPositionX(), part.getPositionY(), TAIL);
    }
}

void Game::setItem() {
    // 최소 한 개의 독 아이템과 성장 아이템을 생성
    do {
        item1 = ItemSetting(map).makeItem(POISON);
    } while (map.getPositionInfo(item1.getItemPosition().getPositionX(), item1.getItemPosition().getPositionY()) != 0);

    do {
        item2 = ItemSetting(map).makeItem(GROWTH);
    } while (map.getPositionInfo(item2.getItemPosition().getPositionX(), item2.getItemPosition().getPositionY()) != 0);

    map.setPositionInfo(item1.getItemPosition().getPositionX(), item1.getItemPosition().getPositionY(), item1.getType());
    map.setPositionInfo(item2.getItemPosition().getPositionX(), item2.getItemPosition().getPositionY(), item2.getType());
    map.setPositionInfo(item3.getItemPosition().getPositionX(), item3.getItemPosition().getPositionY(), item3.getType());
}


void Game::setGate() {
    gate1 = ItemSetting(map).makeGate(1);
    gate2 = ItemSetting(map).makeGate(2);
    
    map.setPositionInfo(gate1.getItemPosition().getPositionX(), gate1.getItemPosition().getPositionY(), gate1.getType());
    map.setPositionInfo(gate2.getItemPosition().getPositionX(), gate2.getItemPosition().getPositionY(), gate2.getType());
    
    gateSpawned = true;
}

// 화면 랜더링
void Game::render() {
    int height = map.getHeight();
    int width = map.getWidth();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = map.getPositionInfo(j, i);
            switch (value) {
                case 0:
                    mvwaddch(game_win, i, j*2, ' ' | COLOR_PAIR(1));
                    break;
                case 1:
                    mvwaddch(game_win, i, j*2, '#' | COLOR_PAIR(1));
                    break;
                case 2:
                    mvwaddch(game_win, i, j*2, '#' | COLOR_PAIR(1));
                    break;
                case POISON:
                    mvwaddch(game_win, i, j*2, 'p' | COLOR_PAIR(2));
                    break;
                case GROWTH:
                    mvwaddch(game_win, i, j*2, 'g' | COLOR_PAIR(2));
                    break;
                case GATE:
                    mvwaddch(game_win, i, j*2, 'G' | COLOR_PAIR(4));
                    break;
                case DESTINATION:
                    mvwaddch(game_win, i, j*2, 'D' | COLOR_PAIR(3));
                    break;
                case HEAD:
                    mvwaddch(game_win, i, j*2, '0' | COLOR_PAIR(5));
                    break;
                case TAIL:
                    mvwaddch(game_win, i, j*2, 'O' | COLOR_PAIR(5));
                    break;
                default:
                    mvwaddch(game_win, i, j*2, ' ' | COLOR_PAIR(1));
                    break;
            }
        }
    }
    refresh();
}

void Game::update() {
    // snake의 머리 다음 위치 계산
    Position nextHead = snake.getHeadPosition();
    switch (snake.getSnakeDirection()) {
        case UP:
            nextHead.setPosition(nextHead.getPositionX(), nextHead.getPositionY() - 1);
            break;
        case DOWN:
            nextHead.setPosition(nextHead.getPositionX(), nextHead.getPositionY() + 1);
            break;
        case LEFT:
            nextHead.setPosition(nextHead.getPositionX() - 1, nextHead.getPositionY());
            break;
        case RIGHT:
            nextHead.setPosition(nextHead.getPositionX() + 1, nextHead.getPositionY());
            break;
    }
    
    mission(nextHead);

    Position tail = snake.getTailPosition();
    map.setPositionInfo(tail.getPositionX(), tail.getPositionY(), 0);
    snake.move();
    setSnake();
    
    // 점수 증가 로직
    incrementScore();
    
    // Score board
    scoreBoard();
    
    // 디버깅 정보 출력
    printDebugInfo();
}


// Item Method
void Game::modifyLength(int value) {
    // 독 아이템을 먹었을 때
    if (value == POISON) {
        Position tail = snake.getTailPosition();
        map.setPositionInfo(tail.getPositionX(), tail.getPositionY(), 0); // 마지막 꼬리 제거
        snake.removeTail(); // 뱀 객체에서 꼬리 제거
    }
    // 성장 아이템을 먹었을 때
    else if (value == GROWTH) {
        Position tail = snake.getTailPosition();
        Position newTail = Position(tail.getPositionX(), tail.getPositionY());
        snake.addTail(newTail); // 뱀 객체에 꼬리 추가
        map.setPositionInfo(newTail.getPositionX(), newTail.getPositionY(), TAIL); // 맵에 꼬리 추가
    }
}

// 게이트 처리 메서드
void Game::gate(Position nextHead) {
    Position gate1Pos = gate1.getItemPosition();
    Position gate2Pos = gate2.getItemPosition();

    // 첫 번째 게이트에 닿았는지 확인
    if (nextHead.getPositionX() == gate1Pos.getPositionX() && nextHead.getPositionY() == gate1Pos.getPositionY()) {
        snake.setSnakePosition(gate2Pos.getPositionX(), gate2Pos.getPositionY()); // 두 번째 게이트로 이동
        afterGate(nextHead, gate2Pos);
    }
    // 두 번째 게이트에 닿았는지 확인
    else if (nextHead.getPositionX() == gate2Pos.getPositionX() && nextHead.getPositionY() == gate2Pos.getPositionY()) {
        snake.setSnakePosition(gate1Pos.getPositionX(), gate1Pos.getPositionY()); // 첫 번째 게이트로 이동
        afterGate(nextHead, gate1Pos);
    }
}

// 방향을 유지하면서 가능하지 않으면 가능한 방향으로 수정
void Game::afterGate(Position &snakeHead, Position &newGate) {
    int x = newGate.getPositionX();
    int y = newGate.getPositionY();

    switch (snake.getSnakeDirection()) {
        case UP:
            if (y - 1 >= 0 && map.getPositionInfo(x, y - 1) != 1 && map.getPositionInfo(x, y - 1) != 2) {
                snake.updateDirection(UP);
                break;
            }
            // 방향을 수정해야 하는 경우
            if (x + 1 < map.getWidth() && map.getPositionInfo(x + 1, y) != 1 && map.getPositionInfo(x + 1, y) != 2) {
                snake.updateDirection(RIGHT);
            } else if (x - 1 >= 0 && map.getPositionInfo(x - 1, y) != 1 && map.getPositionInfo(x - 1, y) != 2) {
                snake.updateDirection(LEFT);
            } else {
                snake.updateDirection(DOWN);
            }
            break;
        case DOWN:
            if (y + 1 < map.getHeight() && map.getPositionInfo(x, y + 1) != 1 && map.getPositionInfo(x, y + 1) != 2) {
                snake.updateDirection(DOWN);
                break;
            }
            // 방향을 수정해야 하는 경우
            if (x + 1 < map.getWidth() && map.getPositionInfo(x + 1, y) != 1 && map.getPositionInfo(x + 1, y) != 2) {
                snake.updateDirection(RIGHT);
            } else if (x - 1 >= 0 && map.getPositionInfo(x - 1, y) != 1 && map.getPositionInfo(x - 1, y) != 2) {
                snake.updateDirection(LEFT);
            } else {
                snake.updateDirection(UP);
            }
            break;
        case LEFT:
            if (x - 1 >= 0 && map.getPositionInfo(x - 1, y) != 1 && map.getPositionInfo(x - 1, y) != 2) {
                snake.updateDirection(LEFT);
                break;
            }
            // 방향을 수정해야 하는 경우
            if (y - 1 >= 0 && map.getPositionInfo(x, y - 1) != 1 && map.getPositionInfo(x, y - 1) != 2) {
                snake.updateDirection(UP);
            } else if (y + 1 < map.getHeight() && map.getPositionInfo(x, y + 1) != 1 && map.getPositionInfo(x, y + 1) != 2) {
                snake.updateDirection(DOWN);
            } else {
                snake.updateDirection(RIGHT);
            }
            break;
        case RIGHT:
            if (x + 1 < map.getWidth() && map.getPositionInfo(x + 1, y) != 1 && map.getPositionInfo(x + 1, y) != 2) {
                snake.updateDirection(RIGHT);
                break;
            }
            // 방향을 수정해야 하는 경우
            if (y - 1 >= 0 && map.getPositionInfo(x, y - 1) != 1 && map.getPositionInfo(x, y - 1) != 2) {
                snake.updateDirection(UP);
            } else if (y + 1 < map.getHeight() && map.getPositionInfo(x, y + 1) != 1 && map.getPositionInfo(x, y + 1) != 2) {
                snake.updateDirection(DOWN);
            } else {
                snake.updateDirection(LEFT);
            }
            break;
    }
}



// Game Mission method
void Game::mission(Position nextHead) {
    // 맵 경계 검사
    int mapHeight = map.getHeight();
    int mapWidth = map.getWidth();
    if (nextHead.getPositionX() < 0 || nextHead.getPositionX() >= mapWidth ||
        nextHead.getPositionY() < 0 || nextHead.getPositionY() >= mapHeight) {
        gameOver();
        return;
    }

    // 충돌 처리
    int value = map.getPositionInfo(nextHead.getPositionX(), nextHead.getPositionY());
    switch (value) {
        case 1:	// WALL
        case 2:	// IMMUNE WALL
        case 4:	// TAIL
            gameOver();
            return;
        case 5:	// POISON
            modifyLength(5);
            score += 10;
            item1 = ItemSetting(map).makeItem(1);
            setItem();
            break;
        case 6:	// GTOWTH
            modifyLength(6);
            score += 10;
            item2 = ItemSetting(map).makeItem(1);
            setItem();
            break;
        case 7: // GATE
            gate(nextHead);
            return;
        case 8:	// DESTINATION
            gameSuccess();
            return;
        default:
            break;
    }

    // 점수 기반 스테이지 클리어
    if (score >= 50) { // 점수가 50점 이상일 때 스테이지 클리어
        gameSuccess();
        return;
    }    
        
    // least length game over
    if (snake.getSnakeLength() < 3) {
    	gameOver();
        return;
    }
}

// 점수 증가 메서드
void Game::incrementScore() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastScoreUpdateTime).count();

    if (stage < 4 && duration >= 1) {
        score += 2;
        lastScoreUpdateTime = now; // 마지막 점수 업데이트 시간 갱신
    }
}

// Score board method
void Game::scoreBoard() {
    mvwprintw(game_win, 16, 47, "======= Stage %d ======= ", stage);
    mvwprintw(game_win, 17, 47, "=                     = ");
    if (stage < 4)
    mvwprintw(game_win, 18, 47, "=   Score : %2d / 50   =", score);
    else
    mvwprintw(game_win, 18, 47, "=  reach Destination  =");
    mvwprintw(game_win, 19, 47, "=                     = ");
    mvwprintw(game_win, 20, 47, "=======================");
}


// 디버깅 정보를 출력 메서드
void Game::printDebugInfo() {
    // 창의 오른쪽에 디버깅 정보를 출력
    mvwprintw(game_win, 0, 50, "Snake Position Info:");
    int y = 1;
    switch(snake.getSnakeDirection()) {
    	case 11: mvwprintw(game_win, y++, 50, "Directon: %s", "UP   "); break;
    	case 12: mvwprintw(game_win, y++, 50, "Directon: %s", "DOWN "); break;
    	case 13: mvwprintw(game_win, y++, 50, "Directon: %s", "LEFT "); break;
    	case 14: mvwprintw(game_win, y++, 50, "Directon: %s", "RIGHT"); break;
    }
    mvwprintw(game_win, y++, 50, "Length: %d", snake.getSnakeLength());
    mvwprintw(game_win, y++, 50, "Head: (%d, %d)    ", snake.getHeadPosition().getPositionX(), snake.getHeadPosition().getPositionY());

    int partNum = 1;
    for (const Position &part : snake.getSnakeBody()) {
        if (part.getPositionX() == snake.getHeadPosition().getPositionX() &&
            part.getPositionY() == snake.getHeadPosition().getPositionY()) {
            continue; // 머리와 같은 위치인 경우 생략
        }
        mvwprintw(game_win, y++, 50, "Tail %d: (%d, %d)   ", partNum++, part.getPositionX(), part.getPositionY());
    }
    wrefresh(game_win);
}



// 게임 진행
void Game::gameStart() {
    std::thread inputThread(&Game::keyInput, this);

    while (!isGameOver) {
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    inputThread.join();
}

void Game::keyInput() {
    int ch;
    while (!isGameOver) {
        ch = getch();
        if (ch != ERR) {
            keyPressed = true;
            bool invalidMove = false;
            switch (ch) {
                case KEY_UP:
                    if (direction == DOWN) invalidMove = true;
                    else direction = UP;
                    break;
                case KEY_DOWN:
                    if (direction == UP) invalidMove = true;
                    else direction = DOWN;
                    break;
                case KEY_LEFT:
                    if (direction == RIGHT) invalidMove = true;
                    else direction = LEFT;
                    break;
                case KEY_RIGHT:
                    if (direction == LEFT) invalidMove = true;
                    else direction = RIGHT;
                    break;
               	case 27: // Esc: Quit the game
               	    gameOver();
               	    break;
            }
            if (invalidMove) gameOver();
            else snake.updateDirection(direction);
        } else {
            keyPressed = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// 게임 종료
void Game::gameOver() {
    isGameOver = true;
    
    // 새로운 창을 만들어 메시지 출력
    WINDOW* game_over_win = newwin(15, 60, 4, 10);
    box(game_over_win, 0, 0);
    mvwprintw(game_over_win, 7, 26, "Game Over!");
    wrefresh(game_over_win);
    
    nodelay(stdscr, FALSE);
    getch();
    delwin(game_over_win);
    
    endwin();
    exit(0);
}

void Game::gameSuccess() {
    WINDOW* game_success_win = newwin(15, 60, 4, 10);
    box(game_success_win, 0, 0);
    
    if (stage < 4) {
    	mvwprintw(game_success_win, 7, 18, "Stage %d Clear! Proceeding to Stage %d...", stage - 1, stage);
        stage++;
        wrefresh(game_win);
        
        getch();
        delwin(game_success_win);
        
        // std::this_thread::sleep_for(std::chrono::seconds(3));
        initializeStage(); // 초기화 메서드 호출
    }
    else {
    	mvwprintw(game_success_win, 6, 22, "Congratulations!");
    	mvwprintw(game_success_win, 8, 16, "You've completed all stages!");
        wrefresh(game_win);
        wrefresh(game_success_win);
        
        nodelay(stdscr, FALSE);
        getch();
        delwin(game_success_win);
        
        endwin();
        exit(0);
    }
}

