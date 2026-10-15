# KERNEL MONITOR

## Operating Systems and Systems Programming

### Project Report

**Course:** 25CS2104E  
**Term:** 2026–27 Term-I  
**Section:** 11  
**Team:** 5  

### Team Members

| Student ID | Name |
|---|---|
| 2520090094 | Chaitanya |
| 2520090182 | Bhardwaj |
| 2520089070 | Salman |

---

## 1. Abstract

Kernel Monitor is a Linux-based system programming project developed to monitor
and display important operating system and running-process information.

The system collects information such as CPU utilization, memory usage,
system uptime, process IDs, process states, process memory usage, and process
names. The information is obtained from Linux system interfaces, especially
the `/proc` filesystem.

The monitor periodically refreshes the displayed information so that the user
can observe the current system state.

---

## 2. Problem Statement

Operating system information such as CPU usage, memory usage, uptime, and
running processes is maintained by the Linux kernel. A user-space program can
access this information using system calls and Linux interfaces such as the
`/proc` filesystem.

The objective of this project is to develop a simple Linux-based Kernel
Monitor that collects and displays this information in a readable format.

---

## 3. Objectives

The main objectives of the project are:

- Monitor CPU utilization.
- Monitor memory usage.
- Display total, available, and free memory.
- Display system uptime.
- Display running process information.
- Display process IDs (PIDs).
- Display process states.
- Display process memory usage.
- Display process names.
- Understand Linux `/proc` filesystem interfaces.
- Understand Linux system programming and process management.
- Refresh system information periodically.

---

## 4. Technologies Used

- Operating System: Linux / Ubuntu
- Programming Language: C
- Compiler: GCC
- Build Tool: Make
- System Interface: `/proc`
- Version Control: Git
- Repository: GitHub

---

## 5. System Architecture

The Kernel Monitor follows the following workflow:

1. Start the Kernel Monitor.
2. Collect system information.
3. Read process information from `/proc`.
4. Calculate resource usage.
5. Display the collected information.
6. Refresh the information periodically.
7. Continue monitoring until the user exits.

---

## 6. Linux `/proc` Interfaces Used

The project uses Linux `/proc` interfaces to obtain system information.

### `/proc/stat`

Used to obtain CPU-related information.

### `/proc/meminfo`

Used to obtain memory information such as:

- Total memory
- Available memory
- Free memory

### `/proc/uptime`

Used to obtain system uptime.

### `/proc/[PID]/stat`

Used to obtain information related to individual processes.

### `/proc/[PID]/status`

Used to obtain process information including memory-related details.

---

## 7. Features

The Kernel Monitor provides the following features:

### System Information

- System uptime
- Total memory
- Available memory
- Free memory
- Memory utilization

### CPU Information

- CPU utilization

### Process Information

- Process ID
- Process state
- Process memory usage
- Process name

### Monitoring

- Automatic refresh every 2 seconds
- Continuous monitoring
- CTRL+C to exit

---

## 8. Project Structure

```text
Kernel-Monitor/
│
├── kernel_monitor.c
├── Makefile
├── README.md
├── docs/
│   ├── PROJECT_REPORT.md
│   ├── SAMPLE_OUTPUT.txt
│   └── OSSP ABSTARCT.docx.pdf
│
└── screenshots/
