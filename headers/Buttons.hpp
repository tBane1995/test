#ifndef Buttons_hpp
#define Buttons_hpp

sf::Color idleColor = sf::Color(32.0f, 32.0f, 32.0f);
sf::Color hoverColor = sf::Color(48.0f, 48.0f, 48.0f);
sf::Color pressedColor = sf::Color(64.0f, 64.0f, 64.0f);

sf::Color spriteIdleColor = sf::Color(192.0f, 192.0f, 192.0f);
sf::Color spriteHoverColor = sf::Color(224.0f, 224.0f, 224.0f);
sf::Color spritePressedColor = sf::Color::White;

enum class ButtonState { Idle, Hover, Pressed };

class Btn {
public:

    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> func;
    sf::Time clickTime;

    Btn(float width = 64, float height = 64, sf::Vector2f position = sf::Vector2f(0, 0)) {

        this->position = position;

        rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setOrigin(width / 2, height / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();

        state = ButtonState::Idle;
        func = { };

        clickTime = currentTime;

        changeColor();
    }

    Btn(Btn* btn) {

        this->position = btn->position;

        this->rect = btn->rect;
        this->sprite = btn->sprite;

        state = ButtonState::Idle;
        this->func = btn->func;

        clickTime = currentTime;

        changeColor();
    }

    Btn(Btn* btn, sf::Vector2f position) {

        this->position = position;

        this->rect = btn->rect;
        this->rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        this->sprite = btn->sprite;
        this->sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        this->func = btn->func;

        clickTime = currentTime;

        changeColor();
    }

    Btn(Texture* texture, sf::Vector2f position) {

        this->position = position;

        sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
        rect = sf::RectangleShape(size);
        rect.setOrigin(size.x / 2, size.y / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
        sprite.setScale(scale);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;

        func = { };

        clickTime = currentTime;

        changeColor();
    }

    virtual void setTexture(Texture* texture) {
        sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
        rect = sf::RectangleShape(size);
        rect.setOrigin(size.x / 2, size.y / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
        sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
        sprite.setScale(scale);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        changeColor();
    }

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    }

    virtual void changeColor() {

        if (state == ButtonState::Pressed) {
            rect.setFillColor(pressedColor);
            sprite.setColor(spritePressedColor);
        }
        else if (state == ButtonState::Hover) {
            rect.setFillColor(hoverColor);
            sprite.setColor(spriteHoverColor);
        }
        else {
            rect.setFillColor(idleColor);
            sprite.setColor(spriteIdleColor);
        }

    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {
            state = ButtonState::Idle;
            changeColor();
        }

    }

    virtual bool hover() {
        if (state != ButtonState::Pressed) {

            float w = rect.getSize().x;
            float h = rect.getSize().y;
            float x = rect.getPosition().x;
            float y = rect.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                state = ButtonState::Hover;
                changeColor();
                GUIwasHover = true;
                return true;
            }
        }
        else {
            // GUI WAS PRESSED
            GUIwasHover = true;
            return true;
        }

        return false;
    }

    virtual bool click() {
        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

            state = ButtonState::Pressed;
            changeColor();
            GUIwasClicked = true;
            clickTime = currentTime;

            if (func)
                func();

            return true;
        }

        return false;
    }

    virtual void update(float dt) {
        rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    }

    virtual void draw() {
        window->draw(rect);
        if (sprite.getTexture() != nullptr)
            window->draw(sprite);
    }
};

class ButtonWithText {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Text text;
    ButtonState state;
    std::function<void()> func;
    sf::Time clickTime;
    short margin;

    ButtonWithText(string s, sf::Vector2f position = sf::Vector2f(0, 0), short characterSize = 17) {

        this->position = position;
        margin = float(characterSize) * 0.4f;

        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(characterSize);
        text.setString(s);
        text.setPosition(position.x + cam->position.x + float(margin)*0.95f, position.y + cam->position.y + float(margin) * 0.6f);

        rect = sf::RectangleShape();
        sf::Vector2f size;
        size.x = text.getLocalBounds().getSize().x + float(margin)*2.15f;
        size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        rect.setSize(size);
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        func = { };

        clickTime = currentTime;
    }

    ButtonWithText(string s, short characterSize) {

        this->position = sf::Vector2f(0,0);
        margin = float(characterSize) * 0.4f;

        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(characterSize);
        text.setString(s);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);

        rect = sf::RectangleShape();
        sf::Vector2f size;
        size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f;
        size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        rect.setSize(size);
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        func = { };

        clickTime = currentTime;
    }

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        text.setPosition(position.x + cam->position.x + margin, position.y + cam->position.y + float(margin) * 0.6f);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    }

    virtual void changeColor() {

        if (state == ButtonState::Pressed) {
            rect.setFillColor(pressedColor);
        }
        else if (state == ButtonState::Hover) {
            rect.setFillColor(hoverColor);
        }
        else {
            rect.setFillColor(idleColor);
        }

    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {
            state = ButtonState::Idle;
            changeColor();
        }

    }

    virtual bool hover() {
        if (state != ButtonState::Pressed) {

            float x1 = rect.getPosition().x;
            float x2 = x1 + rect.getSize().x;
            float y1 = rect.getPosition().y;
            float y2 = y1 + rect.getSize().y;

            if (worldMousePosition.x > x1 && worldMousePosition.x < x2 &&
                worldMousePosition.y > y1 && worldMousePosition.y < y2) {

                state = ButtonState::Hover;
                changeColor();
                GUIwasHover = true;
                return true;
            }
        }
        else {
            // GUI WAS PRESSED
            GUIwasHover = true;
            return true;
        }

        return false;
    }

    virtual bool click() {

        float x1 = rect.getPosition().x;
        float x2 = x1 + rect.getSize().x;
        float y1 = rect.getPosition().y;
        float y2 = y1 + rect.getSize().y;

        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 &&
            worldMousePosition.y > y1 && worldMousePosition.y < y2) {

            state = ButtonState::Pressed;
            changeColor();
            GUIwasClicked = true;
            clickTime = currentTime;

            if (func)
                func();

            return true;
        }

        return false;
    }

    virtual void update(float dt) {
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);
    }

    virtual void draw() {

        window->draw(rect);
        window->draw(text);
    }

};





#endif