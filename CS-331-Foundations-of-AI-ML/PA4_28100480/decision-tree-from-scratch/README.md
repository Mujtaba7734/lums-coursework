# Decision Tree Classifier (From Scratch)

This project implements a binary decision tree classifier from scratch
and applies it to the Titanic survival prediction problem.

The assignment was completed as part of the **CS-331 Foundations of AI & Machine Learning**
course at LUMS.

## Overview

The goal of the project is to understand how decision trees work internally
by implementing the algorithm manually instead of using pre-built libraries.

The model predicts whether a passenger survived the Titanic disaster based on
demographic and ticket information.

## Dataset

Titanic dataset (loaded from Seaborn)

Target:
- `survived` (1 = survived, 0 = did not survive)

Key features used:
- passenger class
- sex
- age
- fare
- number of siblings/spouses
- number of parents/children
- embarkation port

## Implementation

The decision tree was implemented completely from scratch using Python and NumPy.

Key components include:

- entropy calculation
- information gain
- binary feature splitting
- recursive tree construction
- prediction traversal

Stopping conditions:

- maximum depth reached
- minimum samples threshold
- pure node
- no information gain

## Model Evaluation

The model was evaluated using:

- accuracy
- precision
- recall
- F1 score
- confusion matrix

The experiment also explored the effect of **max tree depth** on model performance
to observe underfitting and overfitting behavior.

## Key Concepts Demonstrated

- Decision tree learning
- entropy and information gain
- feature splitting strategies
- overfitting vs underfitting
- model evaluation metrics

## Technologies Used

Python  
NumPy  
Pandas  
Matplotlib  
Seaborn  
Scikit-learn (for utilities and metrics)

## Author

Muhammad Mujtaba  
LUMS – Computer Science