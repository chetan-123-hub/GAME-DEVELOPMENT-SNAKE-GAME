#include <SFML/Graphics.hpp>
#include <vector>

struct SnakeSegment {
    int x, y;
    SnakeSegment(int x, int y) : x(x), y(y) {}
};

int main() {
    const int width = 800;
    const int height = 600;
    const int gridSize = 20;
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");
    sf::Clock clock;
    float timer = 0, delay = 0.1;

    std::vector<SnakeSegment> snake = { {10, 10} };
    int dirX = 1, dirY = 0;
    int foodX = rand() % (width / gridSize);
    int foodY = rand() % (height / gridSize);

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        // Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { dirX = 0; dirY = -1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { dirX = 0; dirY = 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { dirX = -1; dirY = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { dirX = 1; dirY = 0; }

        // Move Snake
        if (timer > delay) {
            timer = 0;
            for (int i = snake.size() - 1; i > 0; --i)
                snake[i] = snake[i - 1];

            snake[0].x += dirX;
            snake[0].y += dirY;

            // Check food
            if (snake[0].x == foodX && snake[0].y == foodY) {
                snake.push_back(snake.back());
                foodX = rand() % (width / gridSize);
                foodY = rand() % (height / gridSize);
            }
        }

        // Draw
        window.clear();

        sf::RectangleShape cell(sf::Vector2f(gridSize - 2, gridSize - 2));
        cell.setFillColor(sf::Color::Green);

        for (auto& s : snake) {
            cell.setPosition(s.x * gridSize, s.y * gridSize);
            window.draw(cell);
        }

        cell.setFillColor(sf::Color::Red);
        cell.setPosition(foodX * gridSize, foodY * gridSize);
        window.draw(cell);

        window.display();
    }

    return 0;
}
