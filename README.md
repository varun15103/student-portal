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

## Run

After a successful build, start the portal:

```bash
./build/student_portal