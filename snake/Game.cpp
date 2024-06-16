#include "Game.h"
#include <iostream>

// 생성자
Game::Game(WINDOW* win, int stage) : game_win(win), stage(stage), score(0), isGameOver(false), direction(LEFT), keyPressed(false) {
    // std::cout << "Game Constructor: Stage " << stage << std::endl;
    initializeStage();
}

// 초기화 메서드
void Game::initializeStage() {
    // std::cout << "Initializing Stage " << stage << std::endl;
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
    setItem();

    gateSpawned = false; // 초기 상태로 설정
    startTime = std::chrono::steady_clock::now(); // 게임 시작 시간 설정
    std::cout << "Stage Initialized" << std::endl;
}

// 설정자
void Game::setSnake() {
    std::cout << "Setting Snake" << std::endl;
    for (const Position &part : snake.getSnakeBody()) {
        map.setPositionInfo(part.getPositionX(), part.getPositionY(), TAIL);
    };
    map.setPositionInfo(snake.getHeadPosition().getPositionX(), snake.getHeadPosition().getPositionY(), HEAD);
}

void Game::setItem() {
    std::cout << "Setting Items" << std::endl;
    map.setPositionInfo(item1.getItemPosition().getPositionX(), item1.getItemPosition().getPositionY(), item1.getType());
    map.setPositionInfo(item2.getItemPosition().getPositionX(), item2.getItemPosition().getPositionY(), item2.getType());
}

void Game::setGate() {
    std::cout << "Setting Gate" << std::endl;
    gate = ItemSetting(map).makeGate(3);
    map.setPositionInfo(gate.getItemPosition().getPositionX(), gate.getItemPosition().getPositionY(), gate.getType());
    gateSpawned = true;
}

// 화면 랜더링
void Game::render() {
    int height = map.getHeight();
    int width = map.getWidth();

    // std::cout << "Rendering the screen" << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = map.getPositionInfo(j, i);
            switch (value) {
                case 0:
                    mvwaddch(stdscr, i, j*2, ' ' | COLOR_PAIR(1));
                    break;
                case 1:
                    mvwaddch(stdscr, i, j*2, '#' | COLOR_PAIR(1));
                    break;
                case 2:
                    mvwaddch(stdscr, i, j*2, '#' | COLOR_PAIR(1));
                    break;
                case POISON:
                    mvwaddch(stdscr, i, j*2, 'p' | COLOR_PAIR(2));
                    break;
                case GROWTH:
                    mvwaddch(stdscr, i, j*2, 'g' | COLOR_PAIR(2));
                    break;
                case GATE:
                    mvwaddch(stdscr, i, j*2, 'G' | COLOR_PAIR(4));
                    break;
                case DESTINATION:
                    mvwaddch(stdscr, i, j*2, 'D' | COLOR_PAIR(3));
                    break;
                case HEAD:
                    mvwaddch(stdscr, i, j*2, '0' | COLOR_PAIR(5));
                    break;
                case TAIL:
                    mvwaddch(stdscr, i, j*2, 'O' | COLOR_PAIR(5));
                    break;
                default:
                    mvwaddch(stdscr, i, j*2, ' ' | COLOR_PAIR(1));
                    break;
            }
        }
    }
    refresh();
}

void Game::update() {
    // std::cout << "Updating the game state" << std::endl;

    // snake의 머리 다음 위치 계산
    Position nextHead = snake.getHeadPosition();
    // std::cout << "Next head position: (" << nextHead.getPositionX() << ", " << nextHead.getPositionY() << ")" << std::endl;
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

    // std::cout << "New head position after move: (" << nextHead.getPositionX() << ", " << nextHead.getPositionY() << ")" << std::endl;

    // 충돌 처리
    int value = map.getPositionInfo(nextHead.getPositionX(), nextHead.getPositionY());
    // std::cout << "Next head position value: " << value << std::endl;
    switch (value) {
        case 1:
        case 2:
        case 4:
            gameOver();
            return;
        case 5:
            score += 10;
            item1 = ItemSetting(map).makeItem(1);
            setItem();
            break;
        case 6:
            score += 10;
            item2 = ItemSetting(map).makeItem(2);
            setItem();
            break;
        case 8:
            gameSuccess();
            return;
        default:
            break;
    }

    // 점수 기반 스테이지 클리어
    if (score >= 100) { // 예시: 점수가 100 이상일 때 스테이지 클리어
        gameSuccess();
        return;
    }

    Position tail = snake.getTailPosition();
    map.setPositionInfo(tail.getPositionX(), tail.getPositionY(), 0);
    snake.move();
    snake.setSnakePosition();
}


// 게임 진행
void Game::gameStart() {
    // std::cout << "Game Started" << std::endl;
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
            switch (ch) {
                case KEY_UP:
                    if (direction != DOWN) direction = UP;
                    break;
                case KEY_DOWN:
                    if (direction != UP) direction = DOWN;
                    break;
                case KEY_LEFT:
                    if (direction != RIGHT) direction = LEFT;
                    break;
                case KEY_RIGHT:
                    if (direction != LEFT) direction = RIGHT;
                    break;
            }
            snake.updateDirection(direction);
        } else {
            keyPressed = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// 게임 종료
void Game::gameOver() {
    // std::cout << "Game Over" << std::endl;
    isGameOver = true;
    mvprintw(10, 7, "Failed!");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}

void Game::gameSuccess() {
    if (stage < 4) {
        stage++;
        mvprintw(10, 7, "Stage %d Clear! Proceeding to Stage %d...", stage - 1, stage);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        initializeStage(); // 초기화 메서드 호출
    } else {
        mvprintw(10, 7, "Congratulations! You've completed all stages!");
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        endwin();
        exit(0);
    }
}

