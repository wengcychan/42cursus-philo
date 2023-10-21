<h1 align="center">42cursus - Philosophers</h1>

<p align="center">
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/wengcychan/42cursus-philo?style=plastic&color=blue&label=C%20language&logo=42"/>
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/wengcychan/42cursus-philo?style=plastic&color=green&logo=42"/>
</p>

The "Philosophers" project is designed to introduce the basics of threading a process.

For more projects related to 42cursus, please visit the [hive-42cursus](https://github.com/wengcychan/hive-42cursus.git) repository.

## Introduction

The main goal is to implement the "Dining Philosophers" problem by leveraging concurrent programming and managing multiple threads.

<img src="./images/philo.gif" alt="Philo Program" width="80%">

## Usage

To compile and use the Philosophers program, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/wengcychan/42cursus-philo.git
	```

2. Compile the program:

   ```bash
	make
	```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This will generate the executable file.

3. Run the program with the required arguments:

   ```bash
	./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Replace the placeholders with appropriate values.
