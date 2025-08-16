import enum
import matplotlib.pyplot as plt
import numpy as np
import functools
import itertools
import copy
import os
import pandas as pd
import sys

x = np.linspace(0, 2 * np.pi, 200)
y = np.sin(x)

fig, axis = plt.subplots()
axis.plot(x, y)
plt.show()

plt.boxplot(x)
plt.show()

