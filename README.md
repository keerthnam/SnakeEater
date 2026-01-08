Object-Oriented Snake Game (C++)

Project Overview

This project is a fully object-oriented implementation of the classic Snake game, developed in C++ as part of COMPENG 2SH4 – Software Design at McMaster University. The primary goal of the project was to refactor prior procedural implementations into a clean, modular, and extensible object-oriented design using industry-standard software engineering practices. An effective analogy for the design is LEGO construction, where small and well-defined blocks such as objPos are combined into larger and more powerful structures like objPosArrayList, which are then composed into higher-level systems including the Snake player and overall game mechanics. This bottom-up approach enabled scalability, maintainability, and a clear separation of responsibilities.

Key Features

The game implements classic Snake gameplay with real-time keyboard input, wraparound movement at the boundaries of the game board, dynamic snake body growth, a scoring system tied to food consumption, collision detection for both food and self-collision, and a complete game-over mechanism with custom exit messages. The final implementation is fully compilable and memory-safe, with careful attention paid to dynamic memory management.

Object-Oriented Design

The project strictly follows object-oriented design principles and emphasizes encapsulation, composition, and modularity. The objPos class encapsulates a single game-board position defined by x and y coordinates along with its ASCII symbol, and it implements proper copy control using the Rule of Four or Rule of Six to safely manage heap-allocated memory. The objPosArrayList class is a custom dynamic array list designed to store ordered collections of objPos objects and is primarily used to track the snake body while supporting efficient head and tail insertion and removal operations. The Player class represents the Snake itself and uses composition to own an objPosArrayList that stores body segments, while also implementing a finite state machine for direction control and movement logic. The GameMechs class serves as a container for core game mechanics, including board dimensions, input handling, score tracking, and game termination flags. Depending on design choice, a Food class may be used to manage random food generation while preventing overlap with the snake body.

Snake Movement Algorithm

Snake movement is implemented using a list-based algorithm in which a new head segment is inserted at the next calculated position and the tail segment is removed to simulate forward movement. When food is consumed, the tail removal step is intentionally skipped, allowing the snake to grow by one segment. This strategy simplifies movement logic while maintaining visual correctness and efficient performance.

Collaboration and Development Process

This project was completed as a two-person collaborative effort using a parallel development workflow. System architecture and object interactions were jointly planned using UML diagrams, after which implementation responsibilities were divided across core modules such as player logic, data structures, and game mechanics. Frequent communication, code reviews, and debugging sessions were used to ensure consistent design decisions and correct integration of independently developed components. Version control was managed using GitHub Classroom, with careful handling of merges and conflict resolution. The development process followed incremental engineering practices, validating each feature thoroughly before introducing additional functionality.

Technologies and Tools

The project was developed in C++ using an object-oriented programming paradigm. Git and GitHub Classroom were used for version control and collaboration, and the overall development approach emphasized incremental implementation, UML-based design, and peer code review.

How to Build and Run

To build and run the project, the repository should be cloned from GitHub Classroom and verified to contain all required source and header files. The project can then be compiled using the provided Makefile or a standard C++ compiler and executed in a terminal that supports ASCII rendering. The project must compile without errors in order to be evaluated.

Learning Outcomes

Through this project, object-oriented design principles were applied to a non-trivial software system, providing hands-on experience with dynamic memory management and copy control in C++. The project also strengthened collaboration, communication, and version control skills, while reinforcing best practices for writing scalable, maintainable, and extensible code suitable for future feature expansion.

Future Improvements

Potential future improvements include supporting multiple food items with special effects, enhancing the scoring system, improving underlying data structures for performance optimization, and extending the project to incorporate more advanced algorithms in subsequent courses such as COMPENG 2SI3.

Authors

Keerthna Manivasagam, Computer Engineering, McMaster University. The project was completed in collaboration with peer developer Bethany Lum (Computer Engineering, McMaster University), as part of COMPENG 2SH4.
