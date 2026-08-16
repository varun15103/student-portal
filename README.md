# Student Portal

A C++ command-line application for managing students, courses, and enrollments.

## Overview

Student Portal is a rewrite of a legacy student-management tool. It will store students and courses, handle enrollment, and expose a menu-driven CLI.

## Planned features

- Student and course registration
- Enrollment and course lists
- Login with session handling
- Student profiles and a dashboard
- User settings saved to a config file

## Prerequisites

- Git
- A C++17 compiler (g++ on MinGW, or MSVC)
- CMake 3.16 or newer

## Build

From the `student-portal` directory:

```bash
cmake -S . -B build
cmake --build build
```

## Run

After a successful build, start the portal:

```bash
./build/student_portal
```

## Project structure

```
student-portal/
  CMakeLists.txt
  README.md
  include/          # public headers
  src/              # Student, Course, portal, CLI
  data/             # saved students, courses, settings
```

Headers will live under `include/` and sources under `src/` after the first code layout pass.

## Data files and extending the portal

Saved records will go under `data/` (students, courses, enrollments, settings). The portal can print an enrollment report from the dashboard and export those files for backup. Do not commit generated `build/` output; it is ignored.

To add a feature, create a branch, add sources under `src/` and headers under `include/`, then merge back to `main`.

