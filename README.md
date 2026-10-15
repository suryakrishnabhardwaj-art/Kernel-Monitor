# KERNEL MONITOR

## Linux-Based System Monitoring Tool

### Course
25CS2104E – Operating Systems and Systems Programming

### Section
11

### Team
Team 5

---

## 👥 Team Members

| Student ID | Name |
|---|---|
| 2520090094 | Chaitanya |
| 2520090182 | Bhardwaj |
| 2520089070 | Salman |

---

## 📌 Project Overview

Kernel Monitor is a Linux-based system monitoring tool developed in C.

The project collects and displays important operating system information using Linux system interfaces, especially the `/proc` filesystem.

The monitor provides information about:

- CPU usage
- Memory usage
- Total and available memory
- System uptime
- Running processes
- Process IDs (PID)
- Process states
- Process memory usage
- Process names

The information is refreshed periodically so that the user can observe the current system state.

---

## 🎯 Objectives

The main objectives of the Kernel Monitor are:

1. Monitor CPU utilization.
2. Monitor system memory usage.
3. Display system uptime.
4. Monitor running processes.
5. Display process IDs and states.
6. Display process memory usage.
7. Understand Linux `/proc` filesystem.
8. Understand Linux system programming and OS concepts.
9. Demonstrate process and resource monitoring using C.

---

## ✨ Features

### System Information

The program displays:

- System uptime
- Total memory
- Available memory
- Free memory
- Memory utilization percentage
- CPU utilization percentage

### Process Information

For running processes, the monitor displays:

- PID
- Process state
- Memory usage
- Process name

### Automatic Refresh

The monitor automatically refreshes every 2 seconds.

Press:

```text
CTRL + C
