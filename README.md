# QtOpenGLEngine

A simple 3D rendering engine built with Qt and OpenGL, demonstrating basic graphics programming concepts including camera controls, shader management, and 3D object rendering.

## Features

- Modern OpenGL (3.3+) rendering pipeline
- Camera system with mouse and keyboard controls
- Shader-based rendering
- Basic 3D primitive rendering (cubes)
- Resource management system for shaders and styles

## Prerequisites

- Qt 6.x
- CMake 3.16 or higher
- C++17 compatible compiler
- OpenGL 3.3+ compatible graphics card

### Environment variable needed
**Qt6_DIR**=/{}/Qt/6.8.1/gcc_64/lib/cmake/Qt6;
**QT_DIR**=/{}/Qt/6.8.1/gcc_64/lib/cmake/Qt6;
**CMAKE_PREFIX_PATH**=/{}/Qt/6.8.1/gcc_64

## Project Structure

```
QtOpenGLEngine/
├── CMakeLists.txt
├── resources.qrc
├── src/
│   ├── main.cpp
│   ├── renderer/
│   └── ui/
├── shaders/
└── style/
```

## Building

1. Clone the repository
2. Create a build directory:
```bash
mkdir build && cd build
```
3. Configure with CMake:
```bash
cmake ..
```
4. Build the project:
```bash
cmake --build .
```

## Controls

- **Mouse Right Button + Drag**: Rotate the camera view
- **Keyboard Controls**:
   - Z: Move forward
   - S: Move backward
   - Q: Move left
   - D: Move right
   - A: Move up
   - E: Move down
- **Mouse Wheel**: Zoom in/out

## Architecture

### Core Components

- **Renderer**: Main OpenGL widget handling the rendering pipeline
- **Camera**: Manages view transformations and user input for navigation
- **RendererObject**: Base class for all renderable objects
- **Cube**: Example implementation of a renderable object

### Shader System

The engine uses two main shaders:
- **Vertex Shader**: Handles vertex transformations and attribute passing
- **Fragment Shader**: Manages color output and pixel processing

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Submit a pull request

## Future Improvements

- [ ] Add texture support
- [ ] Implement lighting system
- [ ] Add more primitive shapes
- [ ] Support for model loading
- [ ] Implement a scene graph
- [ ] Add material system
- [ ] Implement shadow mapping

## License

This project is open-source, feel free to use it as you wish.