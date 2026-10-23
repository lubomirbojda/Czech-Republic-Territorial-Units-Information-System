# Czech Republic Territorial Units Information System

[![C++17](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)](https://visualstudio.microsoft.com/)
[![Course](https://img.shields.io/badge/Course-Algorithms%20%26%20Data%20Structures-orange.svg)](https://fri.uniza.sk)

High-performance C++ console application and custom data structures library designed to parse, index, search, and navigate territorial administrative units of the Czech Republic.

This project was developed as a university semester project for the **Algorithms and Data Structures 1 (AUS 1)** course at the Faculty of Management Science and Informatics, University of Žilina (**FRI UNIZA**).

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Data Structures & Algorithmic Design](#data-structures--algorithmic-design)
- [Installation & How to Run](#installation--how-to-run)
- [CLI Controls & Usage](#cli-controls--usage)
- [Documentation](#documentation)
- [Screenshots](#screenshots)

---

## Overview

The application processes complex real-world demographic and geographical data of the Czech Republic from `CR.csv`. The administrative structure is modeled hierarchically:

Czech Republic (Root) &rarr; Regions (Kraje) &rarr; Administrative Districts (SO ORP) &rarr; Municipalities (Obce)

By combining tree hierarchies, hash tables with collision chaining, and heap sorting with custom predicates, the system provides instantaneous queries, multi-level hierarchy navigation, and flexible filtering criteria.

---

## Key Features

- **Multi-Level Tree Traversal:** Move interactively between administrative tiers (Country &rarr; Region &rarr; District &rarr; Municipality) with parent and child node transitions.
- **$O(1)$ Average Lookup via Hash Tables:** Direct query by unit name and type (`kraj`, `soorp`, `obec`). Duplicate names across different districts are resolved using singly linked lists at each hash bucket.
- **Predicate-Based Filtering:** Generic filter template supporting substring searches (`contains`) and prefix searches (`starts with`) with case-insensitive Czech collation.
- **HeapSort with Custom Comparators:** Sort queried units in-place using:
  - **Alphabetical order** (via Czech locale collation `std::collate<char>`).
  - **Consonant frequency** (counting consonants while correctly handling the Czech/Slovak digraph `ch` as a single consonant).
- **Detailed Municipal Demographics:** For every municipality (`Obec`), the system tracks:
  - Official territorial code & cadastral area
  - Total population and age demographics
  - Infrastructure indicators (public water supply, natural gas network, sewage system, wastewater treatment plant / ČOV)
- **Zero Memory Leaks:** Thorough dynamic allocation management verified using `HeapMonitor`.

---

## Data Structures & Algorithmic Design

| Component | Underlying Data Structure / Algorithm | Complexity | Purpose in Application |
| :--- | :--- | :--- | :--- |
| **Territorial Hierarchy** | `ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>` | Traversal: $O(V)$ | Models arbitrary $N$-ary parent-child relationships between CR, Kraje, SO ORP, and Obce. |
| **Direct Entity Lookup** | `ds::adt::HashTable<std::string, ListUJ>` | Average: $O(1)$, Worst: $O(n)$ | Fast indexing of units by normalized lowercase name. |
| **Collision / Duplicate Handling** | `ds::adt::SinglyLinkedList<T*>` | Insertion: $O(1)$ | Stores homonymous municipalities (units sharing the same name in different regions). |
| **Query Result Cache** | `ds::amt::ImplicitSequence<UzemnaJednotka*>` | Access: $O(1)$ | Holds filtered territorial units ready for display or sorting. |
| **Sorting Engine** | `ds::adt::HeapSort<UzemnaJednotka*>` | Time: $O(n \log n)$, Space: $O(1)$ | In-place sorting using custom lambda comparators (alphabetical & consonant count). |
| **Tree Traversal** | `PreOrderHierarchyIterator` | $O(V + E)$ | Systematic depth-first traversal across all subordinate units under an active node. |

---

## Installation & How to Run

### Prerequisites

- **Operating System:** Windows 10 / 11
- **IDE:** [Visual Studio 2022](https://visualstudio.microsoft.com/) (Community, Professional, or Enterprise)
- **Workload:** *Desktop development with C++* (including MSVC v143 toolset and C++17 support)

### Steps

1. **Clone the repository:**
   ```bash
   git clone https://github.com/lubomirbojda/Czech-Republic-Territorial-Units-Information-System
   cd Czech-Republic-Territorial-Units-Information-System
   ```

2. **Open the solution:**
   - Double-click `DataStructures.sln` to open the project in Visual Studio.

3. **Set the Startup Project:**
   - In the **Solution Explorer**, right-click the `SemestralnaPraca` project and select **Set as Startup Project**.

4. **Select Target Configuration:**
   - Platform: `x64`
   - Configuration: `Debug` or `Release`

5. **Build & Run:**
   - Press `F5` (Start Debugging) or `Ctrl + F5` (Start Without Debugging).
   - Ensure `CR.csv` is located in the working directory (default project path `SemestralnaPraca/CR.csv`).

---

## CLI Controls & Usage

When the program launches, an interactive menu is displayed in the console:

```plaintext
Prehľadávať ČR [1]
Nájsť informácie o ÚJ s daným typom a názvom (tabuľky) [2]
Uroven 1 [3]
Ukončiť aplikáciu [4]
```

### 1. Hierarchical Navigation (`[1] Prehľadávať ČR`)
- Start at the root level (`Česká Republika`).
- Select a region (`Kraj`) to inspect its districts (`SO ORP`), and then select a district to inspect its municipalities (`Obce`).
- Available operations at each level:
  - **Select a subordinate unit** (drills down into the next hierarchy level).
  - **Navigate back to the parent unit** (`accessParent`).
  - **Filter subordinate units** containing or starting with specified text.
  - **Filter subordinate units by type** (`kraj`, `soorp`, `obec`).
  - **Sort results:**
    - `[1]` Default traversal order.
    - `[2]` Alphabetical sort using locale collation.
    - `[3]` Consonant frequency sort (shows count in brackets `[#]`).

### 2. Direct Hash Table Search (`[2] Nájsť informácie o ÚJ`)
- Instant $O(1)$ search across pre-indexed hash tables:
  1. Enter unit type: `kraj`, `soorp`, or `obec`.
  2. Enter the unit's name (case-insensitive).
- Example output for a municipality (`obec Praha`):
  ```plaintext
  PRAHA:
      kód: 554782
      katastrálna výmera: 49621
      počet obyvateľov: 1357326
      vodovod: Áno
      plyn: Áno
      kanalizácia: Áno
      kanalizácia(ČOV): Áno
  ```

### 3. Global Filter (`[3] Uroven 1`)
- Run queries across the entire national dataset for a chosen category (`Kraje`, `Soorpy`, or `Obce`) matching:
  - `[1]` Contains substring
  - `[2]` Starts with prefix

### 4. Exit (`[4] Ukončiť aplikáciu`)
- Cleanly deallocates all allocated tree nodes, hash table records, and lists.
- Displays `HeapMonitor` memory diagnostic report confirming no memory leaks.

---

## Documentation

The project includes complete technical and academic documentation:

- **[Project Documentation (PDF)](https://github.com/lubomirbojda/AUS-SEM/blob/main/Bojda%C4%BDubom%C3%ADrAUS1.pdf)**
  - UML class diagrams and algorithm activity diagrams
  - Choice rationale for data structures (explicit hierarchy vs. implicit, hash table vs. sequence)
  - Time complexity benchmark analysis ($O(1)$ insert, empirical find measurements)
  - User and programmer guides

> **Note:** Code comments, console UI text, and the accompanying PDF documentation are written in the **Slovak language**.

---

## Screenshots

<!-- You can replace the image placeholder below with a screenshot of the running CLI or visual test runner -->

<p align="center">
  <img width="742" height="121" alt="image" src="https://github.com/user-attachments/assets/59e433b3-c79e-4656-8774-ff3d75522337" />
  <img width="912" height="625" alt="image" src="https://github.com/user-attachments/assets/309c36f1-6a6a-4d4a-b9fc-06b382c6544b" />

</p>
```

