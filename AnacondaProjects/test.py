#%% [markdown]
# 你好
#%%
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

x = np.linspace(0, 20, 100)
plt.plot(x, np.sin(x))
plt.show()

#%%
print("this is my log")

#%% 
import torch
import tensorflow as tf
import tensorflow.keras 