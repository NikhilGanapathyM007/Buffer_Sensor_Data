# Buffer_Sensor_Data
This project is a Producer-Consumer simulation built with Qt. It demonstrates a multi-threaded approach to handling high-frequency sensor data, where data is periodically generated, stored in a database, and consumed in a FIFO manner.

**Key Features**

1. **Multi-threaded Design:** Uses QThread to separate data production and consumption tasks, ensuring that these operations do not block the main UI thread.

2. **Database Integration:** Stores sensor data (temperature and voltage) in a local SQLite database, simulating a real-time data buffer.

**Producer-Consumer Model:**

1. **Producer:** Generates sensor data and writes it to the database at fixed intervals.

2. **Consumer:** Reads and deletes the oldest data entry in the database, simulating consumption at a different interval.

3. **Mutex for Thread Safety:** Uses QMutex to ensure safe access to the database when multiple threads are reading/writing data.

4. **Real-time UI Updates:** Displays data written by the producer and read by the consumer in separate UI elements (txtBrowserProducer and txtBrowserConsumer), providing a real-time visual representation of the data flow.

**Technologies Used**
1. **Qt Framework:** Provides the UI, database access, multi-threading, and event-driven programming.
2. **SQLite:** Embedded database used to store sensor data, simulating a buffer for the producer-consumer operations.
3. **C++:** Core programming language for handling the data operations and UI functionality.

**How to Run the Project**
1. **Install Dependencies:** Ensure that you have Qt installed with Qt Creator or Qt libraries for building and running the project.
2. **Clone the Repository:**

```bash
git clone <repository_url>
cd <repository_directory>
```

3. **Build the Project:**
Open the project in Qt Creator.
Configure the project and run qmake if necessary.
Build and run the project.

**Use Cases**
1. **Data Buffer Simulation:** The project can be adapted to real-world scenarios where sensor data is generated at high frequencies, and only the latest data needs to be retained.
2. **Multithreading Practice:** Demonstrates handling concurrent data processing in a GUI application.
3. **Database Operations:** Useful for learning basic SQLite operations (inserting, reading, deleting) in a C++ application.

