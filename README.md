# 2D Platformer Game in C++ with SFML

A complete 2D platformer game featuring character physics, enemy AI, collectibles, and camera system.

## 🎮 Game Features
- **Character Physics**: Movement, jumping, gravity simulation
- **Platform System**: Multiple platforms with collision detection
- **Enemy AI**: Patrolling enemies with simple AI
- **Collectibles**: Coins to collect for score
- **Camera System**: Smooth camera following the player
- **Game States**: Menu, gameplay, game over with restart
- **Score System**: Real-time score tracking

## 🕹️ Controls
- **A** - Move Left
- **D** - Move Right  
- **SPACE** - Jump
- **R** - Restart (when game over)

## 🏗️ Technical Architecture
### Object-Oriented Design
- `Player`: Character physics and movement
- `Platform`: Walkable surfaces with collision
- `Coin`: Collectible items with collision detection
- `Enemy`: AI-driven enemies with patrol behavior
- `Game`: Main game loop and state management

### Physics System
- Gravity simulation with variable strength
- Jump mechanics with ground detection
- Velocity-based movement with damping
- Axis-Aligned Bounding Box (AABB) collision detection

### Rendering Pipeline
- SFML-based rendering with layered drawing
- Camera view for world navigation
- UI overlay for score and game states
- Color-coded game objects for visual clarity

## 📊 Game Objects
- **Player**: Blue rectangle (30x50 pixels)
- **Platforms**: Green rectangles (various sizes)
- **Coins**: Yellow circles with orange outline (10 points each)
- **Enemies**: Red squares with patrol AI

## 🎯 Game Mechanics
1. **Movement**: Horizontal movement with acceleration
2. **Jumping**: Vertical velocity with gravity
3. **Collision**: Platform, coin, and enemy detection
4. **Scoring**: 10 points per collected coin
5. **Game Over**: Player-enemy collision ends game
6. **Restart**: Complete game state reset

## 🔧 Code Highlights
```cpp
// Character physics update
void Player::update() {
    velocity.y += gravity;  // Apply gravity
    body.move(velocity);    // Update position
    
    // Ground collision
    if (body.getPosition().y > 550) {
        setOnGround(true);
    }
}

// Camera following system
void Game::updateCamera() {
    sf::Vector2f playerPos = player.getPosition();
    camera.setCenter(playerPos.x + 150, 300); // Offset view
}
```

##🚀 What I Learned
- 2D game physics implementation
- Collision detection algorithms (AABB)
- Camera systems for platformers
- Enemy AI design and implementation
- Game state management patterns
- SFML viewport and coordinate systems
- Object-oriented game architecture

##📈 Performance Features
- Frame-rate independent movement (60 FPS)
- Efficient collision checking
- Minimal object creation/destruction
- Smart camera bounds checking

##🎨 Visual Design
- Sky blue background (#87CEEB)
- Color-coded game elements for clarity
- Clean UI with score display
- Responsive visual feedback

##🔮 Future Improvements
- Animated sprites instead of shapes
- Sound effects and background music
- Multiple levels with increasing difficulty
- Power-ups and special abilities
- Particle effects for jumps and collisions
- Save system for high scores
- Level editor for custom platforms

##🛠️ Build Instructions
- Install SFML and configure include/library paths
- Build with Visual Studio (x64, Debug)
- Copy SFML DLLs to executable directory
- Ensure font file is available or modify code

##🎯 Real-World Applications
- Game engine development fundamentals
- Physics simulation for interactive applications
- AI programming for game characters
- User interface design for games
- Software architecture for real-time systems

##🔗 Connect
- Portfolio: https://escapeesctr.github.io/my-portfolio/
- LinkedIn: https://www.linkedin.com/in/melihenesaktas/
- GitHub: @escapeesctr
