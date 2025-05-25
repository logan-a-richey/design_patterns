// flyweight.cpp

#include <iostream>
#include <unordered_map>
#include <memory>

// Flyweight class
class Character {
public:
    Character(char intrinsicState) : m_intrinsicState(intrinsicState) {}

    void draw(int extrinsicState) const {
        std::cout   << "Drawing character '" << m_intrinsicState 
                    << "' at position " << extrinsicState << std::endl;
    }

private:
    char m_intrinsicState;
};

// Flyweight factory
class CharacterFactory {
public:
    Character* getCharacter(char key) {
        if (m_characters.find(key) == m_characters.end()) {
            m_characters[key] = std::make_unique<Character>(key);
        }
        return m_characters[key].get(); // Return raw pointer
    }

private:
    std::unordered_map<char, std::unique_ptr<Character>> m_characters;
};

int main() {
    CharacterFactory characterFactory;
    int position = 0;

    characterFactory.getCharacter('A')->draw(position++);
    characterFactory.getCharacter('B')->draw(position++);
    characterFactory.getCharacter('C')->draw(position++);
    characterFactory.getCharacter('A')->draw(position++); // Reuses 'A'

    return 0;
}

