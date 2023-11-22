# CG4002-capstone - Hardware AI 

The aim of this project was to create an Augmented Reality Laser Tag Game. Each player gets a gun, vest and glove. On the glove there are 2 sensors, an Accelerometer and a Gyroscope. Using the sensors on the glove, the aim is to detect one of 9 possible moves that the player can do. \
<img src="https://github.com/prachi2023/CG4002-capstone/assets/60388723/889f4455-bf37-4221-a725-eb19b15d566a" alt="Capstone Hardware" width="300">

\
*Steps* 
1. Determining the window size for collection of data based on average action length 
2. Collecting Data
3. Cleaning Data
4. Pre-processing the data: Fast Fourier Transform and Normalisation
5. Train the CNN
6. Tuning Hyperparameters: Number of Layers, Nodes, Features to use, Window Size, Batch Size


*Implementation*
To increase the speed and efficiency. The model is implemented on an Ultra96 FPGA. The model is written in C++ and using Vitis HLS, we extract the IP layer. 

Through Vivado we created the following block diagram and generated the final bitstream.\
![final block design](https://github.com/prachi2023/CG4002-capstone/assets/60388723/96da140d-c8cb-4495-b45b-2d5682e97f9d)


Using the PYNQ overlay we are able to overlay the bitstream on the ultra96
