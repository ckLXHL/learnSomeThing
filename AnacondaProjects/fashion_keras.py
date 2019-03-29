#%% [markdown]
# <a href="https://colab.research.google.com/github/ckLXHL/learnSomeThing/blob/master/my_keras.ipynb" target="_parent"><img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/></a>

import matplotlib.pyplot as plt
import numpy as np
#%%
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import models
from timeit import timeit

keras.models.Sequential

print(tf.VERSION)
print(tf.keras.__version__)


#%%
fashion_mnist = keras.datasets.fashion_mnist

#加载数据集
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()


#%%
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

print(train_images.shape, test_images.shape, train_labels.shape)

#%%

from sklearn.linear_model import LinearRegression

model = LinearRegression()
