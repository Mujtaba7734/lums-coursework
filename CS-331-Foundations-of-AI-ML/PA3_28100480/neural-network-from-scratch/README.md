# Neural Network MNIST Classifier

This project implements a neural network for handwritten digit classification
using the MNIST dataset as part of the **CS-331 Foundations of AI & Machine Learning**
course at LUMS.

## Overview

The assignment explores both low-level neural network implementation
and modern deep learning frameworks.

The project includes:

• A neural network forward pass implemented **from scratch using NumPy**  
• Implementation of **backpropagation** to compute gradients  
• A **PyTorch-based fully connected neural network**  
• Training and evaluation on the MNIST dataset  
• Hyperparameter tuning and model selection  
• Performance evaluation using multiple metrics

## Neural Network Architecture

Input Layer:
- 784 features (28×28 MNIST image)

Hidden Layers:
- 256 units (ReLU)
- 128 units (ReLU)

Output Layer:
- 10 units (Softmax)

## Features Implemented

### From Scratch (NumPy)

- He weight initialization
- ReLU activation
- Softmax activation
- Forward propagation
- Backpropagation

### PyTorch Implementation

- Fully connected neural network
- Cross-entropy loss
- Adam optimizer
- Training loop
- Validation monitoring
- Best model checkpointing

### Evaluation

The model is evaluated using:

- Accuracy
- F1 Score
- Recall
- Confusion Matrix
- Classification Report
- Error visualization

The trained model achieves **>95% accuracy on the MNIST test dataset**.

### Additional Experiment

An **Out-of-Distribution (OOD) test** was performed using a handwritten digit image
to evaluate how the model performs on real-world inputs.

## Technologies Used

- Python
- NumPy
- PyTorch
- Scikit-learn
- Matplotlib
- Seaborn
- Jupyter Notebook

## Dataset

MNIST Handwritten Digits Dataset  
28×28 grayscale images of digits (0–9)

Train set: 60,000 images  
Test set: 10,000 images

## Author

Muhammad Mujtaba  
LUMS – Computer Science