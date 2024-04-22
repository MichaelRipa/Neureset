# Neureset

# Neureset Project

Neureset is a software simulation of a hypothetical consumer EEG direct neurofeedback device, designed to demonstrate the capabilities of the system through a comprehensive set of UML diagrams, use case and sequence diagrams, and an implementation in Qt.

## Project Structure

This repository includes the following key components:

- `Design-Decisions.pdf`: Document outlining the design decisions made during the project development.
- `Traceability Matrix.pdf`: A detailed traceability matrix linking requirements to their implementation.
- `neureset-demo.mp4`: A video demonstration of the project in action.
- `UML/`: Directory containing UML diagrams.
- `QtProject/`: Contains the source code organized into forms, headers, and source files.
- `UseCase-Diagram_Neureset.png` and `UseCase_Diagram-Neureset.png`: Diagrams illustrating the use cases of the project.
- `Use-cases-and sequence-diagrams.pdf`: Document detailing the use cases and sequence diagrams for the project.

### Detailed File Structure

- **QtProject**
  - `forms/`: UI forms designed with Qt Designer.
    - `main-window.ui`: Main window form of the application.
  - `headers/`: Header files for all classes used in the project.
  - `src/`: Source files for the corresponding headers.
- **UML**
  - `Class-Diagram.png`: The class diagram of the entire project.
  - `UML_Neureset-State_Diagrams.pdf`: State diagrams included in the UML documentation.

## Installation

To run the Neureset project, ensure you have Qt installed and configured properly:

1. Clone the repository:
2. Navigate to the `QtProject` directory:
`cd QtProject` 
3. Open the `Neuroset.pro` file in Qt Creator.
4. Configure the project with the appropriate Qt kit.
5. Build and run the project.

## Usage

After launching the Neureset application, you can interact with the UI to simulate different neurofeedback sessions. Use the controls provided in the main window to start sessions, adjust settings, and view outputs.

## Contributing

Contributions to the Neureset project are welcome. Please read the contributing guidelines before submitting your pull requests. To contribute:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -am 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## License

This project is licensed under the MIT License
